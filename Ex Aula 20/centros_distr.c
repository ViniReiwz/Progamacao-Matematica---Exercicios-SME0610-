#include <stdio.h>
#include <stdlib.h>
#include "custom_types.h"


int main()
{
// Cria um vetor de centros de distribuição, atribuindo os respectivos valores --------------------------------
    CD cds[MAX_CDS];

    cds[0].fix_cost = 1000;
    cds[0].cap = 50;

    cds[1].fix_cost = 1200;
    cds[1].cap = 50;

    cds[2].fix_cost = 800;
    cds[2].cap = 50;

    cds[3].fix_cost = 1500;
    cds[3].cap = 50;
    
    for(int i = 0; i < MAX_CDS; i++)
    {cds[i].id = i+1;}
// ------------------------------------------------------------------------------------------------------------

// Cria as cidades do problema e atribui os valores necessários -----------------------------------------------
    CITY cities[6];

    cities[0].demand = 10;
    cities[1].demand = 15;
    cities[2].demand = 12;
    cities[3].demand = 18;
    cities[4].demand = 8;
    cities[5].demand = 20;

    int total_demand = 0;
    for(int i = 0; i < MAX_CITIES; i++)
    {
        total_demand = total_demand + cities[i].demand;
        cities[i].id = i+1;
    }
// ------------------------------------------------------------------------------------------------------------

// Criação da matriz de custos de distância ('distância' entre o CD_i e a cidade_j)
    int costs[MAX_CDS][MAX_CITIES] = {
        {50, 80, 100, 90, 120, 40},
        {70, 60, 50, 110, 90, 80},
        {20, 100, 90, 60, 10, 30},
        {110, 40, 60, 50, 70, 90},    
    };
// ------------------------------------------------------------------------------------------------------------
}