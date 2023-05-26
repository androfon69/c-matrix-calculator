
# Matrix calculator

### Scopul proiectului
```
Proiectul isi propune sa implementeze operatii simple cu matrici, dar si operatii mai
complexe precum factorizari sau inversa unei matrici, intr-un mediu de terminal linux
prin scrierea unor comenzi din tastatura
```

### Structuri folosite
```c
/* Contine numele, dimensiunile si elementele unei matrici de tip */
typedef struct Matrix {
    int rows, cols;
    char *name;
    double **elems;
} Matrix;

/* Contine un pointer catre o zona de date unde este stocata matricea */
typedef struct ListNode {
    void *mat;
    struct ListNode *next;
} ListNode;

/* Contine numarul de elemente din lista si un pointer catre primul nod din lista */
typedef struct MatrixList {
    int nrMats;
    struct ListNode *head;
} MatrixList;
```

### Modularizarea Codului
Functionalitatea codului este impartita in mai multe fisiere .c si .h
```
    commands.c/.h -> implementeaza functionalitatea terminalului si parsarea comenzilor
                     la  tastatura, apeland functia corespunzatoare

    list.c/.h -> implementeaza o lista simplu inlantuita cu operatii de scriere, stergere
                 si eliberare a memoriei

    matrix.c/.h -> implementeaza operatiile de baza pentru functionalitatea progamului
                   precum alocarea, citirea, eliberarea si afisarea unei matrici

    operations.c/.head -> implementeaza operatii cu matrici precum inmultire, adunare, 
                          inversare si calcularea determinantului
                        
    factorizations.c/.h -> implementeaza factorizarile de tip LU si QR
```

### Modul de functionare
    
In urma rularii executabilului, main apeleaza functia `run()` care citeste comenzi de la
tastaura si ruleaza functiile specifice pana la introducerea comenzii __exit__.

Numele comenzilor se afla intr-un vector de cuvinte. Se verifica numele comenzii introduse
de la tastatura si cu ajutorul unui `switch case` se apeleza functia corespunzatoare. 
Numele fiecarei functii corespunde unui index din vectorul de cuvinte egal cu valoarea din
`enum{COMMANDS_NAME..}`.

```c
    run() {
        while (1) {
            /* Reads command from console */

            /* Gets commandd index */

            if (index == < 0) {
                printf(error);
            }
            else {
                switch (index):
                    // execute command
            }
        }
    }
```

__Comanda help__: 
    
    Afiseaza o lista cu toate comenziile disponibile
```
help -- prints all available commands
clear -- clears the terminal

print -- prints the input matrix, if it exists
print-all -- prints the names of all read matrices
read -- reads a new matrix from console
delete -- deletes input matrix form the list
exit -- exits the program and deallocates memory

add -- adds input matrices
mult -- multiplies input matrices
trans -- transposes input matrix
det -- prints determinant of input matrix
norm -- prints the euclidian norm of input matrix
tr -- prints trace of input matrix
inv -- prints inverse of input matrix

lu -- performs crout LU factorization
qr -- performs QR factorization of a square matrix
```

__Comanda clean__:

    Curata terminalul si refiseaza prompt-ul

__Comanda print__: 

    Afiseaza matrice data ca input din lista de matrici daca a fost citita, sau eroare in
    caz contrar

__Comanda print-all__:

    Afiseaza numele si dimensiunile tuturor matricilor citite, sau in mesaj de eroare in
    cazul in care nu a fost citita nicio matrice

__Comenzile read/delete__:

    Read citeste o matricea data ca input de la tastatura si o adauga in lista. Daca 
    numele matricii exista deja, se ofera posibilitatea suprascrierii acesteia
    
    Delete sterge matricea data ca input din lista

__Comanda exit__:

    Dezaloca memoria ocupata de program si iese din program

__Comenzile add/mult/trans/det/norm/tr/inv__:

    Executa operatia corespunzatoare. Cand are un rezultat matriceal se cere introducerea
    unui nume pentru matricea output, verificandu-se coliziunile de nume atat cu matricile
    din lista cat si cu matricile input. Det(), norm(), tr() returneaza un double iar add()
    mult() trans() si inv() returneaza si insereaza in lista o matrice

__Comenzile lu/qr__:

    Fac factorizarea corespunzatoare si insereaza in lista matricile L, U resectiv Q, R.
    Pentru fiecare matrice output se fac verificari de coliziuni de nume cu lista de
    matrici si inputul

    


