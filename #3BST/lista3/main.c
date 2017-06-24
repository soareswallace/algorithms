//
//  main.c
//  lista3
//
//  Created by Wallace Junior on 06/10/15.
//  Copyright © 2015 Wallace Junior. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int seedX;

typedef struct no{
    struct no* left;
    struct no* right;
    int val;
    int altura;
    int ja_passei;
}no;

int maximo_entre_as_alturas(no* left, no* right){
    if(right!=NULL && left!=NULL){
        if(left->altura>right->altura){
            return left->altura;
        }
        else{
            return right->altura;
        }
    }
    if(right==NULL){
        return left->altura;
    }
    else{
        return right->altura;
    }
}

no* add(no* root, int val, no* cur){
    no* novo;
    int atualizar;
    novo = (no*) malloc(sizeof(no));
    if(root==NULL){
        novo->altura = 0;
        novo->val = val;
        novo->right = NULL;
        novo->left = NULL;
        novo->ja_passei = 0;
        printf("%d\n", novo->altura);
        return novo;
    }
    else{
        if(val<root->val){
            root->left = add(root->left, val, root);
            atualizar = maximo_entre_as_alturas(root->left, root->right);
            root->altura = atualizar + 1;
            return root;
        }
        else if(val>root->val){
            root->right = add(root->right, val, root);
            atualizar = maximo_entre_as_alturas(root->left, root->right);
            root->altura = atualizar + 1;
            return root;
        }
        else{
            printf("%d\n", root->altura);
            return root;
        }
    }
}

no* search(no* root, int val){
    if(root==NULL){
        return NULL;
    }
    else{
        if(root->val==val){
            return root;
        }
        else if(val<root->val){
            return search(root->left, val);
        }
        else{
            return search(root->right, val);
        }
    }
}

no* iniciar_a_BST(no* root, int n, int a, int c, int seedX, int m){
    int array[100000];
    int i;
    for(i=0;i<n;i++){
        if(i==0){
            array[0] = seedX;
        }
        else{
            array[i] = (((a*array[i-1])+c)%m);
        }
    }
    for(i=0;i<n;i++){
        root = add(root, array[i], NULL);
    }
    return root;
}

int main(){
    int val=1;
    int n, m, seedX, a, c;
    no* root = NULL;
    scanf(" %d %d %d %d %d", &n, &m, &seedX, &a, &c);
    root = iniciar_a_BST(root, n, a, c, seedX, m);
    scanf(" %d", &val);
    root = add(root, val, NULL);
    /*while(val>=0){
     scanf(" %d", &val);
     root = add(root, val, NULL);
     }*/
    
}