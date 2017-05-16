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

int add_slice(uint64_t slice)
{
    int min_count = 0;
    int instance = 0;
    int i = 0;

    for(i=0; i<INSTANCE_NUM; i++)
    {
        if(instance_count_map[i] == 0) 
        {
            instance = i;
            break;
        }
        else
        {
            if(instance_count_map[i] < min_count)
            {
                min_count = instance_count_map[i];
                instance = i;
            }
        }
    }

    slice_instance_map[slice] = instance;
    instance_count_map[instance]++;
    return instance;
}

int search_instance(uint64_t slice)
{
    //slice not exist
    if(slice_instance_map.find( slice ) == slice_instance_map.end())
    {
        return add_slice(slice);
    }
    else
    {
        instance_count_map[slice_instance_map[slice]]++;
        return slice_instance_map[slice]; 
    }
}

int main()
{
    uint64_t slice_id = 0;
    int i = 0;
    int instance = 0;

    for(i=0; i<INSTANCE_NUM; i++)
    {
        instance_count_map[i] = 0; 
    }

    for (i = 0; i < (sizeof(g_slice_id)/sizeof(*g_slice_id)); ++ i)
    {
        usleep(5000);
      //usleep(1000000); 1s
//        sleep(1);
        //slice_id = gen_random_number();
        //slice_id = random()%1000;
        slice_id = g_slice_id[i];

        instance = search_instance(slice_id); 

        
        printf("slice = %llu, instance  = %d\n",slice_id, instance);
    }

}
