/*************************************************************************
    > File Name: main.cpp
    > Author: Jinrui 
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: Sat May 13 07:47:54 2017
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <random>
#include <unistd.h>
#include <pthread.h>

#include "cookies.h"
#include "cookie.h"

using namespace std;

map<uint64_t, int> slice_instance_map;
map<int, int> instance_count_map;

pthread_mutex_t mutex0 = PTHREAD_MUTEX_INITIALIZER;

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

void expand_instance(int instance_id, int new_instance_id)
{
    int i = 0;    
    int count = 0;
    
    for(i=0,count=0; i<SLICE_TABLE_NUM; i++)
    {
        if(slice_instance_map[i] == instance_id)
        {
            count++;
            if(count%2 == 0)
                slice_instance_map[i] = new_instance_id;
        }
    }

    return;
}

void shrink_instance(int shrinked_instance_id, int instance_id)
{
    int i = 0;
    
    for(i=0; i<SLICE_TABLE_NUM; i++)
    {
        if(slice_instance_map[i] == shrinked_instance_id)
        {
            slice_instance_map[i] = instance_id;
        }
    }

    instance_count_map[shrinked_instance_id] = -1; 

    return;
}

void print_instance_count()
{
    int i = 0; 

    for(i=0; i<INSTANCE_NUM; i++)
    {
        printf("%4d ", i);
    }
    printf("\n");

    for(i=0; i<INSTANCE_NUM; i++)
    {
        printf("%4d ", instance_count_map[i]);
    }
    printf("\n");

    return;
}

void* monitor_table(void*)
{
    int i = 0;
    int j = 0;
    int min_count = 0;
    int shrink_instance_id = 0;

    while(1)
    {
        sleep(1);

        pthread_mutex_lock(&mutex0);

        print_instance_count();
        for(i=0; i<INSTANCE_NUM; i++)
        {
            if(instance_count_map[i] != -1)
            {
                if(instance_count_map[i] > EXPAND_THRESHOLD)
                {
                    for(j=0; j<INSTANCE_NUM; j++)
                    {
                        if(instance_count_map[j] == -1)
                            break;
                    }
                    if(j == INSTANCE_NUM)
                        continue;
                    expand_instance(i, j);
                }
                if(instance_count_map[i] <  SHRINK_THRESHOLD)
                {
                    for(j=0; j<INSTANCE_NUM; j++)
                    {
                        if(i != j &&
                           instance_count_map[j] != -1 &&
                           instance_count_map[j] < min_count)
                        {
                            shrink_instance_id = j;
                            min_count = instance_count_map[j];
                        }
                    }
                    shrink_instance(i, shrink_instance_id);
                }
            }
        }
        pthread_mutex_unlock (&mutex0);
    }
}

int search_instance(uint64_t slice)
{
    //slice not exist
    if(slice_instance_map.find( slice ) == slice_instance_map.end())
    {
        return -1;
    }
    else
    {
        if(instance_count_map[slice_instance_map[slice]] == -1)
            instance_count_map[slice_instance_map[slice]] = 1;
        else
            instance_count_map[slice_instance_map[slice]]++;

        return slice_instance_map[slice]; 
    }
}

int main()
{
    uint64_t slice_id = 0;
    int i = 0;
    int instance = 0;
    pthread_t monitor;

    pthread_create(&monitor, NULL, monitor_table, NULL);

    for(i=0; i<SLICE_TABLE_NUM; i++)
    {
        slice_instance_map[i] = 0; 
    }

    for(i=0; i<INSTANCE_NUM; i++)
    {
        instance_count_map[i] = -1; 
    }

    for (i = 0; i < (sizeof(g_slice_id)/sizeof(*g_slice_id)); ++ i)
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
        
        printf("slice = %llu, instance  = %d\n",slice_id, instance);
    }
}
