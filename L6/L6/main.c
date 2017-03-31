//
//  main.c
//  L6
//
//  Created by Wallace Junior on 18/11/15.
//  Copyright © 2015 Wallace Junior. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define db if(0)
#define true 1
#define false 0

typedef struct ponto{
    int x;
    int y;
    float angulo;
    float distancia;
}ponto;

ponto menor;
ponto* coord = NULL;
ponto* heap;
ponto* points;
int min_heap_size;
int m;

int function_floor(float n, float x){
    int flour;
    flour = floor(n/x);
    return flour;
}

void salvar_o_menor(ponto coord){
    if(coord.y<menor.y){
        menor = coord;
    }
    else if(coord.y==menor.y && coord.x<menor.x){
        menor = coord;
    }
}

void min_heapify(ponto* heap, int comeco, int heap_size){
    int m, l, r;
    ponto aux;
    m=comeco;
    l=2*comeco+1;
    r=2*comeco+2;
    if(heap_size>=l && (heap[l].angulo<heap[m].angulo || (heap[l].angulo==heap[m].angulo && heap[l].distancia<heap[m].distancia))){
        m = l;
    }
    if(heap_size>=r && ((heap[r].angulo<=heap[m].angulo && heap[r].angulo<heap[l].angulo) || (heap[r].angulo==heap[m].angulo && heap[r].distancia<heap[m].distancia))){
        m = r;
    }
    if(m!=comeco){
        aux = heap[m];
        heap[m]=heap[comeco];
        heap[comeco]=aux;
        min_heapify(heap, m, heap_size);
    }
}

ponto heap_extract(ponto* heap, int heap_size){
    ponto val;
    val = heap[0];
    heap[0] = heap[heap_size-1];
    min_heap_size--;
    min_heapify(heap, 0, min_heap_size);
    return val;
}

void bubble_up(ponto* heap, int onde){
    int i, pai;
    ponto aux;
    i = onde;
    if(i==1 || i==2){
        pai = 0;
    }
    else{
        pai = function_floor(i-1, 2);
    }
    while(i!=0 && pai>=0 && ((heap[i].angulo<heap[pai].angulo) || (heap[i].angulo==heap[pai].angulo && heap[i].distancia<heap[pai].distancia))){
        aux = heap[pai];
        heap[pai]=heap[i];
        heap[i] = aux;
        i = pai;
        pai = function_floor(i-1, 2);
    }
}

void heap_insert(ponto coord){
    heap[min_heap_size] = coord;
    min_heap_size++;
    bubble_up(heap, min_heap_size-1);
}

int produto_vetorial(ponto ponto1, ponto ponto2, ponto ponto3){
    return ((ponto2.x-ponto1.x)*(ponto3.y-ponto1.y))-((ponto2.y-ponto1.y)*(ponto3.x-ponto1.x));
}

ponto distancia(ponto coord){
    float deltax, deltay;
    deltax = coord.x-menor.x;
    deltay = coord.y-menor.y;
    coord.distancia = (float) sqrt((double)(pow(deltax,2)+pow(deltay,2)));
    return coord;
}

void convexhull(ponto coord[], int n){
    int i, cross;
    points = (ponto*) calloc(n+1,sizeof(ponto));
    points[0] = menor;
    for(i=1;i<n;i++){
        points[i] = heap_extract(heap, min_heap_size);
    }
    m=1;
    for(i=2;i<n;i++){
        cross = produto_vetorial(points[m-1], points[m], points[i]);
        while(cross<=0){
            if(m==1 && cross==0){
                points[m] = points[i];
            }
            if(m>1){
                m -= 1;
            }
            else if(i==n){
                break;
            }
            else{
                i+=1;
            }
            cross = produto_vetorial(points[m-1], points[m], points[i]);
        }
        m+=1;
        points[m] = points[i];
    }
}

ponto saber_o_angulo(ponto coord, ponto menor){
    coord.angulo = acos((coord.x-menor.x)/sqrt(pow(coord.y-menor.y, 2)+pow(coord.x-menor.x,2)));
    return coord;
}

int main(){
    int n, i, caso;
    caso = 0;
    while(scanf(" %d", &n)!=EOF){
        min_heap_size = 0;
        menor.x = 99999;
        menor.y = 99999;
        coord = (ponto*) calloc(n, sizeof(ponto));
        heap = (ponto*) calloc(n, sizeof(ponto));
        for(i=0;i<n;i++){
            scanf(" %d %d", &coord[i].x, &coord[i].y);
            salvar_o_menor(coord[i]);
        }
        for(i=0;i<n;i++){
            if(coord[i].x!=menor.x || coord[i].y!=menor.y){
                coord[i] = saber_o_angulo(coord[i], menor);
                coord[i] = distancia(coord[i]);
                heap_insert(coord[i]);
            }
        }
        convexhull(coord, n);
        printf("caso %d:\n", caso);
        for(i=0;i<=m;i++){
            printf("%d %d\n", points[i].x, points[i].y);
        }
        printf("\n");
        free(heap);
        free(coord);
        free(points);
        caso++;
    }
}