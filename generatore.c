#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SET_DI_CARTELLE 3
#define MAX_LENGHT 11
#define NUMERI_PER_RIGA 5
#define ROWS 18
#define COLUMNS 9



//colonna 1: 9 numeri 9 spazi
//colonna 2-8: 10 numeri 8 spazi 
//colonna 9: 11 numeri 7 spazi

void stampaSet(int set[ROWS][COLUMNS], int* cartelle_counter)   {
    for(int i=0; i<ROWS; i++)   {
        if (i % 3 == 0) {
            printf("\nCartella #%d: \n", *cartelle_counter);
            (*cartelle_counter)++;
        }
        
        for(int j=0; j<COLUMNS; j++)    {
            if (set[i][j] != 0)
                printf(" %d ", set[i][j]);
            else if (j != 0)
                printf("    ");
            else
                printf("   ");
        }
        printf("\n");
    }
}

//mischia il vettore colonna, complessità O(n)
void shuffle(int* vet, int N)  {
    int randIndex, temp;

    for(int i=0; i < N; i++)    {
        randIndex = rand() % N;

        temp = vet[i];
        vet[i] = vet[randIndex];
        vet[randIndex] = temp;
    }
}

//genera una riga randomizzata del pattern 
void generaRigaRandomPattern(int* riga, int n) {
    for(int i=0; i < COLUMNS; i++)    {
        if (i < n)
            riga[i] = 1;
        else
            riga[i] = 0;
    }
    shuffle(riga, COLUMNS);
}

void inserisciRigaInSet(int set[ROWS][COLUMNS], int colNeeds[COLUMNS], int* riga, int rowIndex)    {
    for(int i=0; i < COLUMNS; i++)  {
        if (riga[i] == 1)   {
            set[rowIndex][i] = riga[i];
            colNeeds[i]--;
        }
    }
}

//genera una colonna con n numeri
void generaColonna(int* colonna, int numeri, int* count) {
    for(int i=0; i < numeri; i++) {
            colonna[i] = *count;
            (*count)++;
    }
}

void inserisciColonnaInSet(int set[ROWS][COLUMNS], int* colonna, int colIndex)   {
    int j = 0;
    for(int i=0; i < ROWS; i++)   {
        if (set[i][colIndex] == 1)  {
            set[i][colIndex] = colonna[j];
            j++;
        }
    }
}

//inizializza la matrice di zeri e i due vettori per il backtracking
void inizializza(int set[ROWS][COLUMNS], int rowNeeds[ROWS], int colNeeds[COLUMNS]) {
    srand(time(NULL));
    for(int i=0; i < ROWS; i++)
        for(int j=0; j < COLUMNS; j++)
            set[i][j] = 0;
    int c[COLUMNS] = {9, 10, 10, 10, 10, 10, 10, 10, 11};
    for(int i=0; i < COLUMNS; i++)
        colNeeds[i] = c[i];
    for(int i=0; i < ROWS; i++)
        rowNeeds[i] = NUMERI_PER_RIGA;

    //approccio semicasuale, genero randomicamente il pattern delle prime 3 righe
    int riga[COLUMNS], nRighe = 3;
    for(int i=0; i < nRighe; i++)    {
        rowNeeds[i] = 0;
        generaRigaRandomPattern(riga, NUMERI_PER_RIGA);
        inserisciRigaInSet(set, colNeeds, riga, i);
    }
    
}

//restituisce l'indice del massimo elemento del vettore
int massimo(int* vet, int* colUsed, int n)    {
    int maxIndex = 0, last = rand() % 2;    

    if (colUsed[maxIndex])  {   //edge case
        int i = maxIndex + 1;
        while(colUsed[i])
            i++;
        maxIndex = i;
    }

    //last aggiunge un tocco di random nel decidere se prendere il primo o l'ultimo elemento massimo
    for(int i=0; i < n; i++)    {
        if (last)   {   
            if (vet[i] >= vet[maxIndex] && !colUsed[i])
                maxIndex = i;
        }
        else    {
            if (vet[i] > vet[maxIndex] && !colUsed[i])
                maxIndex = i;
        }
    }
    return maxIndex;
}

