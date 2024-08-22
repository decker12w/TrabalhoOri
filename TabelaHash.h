// Pot�ncias de dois devem ser evitadas
// deve ser um n�mero primo distante de pequenas pot�ncias de dois
struct Postagem
{
    char palavra[100];
    int opiniao;
    int RRN;
};

typedef struct hash Hash;

Hash *criaHash(int TABLE_SIZE);
void liberaHash(Hash *ha);
int valorString(char *str);
int insereHash_SemColisao(Hash *ha, struct Postagem post);
int buscaHash_SemColisao(Hash *ha, int mat, struct Postagem *post);
int insereHash_EnderAberto(Hash *ha, struct Postagem post);
int buscaHash_EnderAberto(Hash *ha, int mat, struct Postagem *post);
/*
int chaveDivisao(int chave, int TABLE_SIZE);
int chaveDobra(int chave, int TABLE_SIZE);
int chaveMultiplicacao(int chave, int TABLE_SIZE);
int sondagemLinear(int pos, int i, int TABLE_SIZE);
int sondagemQuadratica(int pos, int i, int TABLE_SIZE);
int duploHashing(int pos, int chave, int i, int TABLE_SIZE);
*/