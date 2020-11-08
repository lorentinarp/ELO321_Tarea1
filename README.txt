# ELO321_Tarea1

Integrantes:
- Loreto Romero Ponce      201554001-2     loreto.romero@sansano.usm.cl
- Camilo Donoso Collao     201521040-3     camilo.donoso@sansano.usm.cl


## Parte A
La parte A de la tarea se desarrolló en un código, codA.c

El código codA.c responde las preguntas 0, 1, 2, 3, 4, 5, y 6 de la parte A. En la primera parte, crea un proceso hijo que se encarga de hacer una llamada a sistema solicitando información del reloj para así a partir de ello imprimir la fecha y hora de la ejecución. El proceso padre espera al proceso hijo que termine, y luego crea un segundo proceso hijo, el cual realiza la escritura en memoria compartida de los elementos de la sucesión de Collatz uno a uno de un número ingresado por línea de comandos y del contador con la cantidad de elementos de la sucesión creada. El proceso padre también espera a este proceso hijo, pero por un periodo de 10 segundos (tiempo considerado para observar su estado de zombie), y luego procede a leer desde la memoria compartida la cantidad de elementos de la sucesión dada por el contador y los imprime por pantalla. Para terminar, el proceso padre elimina el espacio de memoria compartida y se termina el programa.

El programa codA.c se compila de la siguiente manera:

  gcc codA.c -o codA -lrt
  
Y se ejecuta de la siguiente manera:

  ./codA n

donde para ver el proceso zombie, se agrega ps -l:

  ./codA n & ps -l
  
El argumento 'n' corresponde a un número entero positivo.  


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
