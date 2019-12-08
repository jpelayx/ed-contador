#include "descritor.h"
#define MAX_PALAVRA 50

#ifndef AVL_H
#define AVL_H

typedef struct AVLNode {

    char texto[MAX_PALAVRA];
    int freq;
    int fator;
    struct AVLNode *esq; 
    struct AVLNode *dir;

} AVLNode;

AVLNode *insereAVL(AVLNode *pt, char txt[MAX_PALAVRA], descritor *dscr, int *cond);
AVLNode *caso1(AVLNode *pt, descritor *dscr, int *cond);
AVLNode *caso2(AVLNode *pt, descritor *dscr, int *cond);
AVLNode *rotD(AVLNode *pt, descritor *dscr);
AVLNode *rotE(AVLNode *pt, descritor *dscr);
AVLNode *rotDD(AVLNode *pt, descritor *dscr);
AVLNode *rotDE(AVLNode *pt, descritor *dscr);

int alturaAVL(AVLNode *pt, descritor *dscr);
int calcFatorAVL(AVLNode *pt, descritor *dscr);
int isAVL(AVLNode *pt, descritor *dscr);
int freqAVL(AVLNode *pt, char txt[MAX_PALAVRA], descritor *dscr);
int calcMaiorFatorAVL(AVLNode *pt, descritor *dscr);
int calcMaiorAlturaAVL(AVLNode *pt, descritor *dscr);

#endif