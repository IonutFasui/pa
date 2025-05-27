#include "gameoflife.h"

void push(Node** top, int numar,Celula *lista) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->numar = numar;
    newNode->celule=lista;
    newNode->next = *top;
    *top = newNode;
}

Celula *compar(char **a,char **b,int n,int m)
{
    Celula *lista = NULL;
    for(int i=n-1;i>=0;i--)
    {
        for(int j=m-1;j>=0;j--)
        {
            if(a[i][j]!=b[i][j])
            {
                Celula *newNode = (Celula*)malloc(sizeof(Celula));
                newNode->l=i;
                newNode->c=j;
                newNode->next=lista;
                lista=newNode;
            }
        }
    }
    return lista;
}


void citire_date(FILE *fisier,int *numar_task,int *n,int *m,int *k,char ***matrice) 
{
    
    if(fisier == NULL){
        printf("Fisierul nu a putut fi deschis");
        exit(1);
    }
    fscanf(fisier,"%d",numar_task);
    fscanf(fisier,"%d %d",n,m);
    fscanf(fisier,"%d",k);

    *matrice=(char **)malloc(*n * sizeof(char *));
    for (int i=0;i<*n;i++) {
        (*matrice)[i]=(char *)malloc(*m * sizeof(char));
    }
    for (int i=0;i<*n;i++) {
        for (int j=0;j<*m;j++) {
            fscanf(fisier," %c",&((*matrice)[i][j])); 
        }
    }
}

char **copie_matrice(int n,int m,char **matrice)
{
    char **copie = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        copie[i] = malloc(m * sizeof(char));
        for (int j = 0; j < m; j++)
            copie[i][j] = matrice[i][j];
    }
    return copie;
}

void free_matrice(char **matrice,int n)
{
    for (int i=0;i<n;i++)
        free(matrice[i]);
    free(matrice);
}
char **generatie1(int n, int m, char **matrice) 
{

    char **noua=(char **)malloc(n * sizeof(char *));
    for (int i=0;i<n;i++)
        noua[i]=(char *)malloc(m * sizeof(char));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int numar_vecini=0;
            for(int x=-1;x<=1;x++)
            {
                for(int y=-1;y<=1;y++)
                {
                    if(x==0 && y==0) 
                        continue;
                    int pozi=i+x,pozj=j+y;
                    if(pozi >= 0 && pozi < n && pozj >= 0 && pozj < m && matrice[pozi][pozj] == VII)
                        numar_vecini++;
                }
            }
            if (matrice[i][j] == MOARTE && numar_vecini == 2)
                noua[i][j] = VII;
            else
                noua[i][j] = matrice[i][j];
        }
    }
    return noua;
}
char **generatie(int n,int m,char **matrice)
{
    char **noua_matrice=(char **)malloc(n * sizeof(char *));
    for (int i=0;i<n;i++)
        noua_matrice[i]=(char *)malloc(m * sizeof(char));

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int numar_vecini=0;
            for(int x=-1;x<=1;x++)
            {
                for(int y=-1;y<=1;y++)
                {
                    if(x==0 && y==0) 
                        continue;
                    int pozi=i+x,pozj=j+y;
                    if(pozi >= 0 && pozi < n && pozj >= 0 && pozj < m && matrice[pozi][pozj] == VII)
                        numar_vecini++;
                }
            }
            if(matrice[i][j] == VII)
            {
                if(numar_vecini<2 || numar_vecini>3)
                    noua_matrice[i][j]=MOARTE;
                else
                    noua_matrice[i][j]=VII;
            }
            else
            {
                if(numar_vecini==3)
                    noua_matrice[i][j]=VII;
                else
                    noua_matrice[i][j]=MOARTE;
            }
        }
    }
    return noua_matrice;
}

void bonus(Node *top,int n,int m,char **matrice)
{
    int i,j;
    while(top)
    {
        Celula *cel=top->celule;
        while(cel)
        {
            i=cel->l;
            j=cel->c;
            if (i>=0 && i<n && j>=0 && j<m)
            {
                if (matrice[i][j] == VII)
                    matrice[i][j]=MOARTE;
                else
                    matrice[i][j]=VII;
            }   
            cel=cel->next;
        }
        top=top->next;
    }
}

void scriu_bonus(FILE *fisier2,int n,int m,char **matrice)
{   
    if(fisier2 == NULL)
    {
        printf("Fisierul nu poate fi deschis!");
        exit(1);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            fputc(matrice[i][j],fisier2);
        fputc('\n',fisier2);
    }
}

Arbore *construire(int n, int m, int generatie_curenta, int k, char **matrice) 
{
    if (generatie_curenta > k) return NULL;
    Arbore *nod = (Arbore *)malloc(sizeof(Arbore));
    nod->gen = generatie_curenta;
    nod->matrice = copie_matrice(n, m, matrice);

    char **mat1 = generatie1(n, m, matrice);
    char **mat2 = generatie(n, m, matrice);

    nod->left = construire(n, m, generatie_curenta + 1, k, mat1);
    nod->right = construire(n, m, generatie_curenta + 1, k, mat2);

    free_matrice(mat1, n);
    free_matrice(mat2, n);
    return nod;
}

