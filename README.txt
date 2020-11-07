# ELO321_Tarea1

Integrantes:
- Loreto Romero Ponce      201554001-2     loreto.romero@sansano.usm.cl
- Camilo Donoso Collao     201521040-3     camilo.donoso@sansano.usm.cl


## Parte A
La parte A de la tarea se desarrolló en un código, codA.c

...

El programa codA.c se compila de la siguiente manera:

  gcc codA.c -o codA -lrt
  
Y se ejecuta de la siguiente manera:

  ./codA n & ps -l
  
donde el argumento 'n' corresponde a un número entero positivo.  El ps -l sirve para ver el proceso zombie.


## Parte B
La parte B de la tarea se desarrolló en 2 codigos, codB.c y codB_P3.c. 

El código codB.c responde a las preguntas 0,1 y 2 de la parte B,  donde se un proceso con 3 hilos, los cuales calculan el valor medio, el valor mínimo y el valor máximo de un arreglo con 50 números aleatorios entre 1 y 100. Las variables correspondiente a los datos calculados son globales, en pantalla se imprime el ID de cada hilo, que hizo cada hilo y los datos calculados.

El programa codB.c se compila de la siguiente manera:

  gcc codB.c -lpthread -o codB

Y se ejecuta de la siguiente manera:
  
  ./codB

El código codB_P3.c responde a la pregunta 3 de la parte B, este programa también calcula el valor medio, el mínimo y el máximo de un arreglo de 50 números aleatorios entre 1 y 100, pero en este caso los datos calculados se almacenan en variables locales y los hilos generados ejecutan funciones que reciben los parámetros por referencia. En pantalla también imprime el ID de los hilos, que hace cada hilo y los datos calculados.

El programa codB_P3.c se compila de la siguiente manera:

  gcc codB_p3.c -lpthread -o codB_P3

Y se ejecuta de la siguiente manera:

  ./codB_P3
