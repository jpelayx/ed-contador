#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "abp.h"

tipoABP* insereABP(tipoABP *a, char plvr[], descritor *dscr)
{
  if (a == NULL)
  {
    a = (tipoABP*)malloc(sizeof(tipoABP));
    a->esq = NULL;
    a->dir = NULL;
    strcpy(a->palavra, plvr);

    dscr->nodos += 1;
    dscr->comparacoes += 1;

    a->frequencia = 1;
    return a;
  } else if (strcmp(plvr, a->palavra)>0) {
    dscr->comparacoes += 1;
    a->dir = insereABP(a->dir, plvr, dscr);
    return a;
  } else if(strcmp(plvr, a->palavra)<0) {
    dscr->comparacoes += 1;
    a->esq = insereABP(a->esq, plvr, dscr);
    return a;
  } else if(strcmp(plvr, a->palavra) == 0) {
      a->frequencia ++;
      dscr->comparacoes ++;
      return a;
  }
  return a;
}

int freqABP(tipoABP *a, char plvr[], descritor *dscr) {

    if(a == NULL) {
        dscr->comparacoes ++;
        return 0;
    }else{
        dscr->comparacoes ++;
        if(strcmp(plvr, a->palavra) < 0) {
            dscr->comparacoes ++;
            freqABP(a->esq, plvr, dscr);
        }else if(strcmp(plvr, a->palavra) > 0){
            dscr->comparacoes ++;
            freqABP(a->dir, plvr, dscr);
        }else{
            dscr->comparacoes ++;
            return a->frequencia;
        }
    }

}
