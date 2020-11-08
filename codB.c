/*
* @file     : codB.c
* @author   : Loreto Romero Ponce
*             Camilo Donoso Collao
* @date     : 06/11/202
* @brief    : Código para tarea 01 de ELO321, semestre 2020 -2
*             Corresponde a la parte B, preguntas 0, 1 y 2.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/* Variables globales*/
float avg_value;
int min_value;
int max_value;
int numArray[50];

/* Funciones */
void* return_Avg(void *arg);
void* return_Min(void *arg);
void* return_Max(void *arg);

/* Mutex lock */
pthread_mutex_t lock; 

int main()
{
  /* Se inicia el arreglo con 50 numeros aleatorios */
  int i;
  for (i = 0 ; i < 50 ; i++ ){
    numArray[i] = rand() % 100;
  }
    
  /* ID de los hilos */
  pthread_t threadID[3];

  /* Se cream 3 hilos */
  pthread_create(&threadID[0], NULL, return_Avg, NULL);
  pthread_create(&threadID[1], NULL, return_Min, NULL);
  pthread_create(&threadID[2], NULL, return_Max, NULL);

  /* El proceso padre espera a todos los hilos */
  for (i = 0 ; i < 3 ; i++ ){
    pthread_join(threadID[i], NULL);
  }

  /* Se imprimen los valores */
  printf("Valor promedio = %f\n", avg_value);
  printf("Valor mínimo = %i\n", min_value);
  printf("Valor máximo = %i\n", max_value);

  return 0;

}


void* return_Avg(void *arg){
  int tmp = 0;

  /* Se calcula la suma de todos los elementos del arreglo */
  int i;
  for (i = 0 ; i < 50 ; i++){
    tmp = tmp + numArray[i];
  }

  /* Se utilizó mutex cuando los hilos modifican las variables globales */
  pthread_mutex_lock(&lock); // Entry section

  /* Critical section */
  avg_value = tmp/50.0; /* Se calcula el promedio */
  pthread_mutex_unlock(&lock); /* Exit section */

  /* Remainder section */
  printf("Thread ID: %lu calculó promedio\n",pthread_self());
  pthread_exit(NULL); /* Termina el hilo */
}

void* return_Min(void *arg){
  int tmp = numArray[0];

  /* Ciclo for para buscar el valor mínimo del arreglo */
  int i;
  for (i = 0 ; i < 50 ; i++){
    if (tmp > numArray[i]) tmp = numArray[i];
  }

  pthread_mutex_lock(&lock); /* Entry section */

  /* Critical section */
  min_value = tmp;
  pthread_mutex_unlock(&lock); /* Exit section */

  /* Remainder section */
  printf("Thread ID: %lu calculó valor mínimo\n",pthread_self());
  pthread_exit(NULL);
}

void* return_Max(void *arg){
  int tmp = numArray[0];

  /* Ciclo for para buscar el valor máximo del arreglo */
  int i;
  for (i = 0 ; i < 50 ; i++){
    if (tmp < numArray[i]) tmp = numArray[i];
  }

  pthread_mutex_lock(&lock);  /* Entry section */

  /* Critical section */
  max_value = tmp;
  pthread_mutex_unlock(&lock);  /* Exit section */

  /* Remainder section */
  printf("Thread ID: %lu calculó valor máximo\n",pthread_self());
  pthread_exit(NULL);
}

