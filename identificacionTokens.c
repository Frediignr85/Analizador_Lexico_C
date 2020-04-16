#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
//Declaracion de todas las funciones que se utilizaran para evaluar los distintos tokens que reconocera el programa.
int tokenCabeceras(char cadena[]);
int tokenID(char cadena[]);
int tokenNumero(char cadena[]);
int tokenPalabraReservada(char cadena[]);
//Declaracion de una variable global int, la cual tomara el valor que retornen las distintas funciones que se utilizaran.
int resultado;
int main ()
{
    //Se declara un const chat * de nombre 'tokens', el cual almacena en un arreglo, el nombre de todos los
    //distintos tokens que reconocera nuestro programa.
    const char * tokens[] = {"Cabecera", "ID", "Constante numerica", "Palabra reservada"};
    //Declaracion de una variable de tipo char llamada 'cadena' la cual servira para capturar la cadena que
    //ingrese por teclado el usuario, y es la que se comparara con las distintas expresiones regulares de los
    //tokens para ver en cual de ellos realiza un match.
    char cadena[200];
    //Impresion de datos de importancia.
    printf("\n\nEstructura de las cabeceras: (#)(espacio*)(include)(espacio*)(<)(letra+)(.h)(espacio*)(>)(espacio*)");
    printf("\nEjemplo = #include <nombre.h>  o  #  include  <  nombre.h  >");
    printf("\n\nEstructura de los ID = (letra)((letra | numero)*).");
    printf("\nEjemplo = nombre  o  nombre1  o  N1");
    printf("\n\nEstructura de la constante numerica = (numero+)(.*)(numero*).");
    printf("\nEjemplo = 56  o  1.23  o  0.12");
    printf("\n\nEstructura de las palabras reservadas = depende de la palabra reservada.");
    printf("\nEjemplo = if, else, for\n\n");
    printf("\nIngrese una cadena con cualquiera de las estructuras vistas");
    printf("\nIngrese:    ");
    //Captura por teclado de la variable 'cadena'
    fgets(cadena, 200, stdin);
    printf("%s",cadena);
    //La variable numero toma el valor que devuele la funcion 'tokenCabeceras'
    int numero =tokenCabeceras(cadena);
    if(numero == 0){
        printf("Se encontro el token: %s, en la cadena %s", tokens[0], cadena);
    }
    else if(numero == 2){
        printf("No se pudo compilar la expresion regular de la cabecera.\n");
    }
    //Si no se encuentra una cabecera se procede a buscar una palabra reservada
    else{
        //La variable numero toma el valor que devuele la funcion 'tokenPalabraReservada'
        numero = tokenPalabraReservada(cadena);
        if(numero == 0){
            printf("Se encontro el token: %s, en la cadena %s", tokens[3], cadena);
        }
        else if(numero == 2){
            printf("No se pudo compilar la busqueda de palabras reservadas.\n");
        }
        //Si no se encuentra una palabra reservada se procede a encontrar un id.
        else{
            //La variable numero toma el valor que devuele la funcion 'tokenID'
            numero = tokenID(cadena);
            if(numero == 0){
                printf("Se encontro el token: %s, en la cadena %s", tokens[1], cadena);
            }
            else if(numero == 2){
                printf("No se pudo compilar la expresion regular de los id.\n");
            }
            //Si no se encuentra un id se procede a buscar un numero.
            else{
                //La variable numero toma el valor que devuele la funcion 'tokenNumero'
                numero = tokenNumero(cadena);
                if(numero == 0){
                    printf("Se encontro el token: %s, en la cadena %s", tokens[2], cadena);
                }
                else if(numero == 2){
                    printf("No se pudo compilar la expresion regular de las constantes numericas.\n");
                }
                else{
                    //Si no se encuentra un numero se imprime en consola que la cadena no coincide
                    //con ningun patron para reconocimiento de tokens disponibles.
                    printf("\n\nLa cadena no coincide con ninguno de los tokens ingresados\n\n");
                } 
            }   
        }
    }
}
int tokenCabeceras(char cadena[]){
    //Declaracion de la variable 'expresionCompilada', la cual nos ayudara tanto a saber si la expresion
    //regular se puede compilar, asi como si la cadena ingresara hace match con la expresion regular.
    regex_t expresionCompilada;
    //Declaracion y asinacion de la expresion regular para detectar una cabecera
    char * expresionRegular = "^#([[:space:]]*)(include)([[:space:]]*)(<)([[:space:]]*)([A-Za-z]+).h([[:space:]]*)(>)([[:space:]]*)$";
    //Se comprueba si la expresion regular se puede compilar, si el resultado es positivo retornara un 0,
    //si el resultado es negativo retornara un 1.
    if(regcomp(&expresionCompilada, expresionRegular, REG_EXTENDED)){
        printf("No se pudo compilar la expresion regular de la cabecera.\n");
        resultado = 2;
    }
    else{
        //Se comprueba si la expresion regular realizo un match con la variable 'cadena', si el resultado
        // es positivo retornara un 0, y si el resultado es negativo retornara un 1.
        resultado = regexec(&expresionCompilada, cadena, (size_t) 0, NULL, 0);
    }
    regfree(&expresionCompilada);
    //Retorna la variable resultado
    return resultado;
}
int tokenID(char cadena[]){
    //Declaracion de la variable 'expresionCompilada', la cual nos ayudara tanto a saber si la expresion
    //regular se puede compilar, asi como si la cadena ingresara hace match con la expresion regular.
    regex_t expresionCompilada;
    //Declaracion y asinacion de la expresion regular para detectar un id
    char * expresionRegular = "^([A-Za-z]+)([A-Za-z0-9]*)";
    //Se comprueba si la expresion regular se puede compilar, si el resultado es positivo retornara un 0,
    //si el resultado es negativo retornara un 1.
    if(regcomp(&expresionCompilada, expresionRegular, REG_EXTENDED)){
        resultado = 2;
    }
    else{
        //Se comprueba si la expresion regular realizo un match con la variable 'cadena', si el resultado
        // es positivo retornara un 0, y si el resultado es negativo retornara un 1.
        resultado = regexec(&expresionCompilada, cadena, (size_t) 0, NULL, 0);
    }
    regfree(&expresionCompilada);
    //Retorna la variable resultado
    return resultado;
}
int tokenNumero(char cadena[]){
    //Declaracion de la variable 'expresionCompilada', la cual nos ayudara tanto a saber si la expresion
    //regular se puede compilar, asi como si la cadena ingresara hace match con la expresion regular.
    regex_t expresionCompilada;
    //Declaracion y asinacion de la expresion regular para detectar un numero
    char * expresionRegular = "^([0-9]+)(.{0,1}[0-9]*)";
    //Se comprueba si la expresion regular se puede compilar, si el resultado es positivo retornara un 0,
    //si el resultado es negativo retornara un 1.
    if(regcomp(&expresionCompilada, expresionRegular, REG_EXTENDED)){
        resultado = 2;
    }
    else{
        //Se comprueba si la expresion regular realizo un match con la variable 'cadena', si el resultado
        // es positivo retornara un 0, y si el resultado es negativo retornara un 1.
        resultado = regexec(&expresionCompilada, cadena, (size_t) 0, NULL, 0);
    }
    regfree(&expresionCompilada);
    //Retorna la variable resultado
    return resultado;
}
int tokenPalabraReservada(char cadena[]){
    //Declaracion de la variable 'expresionCompilada', la cual nos ayudara tanto a saber si la expresion
    //regular se puede compilar, asi como si la cadena ingresara hace match con la expresion regular.
    regex_t expresionCompilada;
    //Declaracion y asinacion de la expresion regular para detectar una palabra reservada
    char * expresionRegular = "^(if|else|for|while)";
    //Se comprueba si la expresion regular se puede compilar, si el resultado es positivo retornara un 0,
    //si el resultado es negativo retornara un 1.
    if(regcomp(&expresionCompilada, expresionRegular, REG_EXTENDED)){
        resultado = 2;
    }
    else{
        //Se comprueba si la expresion regular realizo un match con la variable 'cadena', si el resultado
        // es positivo retornara un 0, y si el resultado es negativo retornara un 1.
        resultado = regexec(&expresionCompilada, cadena, (size_t) 0, NULL, 0);
    }
    regfree(&expresionCompilada);
    //Retorna la variable resultado
    return resultado;
}