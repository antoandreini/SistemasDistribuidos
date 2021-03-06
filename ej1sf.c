//Ejercicio 1 Secuencial
#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>

//Preguntas
// al inicializar A es necesario poner una ordenada por columna y otra por filas?
//Como hago la matriz transpuesta

//Variable para tiempo
double dwalltime();

//Funcion para calcular el tiempo
double dwalltime(){
	double sec;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	sec = tv.tv_sec + tv.tv_usec/1000000.0;
	return sec;
}

int main(int argc,char*argv[]){
 
  //Controla los argumentos al programa
   if (argc < 2){
   	printf("\n Faltan argumentos:: N dimension de la matriz, T cantidad de threads \n");
   	return 0;
   }
  //variables  
   double *A,*At,*R;
   int i,j,k,N;
   int check=1;
   double timetick;
   N=atoi(argv[1]);
 
   //Aloca memoria para las matrices
   A=(double*)malloc(sizeof(double)*N*N);
   R=(double*)malloc(sizeof(double)*N*N);

   //Inicializa las matriZ A en 1, el resultado sera una matriz R con todos sus valores en N
   for(i=0;i<N;i++){
   	for(j=0;j<N;j++){
       	A[i*N+j]=1;
   	}
   }

   timetick = dwalltime();
   //Realiza la multiplicacion
 
   for(i=0;i<N;i++){
   	for(j=0;j<N;j++){
        	R[i*N+j]=0;
       	for(k=0;k<N;k++){
           	R[i*N+j]= R[i*N+j] + A[k*N+i]*A[k*N+j];
        	}
    	}
   }  
   printf("Tiempo en segundos %f \n", dwalltime() - timetick);

   //Verifica el resultado
   for(i=0;i<N;i++){
   	for(j=0;j<N;j++){
       	check=check&&(R[i*N+j]==N);
   	}
   }  
   if(check){
   	printf("Multiplicacion de matrices resultado correcto\n");
   }else{
   	printf("Multiplicacion de matrices resultado erroneo\n");
   }
   free(A);
   free(R);
 
   return(0);
}
