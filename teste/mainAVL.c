#include <stdio.h>
#include "ArvoreAvl.h"
#include "set.h"
#include "Postagem.h"

int main()
{
    // Criar um conjunto para testar a AVL
    Set *set = criaSet();

    // Criar algumas postagens para inserir na árvore
    Postagem p1 = {1, 100};
    Postagem p2 = {2, 200};
    Postagem p3 = {3, 300};
    Postagem p4 = {4, 400};
    Postagem p5 = {5, 500};

    // Inserir postagens na árvore
    insereSet(set, p1);
    insereSet(set, p2);
    insereSet(set, p3);
    insereSet(set, p4);
    insereSet(set, p5);

    // Exibir as postagens em ordem
    printf("Postagens inseridas na árvore AVL:\n");
    for (beginSet(set); !endSet(set); nextSet(set))
    {
        Postagem postagem;
        getItemSet(set, &postagem);
        printf("RRN: %d, Tamanho da Linha: %d\n", postagem.rrn, postagem.tamanhoLinha);
    }

    // Consultar um elemento na árvore
    Postagem pConsulta = {3, 0}; // Consulta pelo RRN 3
    if (consultaSet(set, pConsulta))
    {
        printf("Postagem com RRN 3 encontrada na árvore.\n");
    }
    else
    {
        printf("Postagem com RRN 3 não encontrada na árvore.\n");
    }

    // Liberar memória alocada para o conjunto
    liberaSet(set);

    return 0;
}
