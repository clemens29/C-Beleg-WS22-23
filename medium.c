//Clemens Näther, "22/041/P2"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "medium.h"

char vBuf[128];

// neues Medium per Nutzereingabe erfassen
medium *getMedium() {
    medium *m1 = malloc(sizeof (medium));
    printf("Medium eingeben:\n");
    printf("Mediumtyp: ");          fgets(vBuf,128,stdin);
    vBuf[strlen(vBuf)-1] = 0;       strcpy(m1->type, vBuf);
    printf("Titel: ");              fgets(vBuf,128,stdin);
    vBuf[strlen(vBuf)-1] = 0;       strcpy(m1->title, vBuf);
    printf("Autor/Interpret: ");    fgets(vBuf,128,stdin);
    vBuf[strlen(vBuf)-1] = 0;       strcpy(m1->author, vBuf);
    printf("Name: ");               fgets(vBuf,128,stdin);
    vBuf[strlen(vBuf)-1] = 0;       strcpy(m1->name, vBuf);
    return m1;
}

//gesamte Daten tabellarisch ausgeben
void showAll(tList* list) {
    medium* m;
    for (m = getFirst(list); m != NULL; m = getNext(list)) {
        displayMedium(m);
    }
}

// Medium ausgeben
void displayMedium(medium *m) {
    printf("%-10s|%-30s|%-20s|%-20s\n", m->type, m->title, m->author, m->name);
}

// Medium in der Textdatei zeilenweise speichern
int saveMedium(FILE* pf, medium *m) {
    return fprintf(pf, "%s\n%s\n%s\n%s\n", m->type, m->title, m->author, m->name);
}

// Lesen eines Datensatzes aus der Datei
medium *readMedium(FILE* pf) {
    int ret;
    medium *tmp = malloc(sizeof (medium));
    if (tmp) {
        ret = fscanf(pf, "%s\n%[^\n]\n%[^\n]\n%[^\n]\n", tmp->type, tmp->title, tmp->author, tmp->name);
        if (ret <= 0) {
            free(tmp); tmp = NULL;
        }
    }
    return tmp;
}

// alle gespeicherten Medien in der Textdatei in die Liste übertragen
void DataIntoList(tList *list, FILE* pf) {
    medium *tmp;
    while ( (tmp = readMedium(pf)) != NULL) {
        insElem(tmp, list);
    }
}

// alle Listenelemente in die Textdatei zeilenweise speichern
void saveData(tList *list, FILE* pf) {
    medium *tmp;
    for (tmp = getFirst(list); tmp; tmp = getNext(list)) {
            saveMedium(pf, tmp);
    }
}

// leere Liste erstellen
tList *createList() {
    tList *tmp = malloc(sizeof(tList));
    if (tmp) {
        tmp->first = tmp->current = tmp->last = NULL;
    }
    return tmp;
}

// neues Element wird geordnet in die Liste eingefügt
void insElem(medium *newMedium, tList *list) {
    tListElement *tmp = malloc(sizeof(tListElement));
    if (tmp) {
        tmp->m = newMedium;
        tmp->next = NULL;
        if (list->first == NULL || strcmp(newMedium->title, list->first->m->title) < 0) {
            tmp->next = list->first;
            list->first = tmp;
            if (list->last == NULL) {
                list->last = tmp;
            }
        } else {
            tListElement *curr = list->first;
            while (curr->next != NULL && strcmp(newMedium->title, curr->next->m->title) > 0) {
                curr = curr->next;
            }
            tmp->next = curr->next;
            curr->next = tmp;
            if (tmp->next == NULL) {
                list->last = tmp;
            }
        }
    }
}

//Suchen eines Datensatzes
int searchData(tList *list, char* suche, int type, int delNum) {
    medium *tmp;
    int count = 0;
    for (tmp = getFirst(list); tmp; tmp = getNext(list)) {
        switch (type) {
            case 1: if (strcmp(tmp->type,suche) == 0) {
                    count++;
                    if (count == delNum && delNum != 0) {
                        delElem(list, tmp);
                        return 0;
                    }
                    if (delNum == 0) displayMedium(tmp);
                }
                break;
            case 3: if (strcmp(tmp->author,suche) == 0) {
                    count++;
                    if (count == delNum && delNum != 0) {
                        delElem(list, tmp);
                        return 0;
                    }
                    if (delNum == 0) displayMedium(tmp);
                }
                break;
            case 4: if (strcmp(tmp->name,suche) == 0) {
                    count++;
                    if (count == delNum && delNum != 0) {
                        delElem(list, tmp);
                        return 0;
                    }
                    if (delNum == 0) displayMedium(tmp);
                }
                break;
            default: if (strcmp(tmp->title,suche) == 0) {
                    count++;
                    if (count == delNum && delNum != 0) {
                        delElem(list, tmp);
                        return 0;
                    }
                    if (delNum == 0) displayMedium(tmp);
                }
        }
    }
    return count;
}

// Element aus der Liste löschen
void delElem(tList *list, medium* m) {
    tListElement *curr = list->first;
    tListElement *prv = NULL;

    while (curr->m != m) {
        prv = curr;
        curr = curr->next;
    }

    if (prv != NULL) {
        prv->next = curr->next;
    } else {
        list->first = curr->next;
    }
    free(curr->m);
    free(curr);
    printf("Datensatz wurde gelöscht.\n");
}

// erstes Element der Liste
medium *getFirst(tList *list) {
    medium *tmp = NULL;
    if (list->first)  {
        tmp = list->first->m;
        list->current = list->first;
    }
    return tmp;
}

// nächstes Element der Liste
medium *getNext(tList *list) {
    medium *tmp = NULL;
    if (list->current) {
        list->current = list->current->next;
        if (list->current) {
            tmp = list->current->m;
        }
    }
    return tmp;
}