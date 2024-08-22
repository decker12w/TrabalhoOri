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
int insereHash(Hash *ha, struct Postagem post);
int buscaHash(Hash *ha, int mat, struct Postagem *post);
