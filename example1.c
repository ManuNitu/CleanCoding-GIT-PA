/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa    
                                                                                                                                                                                                                                                                                                                            

typedef struct Graph {
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct Stack {
    int t;
    int *arr;
    int scap;
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STK *s) {
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;

    g->vis[v_nr] = 1;

    printf("%d ", v_nr);
    push(v_nr, s);

    while (aux != NULL) {
        int con_ver = aux->data;

        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);

        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr) {
    int src, dest;
    printf("Adauga %d muchii:\n", edg_nr);

    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g) {
    for (int i = 0; i < g->v; i++)
        g->vis[i] = 0;
}

void canbe(GPH *g, int nrv, STK *s1, STK *s2) {
    int ans = 0;
    for (int i = 0; i < nrv; i++) {
        DFS(g, s1, i);
        wipe(g);
        DFS(g, s2, i);

        for (int j = 0; j < nrv; j++) {
            if (s1->arr[j] == j && s2->arr[j] == j) {
                ans = 1;
                break;
            }
        }
        if (ans) break;
    }

    if (ans)
        printf("Există drum direct între cele două restaurante.\n");
    else
        printf("Nu există drum direct între cele două restaurante.\n");
}

int main() {
    int nrv;
    int edg_nr;

    printf("Câte noduri are graful? ");
    scanf("%d", &nrv);

    printf("Câte muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr);

    canbe(g, nrv, s1, s2);

    return 0;
}