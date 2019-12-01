// Usando Include Guard para evitar dupla inclusao

#ifndef DESCRITOR_H
#define DESCRITOR_H

typedef struct{
  int nodos, comparacoes, rotacoes, altura, fator;
  double tempo_geracao;
} descritor;

void inicializaDscr(descritor *dscr);

#endif