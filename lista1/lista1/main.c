//
//  main.c
//  lista1
//
//  Created by Wallace Junior on 9/9/15.
//  Copyright (c) 2015 Wallace Junior. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    int valor;
    struct no* next;
}no;

typedef struct elemento{
    no* caixa;
    int estrutura;                          //0 SE A ESTRUTURA FOR FILA, 1 SE A ESTRUTURA FOR PILHA
    struct no* front;
    struct no* rear;
    struct no* top;
}elemento;

int tipoDeEstrutura(elemento* cada){
    if(cada->estrutura){
        return 1;
    }
    else{
        return 0;
    }
}

elemento* stackToQueue(elemento* cada){
    elemento* cur;
    cur = cada;
    cur->front = cur->caixa->next;
    while(cur->caixa->next!=NULL){
        cur->caixa = cur->caixa->next;
    }
    cur->rear = cur->caixa;
    return cur;
}

elemento* queueToStack(elemento* cada){
    elemento* cur;
    cur = cada;
    cur->top = cur->front;
    return cur;
}

elemento* transform(elemento* cada){
    elemento *cur;
    cur = cada;
    if(tipoDeEstrutura(cur)){
        cur = stackToQueue(cur);
        return cur;
    }
    else{
        cur = queueToStack(cur);
        return cur;
    }
}



int empty_queue(no* front, no* rear){
    if(front==rear){
        return 1;
    }
    else{
        return 0;
    }
}

elemento* enqueue (elemento* queue, int val){
    no* novo;
    no* cur;
    cur = queue->front;
    novo = (no*) malloc(1*sizeof(no));
    if(empty_queue(queue->front, queue->rear)){
        queue->caixa->next = NULL;
        queue->caixa = novo;
        novo->next = NULL;
        novo->valor = val;
        queue->rear = novo;
        queue->estrutura = 0;
    }
    else{
        while(cur!=queue->rear){
            cur = cur->next;
        }
        novo->next = NULL;
        cur->next = novo;
        novo->valor = val;
        queue->rear = novo;
    }
    return queue;
}

elemento* dequeue (elemento* queue){
    no* saida;
    if(empty_queue(queue->front, queue->rear)){
        printf("vazia\n");
    }
    else{
        saida = queue->front->next;
        queue->front->next = saida->next;
        if(queue->front->next==NULL){
            queue->rear = queue->front;
        }
        free(saida);
    }
    return queue;
}

int empty_stack(elemento* head){
    if(head->caixa->next==NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int stack_peek(elemento* head){
    return head->caixa->next->valor;
}

elemento* stack_pop(elemento* head){
    no* saida;
    elemento* cur;
    saida = (no*) malloc(1*sizeof(no));
    if(empty_stack(cur)==0){
        saida = cur->caixa->next;
        cur->caixa->next = saida->next;
        printf("pop: %d\n", saida->valor);
        free(saida);
        return cur;
    }
    else{
        return cur;
    }
    
}

elemento* stack_push(elemento* head, int val){
    no* novo;
    elemento* cur;
    novo = (no* ) malloc(1*sizeof(no));
    if(empty_stack(cur)==1){
        cur->caixa->next = novo;
        novo->next = NULL;
        novo->valor = val;
        return cur;
    }
    else{
        novo->next = cur->caixa->next;
        cur->caixa->next = novo;
        novo->valor = val;
        return cur;
    }
}






int main() {
    int val;
    int posicao;
    int iniciou=0;
    char op[3];
    no *head;
    elemento* cada;
   /* while(scanf(" %3s", op)!=EOF){
        head = (no* ) malloc(1*sizeof(no));
        cada = (elemento*) malloc(1*sizeof(elemento));
        cada->front = head;
        cada->rear = head;
        if(strcmp(op, "INS")==0){
            scanf(" %d %d", &posicao, &val);
            if(iniciou==0){
                cada = enqueue(cada, val);
                iniciou = 1;
            }
            else{
                if(tipoDeEstrutura(cada)){
                    cada =  stack_push(cada, val);
                }
                else{
                    cada = enqueue(cada, val);
                }
            }
        }
        printf("\n");

    }
    */
    head = (no* ) malloc(1*sizeof(no));
    cada = (elemento*) malloc(1*sizeof(elemento));
    cada->front = head;
    cada->rear = head;
    while(val>0){
        scanf(" %d", &val);
        if(iniciou==0){
            cada = enqueue(cada, val);
            iniciou = 1;
        }
        else{
            if(tipoDeEstrutura(cada)){
                cada =  stack_push(cada, val);
            }
            else{
                cada = enqueue(cada, val);
            }
        }
    }
    
    if(tipoDeEstrutura(cada)){
        printf("%d\n", cada->top->valor);
    }
    else{
        printf("%d", cada->front->valor);
    }
    
    free(cada);
}
