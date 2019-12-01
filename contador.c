#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "avl.h"
#include "abp.h"

#define MAX_LINHA 1000
#define AVL 1
#define ABP 2

int readInput(char nome[], tipoABP *abp, AVLNode **avl, int modo, descritor *dscr) // ..., tipoAVL *avl, tipoABP *abp);
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
      palavra = strtok(linha, separador);
      while(palavra)
      {
        if (modo == AVL) {
            *avl = insereAVL(*avl, palavra, dscr, &cond);
        }
        if (modo == ABP)
          abp = insereABP(abp, palavra, dscr);
//        printf("%s\n", palavra);
        palavra = strtok(NULL, separador);
      }
  }

  fclose(arq);
  return 0;
}

int parseOps(AVLNode *avl, char nome_entrada[], char nome_saida[], int modo){ //..., tipoAVL *avl, tipoABP *abp)
  char separador[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t─"};
  char *operador, *ops[5], linha[MAX_LINHA];
  int freq = 0;
  char str_aux [MAX_PALAVRA];
  FILE *input, *output;

  input = fopen(nome_entrada, "r");
  output = fopen(nome_saida, "w");

  if (input==NULL || output==NULL)
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
          strcpy(str_aux, ops[0]);


          // a string op[0] vem quebrada de algum jeito bizarro que quebra linha e faz doidera


          printf("\n\t%s", str_aux);

          if (modo == AVL)
              freq = freqAVL(avl, ops[0]);
          //if (modo == ABP)
          //freq = frequencia(arv, palavra)

          printf("\nFrequência de %s: %d\n", str_aux, freq);

          break;
        case 67:
        case 99:
        //contador
          ops[0] = strtok(NULL, separador);
          ops[1] = strtok(NULL, separador);
          //if(modo == AVL)
          //if(modo == ABP) ou um switch sei la
          //contador(arv,ops[0], ops[1])
          printf("\n\nContador %s, %s\n",ops[0], ops[1]);
          break;
      }
      operador = strtok(NULL, separador);
    }
  }
  fclose(input);
  fclose(output);
  return 0;
}


int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{
    int modo;
    tipoABP *abp;
    AVLNode *avl = NULL;
    time_t t0, tf;
    descritor dscr;
    inicializaDscr(&dscr);
    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados
    abp = NULL;

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
    if(readInput(argv[1], abp, &avl, modo, &dscr))
    {
      printf("Erro ao abrir arquivo de entrada\n");
      return 1;
    }

    time(&tf);
    dscr.tempo_geracao = difftime(tf, t0);
    printf("\nTempo: %f\n", dscr.tempo_geracao);

    if(parseOps(avl, argv[2], argv[3], modo))
    {
      printf("Erro ao processar operacoes\n");
    }

    printf("Arquivo %s gerado com sucesso\n", argv[3]);
    return 0;
}
