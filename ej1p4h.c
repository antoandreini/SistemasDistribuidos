#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

//Dimension por defecto de las matrices
int N, elementosThread,numthread;
double *A, *At,*R;


//Para calcular tiempo
double dwalltime(){
   	double sec;
   	struct timeval tv;
   	gettimeofday(&tv,NULL);
   	sec = tv.tv_sec + tv.tv_usec/1000000.0;
   	return sec;
}

void* multiplicacion(void *id){
   int idLocal = *(int*)id;
   int posInicial = idLocal*elementosThread;
   int posFinal = (idLocal+1)*elementosThread;
   for(int i=posInicial;i<posFinal;i++){
 	   for(int j=0;j<N;j++){
           R[i*N+j]=0;
           for(int k=0;k<N;k++){
               R[i*N+j]+=A[i*N+k]*At[k+j*N];
           }
 	   }
   }
   pthread_exit(NULL);
}


int main(int argc,char*argv[]){
int i,j,k;
int check=1;
double timetick, temp;
pthread_t T[4];
int threads[4];


//Controla los argumentos al programa
   if (argc < 3){
   	printf("\n Faltan argumentos:: N dimension de la matriz, T cantidad de threads \n");
   	return 0;
   }

N= atoi(argv[1]);
numthread= atoi(argv[4]);

//Aloca memoria para las matrices
 A=(double*)malloc(sizeof(double)*N*N);
 At=(double*)malloc(sizeof(double)*N*N);
 R=(double*)malloc(sizeof(double)*N*N);
 

//Inicializa las matrices A y B en 1, el resultado sera una matriz con todos sus valores en N
 for(i=0;i<N;i++){
  for(j=0;j<N;j++){
	A[i*N+j]=1;
	At[i*N+j]=1;
  }
 }  


//con dos hilos
  timetick = dwalltime();

  //Genera matriz traspuesta
	  for(i=0;i<N;i++){
	   for(j=i+1;j<N;j++){
			temp = At[i*N+j];
			At[i*N+j]= At[j*N+i];
			At[j*N+i]= temp;
	   }
	  }   
  elementosThread = N/4;
  for (int id=0;id<4; id++){  //crea 4 threads
     threads[id]=id;
     pthread_create(&T[id],NULL,&multiplicacion,(void*)&threads[id]);
 }
 pthread_join(T[0],NULL);
 pthread_join(T[1],NULL);

printf("Tiempo en segundos con 4 pthreads %f\n", dwalltime() - timetick);

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
}

