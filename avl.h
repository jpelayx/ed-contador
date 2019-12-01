#include "descritor.h"
#define MAX_PALAVRA 50

typedef struct AVLNode {

    char texto[MAX_PALAVRA];
    int freq;
    int fator;
    struct AVLNode *esq; 
    struct AVLNode *dir;

} AVLNode;

AVLNode *insereAVL(AVLNode *pt, char txt[MAX_PALAVRA], descritor *dscr, int *cond);
AVLNode *condPositive(AVLNode *pt, descritor *dscr, int *cond);
AVLNode *condNegative(AVLNode *pt, descritor *dscr, int *cond);
AVLNode *rdAVL(AVLNode *pt, descritor *dscr);
AVLNode *reAVL(AVLNode *pt, descritor *dscr);
AVLNode *rddAVL(AVLNode *pt, descritor *dscr);
AVLNode *rdeAVL(AVLNode *pt, descritor *dscr);

int alturaAVL(AVLNode *pt);
int calcFatorAVL(AVLNode *pt);
int isAVL(AVLNode *pt);
int freqAVL(AVLNode *pt, char txt[MAX_PALAVRA]);