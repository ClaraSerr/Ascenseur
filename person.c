#include <stdlib.h>
#include "person.h"

Person* createPerson(int src, int dest){
    // Déclaration de la création d'une Person
    Person* res = (Person*) malloc(sizeof(Person));
    res->src = src;
    res->dest = dest;
    return res;
}

PersonList* insert(Person *p, PersonList *list){
    // Fonction qui renvoie une PersonList à laquelle on a ajouté une Person
    PersonList* res = (PersonList*) malloc(sizeof(PersonList)); // On alloue un nouvel espace à la PersonList
    res->person = p; // on place la nouvelle Person en premier (arbitraire)
    res->next = list; // on replace l'ancienne PersonList dans la nouvelle
    return res;
}

int taille_PL(PersonList *list){
    // Fonction qui renvoie le nombre de Person contenues dans une PersonList
    int count = 0;
    PersonList* copie = list;
    while(copie != NULL){
        count ++;
        copie=copie->next;
    }
    return count;
}

