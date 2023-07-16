#include "lab.03.c"
#include <stdlib.h>

/* Inicializa um polinômio vazio. */
void inicializa_polinomio ( Polinomio * ap_pol){

    *ap_pol = ( No*) calloc ( 1,sizeof ( No));
    ( *ap_pol)->prox = ( *ap_pol)->antec = ( *ap_pol);

}

/* Define que o coeficiente de grau g do polinomio pol eh igual a coef. Deve manter os 
 * coeficientes ordenados por grau. */
void define_coeficiente ( Polinomio pol, int grau, int coef){

    No* percorre = pol;

    if ( pol->prox == pol){
        
        No* novo_noAB = ( No*) malloc (sizeof ( No));
        novo_noAB->valor.grau = grau;
        novo_noAB->valor.coef = coef;

        novo_noAB->prox = pol;
        novo_noAB->antec = pol;

        pol->prox = novo_noAB;
        pol->antec = novo_noAB;

        return;

    }

    while ( percorre->prox->valor.grau < grau && percorre->prox != pol)
        percorre = percorre->prox;
    
    if ( percorre->valor.grau == grau){

        percorre->valor.grau = grau;
        percorre->valor.coef = coef;
        return;

    }
    
    No* novo_noAB = ( No*) malloc (sizeof( No));

    novo_noAB->valor.grau = grau;
    novo_noAB->valor.coef = coef;

    novo_noAB->prox = percorre->prox;
    novo_noAB->antec = percorre;

    percorre->prox->antec = novo_noAB;
    percorre->prox = novo_noAB;
    return;

}

/* Zera o polinomio, tornando-o um polinomio inicializado, mas igual a zero. Desaloca a memória liberada. */
void zera ( Polinomio pol){
    
    pol->antec->prox = NULL;
    No* apagando = pol->prox;

    while ( apagando->prox != NULL || apagando != NULL){   
        No* apagar = apagando;
        apagando = apagando->prox;
        free (apagar);
    }

    pol->prox = pol;
    pol->antec = pol;

    return;

}

/* Computa a soma dos polinomios a e b colocando o resultado em res. 
 * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. */
void soma ( Polinomio res, Polinomio a, Polinomio b){
    
    inicializa_polinomio ( &res);

    if (a->prox == a){
        res = b;
        return;
    }
    if (b->prox == b){
        res = a;
        return;
    }

    No* peratualA = a->prox;
    No* peratualB = b->prox;
    
    while ( peratualA != a && peratualB != b){                    // a estrutura percorre a e b simultaneamente onde, ela incrementa em res e, tambem, ja ordena res 

        if ( peratualB->valor.grau == peratualA->valor.grau){

            define_coeficiente ( res, peratualA->valor.grau, peratualA->valor.coef - peratualB->valor.coef);

            peratualA = peratualA->prox;
            peratualB = peratualB->prox;

        }
        else if ( peratualB->valor.grau > peratualA->valor.grau){
            
            define_coeficiente ( res, peratualA->valor.grau, peratualA->valor.coef);

            peratualA = peratualA->prox;

        }
        else if ( peratualA->valor.grau > peratualB->valor.grau){
            
            define_coeficiente ( res, peratualB->valor.grau, peratualB->valor.coef);

            peratualB = peratualB->prox;

        }
    }

        while ( peratualB != b){

            define_coeficiente ( res, peratualB->valor.grau, peratualB->valor.coef);

            peratualB = peratualB->prox;

        }
    
 

        while ( peratualA != a){
            
            define_coeficiente ( res, peratualA->valor.grau, peratualA->valor.coef);

            peratualA = peratualA->prox;

        }

    return;
}

/* Computa a subtracao dos polinomios a e b colocando o resultado em res. 
 * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. */
void subtrai ( Polinomio res, Polinomio a, Polinomio b){
    
    inicializa_polinomio ( &res);

    if (a->prox == a){
        res = b;
        return;
    }
    if (b->prox == b){
        res = a;
        return;
    }

    No* peratualA = a->prox;
    No* peratualB = b->prox;
    
    while( peratualA != a && peratualB != b){                    // a estrutura percorre a e b simultaneamente onde, ela incrementa em res e, tambem, ja ordena res 

        if ( peratualB->valor.grau == peratualA->valor.grau){

            if ( peratualA->valor.coef - peratualB->valor.coef != 0){

                define_coeficiente ( res, peratualA->valor.grau, peratualA->valor.coef - peratualB->valor.coef);
            }

            peratualA = peratualA->prox;
            peratualB = peratualB->prox;

        }
        else if ( peratualB->valor.grau > peratualA->valor.grau){
            
            define_coeficiente ( res, peratualA->valor.grau, peratualA->valor.coef);

            peratualA = peratualA->prox;

        }
        else if ( peratualA->valor.grau > peratualB->valor.grau){
            
            define_coeficiente ( res, peratualB->valor.grau, peratualB->valor.coef * (-1));

            peratualB = peratualB->prox;

        }
        imprime (res);
    }

        while ( peratualB != b){

            define_coeficiente ( res, peratualB->valor.grau, peratualB->valor.coef);

            peratualB = peratualB->prox;

        }
    
 

        while ( peratualA != a){
            
            define_coeficiente (res, peratualA->valor.grau, peratualA->valor.coef);

            peratualA = peratualA->prox;

        }

    return;
}

/* /\* Computa a multiplicacao dos polinomios a e b colocando o resultado em res.  */
/*  * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. *\/ */
/* void multiplica(Polinomio res, Polinomio a, Polinomio b); */

/* Imprime o polinomio pol no formato do exemplo abaixo
 * [(0,2),(3,-2),(10,5)]
 * onde este polinomio tem 3 coeficientes, o de grau 0 com valor 2, o de grau 3 com valor -2 e o de
 * grau 10 com valor 5. 
 */
void imprime (Polinomio pol){

    No* percorre = pol->prox;
    printf("[");
    while(percorre->prox != pol){
        printf ("(%d,%d),", percorre->valor.grau, percorre->valor.coef);
        percorre = percorre->prox;
    }
    printf ("(%d,%d)]\n", percorre->valor.grau, percorre->valor.coef);
    return;

}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_polinomio (Polinomio *ap_pol){
        
    No* apagando = (*ap_pol)->prox;
    (*ap_pol)->antec->prox = NULL;
    while (apagando->prox != NULL || apagando != NULL){   
        No* apagar = apagando;
        apagando = apagando->prox;
        free (apagar);
    }   
    free (ap_pol); 
    return;
}