/*3. Prethodnom zadatku dodati funkcije:
A. dinamièki dodaje novi element iza odreðenog elementa,
B. dinamièki dodaje novi element ispred odreðenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. èita listu iz datoteke.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 50

//uvedemo novi tip podataka-DEFINIRAMO STRUKTURU
//jednako kao i u zadatku prije
typedef struct _Person* Position;
typedef struct _Person {          //podatci potrebni za rad s datotekon
	char name[N];
	char lastName[N];
	int year;
	Position next;        //liste vezane na iduci cvor medusobno povezivanje
} Person;

//deklaracije starih funkcija
int insertBegin(Position p, char* name, char* lastName, int year);
int insertAfter(Position p, Position newP);
int insertEnd(Position p, char* name, char* lastName, int year);
Position findLName(char* lastName, Position p);
int deletePerson(char* lastName, Position p);

//nove funkcije-deklaracije
int AddAfter(Position p, char* searchLastName, char* name, char* lastName, int birthYear);
int AddBefore(Position p, char* searchLastName, char* name, char* lastName, int birthYear);
int sortList(Position p);
int WriteToFile(Position p, char* filename);
int readFromFile(Position p, char* filename);


//dodajemo novi el izad nekog
//uz pomocu temp varijable dok dodemo do liste izad koje zelimo nesto ubacit 
int AddAfter(Position p, char* searchLastName, char* name, const char* lastName, int birthYear) {
	Position oldPerson = findLName(searchLastName, p); //ova je iz vjezbe2 fja pogledaj 
	if (oldPerson == NULL) {
		printf("Odredena osoba nije pronadena te se ne moze dodat nakon nje\n");
		return -1;
	}
	Position newPerson = (Position)malloc(sizeof(Person)); //alokacija mem za novu osobu koju cemo dodat
	if (newPerson == NULL) {
		printf("Greska pri alokaciji mem\n");
		return -1;
	}
	//stringcopy zbog slova
	strcpy(newPerson->name, name); //kopira ime unutar varijable name u strukturi newPerson
	strcpy(newPerson->lastName, lastName); //isto za prezime kao i za ime
	newPerson->year = year; //zbog int obican znak =, isto kopiranje varijable unutar strukture
	newPerson->next = NULL; //pokazivac next novog clana(cvora) stavljamo na null(uzemljenje)
	//postavimo na null pa lako prispojimo posli

	insertAfter(oldPerson, newPerson); //ubacivanje
	return 0;
}


//dodavanje ispred
//dodavanje prije el je zapravo dodavanje poslije prijasnjeg pod b
int AddBefore(Position p, char* searchLastName, char* name, char* lastName, int birthYear) {
	Position oldPerson = findLName(searchLastName, p);
	if (oldPerson == NULL) {
		printf("Ne postoji ta osoba te se ne moze dodati ispred nje.\n");
		return -1;
	}
	Position prev = p; //pomocni pokazivac prev kojeg postavljamo na pocetak na head
	while (prev->next != oldPerson) { //vrti petlju dok nedodemo do cvora da je iduci clan oldPerson
		prev = prev->next; //pomicemo pom pok na iduci clan u listi
	}
	Position newPerson = (Position)malloc(sizeof(Person)); //alok mem za novi clan
	if (newPerson == NULL) {
		printf("Greska pri alok mem\n");
		return -1;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->lastName, lastName);
	newPerson->year= year; //= zbog int
	newPerson->next = NULL;

	insertAfter(prev, newPerson);
	return 0;

	
}


//sortiranje-triba ga napravit,ali nece bit na kolokviju-razlika izmedu liste i niza
//sortirani unos je bitan iduce vjezbe
int sortList(Position p){
	if (p->next == NULL || p->next->next == NULL) { //provjera je li lista prazna ili samo 1el
		return 0;                                  //ima li potreba za sortiranjem
	}
	Position i, j; //pomocni pokazivaci za usporedbu el
	char tempName[50], tempLastName[50]; //temporary varijable
	//bubble sort- usporeba svakog sa svakim
	for (i = p->next; i != NULL; i = i->next) { //i-vanjska petlja do kraja
		for (j = i->next; j != NULL; j = j->next) { //od el neposredno iza i do kraja unutarnja
			if (strcmp(i->lastName, j->lastName) > 0) { //usporedba lastname ;i u abc nakon j >0
				//zamjena lastname
				strcpy(tempLastName, i->lastName); //prezime iz i stavljamo u temp
				strcpy(i->lastName, j->lastName); //iz j u i
				strcpy(j->lastName, tempLastName); //iz temp u j

				//zamjena imena
				strcpy(tempName, i->name);
				strcpy(i->name, j->name);
				strcpy(j->name, tempName);

				//zamjena year
				tempYear = i->year;
				i->year = j->year;
				j->year = tempYear;

				//sve triba zaminit

			}

		}
	}
	printf("Lista je sortirana\n");
	return 0;

}

 
//upisivanje filea
int WriteToFile(Position p, char*filename){
	FILE* file = fopen(filename, "w"); //otvaranje filea cije je ime definirano u varijabli filename
	if (file == NULL) {
		printf("Greska pri otvaranju datoteke za upisivanje\n");
		return -1;
	}
	//prolazak kroz listu i unos
	Position q = p->next; //q pomc pok krece od prvog pravog el preskace se head
	//head se preskace jer ne sadrzi el o osobama 
	while (q != NULL) { //pretlja se vrsi dok nedode do kraja
		fprintf(file, "%s %s %d\n", q->name, q->lastName, q->year); //upisuje podatke u filea
		q = q->next; //pokazivac se pomice na iducu osobu u listi
	}
	fclose(file); //Zatvaranje datoteke nakon unosa
	printf("Lista je upisana u datoteku\n");
	return 0;
}

//citanje liste iz datoteke
int readFromFile(Position p, char* filename) {
	FILE* file = fopen(filename, "r"); //read samo sad
	if (file == NULL) {
		printf("Greska pri otvaranju\n");
		return -1;
	}
	//brisanje postojece liste u mem
	//prije ocitavanja novih pod iz datoteke treba obrisat ovo iz mem liste
	Position temp = p->next; //nepocinjemo od heada jer ne sadzi podatke o osobi
	while (temp != NULL) { //do kraja liste se vrti petlja
		Position toDelete = temp;
		temp = temp->next;
		free(toDelete);
	}
	p->next = NULL; //pokazivac podstavimo na kraj

	//citamo podatke iz dat i dodajemo u listu
	char name[N];
	char lastName[N];
	int year;

	while (fscanf(file, "%s %s %d", name, lastName, &year) == 3){ //scan cita red po red dok su ucitana sva 3 podatka u redu
		insertEnd(p, name, lastName, year); //fja dodaje na kraj liste pozivom fje
	}
	fclose(file); //zatvorit dat
	printf("Lista je ucitana iz datoteke\n");
	return 0;
}

//vjezba2
int insertBegin(Position p, char* name, char* lastName, int year) {
	Position newPerson = (Position)malloc(sizeof(Person)); //alok
	if (newPerson == NULL) return -1;

	strcpy(newPerson->name, name); //kopiranje ime
	strcpy(newPerson->lastName, lastName); //prez
	newPerson->year = year; //god
	newPerson->next = NULL; //pokazivac na kraj

	insertAfter(p, newPerson);
	return 0;
}

int insertAfter(Position p, Position newP) {
	newP->next = p->next; //pok od novog je pok od p
	p->next = newP; //p pokazuje na novi clan
	return 0;
}

void printList(Position p) {
	Position q = p->next; //pom pok q na prvi clan stavljen
	while(q!=NULL){ //dok nedode do kraja liste
		printf("Ime %s, prezime %s, god rodenja %d\n", q->name, q->lastName, q->year);
		q = q->next; //pomak pokazivaca na iduci
	}
}

int insertEnd(Position p, char* name, char* lastName, int year) {
	Position newPerson = (Position)malloc(sizeof(Person)); //alok
	if (newPerson == NULL) return -1;

	strcpy(newPerson->name, name); //kopiranje
	strcpy(newPerson->lastName, lastName);
	newPerson->year = year;
	newPerson->next = NULL;

	Position curr = p; //trenutna pozicija je head-pocetak
	while (curr->next != NULL) { //dok nedodemo do kraja liste pomicemo se
		curr = curr->next;
	}
	insertAfter(curr, newPerson);
	return 0;
}

Position findLName(char* lastName, Position p) {
	Position q = p->next; //pozicija od 1el ne head
	while (q != NULL) { //pom varijabla dok nedodemo do kraja
		if (strcmp(q->lastName, lastName) == 0) { //usporedba prez ako nademo onda vraca prez
			return q; //vraca
		}
		q = q->next; //u protivnom ide na iduci el
	}
	return NULL; 
}

int deletePerson(char* lastName, Position p) {
	Position curr = findLName(lastName, p);
	if (curr ==NULL) {
		printf("Osoba ne postoji u listi\n");
		return -1;
	}
	Position prev = p; //pozicionirali na head-pocetak
	while (prev->next != curr) { //dok nedodemo do trenutnog kojeg trazimo petlja ide
		prev = prev->next; //pribacujemo na iduceg
	}
	prev->next = curr->next; //spojimo listu s pokazivacima
	//osigurali pristup ostatku liste
	free(curr); //oslobdanje mem
	printf("Osoba je uspjesno izbrisana\n");
	return 0;
}

int main() {
	//inicijalizacija heada
	Position Head = { .name = {0}, .lastName = {0}, .year = 0, .next = NULL };
	Position p = &Head; //postavit p na head

	int choice;
	char name[N], lastName[N], searchLastName[N];
	int year;

	do {
		printf("1.Ispisi listu\n");
		printf("2.Dodaj element na pocetak\n");
		printf("3.Dodaj el na kraj\n");
		printf("4.Dodaj el iza odredenog prezimena\n");
		printf("5.Dodaj el ispred odredenog prezimena\n");
		printf("6.Pronadi osobu po prezimenu\n");
		printf("7.Obrisi osobu iz liste po prezimenu\n");
		printf("8.Sortiraj listu po prezimenima\n");
		printf("9.Upisite listu u datoteku\n");
		printf("10.Ucitajte listu iz datoteke\n");
		printf("0. Izlaz iz programa.\n");
		printf("Izbaerite opciju\n");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printList(p);
			break;

		case 2:
			printf("Unesite ime, prezime i god rodenja:");
			scanf("%s %s %d", name, lastName, &year);
			insertBegin(p, name, lastName, year);
			printf("Element je dodan na pocetak liste\n");
			break;

		case 3:
			printf("Unesite ime, prezime i god rodenjaq:");
			scanf("%s %s %d", name, lastName, &year);
			insertEnd(p, name, lastName, year);
			printf("Dodano je na kraj\n");
			break;

		case 4:
			printf("Unesite prezime elementa nakon kojeg zelite dodat\n");
			scanf("%s", searchLastName);
			printf("Unos podataka nove osobe- ime prezime god rodenja:");
			scanf("%s %s %d", name, lastName, &year);
			AddAfter(p, searchLastName, name, lastName, year);
			break;

		case 5:
			printf("Unesite prezime ispred kojeg zelite dodati novi element:\n");
			scanf("%s", searchLastName);
			printf("Unesite podatke nove osobe- ime prezime i datum rodenja:");
			scanf("%s %s %d", name, lastName, &year);
			AddBefore(p, searchLastName, name, lastName, year);
			break;

		case 6:
			printf("Unesite prezime koje trazite:\n");
			scanf("%s", lastName);
			{
				Position found = findLName(lastName, p); //lokalni pokazivac u koji se sprema rezultat fje 
				if (found != NULL) { //uspjesna ili neuspjesna potraga
					printf("Pronadena osoba -> ime:%s, prezime:%s, godina rodenja:%d\n", found->name, found->lastName, found->year);
				}
				else {
					printf("Zadana osoba nije pronadena\n");
				}
			}
			break;

		case 7:
			printf("Unesite prezime osobe koju zelite izbrisati:\n");
			scanf("%s", lastName);
			deletePerson(lastName, p);
			break;

		case 8:
			sortList(p);
			printList(p);
			break;

		case 9:
			WriteToFile(p, "popis.txt");
			printList(p);
			break;

		case 10:
			readFromFile(p, "popis.txt");
			printList(p);
			break;

		case 0:
			printf("izlazak iz programa i oslobanje memorije\n");
			//oslobadanje mem dinamicke liste
			{
				Position temp = p->next; //privremeni na 1el 
				while (temp != NULL) { //dok privreemni ne dode do kraja liste
					Position toDelete = temp;
					temp = temp->next; //pokazivac na iduci el
					free(toDelete);
				}
			}
			break;

		default:
			printf("Kriva opcija!Pokusajte ponovno\n");
		}











	} while (choice != 0); //petlja se vrti dok je izbor razlicit od 0 tj izlaza iz progr
	return 0;
}