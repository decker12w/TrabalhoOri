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

    // Avança o ponteiro até o primeiro caractere que não seja espaço
    while (isspace((unsigned char)*start))
        start++;

    // Se a string for toda de espaços, retorna uma string vazia
    if (*start == 0)
    {
        *str = 0;
        return;
    }

    // Encontra o final da string
    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end))
        end--;

    // Coloca o null terminator após o último caractere não-espacial
    *(end + 1) = 0;

    // Move a string para o início do buffer, se necessário
    memmove(str, start, end - start + 2);
}

// Função para remover pontuações do início e do final da string
void removePontuacao(char *str)
{
    char *start = str;
    char *end;

    // Avança o ponteiro até o primeiro caractere que não seja pontuação
    while (*start && ispunct((unsigned char)*start))
    {
        start++;
    }

    // Se a string for toda de pontuações, retorna uma string vazia
    if (*start == 0)
    {
        *str = 0;
        return;
    }

    // Encontra o final da string
    end = start + strlen(start) - 1;
    while (end > start && ispunct((unsigned char)*end))
        end--;

    // Coloca o null terminator após o último caractere não-pontuação
    *(end + 1) = 0;

    // Move a string para o início do buffer, se necessário
    if (start != str)
    {
        memmove(str, start, end - start + 2);
    }
}

char *tratadorTexto(char *text)
{
    removeEspaco(text);
    removePontuacao(text);
    removeEspaco(text);
    return text;
}

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
    int line_number = 0;

    while ((read = getline(&line, &len, file)) != -1)
    {
        line_number++;

        // Processa apenas as linhas 3, 4 e 5
        if (line_number >= 3 && line_number <= 5)
        {
            // Remove o newline do final da linha, se houver
            line[strcspn(line, "\n")] = '\0';

            // Quebra a linha em colunas usando o delimitador ','
            char *docID = strtok(line, ",");
            char *opiniao = strtok(NULL, ",");
            char *texto = strtok(NULL, ",");

            if (docID == NULL || opiniao == NULL || texto == NULL)
            {
                printf("Erro ao ler linha %d\n", line_number);
            }

            texto = tratadorTexto(texto);
            printf("Texto: %s\n", texto);
            Postagem *post = criaPostagem(texto, atoi(docID));
            if (post == NULL || insereHash(hash, post) != 0)
            {
                printf("Erro ao inserir postagem %s\n", texto);
            }
        }

        // Pula as linhas após a 5ª
        if (line_number > 5)
        {
            break;
        }
    }

    free(line);
    fclose(file);
    return 0;
}

int main()
{
    Hash *tab = criaHash(10);
    if (lerArquivo("corpus.csv", tab) == -1)
        printf("Erro ao ler arquivo\n");

    int *RRN;
    if (buscaHash(tab, &RRN, "already"))
        printf("Encontrou vetor de rrn %d\n", RRN[0]);
    else
        printf("Não encontrou\n");
}