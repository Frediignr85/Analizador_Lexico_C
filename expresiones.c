#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expreGrp4.h"

int main(){
    char cadena[1000];
    printf("\n\nEvaluarcion de correcta estructura de una expresion regular\n\n");
    fgets(cadena, 1000,stdin);
    printf("%s\n", comprobar(cadena));
}