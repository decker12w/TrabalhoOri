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

    // Remove espaços no início da string
    while (isspace((unsigned char)*start))
        start++;

    // Se a string for composta apenas por espaços, então a string é vazia
    if (*start == 0)
    {
        *str = 0;
        return;
    }

    // Remove espaços no final da string
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

    // Remove pontuações no início da string
    while (*start && ispunct((unsigned char)*start))
    {
        start++;
    }
    // Se a string for composta apenas por pontuações, então a string é vazia
    if (*start == 0)
    {
        *str = 0;
        return;
    }

    // Remove pontuações no final da string
    end = start + strlen(start) - 1;
    while (end > start && ispunct((unsigned char)*end))
        end--;

    // Adiciona o caractere nulo no final da string
    *(end + 1) = 0;

    // Move a string para o início
    if (start != str)
    {
        memmove(str, start, end - start + 2);
    }
}

// Função que trata o texto removendo espaços e pontuações
char *tratadorTexto(char *text)
{
    // Remove espaços no início e no final do texto
    removeEspaco(text);

    // Remove pontuações (exceto pontuações que separam palavras)
    removePontuacao(text);

    // Remove espaços incosistentes se ainda houver após a remoção de pontuações
    removeEspaco(text);
    return text;
}

// Função para ler o arquivo e inserir as postagens na hash
int lerArquivo(char *nomeArquivo, Hash *hash)
{
    // Abre o arquivo para leitura
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

    // Lê o arquivo linha por linha
    while ((read = getline(&line, &len, file)) != -1)
    {
        // leitura do tamanho da linha
        post.tamanhoLinha = strlen(line);

        // leitura do RRN
        post.RRN = ftell(file) - post.tamanhoLinha;

        // Remove o caractere de nova linha
        line[strcspn(line, "\n")] = '\0';

        // Separa a linha em docID, opinião e texto
        char *docID = strtok(line, ",");
        char *opiniao = strtok(NULL, ",");
        char *texto = strtok(NULL, ",");

        // Trata o texto removendo espaços e pontuações
        texto = tratadorTexto(texto);

        // Percorre o texto palavra por palavra e insere na hash
        char *palavra;
        palavra = strtok(texto, " ");
        while (palavra != NULL)
        {
            if ((insereHash(hash, palavra, post)) == -1)
                printf("Erro ao inserir palavra %s\n", palavra);
            palavra = strtok(NULL, " ");
        }
    }

    // Libera a memória alocada para a linha e fecha o arquivo
    free(line);
    fclose(file);
    return 0;
}
