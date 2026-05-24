#ifndef CUSTOM_TYPES
    #define CUSTOM_TYPES

    // Define o número máximo de centros de distribuição e de cidades no problema
    #define MAX_CDS 4       // Número máximo de centros de distribuição
    #define MAX_CITIES 6    // Número máximo de cidades

    // Tipo que representa um centro de distribuição
    typedef struct _cd
    {
        int id;         // Identificação única de cada CD
        int fix_cost;   // Custo fixo de instalação do CD
        int cap;        // Capacidade do CD
    }CD;

    // Tipo que representa uma cidade
    typedef struct city
    {
        int id;         // Identificação única de cada cidade
        int demand;     // Demanda de cada cidade
    }CITY;

    // Tipo auxiliar para a construção de uma solução com a heurística
    typedef struct _sol
    {
        int served_cities[MAX_CITIES];      // CDs que servem à i-ésima cidade
        int total_cost;                     // Custo total da otimização
    }SOLUTION;

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
    SOLUTION greedy_optimize(const CD cds[MAX_CDS], const CITY cities[MAX_CITIES], const int costs[MAX_CDS][MAX_CITIES]);

    /*
        Função que calcula o custo total de uma solução.
        params:
            SOLUTION sol => Solução encontrada, a qual deseja-se calcular o custo;
            const CD cds[MAX_CDS] => Vetor contendo as informações dos centros de distribuição;
            const int costs[MAX_CDS][MAX_CITIES] => Matriz de custos de transporte entre o cd i e a cidade j (costs[i][j]).
        return:
            int cost => Custo total calculado.
    */
    int calculate_cost(SOLUTION sol, const CD cds[MAX_CDS], const int costs[MAX_CDS][MAX_CITIES]);

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
    SOLUTION local_search(SOLUTION old_sol, const CD cds[MAX_CDS], const CITY cities[MAX_CITIES], const int costs[MAX_CDS][MAX_CITIES]);
#endif