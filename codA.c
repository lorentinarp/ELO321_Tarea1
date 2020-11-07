/*
* @file   : codA.c
* @author : Camilo Donoso
*           Loreto Romero
* @date   : 06/11/2020
* @brief  : C�digo para tarea 01 en ELO 321, semestre 2020-2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <wait.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>       
#include <fcntl.h>

int main(int argc, char* argv[]) {
  
  /* Controlar el correcto paso de argumentos por linea de comandos */
  if (argc != 2) {
    printf("Error al ejecutar %s.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Guardar localmente numero recibido y controlar si es positivo*/
  int num;
  num = atoi(argv[1]);
  if (num<=0) {
    printf("El numero ingresado no es positivo.\n");
    exit(EXIT_FAILURE);
  }

  /* Generar proceso hijo */
  pid_t pid1;
  pid1 = fork();

  /* Controlar que se haya ejecutado fork correctamente */
  if (pid1 < 0) {
    printf("Error al crear proceso hijo.\n");
    exit(EXIT_FAILURE);
  }

  /* Llamada a sistema pidiendo hora y fecha de parte del proceso hijo */
  else if (pid1==0){
    struct timespec T1;
    if (clock_gettime(CLOCK_REALTIME, &T1) == -1) {
      printf("Error al retornar la hora.\n");
      exit(EXIT_FAILURE);
    }
  
    /* Imprimir fecha y hora */ 
    long days = T1.tv_sec / 86400;
    if (days > 0) {
      days = days - 11; // a�os bisiestos
      int horas = (int)(T1.tv_sec % 86400) / 3600 - 3;
      if (horas < 0) {
        horas = horas + 24;
        days = days - 1;
      }
      int years = 1970 + (int)(days/365);
      int months;
      days = days % 365;
      if (days <= 31){
        months = 1;
      }
      else if ((days - 31) <= 29){
        days = days - 31;
        months = 2;
      }
      else if ((days - 60) <= 31) {
        days = days - 60;
        months = 3;
      }
      else if ((days - 91) <= 30) {
        days = days - 91;
        months = 4;
      }
      else if ((days - 121) <= 31){
        days = days - 121;
        months = 5;
      }
      else if ((days - 152) <= 30){
        days = days - 152;
        months = 6;
      }
      else if ((days - 182) <= 31) {
        days = days - 182;
        months = 7;
      }
      else if ((days - 213) <= 31){
        days = days - 213;
        months = 8;
      }
      else if ((days - 244) <= 30) {
        days = days - 244;
        months = 9;
      }
      else if ((days - 274) <= 31){
        days = days - 274;
        months = 10;
      }
      else if ((days - 305) <= 30){
        days = days - 305;
        months = 11;
      }
      else {
        days = days - 335;
        months = 12;
      }
    
      printf("Fecha: %02d/%02d/%04d \n", (int)days, months, years);
      printf("Hora: %02d:%02d:%02d \n",horas,(int)(T1.tv_sec%3600)/60,(int)T1.tv_sec%60);
    }
    else {
      printf("La cantidad de segundos retornados es menor o igual a cero.\n");
    }
  }

  /* Proceso padre debe esperar al hijo */
  else {
    wait(NULL);
    printf("Proceso hijo completado.\n");
  }

  /* Establecer espacio de memoria compartida */
  const int SIZE = 4096;
  const char* name = "mem";
  int shm_fd;
  void* ptr;
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, SIZE);
  ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

  return 0;
}