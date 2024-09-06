#include <stdio.h>
#include "ArvoreAux.h" // Inclua o cabeçalho adequado para o ArvoreAux

int main()
{
    // Criar a árvore auxiliar
    ArvAux *arvore = criaArvAux();

    // Criar algumas palavras e postagens de exemplo
    Palavra palavra1 = {"apple", criaSet()};
    Palavra palavra2 = {"banana", criaSet()};
    Palavra palavra3 = {"cherry", criaSet()};

    Postagem post1 = {1, 10}; // Exemplo de postagem 1
    Postagem post2 = {2, 15}; // Exemplo de postagem 2
    Postagem post3 = {3, 20}; // Exemplo de postagem 3

    // Inserir palavras com postagens
    insereArvAux(arvore, palavra1, post1);
    insereArvAux(arvore, palavra2, post2);
    insereArvAux(arvore, palavra3, post3);

    // Realizar busca por uma palavra
    Palavra palavraBuscada;
    char palavraChave[] = "banana";
    if (busca_arvore(arvore, &palavraBuscada, palavraChave) == 0)
    {
        printf("Palavra '%s' encontrada!\n", palavraChave);
    }
    else
    {
        printf("Palavra '%s' não encontrada.\n", palavraChave);
    }

    // Liberar a árvore
    liberaArvAux(arvore);

    return 0;
}
