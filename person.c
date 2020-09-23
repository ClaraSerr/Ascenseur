#include <stdlib.h>
#include "person.h"

Person* createPerson(int src, int dest){
    Person* res = (Person*) malloc(sizeof(Person));
    res->src = src;
    res->dest = dest;
    return res;
}

PersonList* insert(Person *p, PersonList *list){
    PersonList* res = (PersonList*) malloc(sizeof(PersonList));
    res->person = p;
    res->next = list;
    return res;
}

int taille_PL(PersonList *list){
    int count = 0;
    PersonList* copie=list;
    while(copie != NULL){
        count ++;
        copie=copie->next;
    }
    return count;
}

