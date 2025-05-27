# Game of Life - Proiect PA

Acest proiect implementeaza o versiune a **Game of Life** în C, incluzând toate cele 4 task-uri cerute, plus operația bonus de inversare a generatiilor.

## Structură fișiere
- **gameoflife.h** – Fisierul este headeru care include declaratiile tuturor functiilor (structuri etc).
- **gameoflife1.c** – Implementarea tuturor functiilor folosite pentru procesare,salvare,arbori,generare.
- **gameoflife.c** – Fisierul principal main care citeste fisierele .in si ruleaza cu checker.

## Rulare

Programul se compileaza cu ajutorul 'makefile' prin comanda make run in terminal,iar apoi prin comanda go run main.go pentru a accesa checker.

## Task 1 - Generarea regulilor 

Regulile standard la GameOfLife

## Task 2 - Stocarea diferentelor si bonus

Doar celulele ce isi schimba starea in stiva.
Bonus: se aplica o operatie de inversare a generatiilor,adica revenirea la starea initiala.

## Task 3 - Arbore binar de generatii

Se construieste un arbore binar:
La stanga: generatia dupa noua regula 
La dreapta: generatia normala a jocului

## Task 4 - Lant HAMILTONIAN

Se cauta cel mai lung lant Hamiltonian pentru fiecare nod si apoi se scrie lungimea si traseul.

## Structuri de date folosite:

Node, Celula, Arbore, Nod, LH

Node - pentru stiva
Celula - coordonatele unei celule
Arbore - arbore binar pentru generatii
LH - struct pentru lant Hamiltonian