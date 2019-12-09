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

// Funcao auxiliar para tornar todos caracteres de uma string minusculos
// Usado para ignorar diferenças entre maiúsculos e minúsculos

char *strlwr(char *str)
{
    unsigned char *p = (unsigned char *)str;

    // Transforma cada caractere individualmete em minusculo

    while (*p) {
	
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}

// Função para tratar o arquivo de entrada e inserir nodos na arvore seleciona

int readInput(char nome[], tipoABP **abp, AVLNode **avl, int modo, descritor *dscr)
{

  char separador[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t─"};
  char *palavra, linha[MAX_LINHA];
  int cond = 0; //controle rotacao AVL
  FILE *arq; // Arquivo de entrada que contem o texto à ser lido

  // Abre arquivo
  arq = fopen(nome, "r");
  if (arq == NULL)
    //ERRO AO ABRIR ARQUIVO TEXTO DE ENTRADA
    return 1;

  // Loop para ler nova linha enquanto não encontrou EOF
  while (fgets(linha, MAX_LINHA, arq))
  {
      // Usa definicao de separadores para definir palavras
      palavra = strtok(linha, separador);

      // Enquanto há palavras na "fila" da linha
      while(palavra)
      {

	// Insere na árvore selecionada
        if (modo == AVL) {
            *avl = insereAVL(*avl, strlwr(palavra), dscr, &cond);
        }
        if (modo == ABP) {
            *abp = insereABP(*abp, strlwr(palavra), dscr);
	}
	// Prepara para proxima iteração
        palavra = strtok(NULL, separador);
      }
  }

  fclose(arq);
  return 0;
}

// Função para tratar e executar operações
// Escreve resultados no arquivo de saida

int parseOps(tipoABP *abp, AVLNode *avl, ABFreq *abf, char nome_entrada[], FILE *output, int modo, descritor *dscr){

  char separador[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t\r─"};
  char *operador, *ops[5], linha[MAX_LINHA];
  char str_aux[MAX_PALAVRA];
  int freq = 0;
  char str_auxchr [MAX_PALAVRA];
  FILE *input;

  // Abre arquivo de operações
  input = fopen(nome_entrada, "r");

  if (input==NULL)
    //ERRO AO ABRIR ARQUIVOS
    return 1;

  // Loop para ler nova linha enquanto não encontrou EOF
  while (fgets(linha,MAX_LINHA,input)) {
    // Separa operador
    operador = strtok(linha, separador);
    while (operador)
    {
      // Identifica qual operação deve ser executada
      switch (operador[0]) {
        case 70:  // F
        case 102: // f
        //frequencia
	  
	  // Identifica operandos
          ops[0] = strtok(NULL, separador);

	  // Calcula frequencia de acordo com o tipo da árvore
          if (modo == AVL)
              freq = freqAVL(avl, ops[0], dscr);
          if (modo == ABP)
              freq = freqABP(abp, ops[0], dscr);

	  // Escreve resultado no arquivo de saida
          fprintf(output, "\n\t\t[Frequencia de %s: %d]\n", ops[0], freq);

          break;
        case 67:
        case 99:
        //contador

	  // Identifica intervalo
          ops[0] = strtok(NULL, separador);
          ops[1] = strtok(NULL, separador);

	  // Descreve começo do resultado no arq de saida 
          fprintf(output, "\n\n\t\t[Contador %d:%s]\n", atoi(ops[0]), ops[1]);
	  // Chama função que escreve resultados no arquivo e o fecha
          buscaPorRange(abf, atoi(ops[0]), atoi(ops[1]), output);

          break;
      }
      // Prepara para nova iteração
      operador = strtok(NULL, separador);
    }
  }
  // Fecha arquivo de operações e encerra função
  fclose(input);
  return 0;
}

// Função principal

int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{
    int modo;  // Variável que identificará tipo de estrutura escolhida

// Inicializa estruturas

    tipoABP *abp;
    abp = NULL;

    AVLNode *avl;
    avl = NULL;

    ABFreq *abf;
    abf = NULL;

    time_t t0, tf; // Variáveis responsáveis pelo cálculo de tempo

    descritor dscr; // Estrutura para controle de estatísticas da execução
    inicializaDscr(&dscr);

    setlocale(LC_ALL,"Portuguese_Brasil"); //para imprimir corretamente na tela os caracteres acentuados

// Identificação e inicialização do arquivo de saída
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

// Recebe tipo de estrutura da execução
    printf("Escolha o modo desejado:\n1 - AVL, 2 - ABP: \n");
    scanf("%d", &modo);
    while (modo!=AVL && modo!=ABP)
    {
      printf("Modo invalido\n");
      printf("Escolha o modo desejado:\n1 - AVL, 2 - ABP\n:");
      scanf("%d", &modo);
    }

    time(&t0); // Tempo inicial

// Ler e inserir palavras na estrutura
    if(readInput(argv[1], &abp, &avl, modo, &dscr))
    {
      printf("Erro ao abrir arquivo de entrada\n");
      return 1;
    }

// Popular árvore ordenada por frequência de acordo com a estrutura
// utilizada na execução 

    if(modo == AVL) {
        AVLpopulaABF(&abf, avl, &dscr);
    }else if(modo == ABP) {
        ABPpopulaABF(&abf, abp, &dscr);
    }

    time(&tf); // Tempo final
    // Calcular tempo de execução e guardar na estrutura "descritor"
    dscr.tempo_geracao = difftime(tf, t0);

// Inicio da escrita no arquivo de saida
    fprintf(output, "\n\n[Relatorio]===========================");


// Escrever estatísticas no arquivo de acordo com
// a estrutura escolhida
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

// Inicio da escrita de resultados das operações
    fprintf(output, "\n\n\t[Operacoes]==============================\n\n");

    // Função para executar operações
    if(parseOps(abp, avl, abf, argv[2], output, modo, &dscr))
    {
      // Erro ao executar operações
      printf("\t\t[!]Erro ao processar operações.");
    }

// Marca fim do arquivo
    fprintf(output, "\n\n\t=========================================\n\n");

    fprintf(output, "\n\n=================================================\n\n");


    fclose(output); // Fecha arquivo e encerra execução
    printf("\n[!] Arquivo %s gerado com sucesso.\n", argv[3]);
    return 0;
}
