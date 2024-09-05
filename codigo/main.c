#include <stdio.h>
#include <stdlib.h>
#include "LeitorArquivo.h"
#include "TabelaHash.h"

int main()
{
    Hash *tab = criaHash(10);
    if (lerArquivo("corpus.csv", tab) == -1)
        printf("Erro ao ler arquivo\n");

    int *RRN = NULL;
    int value;

    buscaHash(tab, &RRN, "omg");
    printf("Encontrou vetor de rrn %d\n", RRN[0]);
    char *frase = BurcarPeloRRN("corpus.csv", RRN[0]);
    printf("Frase encontrada: %s\n", frase);
}