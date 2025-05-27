#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VII 'X'
#define MOARTE '+'

typedef struct {
    int l, c;
} Nod;

typedef struct {
    int lungime;
    Nod *lant;
}LH;

typedef struct Celula{
    int l,c;
    struct Celula *next;
}Celula;

typedef struct Node{
    int numar;
    Celula *celule;
    struct Node *next;
}Node;

typedef struct Arbore{
    char **matrice;
    int gen;
    struct Arbore *left,*right;
}Arbore;

char **generatie1(int n, int m, char **matrice);
Arbore *construire(int n, int m, int generatie_curenta, int k, char **matrice);
void preorder(Arbore *root, FILE *fisier, int n, int m);
void push(Node **top,int numar,Celula *lista);
Celula *compar(char **a,char **b,int n,int m);
void citire_date(FILE *fisier,int *numar_task, int *n, int *m, int *k, char ***matrice);
char **generatie(int n,int m,char **matrice);
char **copie_matrice(int n,int m, char **original);
void print_stiva(FILE *fisier,Node *stiva);
void free_matrice(char **matrice,int n);
void bonus(Node *top,int n,int m,char **matrice);
void scriu_bonus(FILE *fisier2,int n,int m,char **matrice);


void elibereaza_arbore(Arbore *root, int n);
LH lantH(char **mat, int n, int m);
void scrie_lant(FILE *f,LH lant);
void task4(Arbore *root, int n, int m,FILE *fout);
char **citeste_matrice(FILE *f, int n, int m);