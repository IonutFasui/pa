#include "gameoflife.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        char *filename = argv[i];

        if (strstr(filename, ".out") != NULL || strstr(filename, ".ref") != NULL) 
            continue;

        Node *stiva = NULL;
        int n, m, k, numar_task;
        char **matrice, out[100], **copie, **urm;

        FILE *fisier = fopen(filename, "r");

        citire_date(fisier, &numar_task, &n, &m, &k, &matrice);
        char **matrice_initiala = copie_matrice(n, m, matrice);
        
        char *basename = strrchr(filename, '/');

        if (basename != NULL) {
            basename = basename + 1;
        } else {
            basename = filename;
        }
        char nume_baza[100];
        char *dot = strrchr(basename, '.');

        if (dot != NULL && strcmp(dot, ".in") == 0) 
        {
            int len = (int)(dot - basename);
            if (len >= 0 && len < (int)sizeof(nume_baza)) 
            {
                snprintf(nume_baza, sizeof(nume_baza), "%.*s", len, basename);
            } 
            else 
            {
                strncpy(nume_baza, basename, sizeof(nume_baza) - 1);
                nume_baza[sizeof(nume_baza) - 1] = '\0';
            }
        }
        else 
        {
            strncpy(nume_baza, basename, sizeof(nume_baza) - 1);
            nume_baza[sizeof(nume_baza) - 1] = '\0';
        }

        snprintf(out, sizeof(out), "OutputData/%s.out", nume_baza);



        //TASK 1
        if (numar_task == 1) 
        {
            FILE *fisier1 = fopen(out, "w");

            char **current = copie_matrice(n, m, matrice);
            for (int gen = 0; gen < k; gen++) 
            {
                scriere_mat(fisier1, current, n, m);
                fputc('\n', fisier1);
                char **next = generatie(n, m, current);
                free_matrice(current, n);
                current = next;
            }
            scriere_mat(fisier1, current, n, m);
            fputc('\n', fisier1);
            free_matrice(current, n);
            fclose(fisier1);
        }
        //TASK 2
        if (numar_task == 2) 
        {
                for (int gen = 1; gen <= k; gen++) 
                {
                    copie = copie_matrice(n, m, matrice);
                    urm = generatie(n, m, matrice);
                    Celula *compar1 = compar(matrice, urm, n, m);
                    push(&stiva, gen, compar1);
                    free_matrice(matrice, n);
                    matrice = urm;
                    free_matrice(copie, n);
                }
                Node* stivainv = inversez_stiva(stiva);
                FILE *fisier11 = fopen(out, "w");
                print_stiva(fisier11, stiva);
                bonus(stivainv, n, m, matrice); 

                FILE *bonus_text = fopen("bonus.txt", "wt");
                scriu_bonus(bonus_text, n, m, matrice);
                fclose(bonus_text);
                fclose(fisier11);

                free_stiva(stivainv);

        }
        //TASK 3
        if (numar_task == 3) 
        {
            Arbore *radacina = construire(n, m, 0, k, matrice_initiala);
            FILE *fisier3 = fopen(out, "w");
            preorder(radacina, fisier3, n, m);
            fclose(fisier3);
            elibereaza_arbore(radacina, n);
        }
        //TASK 4
        if (numar_task == 4) 
        {
            Arbore *root = construire(n, m, 0, k, matrice_initiala);
            FILE *fout = fopen(out, "w");
            task4(root, n, m, fout);
            fclose(fout);
            elibereaza_arbore(root, n);
        }

        free_matrice(matrice, n);
        free_matrice(matrice_initiala, n);
        fclose(fisier);
    }

    return 0;
}
