/*
* @file   : codA.c
* @author : Camilo Donoso
*           Loreto Romero
* @date   : 06/11/2020
* @brief  : Código para tarea 01 en ELO 321, semestre 2020-2
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc; char* argv[]) {
  
  /* Controlar el correcto paso de argumentos por linea de comandos */
  if (argc != 2) {
    printf("Error al ejecutar %s.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Guardar localmente numero recibido y controlar si es positivo*/
  int num;
  num = atoi(argv[1]);
  if (num<=0) {
    printf("El número ingresado no es positivo.\n");
    exit(EXIT_FAILURE);
  }

  /* Generar procesos hijos */


  /* Llamadas a sistema pidiendo hora y fecha de ejecucion del programa */
  struct timespec T1;
  T1.tv_sec = ;
  T1.tv_nsec = ;
  int hora = clock_gettime(CLOCK_REALTIME, &T1);
  if (hora == -1) {
    printf("Error al retornar la hora.\n");
    exit(EXIT_FAILURE);
  }


  /* Imprimir hora y fecha */
  printf("Hora: %d", hora);

}