//Pot�ncias de dois devem ser evitadas
//deve ser um n�mero primo distante de pequenas pot�ncias de dois
#include "ListaDinEncad.h"

struct palavra {
    char info[50];  // Palavra armazenada
    Lista *lista;  // Ponteiro para a lista encadeada de inteiros
};

typedef struct hash Hash;

Hash* criaHash(int TABLE_SIZE);
void liberaHash(Hash* ha);
int valorString(char *str);
int insereHash_EnderAberto(Hash* ha, char *al, int id);
int buscaHash_EnderAberto(Hash* ha, char *palav, struct palavra* a);
/*
int chaveDivisao(int chave, int TABLE_SIZE);
int chaveDobra(int chave, int TABLE_SIZE);
int chaveMultiplicacao(int chave, int TABLE_SIZE);
int sondagemLinear(int pos, int i, int TABLE_SIZE);
int sondagemQuadratica(int pos, int i, int TABLE_SIZE);
int duploHashing(int pos, int chave, int i, int TABLE_SIZE);
*/
