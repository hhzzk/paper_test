/*************************************************************************
    > File Name: main.cpp
    > Author: Jinrui 
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: Sat May 13 07:47:54 2017
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <unistd.h>
#include <pthread.h>

#include "cookie.h"
#include "cookies.h"

using namespace std;

Node* g_node_root = NULL;
vector<Node *> instance_set;
// true means available, false means in used
bool instance_pool[INSTANCE_NUM];
pthread_mutex_t mutex0 = PTHREAD_MUTEX_INITIALIZER;

Node* create_node(uint64_t node_id, uint64_t min, uint64_t max)
{
    
    Node* node  = NULL;

    node = (Node*)malloc(sizeof(Node));
    if(!node)
    {
        return NULL;
    }

    memset(node, 0x0, sizeof(Node));

    node -> node_id = node_id;
    node -> min = min;
    node -> max = max;
    node -> type = TYPE_INSTANCE_NODE;
    instance_pool[node_id] = false;

    return node;
}

void 
init_scheduling_tree(uint64_t instance_id, uint64_t slice_id)
{
    if(g_node_root)
    {
        g_node_root = NULL;
    }

    g_node_root = create_node(instance_id, slice_id, slice_id);
    if(g_node_root)
    {
        //store instance to instance_set
        instance_set.push_back(g_node_root);
    }
    
    return;
}

Node* search_instance(uint64_t slice_id)
{
    Node* node = g_node_root;

    if(!node)
    {
        init_scheduling_tree(0, slice_id);
        g_node_root->count++;
        return g_node_root;
    }

    while(node->type == TYPE_SLICE_NODE)
    {
        if(slice_id < node->node_id)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
        //return NULL;
    }

    node->count++;
    if(slice_id < node->min)
    {
        node->min = slice_id;
    }
    if(slice_id > node->max)
    {
        node->max = slice_id;
    }
    return node;
}

// expand instance node
void expand_node(
        Node* node, 
        uint64_t instance_id_new
)
{
    Node* left;
    Node* right;

    if(node->type != TYPE_INSTANCE_NODE)
        return;

    uint64_t instance_id_left = node->node_id;
    Node* parent = node->parent;
    uint64_t min = node->min;
    uint64_t max = node->max;
    uint64_t mid = min/2 + max/2;

    left = create_node(instance_id_left,min, mid);
    right = create_node(instance_id_new, mid, max);
    if(!left || !right)
        return;

    node->left = left;
    node->right = right;
    node->left->parent = node;
    node->right->parent = node;
    node->node_id = mid;
    node->type = TYPE_SLICE_NODE;

    //delete instance from instance set
    instance_set.erase(
            remove(
                instance_set.begin(), 
                instance_set.end(), 
                node
            ), 
            instance_set.end()
        );
    //add new instance to instance set
    instance_set.push_back(node->left);
    instance_set.push_back(node->right);
}

void print_tree(Node* node)
{
    if(!node)
        return;

    if(node->type == TYPE_INSTANCE_NODE)
        printf("(%llu, %d)\n", node->node_id, node->type);
    else
    {
        printf("(%llu, %llu, %llu, %d)\n", node->node_id, node->left->node_id, node->right->node_id, node->type);
        print_tree(node->left);
        print_tree(node->right);
    }
}

void shrink_node(Node* slice_node)
{
    if(slice_node->type == TYPE_INSTANCE_NODE)
        return;

    //two instance children
    if(slice_node->left->type == TYPE_INSTANCE_NODE &&
       slice_node->right->type == TYPE_INSTANCE_NODE)
    {
        printf("Two instance children\n");
        slice_node->node_id = slice_node->left->node_id;
        slice_node->count = 0;
        slice_node->min = slice_node->left->min;
        slice_node->max = slice_node->right->max;
        slice_node->type = TYPE_INSTANCE_NODE;

        //delete right child 
        instance_pool[slice_node->right->node_id] = true;

        //delete instance from instance set
        instance_set.erase(
            remove(
                instance_set.begin(), 
                instance_set.end(), 
                slice_node->left
            ), 
            instance_set.end()
        );
        instance_set.erase(
            remove(
                instance_set.begin(), 
                instance_set.end(), 
                slice_node->right
            ), 
            instance_set.end()
        );
        free(slice_node->left);
        slice_node->left = NULL;
        free(slice_node->right);
        slice_node->right = NULL;

        instance_set.push_back(slice_node);
    }
    //only one instance child
    // left child is instance
    else if(slice_node->left->type == TYPE_INSTANCE_NODE &&
            slice_node->right->type == TYPE_SLICE_NODE)
    {
            printf("Left child is instance\n");
            if(slice_node == g_node_root)
            {
                printf("Is root node\n");
                g_node_root = slice_node->right; 
                slice_node->right->parent = NULL;
            }
            else
            {
                if(slice_node->parent->left == slice_node)
                {
                    printf("Slice is left node\n");
                    slice_node->parent->left = slice_node->right;
                }
                else if(slice_node->parent->right == slice_node)
                {
                    printf("Slice is right node\n");
                    slice_node->parent->right = slice_node->right;
                }
                slice_node->right->parent = slice_node->parent;
            }
            instance_set.erase(
                remove(
                    instance_set.begin(), 
                    instance_set.end(), 
                    slice_node->left
            ), 
                instance_set.end()
            );

            //free instance node
            instance_pool[slice_node->left->node_id] = true;
            free(slice_node->left);
            slice_node->left = NULL;
            //free this slice node
            free(slice_node);
            slice_node = NULL;
    }
        //right child is instance
    else if(slice_node->right->type == TYPE_INSTANCE_NODE &&
            slice_node->left->type == TYPE_SLICE_NODE)
    {
            printf("Right child is instance\n");
            if(slice_node == g_node_root)
            {
                printf("Is root node\n");
                g_node_root = slice_node->left; 
                slice_node->left->parent = NULL;
            }
            else
            {
                if(slice_node->parent->left == slice_node)
                {
                    printf("Slice is left child\n");
                    slice_node->parent->left = slice_node->left;
                }
                else if(slice_node->parent->right == slice_node)
                {
                    printf("Slice is right child\n");
                    slice_node->parent->right = slice_node->left;
                }
                slice_node->left->parent = slice_node->parent;
            }
            instance_set.erase(
                remove(
                    instance_set.begin(), 
                    instance_set.end(), 
                    slice_node->right
            ), 
                instance_set.end()
            );

            //free instance node
            instance_pool[slice_node->right->node_id] = true;
            free(slice_node->right);
            slice_node->right = NULL;    
            //free this slice node
            free(slice_node);
            slice_node = NULL;
    }

    return;
}

void* monitor_scheduling_tree(void*)
{
    int orig_size = 0;
    Node* instance = NULL;
    int i = 0;
    int j = 0;
    vector<Node*> orig;
    uint64_t new_instance = 0;

    
    while(1)
    {   
        sleep(1);

        print_tree(g_node_root);
        orig = instance_set;//original instance set
        orig_size = orig.size();
        
        printf("instance set size=%d\n", orig_size);

        pthread_mutex_lock (&mutex0);
        for(i=0; i<orig_size; i++)
        {
            instance = orig[i];
            // wether instance still exists
            if(find(instance_set.begin(), instance_set.end(),instance)!=instance_set.end() ) 
            {
                printf("instance id=%llu, instance count=%d\n",instance->node_id, instance->count);
                if(instance->count > EXPAND_THRESHOLD)
                {
                    for(j=0; j<INSTANCE_NUM; j++)
                    {
                        if(instance_pool[j])
                        {
                            new_instance = j;
                            break;
                        }
                    }
                    printf("expand %llu\n", new_instance);
                    expand_node(instance, new_instance);    
                }
                else if(instance->count < SHRINK_THRESHOLD)
                {
                    printf("shrink\n");
                    if (instance == g_node_root)
                        continue;
                    shrink_node(instance->parent);    
                }
                else
                {
                    instance->count = 0; 
                }
            }

        }
        pthread_mutex_unlock(&mutex0);
    }

    return NULL;
}

uint64_t gen_random_number()
{
    /* Seed */
    std::random_device rd;

    /* Random number generator */
    std::default_random_engine generator(rd());

    /* Distribution on which to apply the generator */
    std::uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);

    return distribution(generator);
}

int main()
{
    Node* instance = NULL;
    uint64_t slice_id = 0;
    pthread_t monitor;

    memset(instance_pool, true, sizeof(instance_pool));

    pthread_create(&monitor, NULL, monitor_scheduling_tree, NULL);

    for (int i = 0; i < (sizeof(g_slice_id)/sizeof(*g_slice_id)); ++ i)
    {
        usleep(5000);
      //usleep(1000000); 1s
//        sleep(1);
        //slice_id = gen_random_number();
        //slice_id = random()%1000;
        slice_id = g_slice_id[i];
        pthread_mutex_lock (&mutex0);

        instance = search_instance(slice_id); 

        pthread_mutex_unlock (&mutex0);
        
        if(instance)
        {
            printf("Slice= %llu, Instance id = %llu, count = %d, min = %llu, max = %llu\n",slice_id, instance->node_id, instance->count,instance->min,instance->max);
        printf("instance number = %lu\n", instance_set.size());
        }
    }

    //pthread_exit(NULL);
}
