//Clemens Näther, "22/041/P2"

#include <stdio.h>

typedef struct tMedium {
        char type[32];
        char title[32];
        char author[32];
        char name[32];
} medium;

typedef struct ListElement {
        medium *m;
        struct ListElement *next;
} tListElement;

typedef struct {
        tListElement *first;
        tListElement *current;
        tListElement *last;
} tList;

// Nutzereingabe eines Mediums
medium *getMedium();

// Darstellung eines Mediums
void displayMedium(medium *m);

// Speichern eines Mediums in die Datei
int saveMedium(FILE* f, medium *m);

// Auslesen eines Mediums aus der Datei
medium *readMedium(FILE* pf);

// Erstellen einer Liste
tList *createList();

// Anfügen eines Mediums an den Listenanfang
void insElem(medium *newMedium, tList *list);

// Erstes Element der Liste
medium *getFirst(tList *list);

// Nächstes Element der Liste
medium *getNext(tList *list);

// Ausgeben der Elemente der Liste
void showAll(tList *list);

// alle gespeicherten Medien in der Textdatei in die Liste übertragen
void DataIntoList(tList *list, FILE* pf);

// alle Listenelemente in die Textdatei zeilenweise einspeichern
void saveData(tList *list, FILE* pf);

// Suche nach einem Datensatz
int searchData(tList *list, char* suche, int type, int delNum);

// Löschen eines Datensatzes
void delElem(tList *list, medium *m);