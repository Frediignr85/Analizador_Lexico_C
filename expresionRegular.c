
#include <stdio.h>
#include <string.h>
#include <regex.h>

int main ()
{   
    //Declaracion y asinacion de la expresion regular para detectar un correo electronico
    char * expresionRegular = "^([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$"; 
    //Declaracion de una variable de tipo entera que almacenara el valor resultante de evaluar la expresion
    //regular con la cadena que se introducira.
    int    resultado;
    //Declaracion de la variable 'expresionCompilada', la cual nos ayudara tanto a saber si la expresion
    //regular se puede compilar, asi como si la cadena ingresara hace match con la expresion regular.
    regex_t expresionCompilada;
    //Se comprueba si la expresion regular se puede compilar, si el resultado es positivo retornara un 0,
    //si el resultado es negativo retornara un 1.
    if(regcomp(&expresionCompilada, expresionRegular, REG_EXTENDED)){
        printf("No se pudo compilar la expresion regular.\n");  
    }
    else{
        //Declaracion y captura de la variable de tipo char 'correo', la cual nos servira para ingresar
        //un correo, para posteriormente evaluarlo con la expresion regular.
        printf("\nSi se pudo compilar la expresion regular.\n");
        char correo[100];
        printf("\n\nIngrese el correo electronico que desea ingresar: \n");
        scanf("%s",correo);
        //Se comprueba si la expresion regular realizo un match con la variable 'correo', si el resultado
        // es positivo retornara un 0, y si el resultado es negativo retornara un 1.
        resultado = regexec(&expresionCompilada, correo, (size_t) 0, NULL, 0);
        regfree(&expresionCompilada);
        if(resultado == 0){
            printf("\n\nCorreo electronico con sintaxis correcta.\n");
        }
        else{
            printf("\n\nEl correo electronico no cumple con el patron de la expresion regular.\n");
        }
        
    }
}