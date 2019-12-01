#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int freqAVL(AVLNode *pt, char txt[MAX_PALAVRA]) {

    if(pt == NULL) {
        return 0;
    }else{

        if(strcmp(txt, pt->texto) < 0) {
            freqAVL(pt->esq, txt);
        }else if(strcmp(txt, pt->texto) > 0){
            freqAVL(pt->dir, txt);
        }else{
            return pt->freq;
        }

    }

}

int alturaAVL(AVLNode *pt) {

    int alt_e, alt_d;

    if(pt != NULL) {

        alt_d = alturaAVL(pt->dir);
        alt_e = alturaAVL(pt->esq);

        if(alt_d > alt_e) {
            return 1 + alt_d;
        }else{
            return 1 + alt_e;
        }

    }else{
        return 0;
    }

}

int calcFatorAVL(AVLNode *pt) {
    return (alturaAVL(pt->esq) - alturaAVL(pt->dir));
}

int isAVL(AVLNode *pt) {

    int alt_e, alt_d;

    if(pt == NULL) {
        return 1;
    }else{
        alt_e = alturaAVL(pt->esq);
        alt_d = alturaAVL(pt->dir);

        return ((alt_e - alt_d < 2)
            && (alt_d - alt_e < 2)
            && (isAVL(pt->esq))
            && (isAVL(pt->dir)));
    }

}

//  Rotacao Simples Direita
AVLNode *rdAVL(AVLNode *pt, descritor *dscr) {

    dscr->rotacoes += 1;

    AVLNode *pt_aux;

    pt_aux = pt->esq;
    pt->esq = pt_aux->dir;
    pt_aux->dir = pt;
    pt->fator = 0;
    pt = pt_aux;

    return pt;

}

//  Rotacao Simples Esquerda
AVLNode *reAVL(AVLNode *pt, descritor *dscr) {

    dscr->rotacoes += 1;

    AVLNode *pt_aux;

    pt_aux = pt->dir;
    pt->dir = pt_aux->esq;
    pt_aux->esq = pt;
    pt->fator = 0;
    pt = pt_aux;

    return pt;

}

//  Rotacao Dupla Direita
AVLNode *rddAVL(AVLNode *pt, descritor *dscr) {

    dscr->rotacoes += 2;

    AVLNode *pt_aux1, *pt_aux2;

    pt_aux1 = pt->esq;
    pt_aux2 = pt->dir;

    pt_aux1->dir = pt_aux2->esq;
    pt_aux2->esq = pt_aux1;
    pt->esq = pt_aux2->dir;
    pt_aux2->dir = pt;

    // verificacao de fatores
    if(pt_aux2->fator == 1) {
        pt->fator = -1;
    }else{
        pt->fator = 0;
    }

    if(pt_aux2->fator == -1) {
        pt_aux1->fator = 1;
    }else{
        pt_aux1->fator = 0;
    }

    pt = pt_aux2;
    return pt;

}

//  Rotacao Dupla Esquerda
AVLNode *rdeAVL(AVLNode *pt, descritor *dscr) {

    dscr->rotacoes += 2;

    AVLNode *pt_aux1, *pt_aux2;

    pt_aux1 = pt->dir;
    pt_aux2 = pt->esq;

    pt_aux1->esq = pt_aux2->dir;
    pt_aux2->dir = pt_aux1;
    pt->dir = pt_aux2->esq;
    pt_aux2->esq = pt;

    // verificacao de fatores
    if(pt_aux2->fator == 1) {
        pt_aux1->fator = -1;
    }else{
        pt_aux1->fator = 0;
    }

    if(pt_aux2->fator == -1) {
        pt->fator = 1;
    }else{
        pt->fator = 0;
    }

    pt = pt_aux2;
    return pt;

}

AVLNode *condPositive(AVLNode *pt, descritor *dscr, int *cond) {


    if(pt->esq->fator == 1) {
        pt = rdAVL(pt, dscr);
    }else{
        pt = rddAVL(pt, dscr);
    }

    pt->fator = 0;
    *cond = 0;
    return pt;

}

AVLNode *condNegative(AVLNode *pt, descritor *dscr, int *cond) {

    if(pt->dir->fator == -1) {
        pt = reAVL(pt, dscr);
    }else{
        pt = rdeAVL(pt, dscr);
    }

    pt->fator = 0;
    *cond = 0;
    return pt;

}

AVLNode *insereAVL(AVLNode *pt, char txt[MAX_PALAVRA], descritor *dscr, int *cond) {

    if (pt == NULL) {

//        printf("\nNULL\n");

        pt = (AVLNode *) malloc(sizeof(AVLNode));   //aloca memória
        strcpy(pt->texto, txt);
        pt->fator = 0;
        pt->esq = NULL;
        pt->dir = NULL;

        *cond = 1;

        dscr->nodos += 1;
        dscr->comparacoes += 1;

        pt->freq = 1;

    } else {

        if (strcmp(txt, pt->texto) < 0) {

            // esq

//            printf("\nMenor\n");

            dscr->comparacoes += 1;

            pt->esq = insereAVL(pt->esq, txt, dscr, cond);

            // verifica codigo de condicao apos insercao
            if(*cond) {

                if(pt->fator == 1) {
                    printf("\tpos");
                    pt = condPositive(pt, dscr, cond);

                }else if(pt->fator == -1) {

                    pt->fator = 0;
                    *cond = 0;

                }else if(pt->fator == 0) {

                    pt->fator = 1;
                    *cond = 0;

                }

            }

        }

        if (strcmp(txt, pt->texto) > 0) {

//            printf("\nMaior\n");

            //dir
            dscr->comparacoes += 1;

            pt->dir = insereAVL(pt->dir, txt, dscr, cond);

            // verifica codigo de condicao apos insercao
            if(*cond) {

                if(pt->fator == -1) {
//                    printf("\tpneg");
                    pt = condNegative(pt, dscr, cond);

                }else if(pt->fator == 1) {

                    pt->fator = 0;
                    *cond = 0;

                }else if(pt->fator == 0) {

                    pt->fator = -1;
                    *cond = 0;

                }

            }

        }

        if (strcmp(txt, pt->texto) == 0) {

//            printf("\nIgual\n");

            // add freq
            pt->freq += 1;

            printf("\t%s :: %d\n", pt->texto, pt->freq);

            dscr->comparacoes += 1;

        }
    }
    return pt;
}