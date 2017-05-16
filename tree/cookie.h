/*************************************************************************
    > File Name: cookie.h
    > Author: Jinrui 
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: Fri May 12 23:49:59 2017
 ************************************************************************/

#include <stdint.h>
using namespace std;

#ifndef COOKIE_H
#define COOKIE_H 

#define MAX_SLICE_ID 0xFFFFFFFFFFFFFFFF
#define EXPAND_THRESHOLD 5 
#define SHRINK_THRESHOLD 2 

#define TYPE_INSTANCE_NODE 0
#define TYPE_SLICE_NODE    1

#define INSTANCE_NUM 100

typedef struct Node 
{
    uint64_t      node_id;
    uint64_t      min;
    uint64_t      max;
    Node*         left;
    Node*         right;
    Node*         parent;
    int           count;
    int           type;
} Node; 



#endif
