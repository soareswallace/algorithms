//
//  main.c
//  LISTA_5
//
//  Created by Wallace Junior on 31/10/15.
//  Copyright © 2015 Wallace Junior. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define db if(0)


int vertice_que_sao_terminais[100000];
int cont_para_vertices_que_sao_terminais=0;
int min_heap_size=0;
int distancias_ao_primeiro[100000];
#define infinito 999999

typedef struct min_heap{
    int distancia;
    int vertice;
}min_heap;

typedef struct estacao{
    int peso;
    int id_do_vertice;
    struct estacao* next;
}estacao;

typedef struct lista{
    int caminhos_possiveis;
    int key;
    int ja_andei_por_aqui;
    int distancia;
    struct estacao* encadeamento;
}lista;

int function_floor(float n, float x){
    int flour;
    flour = floor(n/x);
    return flour;
}

int vertice_eh_terminal(lista* vertice){
    if(vertice->caminhos_possiveis>2 || vertice->caminhos_possiveis==1){
        return 1;
    }
    else{
        return 0;
    }
}

void ver_cada_conexao(lista* array, int n){
    int i;
    estacao* cur;
    lista mostrar;
    for(i=0;i<n;i++){                                               //FUNCAO AUXILIAR
        mostrar = array[i];
        cur = mostrar.encadeamento;
        db if(cur==NULL){
            printf("Errado %d\n", i);
            exit(1);
        }
       db printf("Andar %d ->", i);
        while(cur!=NULL){
            printf(" %d ", cur->id_do_vertice);
            cur = cur->next;
        }
        printf("\n");
    }
}

void mostrar_terminais(lista *array, int n){
    int i;
    for(i=0;i<n;i++){
        if(vertice_eh_terminal(&array[i])==1){
            vertice_que_sao_terminais[cont_para_vertices_que_sao_terminais] = array[i].key;
           db printf("Terminal %d\n", vertice_que_sao_terminais[cont_para_vertices_que_sao_terminais]);
            cont_para_vertices_que_sao_terminais++;

        }                                                       //FUNCAO AUXILIAR
    }
}

void min_heapify(min_heap* heap, int comeco, int heap_size){
    int m, l, r;
    min_heap aux;
    m=comeco;
    l=2*comeco+1;
    r=2*comeco+2;
    if(heap_size>=l && heap[l].distancia<=heap[m].distancia){
        m = l;
    }
    if(heap_size>=r && heap[r].distancia<=heap[m].distancia && heap[r].distancia<heap[l].distancia){
        m = r;
    }
    if(m!=comeco){
        aux = heap[m];
        heap[m]=heap[comeco];
        heap[comeco]=aux;
        min_heapify(heap, m, heap_size);
    }
}

void bubble_up(min_heap* heap, int onde){
    int i, pai;
    min_heap aux;
    i = onde;
    if(i==1 || i==2){
        pai = 0;
    }
    else{
        pai = function_floor(i-1, 2);
    }
    while(i!=0 && heap[i].distancia<=heap[pai].distancia && pai>=0){
        aux = heap[pai];
        heap[pai]=heap[i];
        heap[i] = aux;
        i = pai;
        pai = function_floor(i-1, 2);
    }
}

int heap_extract(min_heap* heap, int heap_size){
    min_heap val;
    val = heap[0];
    heap[0] = heap[heap_size-1];
    min_heap_size--;
    min_heapify(heap, 0, min_heap_size);
    return val.vertice;
}

void heap_insert(min_heap* heap, int onde, int nova_distancia, int heap_size){
    heap[min_heap_size].vertice = onde;
    heap[min_heap_size].distancia = nova_distancia;
    min_heap_size++;
    bubble_up(heap, min_heap_size-1);
}

void dijkstra(lista* array, int first, int n, min_heap* vertices_com_menor_distancia){
    int v, k;
    estacao* e;
    distancias_ao_primeiro[first] = 0;
    heap_insert(vertices_com_menor_distancia, first, 0, min_heap_size);
    //for(k=0;k<n;k++){
    while(min_heap_size>0){
        v = heap_extract(vertices_com_menor_distancia, min_heap_size);
        e = array[v].encadeamento;
        while(e!=NULL){
            if(distancias_ao_primeiro[v]+e->peso<distancias_ao_primeiro[e->id_do_vertice] || distancias_ao_primeiro[e->id_do_vertice]<0){
                distancias_ao_primeiro[e->id_do_vertice] = distancias_ao_primeiro[v] + e->peso;
                heap_insert(vertices_com_menor_distancia, e->id_do_vertice, distancias_ao_primeiro[e->id_do_vertice], min_heap_size);
            }
            e = e->next;
        }
       // if(min_heap_size==0){
       //     k = n;
     //   }
    }
}

