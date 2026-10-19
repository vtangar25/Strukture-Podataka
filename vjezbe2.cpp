/*Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
A.dinamièki dodaje novi element na poèetak liste,
B.ispisuje listu,
C.dinamièki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

//uvod isti za sve dijelove zadatka zasebne funkcije
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//uvedemo novi tip podataka
typedef struct _Person* Position;
typedef struct _Person {          //podatci potrebni za rad s datotekon
	char name[50];
	char lastName[50];
	int year;
	Position next;        //liste vezane na iduci cvor
} Person; 


int insertBegin(char* name, char* lastName, int year);
int insertAfter(Position p, Position q);
int insertEnd(char* name, char* lastName, int year);
Position findLName(char* lastN, Position p);
int deletePerson(char* lastN, Position p);
void printList(Position p);

//funkcija za a dio zdk
int insertBegin(char* name, char* lastName, int year) {
	Position newPerson = NULL; //pokazivac na novi el mora biti tipa position -poc vrijednost
	                          //svaki pokazivac povezan sa strukturom je position tipa
	newPerson = (Position)malloc(sizeof(Person)); //alokacija mem
	//prva zagrada tip podataka u koji nesto pohranjujemo druga je vel onoga sta mi zelimo rezervirat
	if (newPerson == NULL) {
		printf("GReska pri alok mem\n"); //provjera alokacije
		free(newPerson);
		return -1;
	}
	newPerson->year = year;
	strcpy(newPerson->name, name);
	strcpy(newPerson->lastName, lastName); //neradimo s jednim el vec s nizom funkcija

	newPerson->next = NULL; //next podstavili na uzemljenje sve podstavili za novu osobu
	
	return 0;
}

//novi el-newperson povezat s headom u novoj funkciji
int insertAfter(Position p, Position newP) { //pokazivac na head i na newperson
	newP->next = p->next; //newP next ce pokazivat na prethodnika
	p->next = newP; //p vise nece pokazivat na 1 nego na 2
	return 0;
	
	//crtaj kod
	//pokazivac istovremeno samo na jednu adresu
	//ali vise pokazivaca moze na jednu stvar istovremeno

}
//ispis liste b dio
void printList(Position p) {
	for (Position q = p->next; q != NULL; q = q->next) {
		printf("Ime: %s , Prezime: %s, Godina: %d\n", p->name, p->lastName, p->year);
		p = p->next;
	}
}

//c dio dodavanje na kraj liste
int insertEnd(char* name, char* lastName, int year) {
	Position newPerson = NULL;
	
	//alokacija
	newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) { //provjera alokacije
		printf("Greska!\n");
		free(newPerson);
		return -1;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->lastName, lastName);
	newPerson->year = year;
	newPerson->next = NULL;
	
	while (p->next != NULL) { 
		p = p->next; //pomicanje dok nije "prazno"
	}
	insertAfter(p, newPerson);
	return 0;
	
}

//d- po prezimenu
Position findLName(char*lastName, Position p) { //pokazivac na head
	Position q = p->next; //krece se po listi dok nenade odgovarajuce prezime
	for (q; q != NULL; q = q->next) { //stvori pomocnu varijablu pokazivaca temporary
		if (strcmp(q->lastName, lastN) == 0) { //povratna inf neg poz il nula usporedba prvog slova
			return q; //vracamo q tipa position
		}
		else {
			printf("Prezime nije pronadeno!\n");
		}
	}
}

//e-brisanje odr elem
int deletePerson(char* lastN, Position p) {
	//pazit da se ne izgubi pristup nekom el
	Position prev = p; //prati prethodni el
	Position curr = prev->next; //current
	curr = findLName(lastN, prev); //poziv na funkciju 
	while (prev->next != curr) {
		prev = prev->next;
	}
	if (curr == NULL) {
		printf("Osoba ne postoji u listi.\n");
		return -1;
	}
	prev->next = curr->next; //spremanje pokazivaca na current
	//osigurali pristup ostatku liste
	free(curr); //oslobadanje mem
	return 0;	
}

int main() {
	Person Head = { .name = {0}, .lastName = {0}, .year = 0, .next = NULL };
	//head tipa strukture person, s tockom pristupamo podatcima unutar same strukture
	//next je nulto za adresu znak uzemljenja nista ne pokazuje

	//privremeni pokazivac koji sadrzi adresu heada i prinosimo kao arg u funkcije
	Position p = &Head;

	

	return 0;
}

