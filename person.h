#ifndef PERSON_H
#define PERSON_H

// Définition de la structure de Person
typedef struct _Person {
    int src; // numéro de l'étage d'où vient la personne
    int dest; // numéro de l'étage où va la personne
} Person;

// Définition de la structure PersonList
typedef struct _PersonList {
    Person *person; // première personne dans la liste
    struct _PersonList *next; // liste des personnes restantes (peut être NULL)
} PersonList;

// Annonce des fonctions déclarées dans le fichier person.c 
Person* createPerson(int src, int dest);
PersonList* insert(Person *p, PersonList *list);
int taille_PL(PersonList *list);

#endif
