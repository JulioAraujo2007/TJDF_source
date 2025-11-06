#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Função auxiliar para criar uma nova cidade
Cidade *criarCidade(const char *nome, int posicao) {
    Cidade *nova = (Cidade *)malloc(sizeof(Cidade));
    if (nova == NULL) return NULL;

    strcpy(nova->Nome, nome);
    nova->Posicao = posicao;
    nova->Proximo = NULL;
    return nova;
}

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return NULL;
    }

    int T, N;
    if (fscanf(arq, "%d", &T) != 1 || fscanf(arq, "%d", &N) != 1) {
        fclose(arq);
        return NULL;
    }

    // Verifica restrições
    if (T < 3 || T > 1000000 || N < 2 || N > 10000) {
        fclose(arq);
        return NULL;
    }

    Estrada *E = (Estrada *)malloc(sizeof(Estrada));
    if (E == NULL) {
        fclose(arq);
        return NULL;
    }

    E->T = T;
    E->N = N;
    E->Inicio = NULL;

    int posicoes[10000];
    int contador = 0;

    Cidade *ultima = NULL;

    for (int i = 0; i < N; i++) {
        int pos;
        char nome[256];

        if (fscanf(arq, "%d %[^\n]", &pos, nome) != 2) {
            free(E);
            fclose(arq);
            return NULL;
        }

        //restrições de posição
        if (pos <= 0 || pos >= T) {
            free(E);
            fclose(arq);
            return NULL;
        }

        //posição já existe
        for (int j = 0; j < contador; j++) {
            if (pos == posicoes[j]) {
                free(E);
                fclose(arq);
                return NULL;
            }
        }

        posicoes[contador++] = pos;

        Cidade *nova = criarCidade(nome, pos);
        if (nova == NULL) {
            free(E);
            fclose(arq);
            return NULL;
        }

        if (E->Inicio == NULL)
            E->Inicio = nova;
        else
            ultima->Proximo = nova;

        ultima = nova;
    }

    fclose(arq);
    return E;
}

//qsort
int comparar(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL)
        return -1.0;

    int T, N;
    if (fscanf(arq, "%d", &T) != 1 || fscanf(arq, "%d", &N) != 1) {
        fclose(arq);
        return -1.0;
    }

    if (T < 3 || T > 1000000 || N < 2 || N > 10000) {
        fclose(arq);
        return -1.0;
    }

    int *pos = (int *)malloc(sizeof(int) * N);
    char nome[256];

    for (int i = 0; i < N; i++) {
        if (fscanf(arq, "%d %[^\n]", &pos[i], nome) != 2) {
            free(pos);
            fclose(arq);
            return -1.0;
        }
    }

    fclose(arq);

    qsort(pos, N, sizeof(int), comparar);

    double menor = 1e9;

    for (int i = 0; i < N; i++) {
        double viz;

        if (i == 0) {
            viz = (pos[i+1] - pos[i]) / 2.0 + pos[i];
        } else if (i == N - 1) {
            viz = (T - pos[i]) + (pos[i] - pos[i-1]) / 2.0;
        } else {
            viz = (pos[i+1] - pos[i-1]) / 2.0;
        }

        if (viz < menor)
            menor = viz;
    }

    free(pos);
    return menor;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL)
        return NULL;

    int T, N;
    if (fscanf(arq, "%d", &T) != 1 || fscanf(arq, "%d", &N) != 1) {
        fclose(arq);
        return NULL;
    }

    if (T < 3 || T > 1000000 || N < 2 || N > 10000) {
        fclose(arq);
        return NULL;
    }

    int *pos = (int *)malloc(sizeof(int) * N);
    char **nomes = (char **)malloc(sizeof(char *) * N);

    for (int i = 0; i < N; i++) {
        nomes[i] = (char *)malloc(256);
        if (fscanf(arq, "%d %[^\n]", &pos[i], nomes[i]) != 2) {
            fclose(arq);
            return NULL;
        }
    }

    fclose(arq);

    // Ordena a posição
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (pos[i] > pos[j]) {
                int tmp = pos[i];
                pos[i] = pos[j];
                pos[j] = tmp;

                char tempNome[256];
                strcpy(tempNome, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], tempNome);
            }
        }
    }

    double menor = 1e9;
    int indiceMenor = 0;

    for (int i = 0; i < N; i++) {
        double viz;

        if (i == 0)
            viz = (pos[i+1] - pos[i]) / 2.0 + pos[i];
        else if (i == N - 1)
            viz = (T - pos[i]) + (pos[i] - pos[i-1]) / 2.0;
        else
            viz = (pos[i+1] - pos[i-1]) / 2.0;

        if (viz < menor) {
            menor = viz;
            indiceMenor = i;
        }
    }

    // Aloca o nome da cidade com menor vizinhança
    char *resultado = (char *)malloc(strlen(nomes[indiceMenor]) + 1);
    strcpy(resultado, nomes[indiceMenor]);

    for (int i = 0; i < N; i++)
        free(nomes[i]);
    free(nomes);
    free(pos);

    return resultado;
}
