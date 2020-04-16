#include<stdio.h>
#include <string.h>
int main(){
    //Declaracion de las variable a concatenar.
    char primeraCadena[10];
    char segundaCadena[10];
    //Captura y asignacion de cadenas a las variables a traves de teclado.
    printf("\n\nIngrese la primera cadena: ");
    scanf("%s", primeraCadena);
    printf("\n\nIngrese la segunda cadena: ");
    scanf("%s", segundaCadena);
    printf("\n\nLa concatenacion/union de la primera cadena y la segunda cadena es: \n\n");
    //Concatenacion de la variable primeraCadena con la variable segundaCadena.
    strcat(primeraCadena, segundaCadena);
    //Impresion de las variables ya concatenadas.
    printf("%s\n\n",primeraCadena);
}
