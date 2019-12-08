#include "descritor.h"
#include "abp.h"
#include "avl.h"
#define MAX_PALAVRA 50

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
