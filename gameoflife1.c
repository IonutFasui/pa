#include "gameoflife.h"


//functie push SITE-PA (task2)
void push(Node** top, int numar,Celula *lista) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->numar = numar;
    newNode->celule=lista;
    newNode->next = *top;
    *top = newNode;
}
//eliberez din memorie lista

//Problema cu memoria (rezolvat)
void free_lista_celule(Celula *lista)
{
    while (lista) {
        Celula *temp = lista;
        lista = lista->next;
        free(temp);
    }
}
void free_stiva(Node *top) 
{
    while (top) 
    {
        Node *temp = top;
        top = top->next;
        free_lista_celule(temp->celule);
        free(temp);                    
    }
}
////
//Compar doua matrici si caut diferentele (intre doua generatii)
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

//Citire task1
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

//copiez matrice
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


//free la matrice (-memorie)
void free_matrice(char **matrice,int n)
{
    for (int i=0;i<n;i++)
        free(matrice[i]);
    free(matrice);
}


//arborele de generatii
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

//task 1 generatii regului (GOF)

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

//copiez o lista de celule care au aceleasi date ca originala (ca sa nu modifice lista originala)
Celula* lista_cels(Celula *lista) 
{
    if (!lista) return NULL;
    Celula *copie = NULL,*last = NULL;
    while (lista) 
    {
        Celula *nou = (Celula*)malloc(sizeof(Celula));
        nou->l=lista->l;
        nou->c=lista->c;
        nou->next = NULL;
        if (!copie) {
            copie = nou;
            last = nou;
        } else {
            last->next = nou;
            last = nou;
        }
        lista=lista->next;
    }
    return copie;
}

//o copie inversata a stivei parcurgand din varf spre inceput 

Node* inversez_stiva(Node *top) 
{
    Node *invers = NULL;
    while (top) { 
        Node *nou = (Node*)malloc(sizeof(Node)); //un nod nou
        nou->numar = top->numar; 
        nou->celule = lista_cels(top->celule); //copiez lista de celule 
        nou->next = invers;
        invers = nou;
        top = top->next;
    }
    return invers;
}

//bonus aplic fix invers tranformarile din stiva 
void bonus(Node *top,int n,int m,char **matrice)
{
    int i,j;
    while(top)
    {
        Celula *cel=top->celule; // iau prima celula
        while(cel)
        {
            i=cel->l;
            j=cel->c;//coordonate 
            if (i>=0 && i<n && j>=0 && j<m) // daca e in matrice    
            {
                if (matrice[i][j] == VII)
                    matrice[i][j]=MOARTE;
                else
                    matrice[i][j]=VII;
                //inversez aici
            }   
            cel=cel->next; //trec la celula 
        }
        top=top->next;
    }

}
//scriu in fisier (bonusu)
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
//construiesc arbore binar din generatii cu doua reguli 
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

//scriu matricex
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
//preordinea
void preorder(Arbore* root,FILE *fisier,int n,int m) 
{
    if (root) {
        scriere_mat(fisier, root->matrice, n, m);
        fputc('\n', fisier);
        preorder(root->left, fisier, n, m);
        preorder(root->right, fisier, n, m);
    }
}
//scriu stiva
void print_stiva(FILE *fisier1,Node *top)
{
    if(fisier1 == NULL)
    {
        printf("Fisierul nu poate fi deschis");
        exit(1);
    }
    Node *invers=NULL,*start=NULL;
    //inversez stiva de la coada la cap 
    while(top)
    {
        Node *next = top->next;
        top->next=invers;
        invers=top;
        top=next;
    } //
    start = invers;

    while(invers)
    {
        fprintf(fisier1,"%d",invers->numar);
        //parrcurg lista 
        Celula *nr = invers->celule; //nr este primul element din lista ce s a schimbat 
        while(nr)
        {
            fprintf(fisier1," %d %d",nr->l,nr->c);
            nr=nr->next; // la urmatorea celula
        }
        fprintf(fisier1,"\n");
        invers=invers->next; //trec la urmatoru
    }
    free_stiva(start);
}
void elibereaza_arbore(Arbore *root, int n) 
{
    if (root==NULL) return;
    elibereaza_arbore(root->left, n);
    elibereaza_arbore(root->right, n);
    free_matrice(root->matrice, n);
    free(root);
}
//celulele vii
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
    //salvez coordonatele celulelor vii
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

//verific daca doua celule sunt vecine si sa nu fie pe aceeasi celula
int sunt_vecini(Nod a, Nod b) 
{
    return abs(a.l - b.l) <= 1 && abs(a.c - b.c) <= 1 && !(a.l == b.l && a.c == b.c);
}


//caut recursiv toate drumurile in graf de la un nod si o singura data si daca gaseste un drum mai lung decat cel anterior se actualizaeaza 
void dfs(Nod *noduri, int **matrice_vecini, int nr, int *viz, int *traseu_cur, int depth, int *lgmax, int *traseu_bun) 
{
    if (depth > *lgmax) 
    {
        *lgmax = depth;
        for (int i=0;i<=depth;i++) {
            traseu_bun[i] = traseu_cur[i]; // aici memorez ca cel mai bun traseu
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
///caut cel mai lugn lh 
LH lantH(char **mat, int n, int m) {
    Nod *noduri;
    int nr = cells_alive(mat, n, m, &noduri); // nr este toate celulele vii

    int **matrice_vecini = malloc(nr * sizeof(int *)); // fac o matrice in functie de functia sunt_vecine 
    for (int i=0;i<nr;i++) 
    {
        matrice_vecini[i] = calloc(nr, sizeof(int));
        for (int j=0;j<nr;j++) 
        {
            matrice_vecini[i][j] = sunt_vecini(noduri[i], noduri[j]);
        }
    }
    //cele de la dfs
    int *viz = calloc(nr, sizeof(int)); //daca a fost vizitat
    int *traseu_cur = malloc((nr+1) * sizeof(int)); //traseu curent
    int *traseu_bun = malloc((nr+1) * sizeof(int)); //cel mai lung traseu 
    int lgmax = -1; // tin mint elungimea maxima a unui traseu

    //fac dfs  caut recursiv cel mai lung drum care viziteaza o data fiecare nod si daca se gaseste un lant mai lung decat cel anterior se salveaza
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
    //dau free la fieecare
    free(noduri); 
    free(viz); 
    free(traseu_cur); 
    free(traseu_bun);
    for (int i=0;i<nr;i++) 
        free(matrice_vecini[i]);
    free(matrice_vecini);

    return rezultat;
}
//scriu  lung lantului si fiecare coordonata 
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

//task4 caut recursiv in stanga si in dreapta , caut cel mai lung lant H si dupa scriu lantul
void task4(Arbore *root, int n, int m, FILE *fout) {
    if (root==NULL) return;

    LH lant = lantH(root->matrice, n, m);
    scrie_lant(fout, lant);

    task4(root->left, n, m, fout);
    task4(root->right, n, m, fout);
}

//citesc matricea
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