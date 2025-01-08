README – Generatore di Cartelle della Tombola

Il progetto genera un set di cartelle della Tombola (6 cartelle per set) con approccio semi-casuale, rispettando i vincoli di:
1) 18 righe totali, 9 colonne.
2) Ogni riga ha 5 numeri (e 4 spazi vuoti).
3) Le colonne hanno una quantità prefissata di numeri (9, 10, 10, …, 11).
	- Nel codice, questi valori sono contenuti nell'array colNeeds.

L'approccio semi-casuale consiste nel generare le prime due righe randomicamente;
il resto delle righe viene generato andando a pescare da colNeeds l'indice della colonna più grande (random in caso di parità).

Il valore SET_DI_CARTELLE, inizializzato a 100, può essere modificato per indicare quanti set generare.