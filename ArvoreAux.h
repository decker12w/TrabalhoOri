// ArvoreAux.h content
typedef struct Postagem
{
    char palavra[100]; // Assuming a max word length
    int *RRN;          // Dynamic array for RRN
    int quantPalavras; // Number of RRNs stored
    struct Postagem *esq, *dir;
} Postagem;

typedef Postagem *ArvoreAux;

ArvoreAux *criaArvore();
Postagem *criaPostagem(char palavra[], int RRN);
void liberaNo(Postagem *no);
void liberaArvore(ArvoreAux *raiz);
void insere_arvore(ArvoreAux *raiz, char palavra[], int RRN);
int busca_arvore(ArvoreAux *raiz, int **RRN, char palavra[]);
void imprimeArvore(ArvoreAux *raiz);