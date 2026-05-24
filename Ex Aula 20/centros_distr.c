#include <stdio.h>
#include <stdlib.h>
#include "custom_types.h"

/*
    Encontrando uma solução a partir de algoritmos gulosos.
    Esta função busca encontrar a melhor solução local, encontrando o CD mais barato de se construir para cada cidade, que consegue atender à sua demanda.
    params:
        CD* cds => Vetor do tipo CD, que representa os centros de distribuição disponíveis;
        CITY* cities => Vetor do tipo CITY, que representa as cidades à serem atendidas
        int** costs => Matriz de custos (CD_i para cidade_j)
    return:
        SOLUTION sol => Solução final utilizando os ótimos locais.

*/
SOLUTION greedy_optimize(CD* cds, CITY* cities, int costs[MAX_CDS][MAX_CITIES])
{
    SOLUTION sol;

    // Inicializa o custo total como 0
    sol.total_cost = 0;
    
    // Vetor auxiliar onde remaining_cap[i] recebe a capacidade do cd[i]
    // utilizado auxiliarmente para medir a capacidade restante de cada CD
    int remaining_cap[MAX_CDS];

    // Faz a atribuição supracitada
    for(int i = 0; i < MAX_CDS; i++)
    {
        remaining_cap[i] = cds[i].cap;
    }

    // Percorre todas as cidades
    for(int i = 0; i < MAX_CITIES; i++)
    {
        int best_cd_idx = -1;           // Variável auxiliar => Guarda o índice do melhor CD encontrado para a cidade atual
        int best_cost = __INT_MAX__;    // Variável auxiliar => Guarda o melhor custo local

        // Percorre todos os CDs
        for(int j = 0; j < MAX_CDS; j++)
        {
            // Verifica se há capacidade restante no CD
            if(remaining_cap[j] >= cities[i].demand)
            {
                // Taxa de logística entre cd_j e cidade_i + custo de construção do cd_j
                int curr_cost = costs[j][i] + cds[j].fix_cost;
                
                // Verifica o custo do CD 'j' ao atender a cidade 'i', atribuindo o melhor valor (minimizando)
                // ou seja, encontra o ótimo local para cada cidade.
                if(best_cost > curr_cost)
                {
                    best_cost = curr_cost; 
                    best_cd_idx = j;
                }
            }
        }

        // Se não encontrar nenhum, exibe esta mensagem
        if(best_cd_idx == -1){printf("Solução impossível\n"); exit(1);}

        // Faz a atribuição pelo CD que serve à cidade i
        sol.served_cities[i] = best_cd_idx;

        // Decrementa a capacidade do CD de acordo com a cidade que passou à servir
        remaining_cap[best_cd_idx] -= cities[i].demand;

        // Aumenta o custo total de acordo com a tabela de custos
        sol.total_cost += costs[best_cd_idx][i];

        // Caso ainda não tenha sido feito, atribui o CD como construindo e incrementa o custo fixo
        // de construção no custo total
        if(cds[best_cd_idx].builded == 0)
        {
            cds[best_cd_idx].builded = 1;
            sol.total_cost += cds[best_cd_idx].fix_cost;
        }

    }

    return sol;
}


int main()
{
// Cria um vetor de centros de distribuição, atribuindo os respectivos valores --------------------------------
    CD cds[MAX_CDS];

    cds[0].fix_cost = 1000;
    cds[0].cap = 50;

    cds[1].fix_cost = 1200;
    cds[1].cap = 60;

    cds[2].fix_cost = 800;
    cds[2].cap = 40;

    cds[3].fix_cost = 1500;
    cds[3].cap = 70;
    
    for(int i = 0; i < MAX_CDS; i++)
    {cds[i].id = i+1; cds[i].builded = 0;}
// ------------------------------------------------------------------------------------------------------------

// Cria as cidades do problema e atribui os valores necessários -----------------------------------------------
    CITY cities[6];

    cities[0].demand = 10;
    cities[1].demand = 15;
    cities[2].demand = 12;
    cities[3].demand = 18;
    cities[4].demand = 8;
    cities[5].demand = 20;

    for(int i = 0; i < MAX_CITIES; i++)
    {
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

    SOLUTION solution = greedy_optimize(cds, cities, costs);
    puts("Solução Final:\n");
    for(int i = 0; i < MAX_CITIES; i++)
    {
        printf("Cidade %i atendida pelo CD de id %i\n",cities[i].id,cds[solution.served_cities[i]].id);
    }
    puts("");
}