typedef struct Postagem
{
    char palavra[100];
    int RRN[100];
    int quantPalavras;
    struct Postagem *esq, *dir;
} Postagem;

typedef Postagem *ArvoreAux;

ArvoreAux *criaArvore();
Postagem *criaPostagem(char palavra[], int RRN);
void liberaNo(Postagem *no);
void liberaArvore(ArvoreAux *raiz);
void insere_arvore(ArvoreAux *raiz, char palavra[], int RRN);
int busca_arvore(ArvoreAux *raiz, int **RRN, char palavra[]);
