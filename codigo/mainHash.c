#include <stdio.h>
#include <stdlib.h>
#include "TabelaHash.h" // Inclua o cabeçalho adequado para a TabelaHash
#include "ArvoreAux.h"  // Inclua o cabeçalho adequado para a ArvoreAux

int main()
{
    // Definir o tamanho da tabela hash
    int tamanhoHash = 10;
    Hash *hash = criaHash(tamanhoHash);

    // Verificar se a tabela hash foi criada com sucesso
    if (hash == NULL)
    {
        printf("Erro ao criar a tabela hash.\n");
        return -1;
    }

    // Criar algumas postagens e palavras para inserir na hash
    Postagem post1 = {1, 10}; // Exemplo de postagem 1
    Postagem post2 = {2, 15}; // Exemplo de postagem 2
    Postagem post3 = {3, 20}; // Exemplo de postagem 3

    // Inserir palavras e postagens na tabela hash
    if (insereHash(hash, "apple", post1) == 0)
    {
        printf("Palavra 'apple' inserida com sucesso.\n");
    }
    else
    {
        printf("Erro ao inserir 'apple'.\n");
    }

    if (insereHash(hash, "banana", post2) == 0)
    {
        printf("Palavra 'banana' inserida com sucesso.\n");
    }
    else
    {
        printf("Erro ao inserir 'banana'.\n");
    }

    if (insereHash(hash, "cherry", post3) == 0)
    {
        printf("Palavra 'cherry' inserida com sucesso.\n");
    }
    else
    {
        printf("Erro ao inserir 'cherry'.\n");
    }

    // Buscar palavras na tabela hash
    int ok;
    Set *resultado = buscaHash(hash, "banana", &ok);
    if (ok)
    {
        printf("Palavra 'banana' encontrada na tabela hash.\n");
    }
    else
    {
        printf("Palavra 'banana' não encontrada.\n");
    }

    resultado = buscaHash(hash, "apple", &ok);
    if (ok)
    {
        printf("Palavra 'apple' encontrada na tabela hash.\n");
    }
    else
    {
        printf("Palavra 'apple' não encontrada.\n");
    }

    resultado = buscaHash(hash, "grape", &ok);
    if (ok)
    {
        printf("Palavra 'grape' encontrada na tabela hash.\n");
    }
    else
    {
        printf("Palavra 'grape' não encontrada.\n");
    }

    // Liberar a tabela hash
    liberaHash(hash);

    return 0;
}
