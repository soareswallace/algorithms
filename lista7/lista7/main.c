//
//  main.c
//  lista7
//
//  Created by Wallace Junior on 12/4/15.
//  Copyright © 2015 Wallace Junior. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct servico{
    int start;
    int finish;
    int valor;
    int duracao;
} servico;

int maxima_data = 0;
int min_heap_size = 0;
servico* trabalhos = NULL;
int* k = NULL;

int function_floor(float n, float x){
    int flour;
    flour = floor(n/x);
    return flour;
}

void min_heapify(servico heap[], int i, int heap_size){
    int m, l, r;
    servico aux;
    m=i;
    l=2*i+1;
    r=2*i+2;
    if(heap_size>l && (heap[l].finish<heap[m].finish || (heap[l].finish==heap[m].finish && heap[l].valor>heap[m].valor))){
        m=l;
    }
    if(heap_size>r && (heap[r].finish<heap[m].finish || (heap[r].finish==heap[m].finish && heap[r].valor>heap[m].valor)) && heap[r].finish<heap[l].finish){
        m=r;
    }
    if(m!=i){
        aux = heap[m];
        heap[m]=heap[i];
        heap[i]=aux;
        min_heapify(heap, m, heap_size);
    }
}

servico heap_extract(servico heap[], int heap_size){
    servico val, aux;
    val = heap[0];
    aux = heap[heap_size-1];
    heap[heap_size-1] = heap[0];
    heap[0] = aux;
    min_heap_size--;
    min_heapify(heap, 0, min_heap_size);
    return val;
}

void bubble_up_min(servico heap[]){
    int i;
    int pai;
    servico aux;
    i = min_heap_size-1;
    if(i==1 || i==2){
        pai = 0;
    }
    else{
        pai = function_floor(i-1, 2);
    }
    while(i!=0 && (heap[i].finish<heap[pai].finish || (heap[i].finish==heap[pai].finish && heap[pai].valor>heap[i].valor)) && pai>=0){
        aux = heap[pai];
        heap[pai]=heap[i];
        heap[i] = aux;
        i = pai;
        pai = function_floor(i-1, 2);
    }
}

void heap_insert(servico heap[], servico add){
    heap[min_heap_size] = add;
    min_heap_size++;
    bubble_up_min(heap);
}


int knapSack(servico* trabalhos, int mes, int n){
    int retorno, m;
    servico comparar;
    k = (int*) malloc(sizeof(int)*maxima_data+1);
    k[0] = 0;
    for(m=1;m<=maxima_data;m++){
        k[m] = k[m-1];
        while(trabalhos[0].finish == m && min_heap_size>0){
            comparar = heap_extract(trabalhos, min_heap_size);
            if(comparar.valor+k[m-comparar.duracao]>k[m]){
                k[m] = comparar.valor+k[m-comparar.duracao];
            }
        }
    }
    retorno = k[maxima_data];
    return retorno;
}

int main(){
    int n=0, i=0, caso;
    caso = 1;
    while(scanf(" %d", &n)!=EOF){
        trabalhos = (servico *)malloc(sizeof(servico)* n);
        for(i=0;i<n;i++){
            scanf(" %d %d %d", &trabalhos[i].start, &trabalhos[i].finish, &trabalhos[i].valor);
            trabalhos[i].duracao = (trabalhos[i].finish-trabalhos[i].start) + 1;
            if(trabalhos[i].finish > maxima_data){
                maxima_data = trabalhos[i].finish;
            }
            heap_insert(trabalhos, trabalhos[i]);
        }
        if(caso>1){
            printf("\n\n");
        }
        printf("caso %d: %d", caso, knapSack(trabalhos, maxima_data,  n));
        caso++;
    }
    free(trabalhos);
    free(k);
}