//questa funzione genera un pattern randomico per il set di cartelle tramite ricorsione. 
int generaPattern(int set[ROWS][COLUMNS], int rowNeeds[ROWS], int colNeeds[COLUMNS], int r, int c)    {
    if (r == ROWS)  {
        for(int i=0; i < ROWS; i++) 
            if (rowNeeds[i] != 0)   
                return 0;
        for(int i=0; i < COLUMNS; i++)  
            if (colNeeds[i] != 0) 
                return 0;
        return 1;
    }


    //coordinate della prossima cella
    int next_r = r, next_c = c + 1;
    if (next_c == 9)    {
        next_c = 0;
        next_r = r + 1;
    }

    if (rowNeeds[r] > 0 && colNeeds[c] > 0) {
        set[r][c] = 1;
        rowNeeds[r]--;
        colNeeds[c]--;

        if (generaPattern(set, rowNeeds, colNeeds, next_r, next_c)) return 1;

        // Backtrack
        set[r][c] = 0;
        rowNeeds[r]++;
        colNeeds[c]++;
    }

    // TENTATIVO: Mettere 0
    set[r][c] = 0;
    if (generaPattern(set, rowNeeds, colNeeds, next_r, next_c)) return 1;

    return 0;

    //inserimento di un fattore casualità nella generazione del pattern
    /*
    if (rowNeeds[r] > 0 && colNeeds[c] > 0) {
        int prob = (rand() % 9) + 1;  
        if (prob <= 5)  {   //inserisco un numero se prob è compreso tra 1 e 5
            rowNeeds[r]--;
            colNeeds[c]--;
            set[r][c] = 1;

            if (generaPattern(set, rowNeeds, colNeeds, next_r, next_c)) return 1;
            else    {   //backtrack
                rowNeeds[r]++;
                colNeeds[c]++;
                set[r][c] = 0;
            }
        }
        else if (prob > 5)  {   //altrimenti inserisco uno 0
            if (generaPattern(set, rowNeeds, colNeeds, next_r, next_c)) return 1;
            else    {   //backtrack
                rowNeeds[r]--;
                colNeeds[c]--;
                set[r][c] = 1;
            }
        }
    }
    if (generaPattern(set, rowNeeds, colNeeds, next_r, next_c)) return 1;
    return 0;   //se tutti i casi falliscono (non dovrebbero but...)
    */

}


void generaSet(int* cartelle_counter)    {
    int set[ROWS][COLUMNS], rowNeeds[ROWS], colNeeds[COLUMNS], colonna[MAX_LENGHT], count = 1, righeRandomizzate = 3, n;
    
    inizializza(set, rowNeeds, colNeeds);


   //tentativo di semi-randomizzazione, considerando 3 righe già randomizzate
    for(int i=righeRandomizzate; i < ROWS; i++) {
        //colUsed porta a 1 gli indici già utilizzati 
        int cnt = 0, colUsed[COLUMNS] = {0, 0, 0, 0, 0, 0, 0, 0, 0};    
        while(cnt < NUMERI_PER_RIGA)  {
            int max = massimo(colNeeds, colUsed, COLUMNS);
            if (colNeeds[max] > 0)  {
                set[i][max] = 1;
                colNeeds[max]--;
                colUsed[max] = 1;
                cnt++;
            }
            else
                colUsed[max] = 1;
        }
        rowNeeds[i] = 0;
    }


    count = 1;
    for(int i=0; i<COLUMNS; i++)    {
        if (i == 0) {
            n = 9;
            generaColonna(colonna, n, &count);
        }
        else if (i == 8)    {
            n = 11;
            generaColonna(colonna, n, &count);
        }
        else    {
            n = 10;
            generaColonna(colonna, n, &count);
        }
        shuffle(colonna, n);
        inserisciColonnaInSet(set, colonna, i);

    }

    stampaSet(set, cartelle_counter);

}

// ogni ripetizione del main genera e stampa un set di cartelle (6 x ripetizione)
int main()  {
    int cartelle_counter = 1;   //serve a tenere conto del numero di cartelle

    for(int i=0; i < SET_DI_CARTELLE; i++)  {
        generaSet(&cartelle_counter);
    }
    
    return 0;
}