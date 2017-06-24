//
//  main.c
//  lista2
//
//  Created by Wallace Junior on 20/09/15.
//  Copyright © 2015 Wallace Junior. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  cova{
    int val;
    int jazigo;
    int deletado;
    struct cova* next_cova;
}cova;

typedef struct andar{
    int key;
    int capacidade;
    int preenchido;
    int andares;
    struct andar* next_andar;
    struct cova* next_cova;
}andar;

int tem_espaco(andar* hash){
    if(hash->capacidade>hash->preenchido){
        return 1;
    }                                                      //RETORNA 1 SE O ANDAR CHAMADO HA ESPACO, 0 C.C.
    else{
        return 0;
    }
}

andar* procurar(andar* hash, int chave){
    andar* cur;
    cur = hash;
    while(cur->key!=chave){
        cur = cur->next_andar;
    }
    return cur;
}

andar* andar_com_espaco(andar* hash, andar* cur ,int chave){
    while(!tem_espaco(cur) && cur->key!=chave){
        cur = cur->next_andar;
        if(cur==NULL){
            cur = hash;
        }                                                   //RETORNA NULL CASO NAO ACHE ESPACO VAZIO
    }
    if(cur==NULL || cur->key==chave){
        return NULL;
    }
    else{
        return cur;
    }
}


andar* add(andar* hash, andar* cur ,int morto, int chave, int envio){            //0 - para adicao do usuario, 1-para rehasing
    cova* novo;
    cova* porta;
    porta = cur->next_cova;
    novo = (cova*) malloc(sizeof(cova));
    if(cur->next_cova==NULL){
        cur->next_cova = novo;
        novo->next_cova = NULL;
        novo->jazigo = 0;
        novo->deletado = 0;
        novo->val = morto;
        cur->preenchido++;
        novo->deletado = 0;
        if(envio==0){
            printf(" %d.%d\n", chave, 0);
        }
        return hash;
    }
    else{
        while(porta->next_cova!=NULL){
            porta = porta->next_cova;
        }
        novo->next_cova = porta->next_cova;                  //ADICIONA NO PRIMEIRO NO DO ANDAR
        porta->next_cova = novo;
        novo->jazigo = porta->jazigo + 1;
        novo->val = morto;
        cur->preenchido++;
        novo->deletado = 0;
        if(!envio){
            printf(" %d.%d\n", chave, novo->jazigo);
        }
        return hash;
    }
}

andar* iniciar_tabela(andar* hash, int i, int l, int m){
    andar* novo;
    andar* cur;
    cur = hash;
    novo = (andar*) malloc(1*sizeof(andar));                //SO SERVE PARA INICIAR A TABELA
    while(cur->next_andar!=NULL){
        cur = cur->next_andar;
    }
    cur->next_andar = novo;
    novo->next_cova = NULL;
    novo->key = i;
    novo->next_andar=NULL;
    novo->capacidade = l;
    novo->preenchido = 0;
    novo->andares = m;
    return cur;
}

cova* achar_o_morto(andar* hash, int morto){
    cova* porta;
    porta = hash->next_cova;
    while(porta!=NULL && porta->val!=morto){
        porta = porta->next_cova;
    }
    if(porta==NULL || porta->deletado==1){
        return NULL;
    }
    else{
        return porta;
    }
    
}

andar* criar_nova_tabela( andar* hash,int m, int l, int morto){
    andar* novo;
    andar* adicionar;
    andar* cur;
    cur = hash;
    cova* porta;
    int chave;
    int i;
    novo = (andar*) malloc(1*sizeof(andar));
    novo->key = 0;
    novo->next_andar = NULL;
    novo->next_cova = NULL;
    novo->preenchido = 0;
    novo->capacidade = l;
    for(i=1;i<m;i++){
        iniciar_tabela(novo, i, l, m);
    }
    while(cur!=NULL){
        porta = cur->next_cova;
        while(porta!=NULL){
            if(porta->deletado!=1){
                chave = porta->val%m;
                adicionar = procurar(novo, chave);
                if(!tem_espaco(adicionar)){
                    adicionar = adicionar->next_andar;
                    adicionar = andar_com_espaco(novo, adicionar, chave);
                    novo = add(novo , adicionar, porta->val, chave, 1);
                }
                else{
                    novo = add(novo , adicionar, porta->val, chave, 1);
                }
            }
            porta = porta->next_cova;
        }
        cur = cur->next_andar;
    }
    novo->andares = m;
    return novo;
}



