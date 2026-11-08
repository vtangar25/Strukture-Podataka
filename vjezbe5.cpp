/*5. Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
rezultat.Stog je potrebno realizirati preko vezane liste.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 60

//stog
typedef struct Stack* Position;
typedef struct Stack {
	int broj;
	Position next;
}stack;

//funkcija za ucitat podatke iz datotwkw
//spremit u neki buffer-niz elemenata
//zatvorit datoteku 


int Push(Position head, int num) { //ubacivanje el na pocetak liste nakon heada
	Position newP = NULL;
	newP= (Position)malloc(sizeof(stack)); //alokacija mem
	if (newP == NULL) {
		printf("Greska u alokaciji memorije\n");
		return -1;
	}
	//unos podataka u novi prostor, el
	newP->broj = num;
	//povezivanje head i newP
	newP->next = head->next;
	head->next = newP;

	return 0;
}
//racunanje 
	//izbrisat, oslobodit operatore (p i q) elemente koji su sudjelovali u operaciji
	//funkcija Push ubacivanje izracunatog elementa na pocetak liste
//osloboditi cijelu listu za krivi unos
//prekinit izvodenje tog zadatka

//popunjavanje liste tj sloga
//A) ako je procitani element broj
//B) ako je operand
//C)krivi unos 

//skidanje prvog el s vrha stoga i vracanje vrijednost preko pokazivaca
int Pop(Position head) { //argument je head a funkcija vraca cijeli broj int
	Position p = NULL; //p je privremeni pokazivac 
	int val = 0; //deklaracija cjelobrojne varijable val u koju spremamo vrijednost broja zapisanog u cvoru koji skidamo

	if (head->next == NULL) { //provjera je li stog prazan
		printf("Stog je prazan\n");
		return -1;
	}
	p = head->next; 
	val = p->broj; //spremamo u val
	head->next = p->next;

	free(p); //oslobadanje mem
	return val; //povratak vrijednosti 
}

//funk za citanje dat i zracun
int Calculate(Position head, const char* fileName) {
	//otv datoteke
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) { //provjera
		printf("Greska pri otvaranju datoteke\n");
		return -1;
	}
	char buffer[N]; //buffer cita jedan po jedan el iz dat odvojen razmakon 
	while (fscanf(fp, "%s", buffer) == 1) { //petlja dok se cita iz dat 1el
		//provjera je li el operator
		if (strcmp(buffer, "+") == 0 || strcmp(buffer, "-") == 0 || strcmp(buffer, "*") == 0 || strcmp(buffer, "/") == 0) {
			int op2 = Pop(head); //prvo se sa stoga skida op2 pa op1 
			int op1 = Pop(head);
			int rezultat = 0;

			if (strcmp(buffer, "+") == 0) {
				rezultat = op1 + op2;
			}
			else if(strcmp(buffer, "-") == 0) {
				rezultat = op1 - op2;
			}
			else if (strcmp(buffer, "*") == 0) {
				rezultat = op1 * op2;
			}
			else if (strcmp(buffer, "/") == 0) {
				if (op2 == 0) {
					printf("Nemoze se dijeliti s nulom\n");
					fclose(fp);
					return -1;
				}
				rezultat = op1 / op2;
			}
			Push(head, rezultat); //ubacivanje rezultata na pocetak stoga

		}
		else {
			//ako nije operator onda broj
			int num; //spremit cemo ode broj
			if (sscanf(buffer, "%d", &num) == 1) { //je li ucitan cijeli broj
				Push(head, num); //na vrh stoga
			}
			else { //ako scan vrati nesto a ne 1 onda nije ni cijeli broj ni operator
				printf("Nepoznato\n");
				fclose(fp);
				return -1;
			}
		}

	}
	fclose(fp);

	//provjera rezultata
	if (head->next != NULL) {
		int konacniRezultat = Pop(head);

		if (head->next != NULL) { //unutarnja provjera za provjeru ima li krivog unosa 
			printf("Krivi unos previse brojeva u izrazu\n");
			Position q = head->next; //pom pok, osl meme, brisanje
			while (q != NULL) {
				Position nextNode = q->next;
				free(q);
				q = nextNode;
			}
			head->next = NULL;
			return -1;
		}
		return konacniRezultat;
	}
	else {
		printf("Greska\n");
		return -1;
	}
}




int main(){
	//inicijalizacija
	stack head = { .broj = 0, .next = NULL}; //trenutno stanje u mem imamo stack bez podataka na sebi =head

	//poziv fje
	int rezultat = Calculate(&heaf, "datoteka.txt");

	if (rezultat != -1) {
		printf("Rezultat je:%d\n", rezultat);

	}
	return 0;
}