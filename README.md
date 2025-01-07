# generatore_cartelle_tombola
README – Generatore di cartelle di Tombola

Questo programma genera set di cartelle di Tombola, ciascuna costituita da 3 righe (18 righe, per un totale di 6 cartelle), e rispetta i principali vincoli:
	•	Ogni riga contiene 5 numeri (e 4 spazi vuoti);
	•	9 celle piene nella 1ª colonna;
	•	10 celle piene nelle 7 colonne centrali;
	•	11 celle piene nell’ultima colonna;
    •	in un singolo set di cartelle son compresi tutti i numeri da 1 a 90.

Il programma crea un numero definito di set (nel codice, SET_DI_CARTELLE = 100, ma è modificabile a piacimento), e per ciascun set:
	1.	Costruisce un pattern di 0/1 che rispetti i vincoli di riga e colonna.
	2.	Sostituisce gli 1 con numeri effettivi, shufflati nella giusta colonna.

Struttura generale del codice

1. Costanti principali
	•	ROWS = 18, COLUMNS = 9: struttura della matrice (18 righe e 9 colonne).
	•	NUMERI_PER_RIGA = 5: numero fisso di numeri in ogni riga.
	•	RIGHE_RANDOMIZZATE = 2: numero di righe iniziali da compilare in modo “semi-casuale”.
	•	SET_DI_CARTELLE: quante volte vogliamo generare il set.

2. Funzione main()
	•	Esegue un ciclo per SET_DI_CARTELLE volte, chiamando generaSet(&cartelle_counter).
	•	Tiene traccia del contatore di cartelle (cartelle_counter) per la stampa ordinata.

3. Funzione generaSet(int* cartelle_counter)
	1.	Dichiara la matrice set[ROWS][COLUMNS] e il vettore colNeeds[COLUMNS].
	2.	Inizializza questi valori chiamando inizializza().
	3.	Costruisce il pattern 0/1 con la funzione generaPattern().
	4.	Genera i numeri per ogni colonna (generaColonna()) e li inserisce al posto giusto (inserisciColonnaInSet()).
	5.	Stampa il risultato (pattern + numeri) con stampaSet().

Dettagli sulle funzioni chiave

inizializza(int set[ROWS][COLUMNS], int colNeeds[COLUMNS])
	•	Pulisce la matrice set mettendo tutti 0.
	•	Imposta i fabbisogni di ogni colonna in colNeeds (esempio: 9 nella prima, 10 nelle successive, 11 nell’ultima).
	•	Randomizza le prime RIGHE_RANDOMIZZATE righe (nel codice, 2 righe) usando generaRigaRandomPattern() e inserisciRigaInSet():
	•	generaRigaRandomPattern(riga, NUMERI_PER_RIGA) crea un array di 9 elementi con esattamente 5 “1” e 4 “0”, poi ne mescola l’ordine.
	•	inserisciRigaInSet(...) inserisce gli 1 nella matrice e decrementa colNeeds corrispondente.

generaPattern(int set[ROWS][COLUMNS], int colNeeds[COLUMNS])
	•	Completa le restanti righe da RIGHE_RANDOMIZZATE fino a ROWS.
	•	Trova la colonna “migliore” (quella con colNeeds più alto, tie-break gestiti con casualità) tramite la funzione massimo(...).
	•	Se colNeeds[max] > 0, mette 1 nella matrice e decrementa colNeeds[max].
	•	Se la colonna scelta risulta avere colNeeds=0, la segna come usata e sceglie un’altra colonna.

In questo modo, si crea uno schema 0/1 che rispetta i vincoli di 5 numeri per riga e del limite massimo per colonna.

massimo(int* vet, int* colUsed, int n)
	•	Trova la colonna (non usata) con valore più alto in vet[].
	•	In caso di tie-break (pareggi), sceglie una a caso tra quelle che hanno lo stesso valore massimo.
	•	Ritorna l’indice della colonna da usare.

generaColonna(int* colonna, int numeri, int* count)
	•	Crea un piccolo array con i prossimi numeri valori di count (ad esempio, la colonna 0 avrà 9 numeri da 1 a 9, poi la colonna 1 avrà 10 numeri da 10 a 19, ecc.).
	•	Incrementa *count per passare alla colonna successiva.

inserisciColonnaInSet(int set[ROWS][COLUMNS], int* colonna, int colIndex)
	•	Assegna effettivamente i numeri (che erano in colonna[]) alle righe in cui il pattern 0/1 ha “1” in quella colonna.

stampaSet(int set[ROWS][COLUMNS], int* cartelle_counter)
	•	Stampa la matrice (in gruppi di 3 righe per cartella), mostrando numeri dove set[i][j] != 0 e spazi vuoti altrimenti.

Esecuzione del programma
	•	Una volta compilato ed eseguito, il programma inizierà a generare 100 set (SET_DI_CARTELLE = 100) in modo semi-casuale.
	•	In uscita, vedrai la suddivisione in cartelle numerate e l’effettiva disposizione dei numeri nelle 9 colonne.

Enjoy!