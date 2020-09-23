#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "person.h"

// Définition de la structure Elevator
typedef struct _Elevator {
    int capacity;    // capacité maximale de la cabine
    int currentFloor;// étage courant
    int targetFloor; // destination
    PersonList *persons; // personnes dans la cabine
} Elevator;

// Définition de la structure Building
typedef struct _Building {
    int nbFloor; // nombre d’étage des l’immeuble
    Elevator *elevator; // la cabine d’ascenseur
    PersonList **waitingLists; // array of waiting list (one per floor)
} Building;

// Annonce des fonctions déclarées dans le fichier elevator.c 
Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons);
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists);
int iswlvide(Building *b);

PersonList* exitElevator(Elevator *e);
PersonList* enterElevator(Elevator *e, PersonList *list);
void stepElevator(Building *b);

#endif
