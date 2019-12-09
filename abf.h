#include "descritor.h"
#include "abp.h"
#include "avl.h"
#define MAX_PALAVRA 50

// ABF é uma "árvore binária de frequencia", usada para armazenar as palavras
// coletadas em uma ABP ordenada por frequencia, a fim de facilitar
// a implementacao da operacao "contador"
// Para isso, guarda apenas as informações de frequencia e texto dos nodos

typedef struct ABFreq {
    int freq;
    char texto[MAX_PALAVRA];
    struct ABFreq *esq;
    struct ABFreq *dir;
} ABFreq;

ABFreq *insereABF(ABFreq *pt, int freq, char txt[MAX_PALAVRA], descritor *dscr);
void AVLpopulaABF(ABFreq **abf, AVLNode *avl, descritor *dscr);
void ABPpopulaABF(ABFreq **abf, tipoABP *abp, descritor *dscr);
void buscaPorRange(ABFreq *abf, int min, int max, FILE *output);
