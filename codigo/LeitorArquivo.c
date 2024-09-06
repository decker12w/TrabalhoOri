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

    while ((read = getline(&line, &len, file)) != -1)
    {
        int tamanhoLinha = strlen(line);
        int rrn = ftell(file) - tamanhoLinha;

        line[strcspn(line, "\n")] = '\0';

        char *docID = strtok(line, ",");
        char *opiniao = strtok(NULL, ",");
        char *texto = strtok(NULL, ",");

        texto = tratadorTexto(texto);

        char *palavra;
        palavra = strtok(texto, " ");
        while (palavra != NULL)
        {
            Postagem *post = criaPostagem(palavra, rrn, tamanhoLinha);
            if (post == NULL || insereHash(hash, post) != 0)
            {
                printf("Erro ao inserir postagem %s\n", texto);
            }
            palavra = strtok(NULL, " ");
        }
    }

    free(line);
    fclose(file);
    return 0;
}

int BuscarPeloRRN(char *nomeArquivo, int rrn[], int tamanhoVetor)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    char *linha = NULL;
    size_t tamanho = 0;
    ssize_t lido;

    for (int i = 0; i < tamanhoVetor; i++)
    {
        // Usa fseek para pular para a posição do RRN
        fseek(arquivo, rrn[i], SEEK_SET);

        // Lê a linha na posição do RRN
        lido = getline(&linha, &tamanho, arquivo);
        if (lido != -1)
        {
            // Processa a linha
            char *docID_str = strtok(linha, ",");
            char *opiniao = strtok(NULL, ",");
            char *texto = strtok(NULL, "\n");

            texto = tratadorTexto(texto);

            printf("Frase encontrada: %s\n", texto);
        }
        // Importante: Não feche o arquivo ou libere a linha aqui, pois isso será feito após o loop
    }

    // Libera a linha e fecha o arquivo após o loop
    free(linha);
    fclose(arquivo);

    return 0;
}

void BuscarPalavra(char *nomeArquivo, Hash *hash, char *palavra)
{
    int *RRN = NULL;
    int tamanhoVetor;
    if ((tamanhoVetor = buscaHash(hash, &RRN, palavra)) != -1)
        BuscarPeloRRN(nomeArquivo, RRN, tamanhoVetor);
    else
        printf("Não encontrou\n");
}

/* int main()
{
    Hash *tab = criaHash(10003);
    if (lerArquivo("corpus.csv", tab) == -1)
        printf("Erro ao ler arquivo\n");
    BuscarPalavra("corpus.csv", tab, "omg");
} */
