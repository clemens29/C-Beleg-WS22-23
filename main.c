// Clemens Näther, "22/042/P2"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "medium.h"

char vBuf[128];

int main() {
    tList *list = createList();
    FILE* f;
    f = fopen("data.txt", "rt");
    if (f != NULL) {
            DataIntoList(list, f);
            fclose(f);
    }
    medium *m1;
    char input, suche[128];
    int type, count, delNum;
        
    while (input != 'b') {
        printf("\nDatensatz (e)rfassen, (l)öschen, (s)uchen, (a)nzeigen oder Programm (b)eenden: ");
        fgets(vBuf,128,stdin); input = tolower(vBuf[0]);
        switch (input) {
            case 'e': m1 = getMedium();
                insElem(m1,list);
                break;

            case 'l': printf("Datensatz löschen\n");
                printf("Suche nach (1)Typ, (2)Titel, (3)Autor/Interpret oder (4)Leihende Person: ");
                fgets(vBuf,128,stdin); type = atoi(vBuf);
                printf("Suchbegriff: ");
                fgets(vBuf,128,stdin); strcpy(suche,vBuf);
                suche[strlen(suche)-1] = 0;
                count = searchData(list, suche, type, 0);
                if (count == 0) printf("Keine passenden Datensätze gefunden!\n");
                else {
                    printf("Welcher Datensatz soll gelöscht werden? (1-%d): ", count);
                    fgets(vBuf,128,stdin); delNum = atoi(vBuf);
                    searchData(list, suche, type, delNum);
                }
                break;

            case 's': printf("Suche nach (1)Typ, (2)Titel, (3)Autor/Interpret oder (4)Leihende Person: ");
                fgets(vBuf,128,stdin); type = atoi(vBuf);
                printf("Suchbegriff: ");
                fgets(vBuf,128,stdin); strcpy(suche,vBuf);
                suche[strlen(suche)-1] = 0;
                count = searchData(list, suche, type, 0);
                if (count == 0) printf("Keine passenden Datensätze gefunden!\n");
                break;

            case 'a': showAll(list);
                break;

            case 'b': f = fopen("data.txt", "wt");
                saveData(list, f);
                fclose(f);
                printf("Programm wurde beendet.\n\n"); break;
            default:  printf("Falsche Eingabe.\n"); break;
        }
    }
    return 0;
}