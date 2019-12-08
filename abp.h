#include "descritor.h"
#define MAX_PALAVRA 50

#ifndef ABP_H
#define ABP_H

struct _ABP{
  char palavra[MAX_PALAVRA];
  int frequencia;
  struct _ABP *esq;
  struct _ABP *dir;
}; typedef struct _ABP tipoABP;

tipoABP* insereABP(tipoABP *a, char plvr[], descritor *dscr);
int freqABP(tipoABP *a, char plvr[], descritor *dscr);
int alturaABP(tipoABP *pt, descritor *dscr);
int calcMaiorAlturaABP(tipoABP *pt, descritor *dscr);
#endif
