#include <stdio.h>
#include <stdlib.h>

#define MAX_CDS 4
#define MAX_CITIES 6

typedef struct _cd
{
    int id;
    int fix_cost;
    int cap;
}CD;

typedef struct city
{
    int id;
    int demand;
}CITY;

typedef struct _sol
{
    CD* used_cds[MAX_CDS];
    CITY* served_cities[MAX_CITIES];
    int total_cost;
}SOLUTION;


int main()
{
    CD* cds[MAX_CDS];

    cds[0]->fix_cost = 1000;
    cds[0]->cap = 50;

    cds[1]->fix_cost = 1200;
    cds[1]->cap = 50;

    cds[2]->fix_cost = 800;
    cds[2]->cap = 50;

    cds[3]->fix_cost = 1500;
    cds[3]->cap = 50;
    
    for(int i = 0; i < MAX_CDS; i++)
    {cds[i]->id = i+1;}

    CITY* cities[6];

    cities[0]->demand = 10;
    cities[1]->demand = 15;
    cities[2]->demand = 12;
    cities[3]->demand = 18;
    cities[4]->demand = 8;
    cities[5]->demand = 20;

    int total_demand = 0;
    for(int i = 0; i < MAX_CITIES; i++)
    {
        total_demand = total_demand + cities[i]->demand;
        cities[i]->id = i+1;
    }

    int costs[MAX_CDS][MAX_CITIES] = {
        {50, 80, 100, 90, 120, 40},
        {70, 60, 50, 110, 90, 80},
        {20, 100, 90, 60, 10, 30},
        {110, 40, 60, 50, 70, 90},    
    };
}