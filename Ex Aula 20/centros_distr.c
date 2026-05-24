#include <stdio.h>
#include <stdlib.h>
#include "custom_types.h"

/*
    Encontrando uma solução a partir de algoritmos gulosos.
    Esta função busca encontrar a melhor solução local, encontrando o CD mais barato de se construir para cada cidade, que consegue atender à sua demanda.
    params:
        CD cds[MAX_CDS] => Vetor do tipo CD, que representa os centros de distribuição disponíveis;
        CITY cities[MAX_CITIES] => Vetor do tipo CITY, que representa as cidades à serem atendidas
        const int costs[MAX_CDS][MAX_CITIES] => Matriz de custos (CD_i para cidade_j)
    return:
        SOLUTION sol => Solução final utilizando os ótimos locais.

*/
SOLUTION greedy_optimize(const CD cds[MAX_CDS], const CITY cities[MAX_CITIES], const int costs[MAX_CDS][MAX_CITIES])
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
            // Custo fixo de instalar o cd j por cidade (custo total / número de cidades)
            int fix_cost = cds[j].fix_cost/MAX_CITIES;

            // Verifica se há capacidade restante no CD
            if(remaining_cap[j] >= cities[i].demand)
            {
                // Taxa de logística entre cd_j e cidade_i + custo de construção do cd_j (custo para cada cidade)
                int curr_cost = costs[j][i] + fix_cost;
                
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

    }

    sol.total_cost = calculate_cost(sol,cds,costs);

    return sol;
}

/*
    Função que calcula o custo total de uma solução.
    params:
        SOLUTION sol => Solução encontrada, a qual deseja-se calcular o custo;
        const CD cds[MAX_CDS] => Vetor contendo as informações dos centros de distribuição;
        const int costs[MAX_CDS][MAX_CITIES] => Matriz de custos de transporte entre o cd i e a cidade j (costs[i][j]).
    return:
        int cost => Custo total calculado.
*/
int calculate_cost(SOLUTION sol, const CD cds[MAX_CDS], const int costs[MAX_CDS][MAX_CITIES])
{
    // Inicializa as variáveis de custo e o vetor de cds utilizados
    int cost = 0;
    int used_cds[MAX_CDS] = {0};

    // Percorre todas as cidades
    for(int j = 0; j < MAX_CITIES; j++)
    {
        // Encontra o cd que serve à cidade j;
        int cd_idx = sol.served_cities[j];

        // Incrementa o custo
        cost += costs[cd_idx][j];

        // Incrementa o custo de construção do cd (única vez)
        if(!used_cds[cd_idx])
        {
            cost += cds[cd_idx].fix_cost;
            used_cds[cd_idx] = 1;
        }
    }
    return cost;
}

/*
    Faz uma busca local para aprimorar a solução gulosa, explorando soluções vizinhas em busca de uma melhor otimização.
    params:
        SOLUTION old_sol => Solução gulosa;
        const CD cds[MAX_CDS] => Centros de dsitribuição;
        const CITY cities[MAX_CITIES] => cidades a serem atendidas
        const int costs[MAX_CDS][MAX_CITIES] => Matriz de custos
    return:
        SOLUTION new_sol => Retorna solução aprimorada pela busca local.
*/
SOLUTION local_search(SOLUTION old_sol, const CD cds[MAX_CDS], const CITY cities[MAX_CITIES], const int costs[MAX_CDS][MAX_CITIES])
{
    // Instancia nova solução
    SOLUTION new_sol = old_sol;
    
    // Variável auxiliar, que indica se há possível melhora ainda na solução encontrada
    int can_improve = 1;

    // Atua enquanto houver possibilidade de melhora
    while(can_improve)
    {
        // Seta para 0, para sair do loop caso não encontre melhor solução
        can_improve = 0;

        // Percorre todas as cidades
        for(int i = 0; i < MAX_CITIES; i++)
        {
            // Indíce do CD que serve a i-ésima cidade na solução atual
            int cur_cd = old_sol.served_cities[i];

            // Percorre todas as cidades
            for(int new_cd = 0; new_cd < MAX_CDS; new_cd++)
            {
                // Pula a solução atual
                if(new_cd!=cur_cd)
                {
                    // Variável auxiliar, inicializada em 0, que indica quanto da capacidade do x-ésimo CD foi utilizado
                    int used_cap[MAX_CDS] = {0};

                    // Atribui o quanto das capacidades estão sendo usadas na solução atual, para cada CD que atende à cidade x
                    for(int x = 0; x <MAX_CITIES; x++)
                    {
                        used_cap[old_sol.served_cities[x]] += cities[x].demand;
                    }
                    
                    // Retira o uso da capacidade do CD atual (remove a cidade da lista de antendidas)
                    used_cap[cur_cd] -= cities[i].demand;
                    
                    // Verifica se o novo CD suporta a demanda da cidade recém retirada
                    if(!(used_cap[new_cd] + cities[i].demand > cds[new_cd].cap))
                    {
                        // Atribui nova solução
                        new_sol = old_sol;
                        
                        // Faz com que a iésima cidade seja atendida por um novo CD
                        new_sol.served_cities[i] = new_cd;
    
                        // Recalcula o custo total da nova solução
                        new_sol.total_cost = calculate_cost(new_sol,cds,costs);
                        
                        // Caso a nova solução seja melhor que a anterior, indica possibilidade de melhora e busca novo vizinho baseado na nova solução encontrada (faz old_sol = new_sol)
                        if(new_sol.total_cost < old_sol.total_cost)
                        {
                            can_improve = 1;
                            old_sol = new_sol;
                        }
                    }
                }
            }
        }
    }

    // Retorna a melhor solução encontrada
    new_sol = old_sol;
    return new_sol;
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
    {
        cds[i].id = i+1;
    }
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

// Exibição dos resultados: -----------------------------------------------------------------------------------
    
    FILE* file = fopen("solutions.txt","w");

    SOLUTION solution = greedy_optimize(cds, cities, costs);
    puts("Solução Final -- Gulosa:\n");
    fprintf(file,"Solução Final -- Gulosa:\n\n");
    for(int i = 0; i < MAX_CITIES; i++)
    {
        printf("Cidade %i atendida pelo CD de id %i\n",cities[i].id,cds[solution.served_cities[i]].id);
        fprintf(file,"Cidade %i atendida pelo CD de id %i\n",cities[i].id,cds[solution.served_cities[i]].id);
    }
    puts("");
    printf("Custo final: %i\n",solution.total_cost);
    fprintf(file,"\nCusto final: %i\n",solution.total_cost);
    puts("");

    puts("");
    solution = local_search(solution, cds, cities, costs);
    puts("Solução Final -- Gulosa + Busca Local:\n");
    fprintf(file,"\nSolução Final -- Gulosa + Busca Local:\n\n");
    for(int i = 0; i < MAX_CITIES; i++)
    {
        printf("Cidade %i atendida pelo CD de id %i\n",cities[i].id,cds[solution.served_cities[i]].id);
        fprintf(file,"Cidade %i atendida pelo CD de id %i\n",cities[i].id,cds[solution.served_cities[i]].id);
    }
    puts("");
    printf("Custo final: %i\n",solution.total_cost);
    fprintf(file,"\nCusto final: %i\n",solution.total_cost);
    puts("");

    fclose(file);
// ------------------------------------------------------------------------------------------------------------
}