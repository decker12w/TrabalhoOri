#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LeitorArquivo.h"
#include "handler.h"

#define MAX_LINHA 1000
#define MAX_BUSCA 300

int main()
{
    Hash *hash = criaHash(12003);

    FILE *arquivoTweets = fopen("../arquivoLeitura/corpus.csv", "r");
    if (arquivoTweets == NULL)
    {
        printf("Erro ao abrir arquivo de tweets.");
        exit(1);
    }

    lerArquivo("../arquivoLeitura/corpus.csv", hash);

    int escolha;
    char busca[MAX_BUSCA];
    while (1)
    {
        printf("1-  Busca no banco de dados\n2-  Sair da busca\nOpção: ");
        scanf("%d", &escolha);

        if (!(escolha == 1 || escolha == 2))
        {
            printf("(ERRO) Opção inválida!\n\n");
            continue;
        }

        if (escolha == 2)
        {
            break; // termina o programa
        }

        printf("Pesquise os elementos do arquivo usando (AND, OR, NOT): \n");
        scanf(" %[^\n]", busca);

        int numComponentes;
        char **componentes = Componente(busca, &numComponentes);

        if (componentes == NULL || numComponentes == 0)
        {
            printf("(ERRO) Pesquisa inválida.\n\n");
            continue;
        }

        int tamanhoPostfix, tipoErro;
        char **postfix = converterParaPostfix(componentes, numComponentes, &tamanhoPostfix);

        if (postfix == NULL)
        {
            printf("(ERRO) Tente novamente.\n\n");
            continue;
        }

        Set *resultado = avaliarPostfix(hash, postfix, tamanhoPostfix, &tipoErro);

        if (resultado == NULL)
        {
            switch (tipoErro)
            {
            case 1:
                printf("(ERRO) Necessário ao menos duas palavras para utilizar operadores lógicos AND ou OR.\n\n");
                break;
            case 2:
                printf("(ERRO) Conjunto universo não deve ser utilizado.\n\n");
                break;
            case 3:
                printf("Nenhuma postagem encontrada.\n\n");
                break;

            default:
                printf("(ERRO) Tente novamente.\n\n");
                break;
            }

            continue;
        }

        printf("\n--------------Frases relacionadas---------------\n");
        for (beginSet(resultado); !endSet(resultado); nextSet(resultado))
        {
            char linhaSaida[MAX_LINHA];
            Postagem postagemSaida;

            getItemSet(resultado, &postagemSaida);
            fseek(arquivoTweets, postagemSaida.RRN, SEEK_SET);
            fgets(linhaSaida, postagemSaida.tamanhoLinha, arquivoTweets);
            printf("\n%s", linhaSaida);
        }

        for (int i = 0; i < numComponentes; i++)
        {
            free(componentes[i]);
        }

        free(componentes);
        free(postfix);

        printf("\n");
    }

    liberaHash(hash);
    fclose(arquivoTweets);
    return 0;
}