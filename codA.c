/*
* @file   : codA.c
* @author : Camilo Donoso
*           Loreto Romero
* @date   : 06/11/2020
* @brief  : Código para tarea 01 en ELO 321, semestre 2020-2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

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


  /* Llamada a sistema pidiendo hora y fecha */
  struct timespec T1;
  int hora = clock_gettime(CLOCK_REALTIME, &T1);
  if (hora == -1) {
    printf("Error al retornar la hora.\n");
    exit(EXIT_FAILURE);
  }
  
  /* Imprimir fecha */ 
  long days = T1.tv_sec / (24 * 60 * 60);
  if (days > 0) {
    days = days - 12;
    int years = 1970 + (int)(days/365);
    int months = (int)(days%365);
    if ((months) <= 31){
      days = months;
      months = 1;
    }
    else if ((months - 31) <= 29){
      days = months - 31;
      months = 2;
    }
    else if ((months - 60) <= 31) {
      days = months - 60;
      months = 3;
    }
    else if ((months - 91) <= 30) {
      days = months - 91;    
      months = 4;
    }
    else if ((months - 121) <= 31){
      days = months - 121;
      months = 5;
    }
    else if ((months - 162) <= 30){
      days = months - 162;
      months = 6;
    }
    else if ((months - 192) <= 31) {
      days = months - 192;  
      months = 7;
    }
    else if ((months - 223) <= 31){
      days = months - 223;
      months = 8;
    }
    else if ((months - 254) <= 30) {
      days = months - 254;
      months = 9;
    }
    else if ((months - 284) <= 31){
      days = months - 284;
      months = 10;
    }
    else if ((months - 315) <= 30){
      days = months - 315;      
      months = 11;
    }
    else {
      days = months - 345;
      month = 12;
    }

    printf("Fecha: %d/%d/%d", days, months, years);
  }


}