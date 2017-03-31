#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int kingsizemin = 0; //heap size min

typedef struct coord{
    int x;
    int y;
    float angulo;
    float distancia;
}coord;

coord *hippie;
coord menor;

void bubblegum_min(coord *hippie){ //a.k.a bubbleup
    int i = kingsizemin;
    coord aux;
    while(i>1 && hippie[i].angulo <= hippie[i/2].angulo){
        aux = hippie[i];
        hippie[i] = hippie[i/2];
        hippie[i/2] = aux;
        i = i/2;
    }
}

void* heapifyvos_minimus(coord *hippie, int i){ //a.k.a Heapify
    int m = i;
    coord aux;
    int l = 2*i, r = (2*i + 1);
    if(kingsizemin >= l && hippie[l] < hippie[m]){
        m = l;
    }
    if(kingsizemin >= r && hippie[r] < hippie[m]){
        m = r;
    }
    if(m != i){
        aux = hippie[m];
        hippie[m] = hippie[i];
        hippie[i] = aux;
        heapifyvos_minimus(hippie, m);
    }
}

coord ditadura_min(coord *hippie){ //a.k.a Hippie Extract ou mejor Heap Extract
    coord opression = hippie[1];
    coord aux;
    aux = hippie[1];
    hippie[1] = hippie[kingsizemin];
    hippie[kingsizemin] = aux;
    kingsizemin = kingsizemin - 1;
    heapifyvos_minimus(hippie, 1);
    return opression;
}

coord* hippiesunidos_min(coord *hippie, coord valor){ //Hippies FUCKING INSERT
    hippie[kingsizemin+1] = valor;
    kingsizemin = kingsizemin + 1;
    bubblegum_min(hippie);
    return hippie;
}

int ccw(coord p1, coord p2, coord p3){ //Graham Scan pt1
    int e, r;
    e = (p2.x - p1.x)*(p3.y - p1.y);
    r = (p2.y - p1.y)*(p3.x - p1.x);
    return e - r;
}

void calcAngulo(coord *p_menor_y, coord *p2){
    float hipotenusa, cateto_adja;
    
    hipotenusa = sqrt(pow((p_menor_y->x - p2->x), 2) + pow((p_menor_y->y - p2->y),2));
    cateto_adja = (p2->x - p_menor_y->x);
    
    p2->angulo = acos(hipotenusa/cateto_adja);
}

double distancia(coord *a, coord* b){
    double distanciaux;
    distanciaux = sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) *(a->y - b->y));
    return distanciaux;
}

void menor_ponto(coord *compara){
    if(compara->y < hippie->y){
        hippie = compara;
    }
    if(compara->y == hippie->y){
        if(compara->x < hippie->x){
            hippie = compara;
        }
    }
}

coord organize(coord *hippie, int N){
    coord aux;
    aux = ditadura_min(hippie); //ditadura é o nome da função heap extract
    return aux;
}

int* graham_scan(coord* hippie, int N){
    coord *points;
    points = (coord*) malloc(sizeof(coord));
    int i;
    points[0] = menor;
    
    for(i=1; i<N; i++){
        points[i] = organize(points, N);
    }
    
    int M = 1;
    
    for(i = 2; i<N; i++){
        while(ccw(points[M-1], points[M], points[i]) <= 0){
            if (M > 1){
                M -= 1;
            }
            else{
                i += 1;
            }
            M += 1;
            if(M==1 && ccw(points[M-1], points[M], points[i]) ==0 ){
                points[M] = points[i];
            }
        }
    }
}

int main(){
    hippie = (coord *) malloc(sizeof(coord));
    int N, C = 0, i, j;
    coord *aux;
    aux = (coord *) malloc(sizeof(coord));
    
    while(scanf("%d", &N)!=EOF){
        for(i=0; i<N; i++){
            scanf(" %d %d", &hippie[i].x, &hippie[i].y);
            menor_ponto(hippie);
        }
        
        for(i=0; i<N; i++){
            calcAngulo(&menor, &hippie[i]);
            hippie[i].distancia = distancia(&menor, hippie);
            hippie[kingsizemin] = hippie[i];
            kingsizemin++;
            bubbleup(hippie);
        }
        graham_scan(hippie, N);
        printf("caso %d\n", C);
        C++;
    }
    return 0;
}

