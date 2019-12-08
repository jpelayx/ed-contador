#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "abf.h"

int freqAVL(AVLNode *pt, char txt[MAX_PALAVRA], descritor *dscr) {

    if(pt == NULL) {
        dscr->comparacoes ++;
        return 0;
    }else{
        dscr->comparacoes ++;
        if(strcmp(txt, pt->texto) < 0) {
            dscr->comparacoes ++;
            freqAVL(pt->esq, txt, dscr);
        }else if(strcmp(txt, pt->texto) > 0){
            dscr->comparacoes ++;
            freqAVL(pt->dir, txt, dscr);
        }else{
            dscr->comparacoes ++;
            return pt->freq;
        }

    }

}

int alturaAVL(AVLNode *pt, descritor *dscr) {

    int alt_e, alt_d;

    if(pt == NULL) {
        dscr->comparacoes ++;
        return 0;
    }else{
        dscr->comparacoes ++;
        alt_e = alturaAVL(pt->esq, dscr);
        alt_d = alturaAVL(pt->dir, dscr);
        if(alt_e > alt_d) {
            return (1 + alt_e);
        }else{
            return (1 + alt_d);
        }
    }

}

int calcMaiorAlturaAVL(AVLNode *pt, descritor *dscr) {
    int maior = 0;
    if(pt == NULL) {
        dscr->comparacoes ++;
        return 0;
    }else{
        if(alturaAVL(pt, dscr) > maior) {
            dscr->comparacoes ++;
            maior = alturaAVL(pt, dscr);
        }
        calcMaiorAlturaAVL(pt->esq, dscr);
        calcMaiorAlturaAVL(pt->dir, dscr);
        return maior;
    }
}

int calcFatorAVL(AVLNode *pt, descritor *dscr) {
    return (alturaAVL(pt->esq, dscr) - alturaAVL(pt->dir, dscr));
}

int calcMaiorFatorAVL(AVLNode *pt, descritor *dscr) {
    int maior = 0;
    if(pt == NULL) {
        dscr->comparacoes ++;
        return 0;
    }else{
        dscr->comparacoes ++;
        if(abs(calcFatorAVL(pt, dscr)) > maior) {
            dscr->comparacoes ++;
            maior = calcFatorAVL(pt, dscr);
        }
        calcMaiorFatorAVL(pt->esq, dscr);
        calcMaiorFatorAVL(pt->dir, dscr);
        return maior;
    }
}

int isAVL(AVLNode *pt, descritor *dscr) {

    int alt_e, alt_d;

    if(pt == NULL) {
        dscr->comparacoes ++;
        return 1;
    }else{
        dscr->comparacoes ++;
        alt_e = alturaAVL(pt->esq, dscr);
        alt_d = alturaAVL(pt->dir, dscr);

        return ((alt_e - alt_d < 2)
            && (alt_d - alt_e < 2)
            && (isAVL(pt->esq, dscr))
            && (isAVL(pt->dir, dscr)));
    }

}

//  Rotacao Simples Direita
AVLNode *rotD(AVLNode *pt, descritor *dscr) {

    AVLNode *ptu;

    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->fator = 0;
    pt = ptu;

    dscr->rotacoes += 1;

    return pt;

}

//  Rotacao Simples Esquerda
AVLNode *rotE(AVLNode *pt, descritor *dscr) {

    AVLNode *ptu;

    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->fator = 0;
    pt = ptu;

    dscr->rotacoes += 1;

    return pt;

}

//  Rotacao Dupla Direita
AVLNode *rotDD(AVLNode *pt, descritor *dscr) {

    AVLNode *ptu, *ptv;

    ptu = pt->esq;
    ptv = ptu->dir;

    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;

    if (ptv->fator == 1) {
        dscr->comparacoes ++;
        pt->fator = -1;
    } else {
        dscr->comparacoes ++;
        pt->fator = 0;
    }
    if (ptv->fator == -1) {
        dscr->comparacoes ++;
        ptu->fator = 1;
    } else {
        dscr->comparacoes ++;
        ptu->fator = 0;
    }

    pt = ptv;

    dscr->rotacoes += 2;

    return pt;

}

//  Rotacao Dupla Esquerda
AVLNode *rotDE(AVLNode *pt, descritor *dscr) {

    AVLNode *ptu, *ptv;

    ptu = pt->dir;
    ptv = ptu->esq;

    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;

    if (ptv->fator == -1) {
        pt->fator = 1;
    } else {
        pt->fator = 0;
    }
    if (ptv->fator == 1) {
        ptu->fator = -1;
    } else {
        ptu->fator = 0;
    }

    pt = ptv;

    dscr->rotacoes += 2;

    return pt;

}

AVLNode *caso1(AVLNode *pt, descritor *dscr, int *cond) {

    AVLNode *ptu;

    ptu = pt->esq;
    if(ptu->fator == 1) {
        dscr->comparacoes ++;
        pt = rotD(pt, dscr);
    }else{
        dscr->comparacoes ++;
        pt = rotDD(pt, dscr);
    }

    pt->fator = 0;
    *cond = 0;

    return pt;

}

AVLNode *caso2(AVLNode *pt, descritor *dscr, int *cond) {

    AVLNode *ptu;

    ptu = pt->dir;

    if(ptu->fator == -1) {
        dscr->comparacoes ++;
        pt = rotE(pt, dscr);
    }else{
        dscr->comparacoes ++;
        pt = rotDE(pt, dscr);
    }

    pt->fator = 0;
    *cond = 0;

    return pt;

}

AVLNode *insereAVL(AVLNode *pt, char txt[MAX_PALAVRA], descritor *dscr, int *cond) {

    if(pt == NULL) {

        pt = (AVLNode *) malloc(sizeof(AVLNode));
        strcpy(pt->texto, txt);
        pt->esq = NULL;
        pt->dir = NULL;
        pt->fator = 0;
        pt->freq = 1;
        *cond = 1; //inseriu novo nodo, arvore creseu, pode ter desbalanceado

        dscr->comparacoes += 1;
        dscr->nodos += 1;

    } else if((strcmp(txt, pt->texto) < 0)) {

        pt->esq = insereAVL(pt->esq, txt, dscr, cond);

        // veririca se voltou com cod. cond. ativo
        if(*cond) {
            switch (pt->fator) {
                case -1:
                    pt->fator = 0;
                    *cond = 0;
                    break;
                case 0:
                    pt->fator = 1;
                    break;
                case 1:
                    pt = caso1(pt, dscr, cond);
                    break;
            }
        }

        dscr->comparacoes += 1;

    }else if((strcmp(txt, pt->texto) > 0)) {

        pt->dir = insereAVL(pt->dir, txt, dscr, cond);

        if(*cond) {
            switch (pt->fator) {
                case 1:
                    pt->fator = 0;
                    *cond = 0;
                    break;
                case 0:
                    pt->fator = -1;
                    break;
                case -1:
                    pt = caso2(pt, dscr, cond);
                    break;
            }
        }

        dscr->comparacoes += 1;

    }else{

        // ja contem

        *cond = 0;

        pt->freq += 1;
        dscr->comparacoes += 1;

    }

    return pt;
}