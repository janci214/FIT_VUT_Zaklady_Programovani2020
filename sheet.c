/******************************************
 1-BIT - IZP - Projekt 1 - Praca s textom
 Autor:  Jan Sprlak
 Login:  xsprla01
 email:  xsprla01@stud.fit.vutbr.cz
 Rok: 2020
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <tgmath.h>
#define MAX 10242	// maximalna dlzka jedeho riadku

//zadefinovanie vsetkych funkcii
void irow(int argc, char *argv[], int riadky, int stlpce, char *oddelovac);
void arow(int stlpce, char *oddelovac);
void drow(int argc, char *argv[], int riadky, char *pole);
void drows(int argc, char *argv[], int riadky, char *pole);
void icol(int cislo_stlpca, char *oddelovac, int velkost_pola, char pole[]);
void acol(char *oddelovac, char *pole);
void dcol(int cislo_stlpca, char *oddelovac, int velkost_pola, char *pole);
int jeZnakOddelovac(char znak, char *oddelovac);
int jeZnakCislo(char znak, int cislo);
void cset(int cislo_stlpca, char *text, char *oddelovac, int velkost_pola, char *pole);
void dcols(int cislo_stlpca1, int cislo_stlpca2, char *oddelovac, int velkost_pola, char *pole);
void tolowerr(int cislo_stlpca, char *oddelovac, int velkost_pola, char *pole);
void toupperr(int cislo_stlpca, char *oddelovac, int velkost_pola, char *pole);
void roundd(int cislo_stlpca, char *oddelovac, int velkost_pola, char *pole);
void intc(int cislo_stlpca, char *oddelovac, int velkost_pola, char *pole);
void copy(int cislo_prveho_stlpca, int cislo_posledneho_stlpca, char *oddelovac, int velkost_pola, char *pole);

int main(int argc, char *argv[])
{
	int znak;
	int c = 0;
	char pole[MAX];
	char oddelovac[100];
	int riadky = 1;
	int stlpce = 0;

	if (argc > 2 && strcmp(argv[1], "-d") == 0)	//podmienka ak sa 1 argument rovna -d
	{
		if (strlen(argv[2]) > 100)	//oddelovac nemoze byt dlhsi ako 100 znakov
		{
			printf("Oddelovac nesmie by dlhsi nez 100 znakov.\n");
			return -1;
		}

		strcpy(oddelovac, argv[2]);	//ziska oddelovac
	}
	else if (argc > 2 && strcmp(argv[1], "-d") != 0)	//ak nieje urceny v argumente oddelovac
	{
		strcpy(oddelovac, " ");	//priradi oddelovacu medzeru
	}

	while ((znak = getchar()) != EOF)	// cyklus az kym nepride na koniec tabulky
	{
		if (znak != '\n')
		{
			pole[c] = znak;
			c++;
		}

		for (unsigned int i = 0; i < strlen(oddelovac); i++)
		{
			if (znak != '\n' && znak == oddelovac[i] && riadky == 1)	// pocitadlo stlpcov
			{
				stlpce++;
				break;
			}
		}

		if (znak == '\n')
		{
			for (int i = 0; i < argc; i++)
			{
				if (strcmp(argv[i], "drow") == 0)	//ak sa argument rovna drow
				{
					drow(argc, argv, riadky, pole);	//zavola funkciu drow
				}

				if (strcmp(argv[i], "drows") == 0)	//ak sa argument rovna icol
				{
					drows(argc, argv, riadky, pole);	//zavola funkciu icol
				}

				if (strcmp(argv[i], "icol") == 0)	//ak sa argument rovna icol
				{
					icol(atoi(argv[i + 1]), oddelovac, c, pole);	//zavola funkciu icol
				}

				if (strcmp(argv[i], "acol") == 0)	//ak sa argument rovna acol
				{
					acol(oddelovac, pole);	//zavola funkciu acol
				}

				if (strcmp(argv[i], "dcol") == 0)
				{
					dcol(atoi(argv[i + 1]), oddelovac, c, pole);
				}

				if (strcmp(argv[i], "dcols") == 0)
				{
					dcols(atoi(argv[i + 1]), atoi(argv[i + 2]), oddelovac, c, pole);
				}

				if (strcmp(argv[i], "irow") == 0)
				{
					irow(argc, argv, riadky, stlpce, oddelovac);
				}

				if (strcmp(argv[i], "tolower") == 0)
				{
					tolowerr(atoi(argv[i + 1]), oddelovac, c, pole);
				}

				if (strcmp(argv[i], "toupper") == 0)
				{
					toupperr(atoi(argv[i + 1]), oddelovac, c, pole);
				}

				if (strcmp(argv[i], "round") == 0)
				{
					roundd(atoi(argv[i + 1]), oddelovac, c, pole);
				}

				if (strcmp(argv[i], "cset") == 0)
				{
					cset(atoi(argv[i + 1]), argv[i + 2], oddelovac, c, pole);
				}

				if (strcmp(argv[i], "int") == 0)
				{
					intc(atoi(argv[i + 1]), oddelovac, c, pole);
				}
				if (strcmp(argv[i], "copy") == 0){

					copy(atoi(argv[i + 1]), atoi(argv[i + 2]), oddelovac, c, pole);
				}
			}

			if (strlen(pole) != 0)	//podmienka aby ked sa spusti drow a drows aby nevypsovalo prazdne riadky miesto vymazanych
			{
				printf("%s\n", pole);	//vypise vstup
			}

			for (unsigned int j = 0; j < MAX; j++)	// vymaze pole
			{
				pole[j] = '\0';
			}

			c = 0;	//vynuluje c
			riadky++;	//pocitadlo riadkov
		}
	}

	for (int i = 0; i < argc; i++)	//je nakonci aby sa nove pole vypisalo ako posledny riadok
	{
		if (strcmp(argv[i], "arow") == 0)	//porovna argument ak sa rovna arow
		{
			arow(stlpce, oddelovac);	//spusti funkcu arow
		}
	}

	return 0;
}

void irow(int argc, char *argv[], int riadky, int stlpce, char *oddelovac)
{
	int R;
	for (int i = 0; i < argc; i++)	// nacita argument
	{
		if (strcmp(argv[i], "irow") == 0)
		{
			R = atoi(argv[i + 1]);	// ak sa argument rovna irow tak sa argumet za irow rovna cislu riadka pred ktory prida novy riadok
		}
	}

	if (R <= 0)
	{
		perror("argument sa nesmie rovnat 0");	//argument musi byt vacsi ako 0
	}

	if (R > 0)
	{
		if (riadky == R)
		{
			for (int i = 0; i < stlpce; i++)
			{
				printf("%s", oddelovac);
			}

			printf("\n");
			riadky = riadky + 1;
		}
	}
}

void arow(int stlpce, char *oddelovac)
{
	for (int i = 0; i < stlpce; i++)
	{
		printf("%s", oddelovac);
	}

	printf("\n");
}

void drow(int argc, char *argv[], int riadky, char *pole)
{
	int P;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "drow") == 0)
		{
			P = atoi(argv[i + 1]);
		}
	}

	if (P <= 0)
	{
		perror("argument sa nesmie rovnat 0");
	}

	if (P > 0)
	{
		if (riadky == P)
			for (int j = 0; j <= MAX; j++)
			{
				pole[j] = '\0';
			}
	}
}

void drows(int argc, char *argv[], int riadky, char *pole)
{
	int M;
	int N;
	for (int i = 0; i < argc; i++)	//prejde argumenty a ziska M a N
	{
		if (strcmp(argv[i], "drows") == 0)
		{
			M = atoi(argv[i + 1]);
			N = atoi(argv[i + 2]);
		}
	}

	if (N <= 0)
	{
		perror("argument sa nesmie rovnat 0");
	}

	if (N < M)
	{
		perror("argument N nesmie byt mensi ako M ");
	}

	if (riadky >= M && riadky <= N)	// az dokym nepride po slpec N vymaze riadky
	{
		for (int j = 0; j < MAX; j++)
		{
			pole[j] = '\0';
		}
	}
}

void icol(int cislo_stlpca, char *oddelovac, int velkost_pola, char pole[])
{
    if (cislo_stlpca <= 0)
	{
		perror("argument sa nesmie rovnat 0");	//argument musi byt vacsi ako 0
	}

	int aktualny_stlpec = 1;

	if (cislo_stlpca == 1)	//prvy stlpec musime spracovat osobitne
	{
		char nahrada = oddelovac[0];	// znak, kt. sa prida na nasledujucu poziciu v poli, na zaciatku je to prvy znak oddelovaca
		for (int i = 0; i < velkost_pola; i++)
		{
			char tmp = pole[i];	//nahradime znak v poli a ulozime nahradeny znak do nahrady pre dalsiu iteraciu
			pole[i] = nahrada;
			nahrada = tmp;
		}

		return;
	}

	for (int i = 0; i <= velkost_pola; i++)
	{
		if (jeZnakOddelovac(pole[i], oddelovac) == 1)
		{
			aktualny_stlpec++;
			if (cislo_stlpca == aktualny_stlpec)	// tu pridame novy stlpec
			{
				char nahrada = oddelovac[0];	// rovnaky postup ako hore
				for (int k = i + 1; k < velkost_pola; k++)
				{
					char tmp = pole[k];
					pole[k] = nahrada;
					nahrada = tmp;
				}

				return;
			}
		}
	}
}

void dcol(int cislo_stlpca, char *oddelovac, int velkost_pola, char *pole)
{
    if (cislo_stlpca <= 0)
	{
		perror("argument sa nesmie rovnat 0");	//argument musi byt vacsi ako 0
	}
	if (cislo_stlpca > 0)
	{
		if (cislo_stlpca == 1)	// specialne spracujeme situaciu, ked treba nahradit prvy stlpec
		{
			int poz_oddelovaca = 0;
			for (int i = 0; i <= velkost_pola; i++)
			{
				if (jeZnakOddelovac(pole[i], oddelovac))
				{
					break;	// zapamatame si, kde sa nachadza prvy oddelovac
				}

				poz_oddelovaca++;
			}

			for (int i = 0; i <= velkost_pola; i++)
			{
				pole[i] = pole[++poz_oddelovaca];	// postupne nahradime vsetky znaky v prvom stlpci znakmi z naslednych stlpcov
				if (poz_oddelovaca > velkost_pola)
				{
					return;
				}
			}
		}
		else	// vymazavame stlpec vacsi ako 1
		{
			int poz_zaciatok_stlpca, poz_koniec_stlpca = 0;	// pozicie zaciatku a konca vymazavaneho stlpca
			int stlpec = 1;	// pocitadlo stlpcov
			for (int i = 0; i <= velkost_pola; i++)
			{
				if (jeZnakOddelovac(pole[i], oddelovac))
				{
					if (stlpec == cislo_stlpca - 1)
					{
						poz_zaciatok_stlpca = i;
					}

					if (stlpec == cislo_stlpca)
					{
						poz_koniec_stlpca = i;
						break;
					}

					stlpec++;
				}
			}

			if (poz_koniec_stlpca == 0)	// ak sa neulozila pozicia oddelovaca na konci stlpca, vymazavame posledny stlpec
			{
				poz_koniec_stlpca = velkost_pola;
			}

			int dlzka_mazaneho_stlpca = poz_koniec_stlpca - poz_zaciatok_stlpca;
			for (int i = poz_zaciatok_stlpca; i <= velkost_pola; i++)	// iterujeme od zaciatku mazaneho stlpca az po koniec riadku
			{
				pole[i] = pole[i + dlzka_mazaneho_stlpca];	//postupne presuvame hodnoty z nasledujucich stlpcov na miesto vymazavaneho stlpca
				if (i + dlzka_mazaneho_stlpca > velkost_pola)
				{
					for (int j = i; j < velkost_pola; j++)
					{
						pole[j] = '\0';	// nakoniec vycistime hodnoty na konci riadku, ktore su uz presunute na miesto vymazaneho stlpca
					}
				}
			}
		}
	}
}

int jeZnakOddelovac(char znak, char *oddelovac)
{
	for (unsigned int i = 0; i < strlen(oddelovac); i++)
	{
		if (znak == oddelovac[i])
		{
			return 1;
		}
	}

	return 0;
}

void acol(char *oddelovac, char *pole)
{
	char nahrada = oddelovac[0];
	for (int i = 0; i < MAX; i++)
	{
		if (pole[i] == '\0')
		{
			char tmp = pole[i];	//tak isto ako v icol
			pole[i] = nahrada;
			nahrada = tmp;
		}
	}
}

void dcols(int cislo_stlpca, int cislo_stlpca2, char *oddelovac, int velkost_pola, char *pole)
{
    if (cislo_stlpca <= 0)
	{
		perror("argument sa nesmie rovnat 0");
	}

	if (cislo_stlpca < cislo_stlpca2)
	{
		perror("prvy argument za dcols nesmie byt mensi ako druhy argument za dcols ");
	}
	for (int i = cislo_stlpca; i <= cislo_stlpca2; i++)	// vytvorime si int i kvoli tomu ze ak sa vymaze stlpec1 stlpec za nim sa vlozi na jeho miesto a potom by funkcia nefungovala
	{
		dcol(cislo_stlpca, oddelovac, velkost_pola, pole);
	}
}

void cset(int cislo_stlpca, char *text, char *oddelovac, int velkost_pola, char *pole)
{
    if (cislo_stlpca <= 0)
	{
		perror("argument sa nesmie rovnat 0");	//argument musi byt vacsi ako 0
	}
	if (cislo_stlpca > 0)
	{
		int stlpec = 1;	// pocitadlo stlpcov
		for (int i = 0; i < velkost_pola && stlpec <= cislo_stlpca; i++)
		{
			if (stlpec == cislo_stlpca)	//zmensuje az kym sa upravovany stlpec nerovna argumentu
			{
				for (int index_dalsieho_oddelovaca = i; index_dalsieho_oddelovaca <= velkost_pola; index_dalsieho_oddelovaca++)	// najdeme najblizsi oddelovac, kedze stlpec nemusi byt prazdny
				{
					if (jeZnakOddelovac(pole[index_dalsieho_oddelovaca], oddelovac))
					{
						strncpy(pole + i + strlen(text), pole + index_dalsieho_oddelovaca, velkost_pola - index_dalsieho_oddelovaca);	// zvysok textu ulozime na koniec pola

						int nadbytocne_znaky = strlen(pole + i + strlen(text)) - strlen(pole + index_dalsieho_oddelovaca);
						for (int j = velkost_pola - 1; j >= velkost_pola - nadbytocne_znaky; j--)	// vymazeme nadbytocne znaky
						{
							pole[j] = '\0';
						}

						break;
					}
				}

				strncpy(pole + i, text, strlen(text));
				break;
			}

			if (jeZnakOddelovac(pole[i], oddelovac))	//pocitadlo stlpcov
			{
				stlpec++;
			}
		}
	}
}

void tolowerr(int cislo_stlpca, char *oddelovac, int velkost_pola, char *pole)
{
    if (cislo_stlpca <= 0)
	{
		perror("argument sa nesmie rovnat 0");	//argument musi byt vacsi ako 0
	}
	if (cislo_stlpca > 0)
	{
		if (cislo_stlpca == 1)	// specialne spracujeme situaciu, ked treba zmensit pismena v prvom stlpci
		{
			int i = 0;
			while (!(jeZnakOddelovac(pole[i], oddelovac)))	//zmensuje az dokym nepride k oddelovacu
			{
				pole[i] = tolower(pole[i]);
				i++;
			}
		}
		else
		{
			int stlpec = 1;	// pocitadlo stlpcov
			for (int i = 0; i <= velkost_pola; i++)
			{
				if (jeZnakOddelovac(pole[i], oddelovac))	//pocitadlo stlpcov
				{
					stlpec++;
				}

				if (stlpec == cislo_stlpca)	//zmensuje az kym sa upravovany stlpec nerovna argumentu
					pole[i] = tolower(pole[i]);
			}
		}
	}
}

void toupperr(int cislo_stlpca, char *oddelovac, int velkost_pola, char *pole)
{
    if (cislo_stlpca <= 0)
	{
		perror("argument sa nesmie rovnat 0");	//argument musi byt vacsi ako 0
	}
	if (cislo_stlpca > 0)	//presne takisto ako v tolowerr
	{
		if (cislo_stlpca == 1)
		{
			int i = 0;
			while (!(jeZnakOddelovac(pole[i], oddelovac)))
			{
				pole[i] = toupper(pole[i]);
				i++;
			}
		}
		else
		{
			int stlpec = 1;
			for (int i = 0; i <= velkost_pola; i++)
			{
				if (jeZnakOddelovac(pole[i], oddelovac))
				{
					stlpec++;
				}

				if (stlpec == cislo_stlpca)
					pole[i] = toupper(pole[i]);
			}
		}
	}
}

//FUNKCIA round mi FUNGUJE LEN S PRELOZENIM -lm preto som ju radsej nechal iba v komentari aby som nemal dole body za to ze mi program nejde prelozit

void roundd(int cislo_stlpca, char *oddelovac, int velkost_pola, char *pole)
{
	if (cislo_stlpca <= 0)
	{
		perror("argument sa nesmie rovnat 0");	//argument musi byt vacsi ako 0
	}
	if (cislo_stlpca > 0)
	{
		int stlpec = 1;	// pocitadlo stlpcov
		for (int i = 0; i < velkost_pola && stlpec <= cislo_stlpca; i++)
		{
			if (stlpec == cislo_stlpca)
			{
				int index_dalsieho_oddelovaca = i + 1;
				for (; index_dalsieho_oddelovaca < velkost_pola; index_dalsieho_oddelovaca++)	// najdeme najblizsi oddelovac, kedze stlpec nemusi byt prazdny
				{
					if (jeZnakOddelovac(pole[index_dalsieho_oddelovaca], oddelovac))
					{
						break;
					}
				}

				char hodnota[index_dalsieho_oddelovaca - i];
				strncpy(hodnota, pole + i, sizeof(hodnota));	// naplnime premennu hodnota textom
				double hodnota_z_textu = atof(hodnota);
				double zaokruhlena_hodnota = round(hodnota_z_textu);

				if (zaokruhlena_hodnota == 0 && sizeof(hodnota) > 1)
				{
					// bud bola hodnota text alebo sa rovna 0.0 => netreba konvertovat
					break;
				}

				memset(hodnota, '\0', sizeof(hodnota));	// nastavime hodnotu na prazdnu
				sprintf(hodnota, "%.0f", zaokruhlena_hodnota);	// do premennej hodnota ulozime zaokruhlenu hodnotu
				strncpy(pole + i, hodnota, sizeof(hodnota) - 1 + 1);	// do stlpca ulozime zaokruhleny vysledok

				strncpy(pole + i + strlen(hodnota), pole + index_dalsieho_oddelovaca, velkost_pola - index_dalsieho_oddelovaca);	// kedze je vysledok kratsi tak ho presunieme

				int nadbytocne_znaky = strlen(pole + i + strlen(hodnota)) - strlen(pole + index_dalsieho_oddelovaca);
				for (int j = velkost_pola - 1; j >= velkost_pola - nadbytocne_znaky; j--)	// vymazeme nadbytocne znaky
				{
					pole[j] = '\0';
				}

				break;
			}

			if (jeZnakOddelovac(pole[i], oddelovac))
			{
				stlpec++;
			}
		}
	}
}

void intc(int cislo_stlpca, char *oddelovac, int velkost_pola, char *pole)
{
    if (cislo_stlpca <= 0)
	{
		perror("argument sa nesmie rovnat 0");	//argument musi byt vacsi ako 0
	}
	if (cislo_stlpca > 0)
	{
		int stlpec = 1;	// pocitadlo stlpcov
		for (int i = 0; i < velkost_pola && stlpec <= cislo_stlpca; i++)
		{
			if (stlpec == cislo_stlpca)
			{
				int index_dalsieho_oddelovaca = i + 1;
				for (; index_dalsieho_oddelovaca < velkost_pola; index_dalsieho_oddelovaca++)	// najdeme najblizsi oddelovac, kedze stlpec nemusi byt prazdny
				{
					if (jeZnakOddelovac(pole[index_dalsieho_oddelovaca], oddelovac))
					{
						break;
					}
				}

				char hodnota[index_dalsieho_oddelovaca - i];
				strncpy(hodnota, pole + i, sizeof(hodnota));	// naplnime premennu hodnota textom

				int zaokruhlena_hodnota = atoi(hodnota);

				if (zaokruhlena_hodnota == 0 && sizeof(hodnota) > 1)
				{
					// bud bola hodnota text alebo sa rovna 0.0 => netreba konvertovat
					break;
				}

				memset(hodnota, '\0', sizeof(hodnota));	// nastavime hodnotu na prazdnu
				sprintf(hodnota, "%d", zaokruhlena_hodnota);	// do premennej hodnota ulozime zaokruhlenu hodnotu
				strncpy(pole + i, hodnota, sizeof(hodnota) - 1);	// do stlpca ulozime zaokruhleny vysledok

				strncpy(pole + i + strlen(hodnota), pole + index_dalsieho_oddelovaca, velkost_pola - index_dalsieho_oddelovaca);	// kedze je vysledok kratsi tak ho presunieme

				int nadbytocne_znaky = strlen(pole + i + strlen(hodnota)) - strlen(pole + index_dalsieho_oddelovaca);
				for (int j = velkost_pola - 1; j >= velkost_pola - nadbytocne_znaky; j--)	// vymazeme nadbytocne znaky
				{
					pole[j] = '\0';
				}

				break;
			}

			if (jeZnakOddelovac(pole[i], oddelovac))
			{
				stlpec++;
			}
		}
	}
}

void copy(int cislo_prveho_stlpca, int cislo_posledneho_stlpca, char *oddelovac, int velkost_pola, char *pole)
{
	if (cislo_prveho_stlpca <= 0 || cislo_prveho_stlpca <= 0)
	{
		perror("argument sa nesmie rovnat 0");	//argument musi byt vacsi ako 0
	}
	else
	{
		int stlpec = 1;	// pocitadlo stlpcov
		for (int i = 0; i < velkost_pola; i++)
		{
			while(stlpec == cislo_prveho_stlpca && cislo_posledneho_stlpca == 0)
			{
				
			}

			if (jeZnakOddelovac(pole[i], oddelovac))	//pocitadlo stlpcov
			{
				stlpec++;
			}
		}
	}

}