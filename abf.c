#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "abp.h"
#include "abf.h"

ABFreq *insereABF(ABFreq *pt, int freq, char txt[MAX_PALAVRA], descritor *dscr) {

    if(pt == NULL) {

        //insere
        dscr->comparacoes ++;
        pt = (ABFreq*) malloc(sizeof(ABFreq));
        pt->freq = freq;
        strcpy(pt->texto, txt);
        pt->esq = NULL;
        pt->dir = NULL;
        return pt;

    }else{

        if(freq < pt->freq) {
            dscr->comparacoes ++;
            pt->esq = insereABF(pt->esq, freq, txt, dscr);
            return pt;
        }else{
            // >=
            dscr->comparacoes ++;
            pt->dir = insereABF(pt->dir, freq, txt, dscr);
            return pt;
        }

    }

}

void AVLpopulaABF(ABFreq **abf, AVLNode *avl, descritor *dscr) {

    if(avl == NULL) {
        dscr->comparacoes ++;
        return;
    }else{
        dscr->comparacoes ++;
        *abf = insereABF(*abf, avl->freq, avl->texto, dscr);
        AVLpopulaABF(abf, avl->esq, dscr);
        AVLpopulaABF(abf, avl->dir, dscr);
    }

}

void ABPpopulaABF(ABFreq **abf, tipoABP *abp, descritor *dscr) {

    if(abp == NULL) {
        dscr->comparacoes ++;
        return;
    }else{
        dscr->comparacoes ++;
        *abf = insereABF(*abf, abp->frequencia, abp->palavra, dscr);
        ABPpopulaABF(abf, abp->esq, dscr);
        ABPpopulaABF(abf, abp->dir, dscr);
    }

}

void buscaPorRange(ABFreq *abf, int min, int max, FILE *output) {

    if(abf != NULL) {
        if(abf->freq >= min) {
            if(abf->freq <= max) {
                buscaPorRange(abf->esq, min, max, output);
                fprintf(output, "\n\t\t\t%s  ::  %d", abf->texto, abf->freq);
                printf("\n\t\t\t%s  ::  %d", abf->texto, abf->freq);
                buscaPorRange(abf->dir, min, max, output);
            }else{
//                printf("\n>");
                buscaPorRange(abf->esq, min, max, output);
            }
        }else{
//            printf("\n<");
            buscaPorRange(abf->dir, min, max, output);
        }
    }
    return;
}

int alturaABP(tipoABP *pt, descritor *dscr) {

    int alt_e, alt_d;

    if(pt == NULL) {
        dscr->comparacoes ++;
        return 0;
    }else{
        dscr->comparacoes ++;
        alt_e = alturaABP(pt->esq, dscr);
        alt_d = alturaABP(pt->dir, dscr);
        if(alt_e > alt_d) {
            return (1 + alt_e);
        }else{
            return (1 + alt_d);
        }
    }

}

int calcMaiorAlturaABP(tipoABP *pt, descritor *dscr) {
    int maior = 0;
    if(pt == NULL) {
        dscr->comparacoes ++;
        return 0;
    }else{
        if(alturaABP(pt, dscr) > maior) {
            dscr->comparacoes ++;
            maior = alturaABP(pt, dscr);
        }
        calcMaiorAlturaABP(pt->esq, dscr);
        calcMaiorAlturaABP(pt->dir, dscr);
        return maior;
    }
}