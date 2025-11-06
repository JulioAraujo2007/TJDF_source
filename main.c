#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cidades.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    Estrada *E = getEstrada("teste01.txt");
    if (E == NULL) {
        printf("Erro ao ler o arquivo!\n");
        return 1;
    }

    double menor = calcularMenorVizinhanca("teste01.txt");
    char *cidade = cidadeMenorVizinhanca("teste01.txt");

   
    printf("Comprimento da estrada: %d\n", E->T);
    printf("Numero de cidades: %d\n", E->N);
    printf("Menor vizinhanca: %.2lf\n", menor);
    printf("Cidade com menor vizinhanca: %s\n", cidade);

    free(cidade);
    return 0;
}
