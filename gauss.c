#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#define EPSILON 0.000001

double **alocaMatriz(int l, int c){
    /*
    Se houver memória disponível, aloca uma matriz bidimensional
    de double com l linhas e c colunas, e devolve um ponteiro para 
    essa matriz.
    Caso contrário, devolve um ponteiro nulo.
    */

   int i, j;
   double **m;
   m = malloc(sizeof(m)*l);
   if (m == NULL)
   {
       return NULL;    //Faltou memória
   }
   for (i = 0; i < l; i++)
   {
       m[i] = malloc(sizeof(double)*c);
       if (m[i] == NULL)    //Faltou memória
       {
           for (j = 0; j < i; j++)
           {
               free(m[j]);
           }
           free(m);
           return NULL;
       }
   }
   return m;    //Fim da função alocaMatriz.
}   // Fim da função alocaMatriz.

void leMatriz(double **m, int l, int c){
    /* 
    Lê valores de uma matriz de doubles, alocada dinâmicamente, com
    l linhas e c colunas.
     */
    int i, j;
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {    
            printf("M[%d][%d]: ", i+1, j+1);
            scanf("%lf", &m[i][j]);
        }
    }
}   // Fim da função leMatriz.

void imprimeMatriz(double **m, int l, int c){
    /* Imprime uma matriz de double, com l linhas e c colunas. */

    int i, j;
    for (i = 0; i < l; i++)
    {
        for(j = 0; j < c; j++)
        {
            printf("%10.4lf ", m[i][j]);
        }
        printf("\n");
    }
}   // Fim de imprimeMatriz.

void Gauss(double **m, int n) {
    /* Recebe M, a matriz aumentada de um SL com n variáveis
    *  e transforma m na matriz aumentada de umm SL TS equivalente.
    */
   int i, j, k;
   double mult, *aux;

   for (int i = 0; i < n-1; i++)
   {
       if(m[i][i] == 0) {
           j = i + 1;

           while (j<n && m[j][i]==0) {
               j++;
           }

           if (j<n) {
               aux = m[i];
               m[i] = m[j];
               m[j] = aux;
           }
       }

       if(m[i][i] != 0) {
           for(j=i+1; j<n; j++) {
               mult = -m[j][i]/m[i][i];
               m[j][i] = 0;
               for(k=i+1; k<=n; k++) {
                   m[j][k] += mult * m[i][k];
               }
           }
       }
   }
   
}   // Fim de Gauss

int sretro (double **M, int n, double X[]){
    /*Recebe M, a matriz aumentada  de um SL TS com n variáveis. 
    Se o SL for indeterminado, coloca um X na solução de SL e devolve 0;
    Se for determinado, coloca em X uma solução e devolve 1; 
    Se for incompatível devolve 2
    */ 

	int i, j, tipo = 0;
	double soma;
	for (i = n-1; i>=0; i--){
		soma = 0;
		for (j=i+1; j-n; j++){
			soma = soma + M[i][j] * X[j];
		}
		if (M[i][i] == 0){
			if(fabs(M[i][n] - soma) < EPSILON){ /* Xi é variável livre */
				tipo = 1;
				X[i] = 0;
			}
			else { 
				return 2;
			}	
		}
		else {
			X[i] = (M[i][n] - soma) / M[i][i];
		}
	}
	return tipo;	
} // Fim sretro

int main(){
    int n, i, tipo;
    double **a, *x;

    printf("Quantidade de variáveis: ");
    scanf("%d", &n);

    a = alocaMatriz(n, n+1);
    if (a == NULL) { //Sem memória disponível.
        printf("Deu pau.\n Falta de memória.");
        return 1;
    }
    x = malloc(sizeof(double)*n);

    leMatriz(a, n, n+1);
    printf("\n");
    imprimeMatriz(a, n, n+1);
    Gauss(a, n);
    printf("SL TS: \n");
    imprimeMatriz(a, n, n+1);
    tipo = sretro(a, n, x);
	if(tipo == 2){
		printf("SL Imcompativel!");
	}
	else{
		printf("\nSL %sDETERMINADO\n\n", tipo ? "IN" : "");
		for(i = 0; i < n; i++){
			printf("X[%d]: %10.4lf\n", i+1, x[i]);
		}
	}
    return 0;
    
}   // Fim do main.
