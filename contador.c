#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#include "avl.h"
#include "abp.h"
#include "abf.h"

#define MAX_LINHA 1000
#define AVL 1
#define ABP 2

char *strlwr(char *str)
{
    unsigned char *p = (unsigned char *)str;

    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}

int readInput(char nome[], tipoABP **abp, AVLNode **avl, int modo, descritor *dscr) // ..., tipoAVL *avl, tipoABP *abp);
{

  char separador[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t─"};
  char *palavra, linha[MAX_LINHA];
  int cond = 0;            //controle rotacao AVL
  FILE *arq;

  arq = fopen(nome, "r");
  if (arq == NULL)
    //ERRO AO ABRIR ARQUIVO TEXTO DE ENTRADA
    return 1;

  while (fgets(linha, MAX_LINHA, arq))
  {
      palavra = strtok(linha, separador);;

      while(palavra)
      {
        if (modo == AVL) {
            *avl = insereAVL(*avl, strlwr(palavra), dscr, &cond);
        }
        if (modo == ABP)
            *abp = insereABP(*abp, strlwr(palavra), dscr);
        palavra = strtok(NULL, separador);
      }
  }

  fclose(arq);
  return 0;
}

int parseOps(tipoABP *abp, AVLNode *avl, ABFreq *abf, char nome_entrada[], FILE *output, int modo, descritor *dscr){ //..., tipoAVL *avl, tipoABP *abp)
  char separador[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t\r─"};
  char *operador, *ops[5], linha[MAX_LINHA];
  char str_aux[MAX_PALAVRA];
  int freq = 0;
  char str_auxchr [MAX_PALAVRA];
  FILE *input;

  input = fopen(nome_entrada, "r");

  if (input==NULL)
    //ERRO AO ABRIR ARQUIVOS
    return 1;

  while (fgets(linha,MAX_LINHA,input)) {
    operador = strtok(linha, separador);
    while (operador)
    {
      switch (operador[0]) {
        case 70:  // F
        case 102: // f
        //frequencia

          ops[0] = strtok(NULL, separador);

          if (modo == AVL)
              freq = freqAVL(avl, ops[0], dscr);
          if (modo == ABP)
              freq = freqABP(abp, ops[0], dscr);

          fprintf(output, "\n\t\t[Frequencia de %s: %d]\n", ops[0], freq);
          printf("\n\t\t[Frequência de %s: %d]\n", ops[0], freq);
          break;
        case 67:
        case 99:
        //contador

          ops[0] = strtok(NULL, separador);
          ops[1] = strtok(NULL, separador);

          fprintf(output, "\n\n\t\t[Contador %d:%s]\n", atoi(ops[0]), ops[1]);
          printf("\n\n\t\t[Contador %d:%s]\n", atoi(ops[0]), ops[1]);
          buscaPorRange(abf, atoi(ops[0]), atoi(ops[1]), output);

          break;
      }
      operador = strtok(NULL, separador);
    }
  }
  fclose(input);
  return 0;
}


int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{
    int modo;
    tipoABP *abp;

    AVLNode *avl;
    avl = NULL;

    ABFreq *abf;
    abf = NULL;

    time_t t0, tf;
    descritor dscr;
    inicializaDscr(&dscr);
    setlocale(LC_ALL,"Portuguese_Brasil"); //para imprimir corretamente na tela os caracteres acentuados
    abp = NULL;

    FILE *output;

    output = fopen(argv[3], "w");

    if (output==NULL)
        //ERRO AO ABRIR ARQUIVOS
        return 1;

    if (argc!=4)  //o numero de parametros esp1erado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf ("Numero incorreto de parametros.\n Para chamar o programa digite: ./contador <arq_entrada> <arq_ops> <arq_saida>\n");
        return 1;
    }

    printf("Escolha o modo desejado:\n1 - AVL, 2 - ABP: \n");
    scanf("%d", &modo);
    while (modo!=AVL && modo!=ABP)
    {
      printf("Modo invalido\n");
      printf("Escolha o modo desejado:\n1 - AVL, 2 - ABP\n:");
      scanf("%d", &modo);
    }
    time(&t0);
    if(readInput(argv[1], &abp, &avl, modo, &dscr))
    {
      printf("Erro ao abrir arquivo de entrada\n");
      return 1;
    }

    if(modo == AVL) {
        AVLpopulaABF(&abf, avl, &dscr);
    }else if(modo == ABP) {
        ABPpopulaABF(&abf, abp, &dscr);
    }

    time(&tf);
    dscr.tempo_geracao = difftime(tf, t0);

    fprintf(output, "\n\n[Relatorio]===========================");

    if(modo == AVL) {

        fprintf(output, "\n\n\t[Estatisticas AVL]=======================\n\n");
        fprintf(output, "\t\t[Rotacoes: %d]\n", dscr.rotacoes);
        fprintf(output, "\t\t[Comparacoes: %d]\n", dscr.comparacoes);
        fprintf(output, "\t\t[Nodos: %d]\n", dscr.nodos);
        fprintf(output, "\t\t[Altura: %d]\n", calcMaiorAlturaAVL(avl, &dscr));
        fprintf(output, "\t\t[Fator: %d]\n", calcMaiorFatorAVL(avl, &dscr));
        fprintf(output, "\t\t[Tempo de Geracao: %.5fs]", dscr.tempo_geracao);
        fprintf(output, "\n\n\t=========================================");

    } else if(modo == ABP) {

        fprintf(output, "\n\n\t[Estatisticas ABP]=======================\n\n");
        fprintf(output, "\t\t[Comparacoes: %d]\n", dscr.comparacoes);
        fprintf(output, "\t\t[Nodos: %d]\n", dscr.nodos);
        fprintf(output, "\t\t[Altura: %d]\n", calcMaiorAlturaABP(abp, &dscr));
        fprintf(output, "\t\t[Tempo de Geracao: %.5fs]", dscr.tempo_geracao);
        fprintf(output, "\n\n\t=========================================");

    }

    fprintf(output, "\n\n\t[Operacoes]==============================\n\n");
    if(parseOps(abp, avl, abf, argv[2], output, modo, &dscr))
    {
      printf("\t\t[!]Erro ao processar operações.");
    }
    fprintf(output, "\n\n\t=========================================\n\n");

    fprintf(output, "\n\n=================================================\n\n");


    fclose(output);
    printf("Arquivo %s gerado com sucesso.\n", argv[3]);
    return 0;
}
