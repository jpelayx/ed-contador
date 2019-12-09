// Usando Include Guard para evitar dupla inclusao

// Estrutaura descritor é usada para armezanar os numeros
// de insercoes, rotacoes, comparacoes, etc, que pode ser
// usado tanto por AVL quanto por ABP

#ifndef DESCRITOR_H
#define DESCRITOR_H

typedef struct{
  int nodos, comparacoes, rotacoes, altura, fator;
  double tempo_geracao;
} descritor;

void inicializaDscr(descritor *dscr);

#endif