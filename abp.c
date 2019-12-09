#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "abp.h"

// Função de inserção

tipoABP* insereABP(tipoABP *a, char plvr[], descritor *dscr)
{
  if (a == NULL)
  {

      // Inserção

    a = (tipoABP*)malloc(sizeof(tipoABP));
    a->esq = NULL;
    a->dir = NULL;
    strcpy(a->palavra, plvr);

    dscr->nodos += 1;
    dscr->comparacoes += 1;

    a->frequencia = 1;
    return a;
  } else if (strcmp(plvr, a->palavra)>0) {

      // ->

    dscr->comparacoes += 1;
    a->dir = insereABP(a->dir, plvr, dscr);
    return a;


  } else if(strcmp(plvr, a->palavra)<0) {

      // <-

    dscr->comparacoes += 1;
    a->esq = insereABP(a->esq, plvr, dscr);
    return a;
  } else if(strcmp(plvr, a->palavra) == 0) {

      // ja existe, incrementa frequencia

      a->frequencia ++;
      dscr->comparacoes ++;
      return a;
  }
  return a;
}

// Retorna a frequencia do nodo que possui a palavra entrada

int freqABP(tipoABP *a, char plvr[], descritor *dscr) {

    if(a == NULL) {
	// Palavra não encontrada
        dscr->comparacoes ++;
        return 0;
    }else{
        dscr->comparacoes ++;
        if(strcmp(plvr, a->palavra) < 0) {
	    // Palavra está à esquerda
            dscr->comparacoes ++;
            freqABP(a->esq, plvr, dscr);
        }else if(strcmp(plvr, a->palavra) > 0){
	    // Palavra está à direita
            dscr->comparacoes ++;
            freqABP(a->dir, plvr, dscr);
        }else{
	    // Palavra encontrada
            dscr->comparacoes ++;
            return a->frequencia;
        }
    }

}

// Calcula a altura de um nodo da ABP

int alturaABP(tipoABP *pt, descritor *dscr) {

    int alt_e, alt_d;

    if(pt == NULL) {

	// Nodo vazio
        dscr->comparacoes ++;
        return 0;
    }else{
        dscr->comparacoes ++;
	// Calcula altura recursivamente
        alt_e = alturaABP(pt->esq, dscr);
        alt_d = alturaABP(pt->dir, dscr);
        if(alt_e > alt_d) {
            return (1 + alt_e);
        }else{
            return (1 + alt_d);
        }
    }

}

// Encontra o valor da maior altura da ABP que, por definição,
// é a altura da árvore.

int calcMaiorAlturaABP(tipoABP *pt, descritor *dscr) {
    int maior = 0;
    if(pt == NULL) {
        dscr->comparacoes ++;
        return 0;
    }else{
        if(alturaABP(pt, dscr) > maior) {
	    // Substitui valor de maior
            dscr->comparacoes ++;
            maior = alturaABP(pt, dscr);
        }
	// Recursões
        calcMaiorAlturaABP(pt->esq, dscr);
        calcMaiorAlturaABP(pt->dir, dscr);
        return maior;
    }
}
