#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include "LeitorArquivo.h"

// Função para remover espaços no início e fim da string
void removeEspaco(char *str)
{
    char *start = str;
    char *end;

    while (isspace((unsigned char)*start))
        start++;

    if (*start == 0)
    {
        *str = 0;
        return;
    }

    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end))
        end--;

    *(end + 1) = 0;
    memmove(str, start, end - start + 2);
}

// Função para remover pontuações do início e do final da string
void removePontuacao(char *str)
{
    char *start = str;
    char *end;

    while (*start && ispunct((unsigned char)*start))
    {
        start++;
    }

    if (*start == 0)
    {
        *str = 0;
        return;
    }

    end = start + strlen(start) - 1;
    while (end > start && ispunct((unsigned char)*end))
        end--;

    *(end + 1) = 0;

    if (start != str)
    {
        memmove(str, start, end - start + 2);
    }
}

// Função que trata o texto removendo espaços e pontuações
char *tratadorTexto(char *text)
{
    removeEspaco(text);
    removePontuacao(text);
    removeEspaco(text);
    return text;
}

// Função para ler o arquivo e inserir as postagens na hash
int lerArquivo(char *nomeArquivo, Hash *hash)
{
    printf("Lendo arquivo %s\n", nomeArquivo);
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    Postagem post;
    while ((read = getline(&line, &len, file)) != -1)
    {
        post.tamanhoLinha = strlen(line);
        post.rrn = ftell(file) - post.tamanhoLinha;

        line[strcspn(line, "\n")] = '\0';

        char *docID = strtok(line, ",");
        char *opiniao = strtok(NULL, ",");
        char *texto = strtok(NULL, ",");

        texto = tratadorTexto(texto);

        char *palavra;
        palavra = strtok(texto, " ");
        while (palavra != NULL)
        {
            if ((insereHash(hash, palavra, post)) == -1)
                printf("Erro ao inserir palavra %s\n", palavra);
            palavra = strtok(NULL, " ");
        }
    }

    free(line);
    fclose(file);
    return 0;
}

// Função para buscar uma palavra na hash e imprimir o texto tratado
void BuscarPalavra(char *nomeArquivo, Hash *hash, char *palavra)
{
    FILE *arquivoTweets = fopen(nomeArquivo, "r");
    if (arquivoTweets == NULL)
    {
        perror("Erro ao abrir o arquivo para leitura.");
        return;
    }

    int ok;
    Set *resultado = buscaHash(hash, palavra, &ok);

    if (ok == -1)
    {
        printf("Palavra '%s' não encontrada\n", palavra);
        fclose(arquivoTweets);
        return;
    }

    printf("Resultados para a palavra '%s':\n", palavra);

    // Se o conjunto de resultados estiver correto, iteramos e imprimimos as ocorrências
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

/* // Função principal para testar o código
int main()
{
    Hash *tab = criaHash(10003);
    if (lerArquivo("corpusTeste.csv", tab) == -1)
        printf("Erro ao ler arquivo\n");

    // Exemplo de busca de uma palavra
    BuscarPalavra("corpusTeste.csv", tab, "omg");

    return 0;
}
 */