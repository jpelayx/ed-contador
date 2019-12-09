#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "abp.h"
#include "abf.h"

// Insercao ordenada por frequencia, gera uma ABP

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
	    // Nodo deve ser inserido à esquerda
            dscr->comparacoes ++;
            pt->esq = insereABF(pt->esq, freq, txt, dscr);
            return pt;
        }else{
	    // Nodo deve ser inserido à direita
            dscr->comparacoes ++;
            pt->dir = insereABF(pt->dir, freq, txt, dscr);
            return pt;
        }

    }

}

// Popular a ABF com os nodos recebidos da AVL gerada
// Entram na arvore apenas a freq e a palavra

void AVLpopulaABF(ABFreq **abf, AVLNode *avl, descritor *dscr) {

    if(avl == NULL) {
        dscr->comparacoes ++;
        return;
    }else{
        dscr->comparacoes ++;
        *abf = insereABF(*abf, avl->freq, avl->texto, dscr);
	// Recursões
        AVLpopulaABF(abf, avl->esq, dscr);
        AVLpopulaABF(abf, avl->dir, dscr);
    }

}

// Popular a ABF com os nodos recebidos da ABP gerada
// Entram na arvore apenas a freq e a palavra

void ABPpopulaABF(ABFreq **abf, tipoABP *abp, descritor *dscr) {

    if(abp == NULL) {
        dscr->comparacoes ++;
        return;
    }else{
        dscr->comparacoes ++;
        *abf = insereABF(*abf, abp->frequencia, abp->palavra, dscr);
	// Recursões
        ABPpopulaABF(abf, abp->esq, dscr);
        ABPpopulaABF(abf, abp->dir, dscr);
    }

}

// Caminhamento central, escrevendo direto no arquivo de saída.
// Resulta em uma ordem crescente de nodos com freq entre MIN até MAX no arquivo

void buscaPorRange(ABFreq *abf, int min, int max, FILE *output) {

    if(abf != NULL) {
        if(abf->freq >= min) {
            if(abf->freq <= max) {
		// Nodo dentro dos limites
                buscaPorRange(abf->esq, min, max, output);
                fprintf(output, "\n\t\t\t%s  ::  %d", abf->texto, abf->freq);
                buscaPorRange(abf->dir, min, max, output);
            }else{
		// Nodo com freq maior que MAX, vai pra esquerda
                buscaPorRange(abf->esq, min, max, output);
            }
        }else{
	    // Nodo atual é menor que MIN, vai pra direita
            buscaPorRange(abf->dir, min, max, output);
        }
    }
    return;
}
