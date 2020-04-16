#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    //Declaracion de las variables, c y d (c = cantidad de caracteres) (d = veces que se repetira la cerradura)
    int c, d;
    //Captura y asignacion de la variable c
    printf("\n\nIngrese cuantos caracteres quiere que tenga la cerradura de Kleene\n\n");
    scanf("%d", &c);
    //Creacion de un arreglo tipo entero con tamaño 'c' para capturar los datos de los caracteres.
    char *arreglo[c];
    //For que se repetira 'c' veces para capturar los 'c' numeros de caracteres
    for(int x =0; x < c; x++){
        //Declaracion de la variable en donde se escribira el caracter numero 'x+1'
        char caracter[20];
        //Captura y asignacion de la variable caracter para el caracter numero 'x+1'
        printf("\nIngrese el caracter/es #%d de la cerradura de Kleene:    ",x+1);
        scanf("%s",caracter);
        //Creacion y asignacion de un valor para la variable str el cual tendra el tamaño de la variable 'caracter'
        char * str = (char *) malloc(1 + strlen(caracter));
        //Se copia en la variable 'str' el valor de la variable 'caracter'
        strcpy(str, caracter);
        //Se le asigna el valor de la variable 'str' al arreglo de tipo char * 'arreglo' en la posicion 'x' 
        arreglo[x] = str;
    }
    //Captura y asignacin de la variable d
    printf("\n\nIngrese cuantas veces quiere que se de esta cerradura de Kleene\n\n");
    scanf("%d", &d);
    //Declaracion de la variable carac, la cual servira para concatenar la cerradura de Kleene con la que se trabajara.
    char carac[100];
    //A la variable carac se le copia nada, para inicializarla
    strcpy(carac, "");
    //Recorrido de 'c' veces para concatenar a la variable 'carac' todos los valores del arreglo 'arreglo'
    for (int x = 0; x < c; x++){
        if (x == 0){
            strcat(carac, "{");
        }
        if (x != 0){
            strcat(carac, ",");
        }
        strcat(carac, arreglo[x]);
        if (x == c - 1){
            strcat(carac, "}");
        }
    }
    //Imprimir la cerradura de Kleene con la que se trabajara
    printf("\n\nAplicando %d repeticiones para la siguiente cerradura de Kleene:\nL=%s\n\n", d, carac);
    printf("\nL0 = {λ}");
    //Declaracion de la varible 'numero', la cual servira para iterar 'd' veces un while, y asi saber cuantos caracteres habra en cada iteracion de la cerradura de Kleene.
    //Declaracion de la varible 'num', la cual servirar para saber cuantos caracteres tendra la cerradura de Kleene en cada iteracion.
    //Declaracion de la variable 'sum', la cual servira para ir sumando el valor de la variable 'num' en todas las iteraciones.
    int numero = 1, num = 1, sum=0;
    //Se declara un arreglo de tipo entero con tamaño 'n' para saber cuantos caracteres habra en cada iteracion de la cerradura de kleene.
    int arregloInt[d];
    while (numero < d + 1){
        //Declaracion de una varible 'x' la cual controlara el while que sirve para calcular la variable 'num'.
        int x = 0;
        //Declaracion de un while, que mientras la variable 'x' sea menor a la variable 'numero' este se seguira repitiendo.
        while (x < numero){
            //Asignacion numero 'x+1' de la variable 'num'.
            num = num * c;
            //La variable 'x' aumenta en 1.
            x++;
        }
        //El arreglo de tipo entero 'arregloInt' toma el valor de la variable entera 'num' en la posicion 'numero-1'.
        arregloInt[numero-1] = num;
        //A la varible 'sum' se le suma el valor de la variable 'num' en la iteracion numero 'numero'
        sum = sum+num;
        //La variable 'num' se reterea a 1.
        num=1;
        //La varible 'numero' aumenta en 1.
        numero++;
    }
    //Se crea un arreglo de tipo char * llamado 'arregloCadenas' con un tamaño 'sum' el cual sera el
    // responsable de tener en cada una de sus posiciones, el conjunto de caracteres de la cerradura 
    // de Kleene correspondiente.
    char *arregloCadenas[sum];
    //Creacion de la variable 'principio', el cual controlara cuantos caracteres tienen los distintos L de la
    // cerradura de Kleene.
    //Creacion de la variable 'posic' la cual controlara la posicion del arreglo 'arregloCadenas' en donde
    // se iran agregando las nuevas cadenas de la cerradura de Kleene.
    int principio=0, posic=0;
    //Inicio del for para asignar valores a los distintos L de la cerradura de Kleene.
    for(int x=0; x < d;x++){
        //Creacion de la varible de tipo char 'conca' la cual servira para ir concatenando los valores de 
        // cada cerradura de Kleene para cada iteracion.
        //Creacion de la variable de tipo char 'nume', la cual servira para almacenar el valor de la variable 'x+1' 
        char conca[20000], nume[100];
        //Asignacion de la variable 'x+1' a la variable nume.
        sprintf(nume, "%d", x+1);
        //Concatenacion inicial de la cerradura de Kleene L'x+1'.
        strcpy(conca,"");
        strcat(conca,"L");
        strcat(conca,nume);
        strcat(conca,"= {");
        //Creacion de la varible entera 'numero', la cual almacenara el valor del arreglo de tipo entero 'arregloInt'
        //en la posicion 'x'
        //Creacion de la variable entera 'count' el cual servira para controlar el numero de repeticiones que debe
        //de esperar la cerradura de Kleene en la iteracion numero 'x+1' para cambiar a la siguiente posicion en el 
        // arreglo de tipo char* 'arreglo'
        //Creacion de la variable 'co' la cual servira para saber la posicion del arreglo de tipo char * 'arreglo'
        //que se tiene que usar.
        int numero = arregloInt[x], count=0, co=0;
        //Mientras la variable 'principio', sea menor que la variable 'numero' se desarrollara lo siguiente.
        while(principio < numero){
            //Evalua si la variable 'count' es igual a 'numero/c' lo cual denota que debe de realizar un salto
            //y aumentar la variable 'co' en 1, para utilizar el siguiente valor del arreglo de tipo char* 'arreglo'
            if(count == numero/c){
                co++;
                count=1;
            }
            else{
                count++;
            }
            //Si la variable 'posic' es mayor o igual que la variable 'c', significa que ya estamos en un Li en donde 
            //i>=2 por lo cual, ahora los valores de la cerradura de Kleene para cada Li, tendran mas de un caracter
            //por cada posicion
            if(posic >= c){
                //Captura en la variable de tipo char *'me' el valor del arreglo 'arreglo' en la posicion 'co'.
                char *me = arreglo[co];
                //Captura en la variable de tipo char * 'ca' el valor del arreglo 'arregloCadenas' en la 
                //posicion 'posic - (numero/c)*(co+1)'
                char *ca = arregloCadenas[posic - (numero/c)*(co+1)];
                //Declara la variable de tipo char * 'str3' y le asigna un tamaño que es la sumatoria de la variable
                // 'me' y 'ca' +1
                char * str3 =(char *) malloc(1 + strlen(me)+ strlen(ca));
                //Copia y concatena la variable 'me' y la variable 'ca' en la variable 'str3'
                strcpy(str3, me);
                strcat(str3, ca);
                //Le asigna el valor de la variable de tipo char * 'str3' al arreglo 'arregloCadenas' en la posicion 'posic'
                arregloCadenas[posic] = str3;  
            }
            //Si la variable posic es menor que c entonces realiza lo siguiente:
            else{
                //Captura en la variable de tipo char *'me' el valor del arreglo 'arreglo' en la posicion 'co'.
                char *me = arreglo[co];
                //Declara la variable de tipo char * 'str3' y le asigna un tamaño que es la sumatoria de la variable
                // 'me' +1
                char * str3 =(char *) malloc(1 + strlen(me));
                //Copia la variable 'me' en la variable 'str3'
                strcpy(str3, me);
                //Le asigna el valor de la variable de tipo char * 'str3' al arreglo 'arregloCadenas' en la posicion 'posic'
                arregloCadenas[posic] = str3;  
            } 
            //Concatena a la variable de tipo char 'conca' el valor del arreglo de tipo char * 'arregloCadenas'
            //en la posicion posic.
            strcat(conca, arregloCadenas[posic]);
            //Mientas la variable 'principio' sea distinto de 'numero -1' se pondra una coma (,), de lo contrario
            //no se pondra nada, lo cual significa que es el ultimo elemento de la cerradura de Kleene en L'x+1'
            if(principio != numero -1){
                strcat(conca,",");
            }
            //La variable 'principio' aumenta en 1.
            principio++;
            //La variable 'posic' aumenta en 1
            posic++;
        }    
        //Se le concatena a la variable 'conca' al final el simbolo '}'
        strcat(conca,"}");
        //Se imprime el valor de la variable 'conca'
        printf("\n%s\n",conca);    
        //La variable 'principio' se iguala a 0.
        principio=0;
    }
}