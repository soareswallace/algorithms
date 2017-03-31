//
//  main.c
//  lista4
//
//  Created by Wallace Junior on 14/10/15.
//  Copyright © 2015 Wallace Junior. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int max=-1;
int med=-1;
int min=-1;
int min_heap_size=0;
int max_heap_size=0;



int function_floor(float n, float x){
    int flour;
    flour = floor(n/x);
    return flour;
}


int retorna_mediano(int heap[]){
    int x;
    x = function_floor(min_heap_size, 2);
    return heap[x];
}

void min_heapify(int heap[], int i, int heap_size){
    int m, l, r, aux, filho_esq, filho_dir, pai;
    m=i;
    l=2*i+1;
    r=2*i+2;
    if(heap_size>l && heap[l]<=heap[m]){
        m=l;
    }
    if(heap_size>r && heap[r]<=heap[m]){
        m=r;
    }
    if(m!=i){
        aux = heap[m];
        heap[m]=heap[i];
        heap[i]=aux;
        min_heapify(heap, m, heap_size);
    }
}

void max_heapify(int heap[], int i, int heap_size){
    int m, l, r, aux, filho_esq, filho_dir, pai;
    m=i;
    l=2*i+1;
    r=2*i+2;
    if(heap_size>l && heap[l]>=heap[m]){
        m=l;
    }
    if(heap_size>r && heap[r]>=heap[m]){
        m=r;
    }
    if(m!=i){
        aux = heap[m];
        heap[m]=heap[i];
        heap[i]=aux;
        max_heapify(heap, m, heap_size);
    }
}


int heap_extract(int heap[], int heap_size){
    int val, aux;
    if(heap_size==min_heap_size){
        val = heap[0];
        aux = heap[heap_size-1];
        heap[heap_size-1] = heap[0];
        heap[0] = aux;
        heap[heap_size-1]=-1;
        min_heap_size--;
        min_heapify(heap, 0, min_heap_size);
        return val;
    }
    else{
        val = heap[0];
        aux = heap[heap_size-1];
        heap[heap_size-1] = 0;
        heap[0] = aux;
        max_heap_size--;
        max_heapify(heap, 0, max_heap_size);
        return val;
    }
}

void bubble_up_min(int heap[]){
    int i;
    int pai;
    int aux;
    i = min_heap_size-1;
    if(i==1 || i==2){
        pai = 0;
    }
    else{
        pai = function_floor(i-1, 2);
    }
    while(i!=0 && heap[i]<=heap[pai] && pai>=0){
        aux = heap[pai];
        heap[pai]=heap[i];
        heap[i] = aux;
        i = pai;
        pai = function_floor(i-1, 2);
    }
}

void add_min(int heap[], int val){
    heap[min_heap_size]=val;
    if(min_heap_size==0){
        max = val;
        min = val;
        med=val;
        min_heap_size++;
    }
    else{
        if(val>max){
            heap[min_heap_size]=val;
            max = val;
            min_heap_size++;
        }
        else{
            heap[min_heap_size]=val;
            min_heap_size++;
            bubble_up_min(heap);
            med = heap[function_floor(min_heap_size, 2)];
            if(val<min){
                min = val;
            }
        }
    }
}

void bubble_up_max(int heap[]){
    int i;
    int pai;
    int aux;
    i = max_heap_size-1;
    if(i==1 || i==2){
        pai = 0;
    }
    else{
        pai = function_floor(i-1, 2);
    }
    while(i!=0 && heap[i]>=heap[pai] && pai>=0){
        aux = heap[pai];
        heap[pai]=heap[i];
        heap[i] = aux;
        i = pai;
        pai = function_floor(i-1, 2);
    }
}

void add_max(int heap[], int val){
    heap[max_heap_size]=val;
    if(max_heap_size==0){
        max_heap_size++;
    }
    else{
        heap[max_heap_size]=val;
        max_heap_size++;
        bubble_up_max(heap);
        med = heap[function_floor(max_heap_size, 2)];
    }
}

int* resete(int heap[]){
    int* new_array;
    new_array = (int*) malloc(sizeof(int)*10000);
    return new_array;
}



int main(){
    int med=-1;
    int val=1;
    char op[4];
    int min_heap[300000];
    int max_heap[300000];
    int move;
    while(scanf(" %3s", op)!=EOF){
        if(strcmp(op, "ADD")==0){
            scanf(" %d", &val);
            if(med<0){
                max = val;
                med = val;
                min = val;
                add_min(min_heap, min);
                printf("%d %d %d\n", min, med, max);
            }
            else{
                if(val<med){
                    add_max(max_heap, val);
                    if(max_heap_size-min_heap_size>1){
                        move = heap_extract(max_heap, max_heap_size);
                        add_min(min_heap, move);
                        med = min_heap[0];
                    }
                    else{
                        if(max_heap_size>min_heap_size){
                            med = max_heap[0];
                        }
                        if(max_heap_size==min_heap_size){
                            med = min_heap[0];
                        }
                    }
                }
                else{
                    add_min(min_heap, val);
                    if(min_heap_size-max_heap_size>1){
                        move = heap_extract(min_heap, min_heap_size);
                        add_max(max_heap, move);
                        med = min_heap[0];
                    }
                    else{
                        if(min_heap_size>max_heap_size){
                            med = min_heap[0];
                        }
                        if(max_heap_size==min_heap_size){
                            med = min_heap[0];
                        }
                    }
                }
                if(val<min){
                    min=val;
                }
                if(val>max){
                    max = val;
                }
                printf("%d %d %d\n", min, med, max);
            }
        }
        if(strcmp(op, "MIN")==0){
            if(min>=0){
                printf("%d\n", min);
            }
            else{
                printf("%d\n", -1);
            }
        }
        if(strcmp(op, "MAX")==0){
            if(max>0){
                printf("%d\n", max);
            }
            else{
                printf("%d\n", -1);
            }
        }
        if(strcmp(op, "MED")==0){
            if(med>0){
                printf("%d\n", med);
            }
            else{
                printf("%d\n", -1);
            }
        }
        if(strcmp(op, "RES")==0){
            printf("%d\n", min_heap_size+max_heap_size);
            max = -1;
            min = -1;
            med = -1;
            max_heap_size = 0;
            min_heap_size = 0;
        }
    }
}