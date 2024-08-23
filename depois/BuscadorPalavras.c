#include <stdio.h>
#include <stdlib.h>

void armazenarPostagens(char arq[])
{
    FILE *arquivo;
    int rrn, opiniao;
    char palavra[500];

    arquivo = fopen(arq, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return;
    }

    while (getc(arquivo) != '\n')
    {
        /* code */
    }

    // Continua com a leitura dos dados
    fscanf(arquivo, "%d,%d,%s", &rrn, &opiniao, palavra);
    printf("%d,%d,%s\n", rrn, opiniao, palavra);
    fclose(arquivo);
}

int main()
{
    char busca[100];
    printf("Digite sua busca:");
    fgets(busca, 100, stdin);
    armazenarPostagens("corpus.csv");

    return 0;
}