/*
* @file   : codA.c
* @author : Camilo Donoso
*           Loreto Romero
* @date   : 06/11/2020
* @brief  : Codigo para tarea 01 en ELO 321, semestre 2020-2
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

/**
 * @brief   : recibe n y genera el siguiente numero generado de la sucesion de Collatz
 * @param n : numero entero positivo
 * @return  : numero siguiente a n en la sucesion de Collatz
 */
int sucesion_Collatz(unsigned int n);

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

  /* Generar proceso hijo para ejecutar llamada a sistema */
  pid_t pid1;
  pid1 = fork();

  /* Controlar que se haya ejecutado fork correctamente */
  if (pid1 < 0) {
    printf("Error al crear primer proceso hijo.\n");
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
      days = days - 11; // bisiestos
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

  /* Proceso padre debe esperar al primer proceso hijo */
  else {
    wait(NULL);
    printf("Primer proceso hijo completado.\n");

    /* Establecer espacio de memoria compartida y de contador de elementos de la sucesion */
    const int SIZE = 4096;
    const char* name = "mem";
    const char* name2 = "count";
    int shm_fd;
    int shm_fd2;
    void* ptr;
    void* ptr2;

    /* Memoria compartida */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    /* Contador */
    shm_fd2 = shm_open(name2, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd2, SIZE);
    ptr2 = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd2, 0);

    /* Generar proceso hijo para escribir sucesion de Collatz en mem */
    pid_t pid2;
    pid2 = fork();
  
    /* Controlar que se haya ejecutado fork correctamente */
    if (pid2 < 0) {
      printf("Error al crear segundo proceso hijo.\n");
      exit(EXIT_FAILURE);
    }

    /* Calcular sucesion de Collatz a partir de num de parte de proceso hijo */
    else if (pid2==0) {

      /* Escribir en mem primer elemento, controlando si hubo error */
      if (sprintf(ptr, "%d", num) == -1) {
        printf("Error al escribir %d en espacio de memoria compartida.\n", num);
        exit(EXIT_FAILURE);
      }
      ptr += sizeof(int);
      int c = 1;

      /* Calcular los elementos siguientes y escribirlos uno a uno en mem */
      while (num!=1){
        num = sucesion_Collatz((unsigned int)num);

        /* Controlando si hubo error */
        if (sprintf(ptr, "%d", num) == -1) {
          printf("Error al escribir %d en espacio de memoria compartida.\n",num);
          exit(EXIT_FAILURE);
        }
        ptr += sizeof(int); 
        c += 1;
      }

      /* Escribir en espacio compartido de contador, controlando si hubo error */
      if (sprintf(ptr2, "%d", c) == -1) {
        printf("Error al escribir contador en espacio de memoria compartida.\n");
        exit(EXIT_FAILURE);
      }
    }

    /* Proceso padre debe esperar al segundo proceso hijo */
    else {
      sleep(10);
      wait(NULL);
      printf("Segundo proceso hijo completado.\n");

      /* Leer elementos de sucesion desde espacio de memoria compartida */
      shm_fd = shm_open(name, O_RDONLY, 0666);
      ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

      /* Leer el contador desde espacio de memoria compartida */
      shm_fd2 = shm_open(name2, O_RDONLY, 0666);
      ptr2 = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd2, 0);
      char count[2];
      sprintf(count,"%s\n", (char*)ptr2);

      /* Imprimir sucesion de numeros leidos */
      int i;
      for (i=0;i<atoi(count);i++){
        printf("%s\n", (char*)ptr);
        ptr += sizeof(int);
      }

      /* Eliminar espacio de memoria compartida */
      if (shm_unlink(name)==-1)
        printf("Error al eliminar espacio de memoria compartida.\n");
      else
        printf("Se eliminó correctamente el espacio de memoria compartida.\n");
    }
  }

  return 0;

}

int sucesion_Collatz(unsigned int n) {

  int sgte;

  /* Verificar si n es par */
  if (n % 2 == 0) 
    sgte = n / 2;

  /* En caso de que no sea par */
  else {
    sgte = 3 * n + 1;
  }

  return sgte;

}