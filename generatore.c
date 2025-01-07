#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SET_DI_CARTELLE 100
#define MAX_LENGHT 11
#define NUMERI_PER_RIGA 5
#define RIGHE_RANDOMIZZATE 2
#define ROWS 18
#define COLUMNS 9
//possibile miglioria: funzione di controllo generale dei vincoli prima dell'uscita da fz generaPattern()


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
    srand(time(NULL));
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
void inizializza(int set[ROWS][COLUMNS], int colNeeds[COLUMNS]) {
    srand(time(NULL));
    for(int i=0; i < ROWS; i++)
        for(int j=0; j < COLUMNS; j++)
            set[i][j] = 0;
    int c[COLUMNS] = {9, 10, 10, 10, 10, 10, 10, 10, 11};
    for(int i=0; i < COLUMNS; i++)
        colNeeds[i] = c[i];

    //approccio semicasuale, genera randomicamente il pattern delle prime n righe (RIGHE_RANDOMIZZATE) 
    int riga[COLUMNS];
    for(int i=0; i < RIGHE_RANDOMIZZATE; i++)    {
        generaRigaRandomPattern(riga, NUMERI_PER_RIGA);
        inserisciRigaInSet(set, colNeeds, riga, i);
    }
    
}

//restituisce l'indice del massimo elemento del vettore, in caso di tie-break ne restituisce uno random tra i massimi
int massimo(int* vet, int* colUsed, int n)    {
    srand(time(NULL));
    int maxIndex, cnt = 0, indexList[COLUMNS] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i=0; i < n; i++)    {   //trovo la prima colonna libera
        if (!colUsed[i])  {
            maxIndex = i;
            break;
        }
    }

    for(int i=0; i < n; i++)    {   //trovo il massimo tra gli elementi del vettore
        if (vet[i] > vet[maxIndex] && !colUsed[i])
            maxIndex = i;
    }

    for(int i=0; i < n; i++)    {   //ogni indice dell'elemento pari al massimo viene salvato
        if (vet[i] == vet[maxIndex] && !colUsed[i])    {
            indexList[cnt] = i;
            cnt++;
        }
    }
    if (cnt == 0)   exit(-1);
    maxIndex = rand() % cnt;
    return indexList[maxIndex];
}

//questa funzione genera un pattern randomico per il set di cartelle
void generaPattern(int set[ROWS][COLUMNS], int colNeeds[COLUMNS])    {
    for(int i=RIGHE_RANDOMIZZATE; i < ROWS; i++) {
        int cnt = 0, colUsed[COLUMNS] = {0, 0, 0, 0, 0, 0, 0, 0, 0};    //colUsed porta a 1 gli indici già utilizzati 

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
    }

}

void generaSet(int* cartelle_counter)    {
    int set[ROWS][COLUMNS], colNeeds[COLUMNS], colonna[MAX_LENGHT], count = 1, n;
    
    inizializza(set, colNeeds);
    generaPattern(set, colNeeds);
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