#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "abp.h"

tipoABP* insereABP(tipoABP *a, char plvr[], descritor *dscr)
{
  if (a == NULL)
  {
    printf("bota");
    a = (tipoABP*)malloc(sizeof(tipoABP*));
    a->esq = NULL;
    a->dir = NULL;
    strcpy(a->palavra, plvr);
    dscr->nodos += 1;
    dscr->comparacoes += 1;
    a->frequencia = 0;
    printf(" boto");
    return a;
  }
  if (strcmp(plvr, a->palavra)>0)
  {
    printf("o porra ");
    dscr->comparacoes += 1;
    a->esq = insereABP(a->esq, plvr, dscr);
    return a;
  }
  if(strcmp(plvr, a->palavra)<0)
  {
    printf("a porro ");
    dscr->comparacoes += 1;
    a->dir = insereABP(a->dir, plvr, dscr);
    return a;
  }

  dscr->comparacoes += 1;
  a->frequencia += 1;
  return a;
}