void fazer_a_conexao(lista* andar1, lista* andar2, int term1, int term2, int distancia, min_heap* heap){
    estacao* conexao_para_term1;
    estacao* conexao_para_term2;
    estacao* cur;
    conexao_para_term1 = (estacao*) calloc(sizeof(estacao), 1);
    conexao_para_term2 = (estacao*) calloc(sizeof(estacao), 1);
    if(andar1->ja_andei_por_aqui!=1 && andar2->ja_andei_por_aqui!=1){
        //ANDARES
        andar1->ja_andei_por_aqui = 1;
        andar1->caminhos_possiveis++;
        andar2->ja_andei_por_aqui = 1;
        andar2->caminhos_possiveis++;
        //FASE_2
        andar1->encadeamento = conexao_para_term1;
        conexao_para_term1->peso = distancia;                  //no andar do terminal 1, entrou  terminal 2
        conexao_para_term1->id_do_vertice = term2;
        conexao_para_term1->next = NULL;
        //ESPACO EM BRANCO PARA DIVIDIR AS CONEXOES
        andar2->encadeamento = conexao_para_term2;
        conexao_para_term2->peso = distancia;                  //no andar do terminal 2, entrou  terminal 1
        conexao_para_term2->id_do_vertice = term1;
        conexao_para_term2->next = NULL;
    }
    else if(andar1->ja_andei_por_aqui==1 && andar2->ja_andei_por_aqui!=1){
        cur = andar1->encadeamento;
        andar1->caminhos_possiveis++;
        while(cur->next!=NULL){
            cur = cur->next;
        }
        cur->next = conexao_para_term1;
        conexao_para_term1->peso = distancia;                  //no andar do terminal 1, entrou  terminal 2
        conexao_para_term1->id_do_vertice = term2;
        conexao_para_term1->next = NULL;
        andar2->ja_andei_por_aqui = 1;
        andar2->caminhos_possiveis++;
        andar2->encadeamento = conexao_para_term2;
        conexao_para_term2->peso = distancia;                  //no andar do terminal 2, entrou  terminal 1
        conexao_para_term2->id_do_vertice = term1;
        conexao_para_term2->next = NULL;
    }
    else if(andar1->ja_andei_por_aqui!=1 && andar2->ja_andei_por_aqui==1){
        andar1->caminhos_possiveis++;
        andar1->encadeamento = conexao_para_term1;
        andar1->ja_andei_por_aqui=1;
        conexao_para_term1->peso = distancia;                  //no andar do terminal 1, entrou  terminal 2
        conexao_para_term1->id_do_vertice = term2;
        conexao_para_term1->next = NULL;
        cur = andar2->encadeamento;
        while(cur->next!=NULL){
            cur = cur->next;
        }
        cur->next = conexao_para_term2;
        conexao_para_term2->peso = distancia;                  //no andar do terminal 2, entrou  terminal 1
        conexao_para_term2->id_do_vertice = term1;
        andar2->caminhos_possiveis++;
        conexao_para_term2->next = NULL;
    }
    else{
        andar1->caminhos_possiveis++;
        andar2->caminhos_possiveis++;
        cur = andar1->encadeamento;
        while(cur->next!=NULL){
            cur = cur->next;
        }
        cur->next = conexao_para_term1;
        conexao_para_term1->peso = distancia;
        conexao_para_term1->id_do_vertice = term2;
        conexao_para_term1->next = NULL;
        cur = andar2->encadeamento;
        while(cur->next!=NULL){
            cur = cur->next;
        }
        cur->next = conexao_para_term2;
        conexao_para_term2->peso = distancia;
        conexao_para_term2->id_do_vertice = term1;
        conexao_para_term2->next = NULL;
    }
}

void setar_distancias(int* distancias, int n){
    int i;
    for(i=0;i<n;i++){
        distancias_ao_primeiro[i] = -1;
    }
}

void make_a_conection(int term1, int term2, int distancia, lista* array, min_heap* heap){
    if(array[term1].key != term1){
        array[term1].key = term1;
    }
    if(array[term2].key != term2){
        array[term2].key = term2;
    }
    fazer_a_conexao(&array[term1], &array[term2], term1, term2, distancia, heap);
}

void liberar_encademaento(estacao* encadeamento){
    if(encadeamento!=NULL){
        liberar_encademaento(encadeamento->next);
        free(encadeamento);
    }
}

void liberar_memoria(lista* array, int n){
    int i;
    for(i=0;i<n;i++){
        liberar_encademaento(array[i].encadeamento);
    }
    free(array);
}

int main(){
    int i,n, m, caso=0, term1, term2, distancia, cont;
    lista* array;
    int* distancias;
    min_heap* vertices_com_menor_distancia;
    while(scanf(" %d %d", &n, &m)!=EOF){
        cont_para_vertices_que_sao_terminais = 0;
        if(caso!=0){
            printf("\n\n");
        }
        vertices_com_menor_distancia = (min_heap*) calloc(sizeof(min_heap), n);
        distancias = (int*) calloc(sizeof(int), n);
        array = (lista*) calloc(sizeof(lista), n);
        min_heap_size = 0;
        for(i=0;i<m;i++){
            scanf(" %d %d %d", &term1, &term2, &distancia);
            make_a_conection(term1, term2, distancia, array, vertices_com_menor_distancia);
        }
        setar_distancias(distancias_ao_primeiro, n);
        mostrar_terminais(array, n);
        printf("caso %d", caso);

        for(cont=0;cont<cont_para_vertices_que_sao_terminais;cont++){
            if(distancias_ao_primeiro[vertice_que_sao_terminais[cont]]==-1){
                dijkstra(array, vertice_que_sao_terminais[cont], n, vertices_com_menor_distancia);
            //   printf(" '%d(%d)'", distancias_ao_primeiro[vertice_que_sao_terminais[cont]], vertice_que_sao_terminais[cont]);
               printf("\n0");
            }
            else{
              printf(" %d",distancias_ao_primeiro[vertice_que_sao_terminais[cont]]);
            }
        }
        //ver_cada_conexao(array, n);
        liberar_memoria(array, n);
        free(distancias);
        free(vertices_com_menor_distancia);
        caso++;
    }
    printf("\n\n");
}