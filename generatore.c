#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SET_DI_CARTELLE 1
#define COL_LENGHT 18
#define RAWS 18
#define CARTELLA_RAWS 3
#define COLUMNS 9



//colonna 1: 9 numeri 9 spazi
//colonna 2-8: 10 numeri 8 spazi 
//colonna 9: 11 numeri 7 spazi

//mischia il vettore colonna, complessità O(n)
void shuffle(int* set, int N)  {
    int randIndex, temp;

    for(int i=0; i < N; i++)    {
        randIndex = rand() % N;

        temp = set[i];
        set[i] = set[randIndex];
        set[randIndex] = temp;
    }
}

//genera una colonna con n numeri e COL_LENGHT - n spazi (segnati come 0)
void generaColonna(int* colonna, int numeri, int* count) {

    for(int i=0; i < COL_LENGHT; i++) {
        if (i < numeri)    {
            colonna[i] = *count;
            (*count)++;
        }
        else
            colonna[i] = 0;
    }
    
}

void inserisciInSet(int set[RAWS][COLUMNS], int* colonna, int colIndex)   {
    for(int i=0; i<RAWS; i++)
        set[i][colIndex] = colonna[i];
}

void stampaSet(int set[RAWS][COLUMNS], int* cartelle_counter)   {
    for(int i=0; i<RAWS; i++)   {
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

void generaSet(int* cartelle_counter)    {
    int set[RAWS][COLUMNS], colonna[COL_LENGHT], count = 1;

    for(int i=0; i<COLUMNS; i++)    {
        if (i == 0) 
            generaColonna(colonna, 9, &count);
        else if (i == 8)
            generaColonna(colonna, 11, &count);
        else
            generaColonna(colonna, 10, &count);
        shuffle(colonna, COL_LENGHT);
        inserisciInSet(set, colonna, i);
    }

    aggiustaSet(set);
    stampaSet(set, cartelle_counter);

}

// ogni ripetizione del main genera e stampa un set di cartelle (6 x ripetizione)
int main()  {
    int cartelle_counter = 1;
    srand(time(NULL));

    for(int i=0; i < SET_DI_CARTELLE; i++)
        generaSet(&cartelle_counter);
    

    return 0;
}