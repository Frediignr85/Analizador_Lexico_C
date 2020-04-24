#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
char retorno[100], devolver[100],devolver1[100];
int error =0;
int principio=0, final=0, se;
int tamanioCadena(char *s){
    int length = 0;
    while(*s != '\0'){
        length++;
        s++;
    }
    return length;
}
int comprobarCaracteresRepetido(char *cadena, char *subcadena){
    int j = 0;
    int i,counter=0;
    for(i = 0;i < tamanioCadena(cadena);i++){
        if(cadena[i] == subcadena[j]){
            if(j == tamanioCadena(subcadena)-1){
                counter++;
                j = 0;
                continue;
            }       
        }
        else{
            j = 0;
            continue;
        }
        j++;
    }
    return counter;
}
char * eliminarSubCadena(char *string, char *sub) {
    strcpy(devolver1,"");
    char *match = string;
    int len = strlen(sub);
    while ((match = strstr(match, sub))) {
        *match = '\0';
        strcat(string, match+len);
        match++;
    }
    strcpy(devolver1,string);
    return devolver1;
}
char * eliminarSeparadores(char cadena[], int posicion){
    int prime=0;
    strcpy(devolver,"");
    if(posicion == 0){
        if(strstr(cadena,"*/pi(") != NULL){
            principio = 1;
        }
        else{
            principio = 0;
        }
    }
    if(posicion == se){
        if(strstr(cadena,")/ff*") != NULL){
            final = 1;
        }
        else{
            final = 0;
        }
    }
    if(strstr(cadena,"*/pi(") != NULL){
        strcpy(cadena, eliminarSubCadena(cadena,"*/pi("));
    }
    if(strstr(cadena,")/pf$$(") != NULL){
        strcpy(cadena, eliminarSubCadena(cadena,")/pf$$("));
    }
    if(strstr(cadena,")$$(") != NULL){
        strcpy(cadena, eliminarSubCadena(cadena,")$$("));
    }
    if(strstr(cadena,")$$/fi(") != NULL){
        strcpy(cadena, eliminarSubCadena(cadena,")$$/fi("));
    }
    if(strstr(cadena,")/ff*") != NULL){
        strcpy(cadena, eliminarSubCadena(cadena,")/ff*"));
    }
    if(strstr(cadena,")/pf*") != NULL){
        strcpy(cadena, eliminarSubCadena(cadena,")/pf*"));
    }
    if(strstr(cadena,"*/fi(") != NULL){
        strcpy(cadena, eliminarSubCadena(cadena,"*/fi("));
    }
    if(strstr(cadena,"*(") != NULL){
        strcpy(cadena, eliminarSubCadena(cadena,"*("));
    }
    if(strstr(cadena,")*") != NULL){
        strcpy(cadena, eliminarSubCadena(cadena,")*"));
    }
    strcpy(devolver,cadena);
    return devolver;
}
char * comprobar(char expresion[]){
    int tamanio = strlen(expresion);
    char nuevaExpresion[1000];
    int g=0;
    for(int c =0; c < tamanio; c++){
        if(expresion[c] != ' '){
            nuevaExpresion[g] = expresion[c];
            g++;
        }
    }
    nuevaExpresion[g] = '\0';
    char expre[1000];
    strcpy(expre,"*");
    strcat(expre,nuevaExpresion);
    strtok(expre,"\n");
    strcat(expre,"*");
    char *separadores[20];
    int s=0;
    char *separador = "*";
    char * str3 =(char *) malloc(1 +  strlen(separador));
    strcpy(str3, separador);
    separadores[s] = str3;
    s++;
    int parte1 = comprobarCaracteresRepetido(expre,")$$(");
    int parte2 = comprobarCaracteresRepetido(expre,"*/pi(");
    int parte3 = comprobarCaracteresRepetido(expre,"$$/fi(");
    int parte4 = comprobarCaracteresRepetido(expre,"$$$");
    if(parte4 >0){
        error=1;
    }
    if(parte1 > 0){
        for(int g =0; g < parte1; g++){
            char *separador = ")$$(";
            char * str3 =(char *) malloc(1 +  strlen(separador));
            strcpy(str3, separador);
            separadores[s] = str3;
            s++;
        }
        parte1++;
    }
    if(parte2 == 0){
        int parte21 = comprobarCaracteresRepetido(expre,")/pf");
        if(parte21 > 0){
            error++;
        }
    }
    else if(parte2 >1){
        error++;
    }
    else if(parte2 == 1){
        int parte21 = comprobarCaracteresRepetido(expre, ")/pf$$");
        if(parte21 == 0){
            int parte22 = comprobarCaracteresRepetido(expre,")/pf*");
            if(parte22 == 0){
                error++;
            }
            else if(parte22 == 1){
                char *separador = "/pf*";
                char * str3 =(char *) malloc(1 +  strlen(separador));
                strcpy(str3, separador);
                separadores[s] = str3;
                s++;
            }
            else{
                error++;
            }   
        }
        else if(parte21 == 1){
            char *separador = ")/pf$$";
            char * str3 =(char *) malloc(1 +  strlen(separador));
            strcpy(str3, separador);
            separadores[s] = str3;
            s++;
        }
        else{
            error++;
        }   
    }
    if(parte3 == 0){
        int parte31 = comprobarCaracteresRepetido(expre,"*/fi(");
        if(parte31 == 0){
            int parte32 = comprobarCaracteresRepetido(expre,")/ff*");
            if(parte32 > 0){
                error++;
            }
            char *separador = "*";
            char * str3 =(char *) malloc(1 +  strlen(separador));
            strcpy(str3, separador);
            separadores[s] = str3;
            s++;
        }
        else if(parte31 == 1){
            int parte32 = comprobarCaracteresRepetido(expre,")/ff*");
            if(parte32 == 0){
                error++;
            }
            else if(parte32 == 1){
                char *separador = ")/ff*";
                char * str3 =(char *) malloc(1 +  strlen(separador));
                strcpy(str3, separador);
                separadores[s] = str3;
                s++;
                parte3++;
                
            }
            else{
                error++;
            }
        }
        else{
            error++;
        }
    }
    else if(parte3 >1){
        error++;
    }
    else if(parte3 == 1){
        int parte31 = comprobarCaracteresRepetido(expre,"/ff*");
        if(parte31 == 0){
            error++;
        }
        else if(parte31 == 1){            
            if(parte1 == 0){
                parte3++;
                
            }
            char *separador = ")$$/fi";
            char * str3 =(char *) malloc(1 +  strlen(separador));
            strcpy(str3, separador);
            separadores[s] = str3;
            s++;
            char *separador1 = "/ff*";
            char * str31 =(char *) malloc(1 +  strlen(separador1));
            strcpy(str31, separador1);
            separadores[s] = str31;
            s++;
        }
        else{
            error++;
        }
    }
    if(error > 0){
        printf("\nHay %d errores\n",error);
    }
    else{
        int secciones = parte1 + parte2 + parte3;
        int correcto=1;
        if(secciones == 0){
            int sec1= comprobarCaracteresRepetido(expre,"*(");
            int sec2= comprobarCaracteresRepetido(expre,")*");
            if(sec1 + sec2 == 2){
                secciones++;
                correcto++;
            }
            else
            {
                correcto=0;
            }
        }
        if(parte2 == 0 && parte3 == 0){
            int sec1 = comprobarCaracteresRepetido(expre, "$$*");
            if(sec1 == 1){
                correcto = 0;
            }
        }
        if(correcto > 0){
            printf("\nHay %d secciones\n",secciones);
            char * separ[s];
            int tamanioCadena= strlen(expre);
            int posiciones[22];
            for(int x =0; x < 22; x++){
                posiciones[x] = 0;
            }
            posiciones[0] = 0;
            int p=1;
            for(int x = 1; x < s -1; x++){
                char * separa = separadores[x];
                int tamanioSepa = strlen(separa);
                int c =0;
                while(c < tamanioCadena - tamanioSepa){
                    char comparar[100];
                    strcpy(comparar,"");
                    int g=0;
                    int l =c;
                    for(int x = l; x < l + tamanioSepa; x++){
                        comparar[g] = expre[x];
                        g++;
                    }
                    if(strcmp(comparar, separadores[x]) == 0){
                        if(p == 0){
                            posiciones[p] = c;
                            p++;
                        }
                        else{
                            int coincide=0;
                            for(int v =0; v < p; v++){
                                if(posiciones[v] == c){
                                    coincide++;
                                }
                            }
                            if(coincide == 0){
                                posiciones[p] = c;
                                p++;
                            }
                        }
                    }
                    c++;
                    strcpy(comparar,"");
                }
            }
            posiciones[p] = tamanioCadena -1;
            p++;
            int j, i, temp;
            char tempo[100]; 
            for (i = 0; i < (p); i++) { 
                for (j = i + 1; j < p; j++) { 
                    if (posiciones[j] < posiciones[i]) { 
                        temp = posiciones[j]; 
                        posiciones[j] = posiciones[i]; 
                        posiciones[i] = temp; 
                        strcpy(tempo, separadores[j]);
                        separadores[j] = separadores[i];
                        char * tempo1 = tempo;
                        char * str3 =(char *) malloc(1 +  strlen(tempo1));
                        strcpy(str3, tempo1);
                        separadores[i] = str3;
                    } 
                } 
            }
            char * partesSecciones[p];
            int l=0,m=0,n=1;
            char termi[100];
            char compaExpre[100];
            strcpy(termi,"");
            strcpy(compaExpre,"");
            if(p == 2){
                for(int y = posiciones[0]; y < posiciones[1]; y++){
                    termi[l] = expre[y];
                    l++;
                }
                strcat(termi,"*");
                char *par = termi;
                char * str3 =(char *) malloc(1 +  strlen(par));
                strcpy(str3, par);
                partesSecciones[m] = str3;
                m++;
            }
            else{
                for(int x=0; x < p-1; x++){
                    strcpy(termi,"");
                    l=0;
                    for(int y = posiciones[x]; y < posiciones[x+1]; y++){
                        termi[l] = expre[y];
                        l++;
                    }
                    if(x == p -2){
                        strcat(termi,"*");
                    }
                    char *par = termi;
                    char * str3 =(char *) malloc(1 +  strlen(par));
                    strcpy(str3, par);
                    partesSecciones[m] = str3;
                    m++;
                    for(int z=0; z < 100; z++){
                        termi[z]=0;
                    }
                }
            }
            se =m-1;
            for(int x=0; x < m; x++){
                printf("\n::parte1: %s::\n",partesSecciones[x]);
                char * devuelto = eliminarSeparadores(partesSecciones[x], x);
                char * str3 =(char *) malloc(1 +  strlen(devuelto));
                strcpy(str3, devuelto);
                partesSecciones[x] = str3;
                printf("\n::parte2: %s::\n",partesSecciones[x]);
            }
            int subsecciones[m];
            int o=0;
            int error1=0;
            int sum =0;
            for(int x =0; x < m ; x++){
                int subseccion =  comprobarCaracteresRepetido(partesSecciones[x],"],,[");
                int c1 = comprobarCaracteresRepetido(partesSecciones[x],"],[");
                int c2 = comprobarCaracteresRepetido(partesSecciones[x],"][");
                int c3 = comprobarCaracteresRepetido(partesSecciones[x],",,,");
                int c4 = comprobarCaracteresRepetido(partesSecciones[x],",]");
                int c5 = comprobarCaracteresRepetido(partesSecciones[x],"[,");
                int c6 = comprobarCaracteresRepetido(partesSecciones[x],",,]");
                int c7 = comprobarCaracteresRepetido(partesSecciones[x],"");
                int tamanioPar = strlen(partesSecciones[x]);
                char veri[100];
                strcpy(veri,partesSecciones[x]);
                if(veri[tamanioPar-1] != '*' && veri[tamanioPar-1] != '+' && veri[tamanioPar-1] != '?' && veri[tamanioPar-1] != 0 && veri[tamanioPar-1] != ']'){
                    printf("\n%c\n",veri[tamanioPar-1]);
                    error1++;
                }
                if(c1+c2+c3+c4+c5+c6+c7 > 0){
                    printf("\n::1-%d::\n",c1);
                    printf("\n::2-%d::\n",c2);
                    printf("\n::3-%d::\n",c3);
                    printf("\n::4-%d::\n",c4);
                    printf("\n::5-%d::\n",c5);
                    printf("\n::6-%d::\n",c6);
                    printf("\n::7-%d::\n",c7);
                    error1++;
                }
                if(error1 >0){
                    break;
                }
                else{
                    subsecciones[o] = subseccion+1;
                    sum = sum + subseccion+1;
                    o++;
                }
            }
            if( error1 > 0){
                printf("\nError\n");
            }
            else{ 
                char * subsecc[sum];
                int d=0;
                printf("\nHay un total de %d posiciones\n",sum);   
                for(int x=0; x < m; x++){
                    int tamanioSec = strlen(partesSecciones[x]);
                    char parteSeccion[100];
                    char compara[100];
                    strcpy(compara, partesSecciones[x]);
                    int a =0, b=0;
                    for(int y =0; y < tamanioSec; y++){
                        parteSeccion[a] = compara[b];
                        char com[3];
                        com[0] =compara[b];
                        com[1] = compara[b+1];
                        com[2] = '\0';
                        if(strcmp(com,",,")==0){
                            parteSeccion[strlen(parteSeccion)-1]='\0';
                            char *separador = parteSeccion;
                            char * str3 =(char *) malloc(1 +  strlen(separador));
                            strcpy(str3, separador);
                            subsecc[d] = str3;
                            d++;
                            strcpy(parteSeccion,"");
                            a=0;
                            
                        }   
                        else{
                            a++;
                            strcpy(com,"");
                        }
                        if(y == tamanioSec -1){
                            char *separador = parteSeccion;
                            char * str3 =(char *) malloc(1 +  strlen(separador));
                            strcpy(str3, separador);
                            subsecc[d] = str3;
                            d++;
                        }
                        b++;
                    }
                }
                for(int x =0; x < sum; x++){
                    printf("\n::Seccion %d: %s::\n",x+1,subsecc[x]);
                }
            }
            
        }
        if(correcto == 0){
            printf("\nError\n");
        }
    }
    return retorno;
}
