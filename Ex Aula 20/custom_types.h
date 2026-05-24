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
#endif