void scriere_mat(FILE *fisier,char **matrice,int n,int m) 
{
    if(fisier == NULL)
    {
        printf("Fisierul nu potae fi deschis!");
        exit(1);
    }
    for (int i=0;i<n;i++) 
    {
        for (int j=0;j<m;j++)
            fputc(matrice[i][j],fisier);
        fputc('\n',fisier);
    }
}

void preorder(Arbore* root,FILE *fisier,int n,int m) 
{
    if (root) {
        scriere_mat(fisier, root->matrice, n, m);
        fputc('\n', fisier);
        preorder(root->left, fisier, n, m);
        preorder(root->right, fisier, n, m);
    }
}

void print_stiva(FILE *fisier1,Node *top)
{
    if(fisier1 == NULL)
    {
        printf("Fisierul nu poate fi deschis");
        exit(1);
    }
    Node *invers=NULL;
    while(top)
    {
        Node *next = top->next;
        top->next=invers;
        invers=top;
        top=next;
    } //
    while(invers)
    {
        fprintf(fisier1,"%d",invers->numar);
        Celula *nr = invers->celule;
        while(nr)
        {
            fprintf(fisier1," %d %d",nr->l,nr->c);
            nr=nr->next;
        }
        fprintf(fisier1,"\n");
        invers=invers->next;
    }
}
void elibereaza_arbore(Arbore *root, int n) 
{
    if (root==NULL) return;
    elibereaza_arbore(root->left, n);
    elibereaza_arbore(root->right, n);
    free_matrice(root->matrice, n);
    free(root);
}

int cells_alive(char **mat, int n, int m, Nod **rezultat) 
{
    int count=0;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            if (mat[i][j] == VII)
                count++;
        }
    }
    *rezultat = malloc(count * sizeof(Nod));
    int poz = 0;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            if (mat[i][j] == VII)
            {
                Nod aux;
                aux.l = i;
                aux.c = j;
                (*rezultat)[poz++] = aux;
            }
        }
    }
    return count;
}

int sunt_vecini(Nod a, Nod b) 
{
    return abs(a.l - b.l) <= 1 && abs(a.c - b.c) <= 1 && !(a.l == b.l && a.c == b.c);
}

void dfs(Nod *noduri, int **matrice_vecini, int nr, int *viz, int *traseu_cur, int depth, int *lgmax, int *traseu_bun) 
{
    if (depth > *lgmax) 
    {
        *lgmax = depth;
        for (int i=0;i<=depth;i++) {
            traseu_bun[i] = traseu_cur[i];
        }
    }
    for (int i=0;i<nr;i++) 
    {
        if (!viz[i] && matrice_vecini[traseu_cur[depth]][i]) 
        {
            viz[i] = 1;
            traseu_cur[depth+1] = i;
            dfs(noduri, matrice_vecini, nr, viz, traseu_cur, depth+1, lgmax, traseu_bun);
            viz[i] = 0;
        }
    }
}

LH lantH(char **mat, int n, int m) {
    Nod *noduri;
    int nr = cells_alive(mat, n, m, &noduri);

    int **matrice_vecini = malloc(nr * sizeof(int *));
    for (int i=0;i<nr;i++) 
    {
        matrice_vecini[i] = calloc(nr, sizeof(int));
        for (int j=0;j<nr;j++) 
        {
            matrice_vecini[i][j] = sunt_vecini(noduri[i], noduri[j]);
        }
    }

    int *viz = calloc(nr, sizeof(int));
    int *traseu_cur = malloc((nr+1) * sizeof(int));
    int *traseu_bun = malloc((nr+1) * sizeof(int));
    int lgmax = -1;

    for (int i=0;i<nr;i++) 
    {
        viz[i] = 1;
        traseu_cur[0] = i;
        dfs(noduri, matrice_vecini, nr, viz, traseu_cur, 0, &lgmax, traseu_bun);
        viz[i] = 0;
    }

    LH rezultat;
    if (lgmax == -1) 
    {
        rezultat.lungime = -1;
        rezultat.lant = NULL;
    } 
    else 
    {
        rezultat.lungime = lgmax;
        rezultat.lant = malloc((lgmax + 1) * sizeof(Nod));
        for (int i=0;i<=lgmax;i++)
            rezultat.lant[i] = noduri[traseu_bun[i]];
    }

    free(noduri); 
    free(viz); 
    free(traseu_cur); 
    free(traseu_bun);
    for (int i=0;i<nr;i++) 
        free(matrice_vecini[i]);
    free(matrice_vecini);

    return rezultat;
}

void scrie_lant(FILE *f, LH lant) 
{
    fprintf(f,"%d\n",lant.lungime);
    for (int i=0;i<=lant.lungime;i++) 
    {
        fprintf(f,"(%d,%d) ",lant.lant[i].l, lant.lant[i].c);
    }
    fprintf(f,"\n");
    free(lant.lant);
}

void task4(Arbore *root, int n, int m, FILE *fout) {
    if (root==NULL) return;

    LH lant = lantH(root->matrice, n, m);
    scrie_lant(fout, lant);

    task4(root->left, n, m, fout);
    task4(root->right, n, m, fout);
}

char **citeste_matrice(FILE *f, int n, int m) 
{
    char **mat = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) 
    {
        mat[i] = malloc(m * sizeof(char));
        for (int j = 0; j < m; j++) 
        {
            fscanf(f," %c", &mat[i][j]);
        }
    }
    return mat;
}