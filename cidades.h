#ifndef CIDADES_H
#define CIDADES_H

typedef struct Cidade {
    char Nome[256];       // Nome da cidade
    int Posicao;          // Posição (coordenada) da cidade
    struct Cidade *Proximo; // Ponteiro para a próxima cidade da estrada
} Cidade;

typedef struct {
    int N;            // Número de cidades
    int T;            // Comprimento da estrada
    Cidade *Inicio;   // Ponteiro para a primeira cidade da estrada
} Estrada;


// Lê o arquivo, valida restrições e cria a lista encadeada de cidades
Estrada *getEstrada(const char *nomeArquivo);

// Calcula e retorna o menor comprimento de vizinhança entre todas as cidades
double calcularMenorVizinhanca(const char *nomeArquivo);

// Retorna o nome da cidade que possui a menor vizinhança (string alocada dinamicamente)
char *cidadeMenorVizinhanca(const char *nomeArquivo);

#endif
