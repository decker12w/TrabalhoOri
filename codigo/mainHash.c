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

    insereHash(hash, "palavra1", post1);
    insereHash(hash, "palavra2", post2);
    insereHash(hash, "palavra3", post3);
    insereHash(hash, "palavra1", post3); // Inserindo novamente para testar busca

    int ok;
    Set *resultado = buscaHash(hash, "palavra1", &ok);

    if (ok == -1)
    {
        printf("Palavra não encontrada.\n");
    }
    else
    {
        printf("Resultados para a palavra 'palavra1':\n");
        for (beginSet(resultado); !endSet(resultado); nextSet(resultado))
        {
            Postagem postagem;
            getItemSet(resultado, &postagem);
            printf("Postagem { rrn: %d, tamanhoLinha: %d }\n", postagem.rrn, postagem.tamanhoLinha);
        }
    }

    // Liberar a tabela hash
    liberaHash(hash);

    return 0;
}
