/*4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

//koef veliki broj, potencija ili eks mali broj

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Poly; //postojat ce struktura Poly
typedef struct Poly* Position; //position je pokazivac na struk Poly
typedef struct Poly { //definicija strukture
	int coeff; //koeficijent uz clan polinoma-veliki
	int pow; //potencija-mali broj 
	Position next;
}polynom;

//dekalaracije fja
int ReadFromFile(Position head, const char* filename);
int InsertSorted(Position head, Position head1, Position head2);
int AddPolynomials(Position result, Position head1, Position head2);
int MultiplyPolynomials(Position result, Position head1, Position head2);
int Print(Position head);

//sortirano po eksponentima silazno
int InsertSorted(Position head, int coeff, int pow) {
	if (coeff == 0) {
		return 0;//ako je koef prvog clana 0- funkcija se prekida i vraca se 0 pr. 0x^2=0
	}            //nedodajemo taj clan u polinom, neutjece na nista
								
	Position newNode = (Position)malloc(sizeof(polynom)); 
	//alokacija mem za novi broj koji cemo potencijalno dodat

	if (!newNode) {
		printf("Greska pri alokaciji memorije!\n");
		return -1;
	}//provjera alokacije

	newNode->coeff = coeff; //upisujemo podatke u novi cvor koji smo stvorili koef 
	newNode->pow = pow;	//i potenciju
	newNode->next = NULL; //pokazivac od cvora spajamo na null da neizgubimo

	Position p = head; //pomocni pokazivac na head

	//trazimo misto za unos
	while (p->next != NULL && p->next->pow > pow) { //usporedba potencije iduceg cvora u listi s pot novog cvora kojeg dodajemo
		p = p->next; //sece se po listi dok je pot sljedeceg cvora veca od pot novog
	}
	//prije nego petlja stane provjerit postoji li vec u listi clan s istom potencijom
	//ako ga pronademo onda	NE STVARAMO CVOR NOVI vec samo zbrojimo s koef koji ima tu potenciju 
	//npr 7x^2 + 5x^2
	if (p->next != NULL && p->next->pow == pow) {
		p->next->coeff += coeff; //zbr koef s iston potencijom
		free(newNode); //osl mem koju smo napravili za novi cvor ali necemo iskoristit u ovon slucaju

		if (p->next->coeff == 0) { //podslucaj-ako je zbrojj koef 0 izbrisemo to 
			Position temp = p->next; //izoliramo u privremeni pok
			p->next = temp->next; //premostimo
			free(temp);
		}
	} else { 
//ako u list nije pronaden clan s istom pot znaci da se novi clan mora ubacit izmedu ta dva postojeca cvora ili kraj
//nije veci nije isti onda je manji znaci da se tu mora smistit u listi
			newNode->next = p->next; //povezuje se na ostatak liste
			p->next = newNode; //preth cvor pokazuje na novi- sortirano
	}
	return 0;
	
}

//citanje iz datoteke
int ReadFromFile(Position head, const char* filename) {
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Greska pri otvaranju datoteke!\n", filename);
		return -1;
	}
	int coeff, pow;
	while (fscanf(fp, "%d %d", &coeff, &pow) == 2) { //ukoliko ucita tocno 2 broja ulazimo u fju sortiranje
		InsertSorted(head, coeff, pow);

	}
	fclose(fp); //uvik zatvori dat
	return 0;

}

//zbrajanje result=head1+head2
int AddPolynomials(Position result, Position head1, Position head2) {
	Position p1 = head1->next; //privremeni
	Position p2 = head2->next;

	while (p1 != NULL) { //petlja prolazi kroz cili prvi polinom dok nedode dok kraja
		InsertSorted(result, p1->coeff, p1->pow); //clanove iz prvog polinmoa koef i pot u rezultantnu listu ubacujemo s fjom
		p1 = p1->next;
	}
	while (p2 != NULL) {
		InsertSorted(result, p2->coeff, p2->pow);
		p2 = p2->next;
	}
	return 0;
}

//mnozenje result=head1*head2
//mnozenje ide svaki sa svakim 
//mnoze se koef a zbrajaju potencije i onda se opet zbrajaju iste pot zbog urednosti
int MultiplyPolynomials(Position result, Position head1, Position head2) {
	Position p1 = head1->next;

	while (p1 != NULL) {
		Position p2 = head2->next;
		while (p2 != NULL) { //za svaki p1 razlicit od null prolazimo kroz 2 pol
			//svaki clan prvog pol pomnozit sa svakim clanom drugog pol
			int multCoeff = p1->coeff * p2->coeff; //koef mnoze
			int sumPow = p1->pow + p2->pow; //potencije zbrajaju
			InsertSorted(result, multCoeff, sumPow); //poslozit i zbrijit sredit listu
			p2 = p2->next;

		}
		p1 = p1->next;
	}
	return 0;
}

//ispis
int Print(Position head) {
	Position p = head->next;
	if (p == NULL) { //provjera je li polinom prazan
		printf("0\n");
		return 0;
	}
	while (p != NULL) {
		if (p->coeff > 0 && p != head->next)printf("+"); //akoe koef pozitivian ali nije prvi u redu ispisuje se +
		else if (p->coeff < 0)printf("-"); //koef negativan onda minus

		printf("%dx^%d", abs(p->coeff), p->pow); //apsolutnu vrijednost ispisujemo jer smo rucno vecpredznak
		p = p->next;
	}
	printf("\n");
	return 0;
}


int main() {
	//inicijalizacija headova
	polynom headFirst = { .coeff = 0, .pow = 0, .next = NULL };
	polynom headSecond = { .coeff = 0, .pow = 0, .next = NULL };
	polynom headZbroj = { .coeff = 0, .pow = 0, .next = NULL };
	polynom headUmnozak = { .coeff = 0, .pow = 0, .next = NULL };

	//neuspjesno ucitavanje datoteke za prvi i za drugi polinom
	//javit gresku u ton slucasju
	if (ReadFromFile(&headFirst, "prvipolinom.txt") != 0) { //razlicito od 0 neuspjeh 
		printf("Greska pri otv ili citanju datoteke za prvi polinom\n");
		return 1; 
	}
	if (ReadFromFile(&headSecond, "drugipolinom.txt") != 0) {
		printf("Greska pri otv ili citanju datoteke za drugi polinom\n");
		return 1;
	}
	printf("Prvi polinom:");
	Print(&headFirst);

	printf("Drugi:");
	Print(&headSecond);

	AddPolynomials(&headZbroj, &headFirst, &headSecond);
	printf("Zbroj:");
	Print(&headZbroj);

	MultiplyPolynomials(&headUmnozak, &headFirst, &headSecond);
	printf("Umnozak:");
	Print(&headUmnozak);

	return 0;
}