andar* colocar_no_andar(andar* hash, int chave, int morto, int l, int m){
    andar* cur;
    andar* adicionar;
    cur = procurar(hash, chave);
    if(!tem_espaco(cur)){
        if(cur->next_andar!=NULL){
            cur = cur->next_andar;
        }
        else{
            cur = hash;
        }
        cur = andar_com_espaco(hash, cur, chave);
        if(cur!=NULL){                                      //se a funcao andar_com_espaco retornar NULL
            hash = add(hash, cur, morto, cur->key, 0);      //quer dizer que nao ha espacos vazios
            return hash;                                     //sendo necessario fazer o hasing novamente
        }
        else{
            hash = criar_nova_tabela(hash, 2*m+1 , l, morto);
            adicionar = procurar(hash, morto%hash->andares);
            hash = add(hash, adicionar, morto, morto%(2*m+1), 0);
            return hash;
        }
    }
    else{
        hash = add(hash ,cur, morto, chave, 0);
        return hash;
    }
}

void operacao_delete(andar*hash, int chave, int morto){
    andar* cur;
    cova* body;
    int achou = 0;
    int sair = 0;
    cur = procurar(hash, chave);
    while(achou==0 && sair == 0){
        body = achar_o_morto(cur, morto);
        if(body!=NULL && body->deletado!=1){
            printf(" %d.%d\n", cur->key, body->jazigo);
            body->deletado = 1;
            achou = 1;
        }
        else{
            cur = cur->next_andar;
        }
        if(cur==NULL){
            cur = hash;
        }
        if(tem_espaco(cur)){
            sair = 1;
        }
        if(cur->key==chave){
            sair = 1;
        }
    }
    if(achou==0){
        printf(" ?.?\n");
    }
}

void operacao_qry(andar* hash, int morto, int chave){
    andar* cur;
    cova* porta;
    int achou = 0;
    int sair = 0;
    cur = procurar(hash, chave);
    while(sair == 0 && achou==0){
        porta = achar_o_morto(cur, morto);
        if(porta!=NULL && porta->deletado!=1){
            printf(" %d.%d\n", cur->key, porta->jazigo);
            achou = 1;
        }
        else{
            cur = cur->next_andar;
        }
        if(cur==NULL){
            cur = hash;
        }
        if(tem_espaco(cur)){
            sair = 1;
        }
        if(cur->key==chave){
            sair = 1;
        }
    }
    if(!achou){
        printf(" ?.?\n");
    }
}

int main(){
    andar* hash;
    int i, m, l, morto, chave;
    int n =0 ;
    char op[4];
    hash = (andar*) malloc(1*sizeof(andar));
    hash->key = 0;
    hash->next_andar = NULL;
    hash->next_cova = NULL;
    scanf(" %d %d", &m , &l);
    hash->capacidade = l;
    hash->preenchido = 0;
    hash->andares = m;
    for(i=1;i<m;i++){
        iniciar_tabela(hash, i, l, m);
    }
    while(scanf(" %3s %d", op, &morto)!=EOF){
        chave = morto%hash->andares;
        printf("%d", n);
        n++;
        if(strcmp("ADD", op)==0){
            hash = colocar_no_andar(hash, chave, morto, l, hash->andares);
        }
        else if(strcmp("QRY", op)==0){
            operacao_qry(hash, morto, chave);
        }
        else{
            operacao_delete(hash, chave, morto);
        }
    }
    
}