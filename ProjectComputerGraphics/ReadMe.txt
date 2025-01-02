Vincoli per modificare il numero di forzieri nella mappa:
	- numOfHiddenChests deve essere < numOfSpawns, 
		quindi i forzieri nascosti devono essere sempre minori (stretti) del numero di spawn
	- text al momento è fatto per avere al massimo 9 chest da cercare
	- sistemare di quanto scalare ogni volta il forziere, modificare quello che succede in setParameters
		e come viene decrementato il fattore di scala nella funzione FoundChest
		al momento parte da 0.0027 e viene decrementata di 0.0003 ogni volta.
		Maggiore è il numero di chest da cercare più la cassa diventa piccola