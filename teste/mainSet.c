#include <stdio.h>
#include <stdlib.h>
#include "set.h"

int main()
{
    // Criando dois sets
    Set *setA = criaSet();
    Set *setB = criaSet();

    // Verificando se os sets foram criados corretamente
    if (setA == NULL || setB == NULL)
    {
        printf("Erro ao criar os sets.\n");
        return -1;
    }

    // Criando algumas postagens para inserir
    Postagem post1 = {1, 100}; // Exemplo de postagem 1 (rrn=1, tamanhoLinha=100)
    Postagem post2 = {2, 150}; // Exemplo de postagem 2 (rrn=2, tamanhoLinha=150)
    Postagem post3 = {3, 200}; // Exemplo de postagem 3 (rrn=3, tamanhoLinha=200)
    Postagem post4 = {4, 250}; // Exemplo de postagem 4 (rrn=4, tamanhoLinha=250)

    // Inserindo postagens no Set A
    insereSet(setA, post1);
    insereSet(setA, post2);

    // Inserindo postagens no Set B
    insereSet(setB, post3);
    insereSet(setB, post4);
    insereSet(setB, post1); // Também inserindo post1 em B para testar interseção

    // Iterando e exibindo os itens do Set A
    printf("Itens no Set A:\n");
    for (beginSet(setA); !endSet(setA); nextSet(setA))
    {
        Postagem postagem;
        getItemSet(setA, &postagem);
        printf("Postagem { rrn: %d, tamanhoLinha: %d }\n", postagem.rrn, postagem.tamanhoLinha);
    }

    // Iterando e exibindo os itens do Set B
    printf("\nItens no Set B:\n");
    for (beginSet(setB); !endSet(setB); nextSet(setB))
    {
        Postagem postagem;
        getItemSet(setB, &postagem);
        printf("Postagem { rrn: %d, tamanhoLinha: %d }\n", postagem.rrn, postagem.tamanhoLinha);
    }

    // Realizando a união dos sets
    Set *setUniao = uniaoSet(setA, setB);
    printf("\nItens na União de A e B:\n");
    for (beginSet(setUniao); !endSet(setUniao); nextSet(setUniao))
    {
        Postagem postagem;
        getItemSet(setUniao, &postagem);
        printf("Postagem { rrn: %d, tamanhoLinha: %d }\n", postagem.rrn, postagem.tamanhoLinha);
    }

    // Realizando a interseção dos sets
    Set *setInterseccao = interseccaoSet(setA, setB);
    printf("\nItens na Interseção de A e B:\n");
    for (beginSet(setInterseccao); !endSet(setInterseccao); nextSet(setInterseccao))
    {
        Postagem postagem;
        getItemSet(setInterseccao, &postagem);
        printf("Postagem { rrn: %d, tamanhoLinha: %d }\n", postagem.rrn, postagem.tamanhoLinha);
    }

    // Liberando memória dos sets
    liberaSet(setA);
    liberaSet(setB);
    liberaSet(setUniao);
    liberaSet(setInterseccao);

    return 0;
}
