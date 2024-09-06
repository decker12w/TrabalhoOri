#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LeitorArquivo.h"
#include "utilitario.h"

#define MAX_LINHA 1000
#define MAX_BUSCA 300

int main()
{
    Hash *hash = criaHash(10007);

    FILE *arquivoTweets = fopen("corpusTeste.csv", "r");
    if (arquivoTweets == NULL)
    {
        printf("Erro ao abrir arquivo de tweets.");
        exit(1);
    }

    lerArquivo("corpusTeste.csv", hash);

    int escolha;
    char busca[MAX_BUSCA];
    while (1)
    {
        printf("(1) Buscar nova palavra\n(2) Sair da busca\nOpção: ");
        scanf("%d", &escolha);

        if (!(escolha == 1 || escolha == 2))
        {
            printf("(ERRO) Opção inválida!\n\n");
            continue;
        }

        if (escolha == 2)
        {
            break;
        }

        printf("Formule a sua busca utilizando operadores lógicos (AND, OR, NOT): ");
        scanf(" %[^\n]", busca);

        int numComponentes;
        char **componentes = separarBuscaEmComponentes(busca, &numComponentes);

        if (componentes == NULL || numComponentes == 0)
        {
            printf("(ERRO) Pesquisa inválida.\n\n");
            continue;
        }

        int tamanhoPostfix, tipoErro;
        char **postfix = converterComponentesParaPostfix(componentes, numComponentes, &tamanhoPostfix);

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

        for (beginSet(resultado); !endSet(resultado); nextSet(resultado))
        {
            char *linhaSaida = NULL;
            size_t len = 0;
            Postagem postagemSaida;

            getItemSet(resultado, &postagemSaida);
            fseek(arquivoTweets, postagemSaida.rrn, SEEK_SET);

            // Usar getline para ler a linha completa a partir do RRN
            if (getline(&linhaSaida, &len, arquivoTweets) != -1)
            {
                char *texto = strtok(linhaSaida, ","); // pula docID
                texto = strtok(NULL, ",");             // pula opiniao
                texto = strtok(NULL, ",");             // pega o texto

                texto = tratadorTexto(texto); // trata o texto
                printf("Texto tratado: %s\n", texto);
            }
            free(linhaSaida); // Libera a memória alocada pelo getline
        }

        fclose(arquivoTweets);
    }
    return 0;
}