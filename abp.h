#include "descritor.h"
#define MAX_PALAVRA 50

struct _ABP{
  char palavra[MAX_PALAVRA];
  int frequencia;
  struct _ABP *esq;
  struct _ABP *dir;
}; typedef struct _ABP tipoABP;

tipoABP* insereABP(tipoABP *a, char plvr[], descritor *dscr);
tipoABP* inicializa();
