#define _CRT_SECURE_NO_WARNINGS //mora uvik bit prva linija koda
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Student {
	char ime[50]; //mozemo i pisat svuda define N 50 i umisto 50 N
	char prezime[50];
	int bodovi;
}stud;

int main() {

	int i = 0;
	int brojac = 0;
	FILE* fp; //filepointer
	fp = fopen("popis.txt", "r");
	if (!fp) {
		printf("Greska!");
		return -1; //#define FILE_NOT_OPENED(-1); greska pri otvaranju filea
	}
	char buffer[50] = { 0 };
	while (!feof(fp)) {
		fgets(buffer, 50, fp); //ako nije kraj filea kao file end of file
		brojac++;
	}
	rewind(fp); 

	stud* studenti = NULL;
	studenti = (stud*)malloc(brojac * sizeof(stud)); //alok

	if (!studenti) {
		printf("Greska pri alok memorije");
		free(studenti);
		fclose(fp);
		return -1;
	}

	while (!feof(fp) && fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi) == 3) {
		i++; //tren pozicija 
	}

	fclose(fp); //zatvorit kad smo gotovi nakraju

	float max_bodova = 0; //postavit na nulu float zbog vece preciznosti
	for (int j = 0; j < i; j++) {
		if (studenti[j].bodovi > max_bodova) {
			max_bodova = (float)studenti[j].bodovi;
		}
	}
	if (max_bodova == 0) max_bodova = 1.0; //ne dijeliti s 0 za relativan br bodova

	printf("\n rezultati studenata \n");
	for (int j = 0; j < i; j++) {
		float relativan_br_bodova = ((float)studenti[j].bodovi / max_bodova) * 100;

		printf("Ime: %s, prezime: %s, bodovi: %d, relativni br bodova: %.2f%%\n", studenti[j].ime, studenti[j].prezime, studenti[j].bodovi, relativan_br_bodova);
	}

	free(studenti); //oslobadanje memorije

	return 0;

}
