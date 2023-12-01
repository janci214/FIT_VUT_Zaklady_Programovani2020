# FIT_VUT_Zaklady_Programovani2020
## Projekt 1 - Práce s textem\
### Motivace projektu\
\
Představme si, že máme jednoduchý textový soubor obsahující tabulkové informace (například řádky s jednotlivými\
buňkami oddělené mezerou). Představme si, že chceme spočítat součet všech hodnot ve třetím sloupci, nebo zjistit\
jejich aritmetický průměr, odebrat nějaký sloupec nebo přidat nový, který bude představovat součet dvou\
předchozích buněk? Musíme si spustit těžkopádný tabulkový procesor (Excel, Libreoffice Calc, Google Sheets apod.),\
data do něj importovat, klikat, co chceme provést, a následně uložit. A co když takových souborů stejného typu, ale\
s různými daty máme hodně? Hodil by se jednoduchý nástroj pro příkazovou řádku, kterému bychom řekli, co s\
textovým souborem má dělat, a nástroj automaticky spustili opakovaně nad každým souborem. Nebude to sice\
hezky "klikatelné", ale ušetří nám to spoustu práce.\
\
### Popis projektu:\
\
Cílem projektu je vytvořit program, který bude implementovat základní operace tabulkových procesorů. Vstupem\
programu budou textová data, zadání operací bude prostřednictvím argumentů příkazové řádky a svůj výsledek bude\
program vypisovat na výstup.\
\
### Detailní specifikace:\
\
Program implementujte ve zdrojovém souboru sheet.c. Vstupní data budou čtena ze standardního vstupu (stdin),\
výstup bude tisknut na standardní výstup (stdout).\
Překlad a odevzdání zdrojového souboru\
Odevzdání: Odevzdejte zdrojový soubor sheet.c prostřednictvím informačního systému.\
Překlad: Program překládejte s následujícími argumenty\
$ gcc -std=c99 -Wall - Wextra -Werror sheet.c -o sheet\
Syntax spuštění\
Program se spouští v následující podobě: (./sheet značí umístění a název programu):\
Úprava velikosti tabulky:\
\
**./sheet [-d DELIM] [Příkazy pro úpravu tabulky]\**
\
nebo zpracování dat:\
\
**./sheet [-d DELIM] [Selekce řádků] [Příkaz pro zpracování dat]\**
\
• Argument -d specifikuje, jaké znaky lze interpretovat jako oddělovače jednotlivých buněk. Každý znak ve\
vstupním řádku, který je obsažen v řetězci DELIM, se chová jako oddělovač dvou sousedících buněk. Ve výchozím\
nastavení je DELIM řetězec obsahující mezeru. Vícenásobný výskyt stejných znaků v řetězci DELIM je ignorován.\
První znak z řetězce DELIM bude také použit jako oddělovač výstupních hodnot.\
Úprava tabulky\
Úpravy tabulky způsobují zvětšení či zmenšení tabulky, resp. řádků a sloupců. Příkazů pro úpravu tabulky může být\
zadáno více. V takovém případě budou zadány jako sekvence více argumentů příkazové řádky:\
\
### Příkazy pro úpravu tabulky:\
\
•irow R - vloží řádek tabulky před řádek R > 0 (insert-row).\
• arow - přidá nový řádek tabulky na konec tabulky (append-row).\
•drow R - odstraní řádek číslo R > 0 (delete-row).\
• drows N M - odstraní řádky N až M (N <= M). V případě N=M se příkaz chová stejně jako drow N.\
•icol C - vloží prázdný sloupec před sloupec daný číslem C.\
• acol - přidá prázdný sloupec za poslední sloupec.\
• dcol C - odstraní sloupec číslo C.\
• dcols N M - odstraní sloupce N až M (N <= M). V případě N=M se příkaz chová stejně jako dcol N.\
Budou kontrolovány samostatné příkazy a sekvence příkazů, které nemají kolizní čísla řádků nebo sloupců (např.\
arow irow 10, nebo dcol 5 drow 3).\
\
### Zpracování dat\
\
Zpracování dat představuje úpravy obsahu jednotlivých buněk tabulky. Každé spuštění programu může obsahovat\
nejvíce jeden příkaz pro zpracování dat. Příkazy pro zpracování dat jsou následující:\
\
• Příkazy, které jsou povinné pro úspěšné splnění projektu:\
• cset C STR - do buňky ve sloupci C bude nastaven řetězec STR.\
• tolower C - řetězec ve sloupci C bude převeden na malá písmena.\
•toupper C - řetězec ve sloupce C bude převeden na velká písmena.\
• round C - ve sloupci C zaokrouhlí číslo na celé číslo.\
int C- odstraní desetinnou část čísla ve sloupci C.\
