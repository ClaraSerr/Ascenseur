#include <stdlib.h>
#include "elevator.h"


Elevator* create_elevator(int capacity, int currentFloor, PersonList *persons){
    // Déclaration de la création d'un Elevator
    Elevator* res = (Elevator*) malloc(sizeof(Elevator));
    res->capacity = capacity;
    res->currentFloor = currentFloor;
    res->persons = persons;
    res->targetFloor = persons?persons->person->dest:0; // Si l'ascenseur est créé vide, il reste au niveau 0
    return res;
}

Building* create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    // Déclaration de la création d'un Building
    Building* res = (Building*) malloc(sizeof(Building));
    res->nbFloor = nbFloor;
    res->elevator = elevator;
    res->waitingLists = waitingLists;
    return res;
}

int iswlvide(Building *b){
    // Fonction qui retourne la source d'une Person dans la file d'attente, et -1 si plus personne n'attend l'ascenseur
    for(int j=0;j<=4;j++){ // on sait qu'il y a 4 étages, je n'ai pas réussi à extraire la taille d'un **PersonList
        if(b->waitingLists[j] != NULL){ // l'étage j a une file d'attente non nulle
            return b->waitingLists[j]->person->src; // on renvoie l'étage source de la première Person trouvée
        }
    }
    return -1; // il n'y a plus personne qui attend l'ascenseur
}

PersonList* exitElevator(Elevator *e){
    // Fonction qui renvoie la PersonList des Person qui restent dans l'ascenseur après avoir atteint l'étage Target
    PersonList* stay = NULL; // on initialise la PersonList à retourner
    PersonList* cabine = e->persons; // copie de la cabine à l'arrivée à l'étage
  
    while(cabine != NULL){ // on passe en revue toutes les Person de la cabine
        if(cabine->person->dest != e->currentFloor){
            // on insère les personnes qui ne sont pas arrivées à destination dans la PersonList à retourner
            stay=insert(cabine->person,stay);
        }
        cabine=cabine->next;
    }
    return stay;
    }

PersonList* enterElevator(Elevator *e, PersonList *waitingList){
    // Fonction qui renvoie la nouvelle liste d'attente de l'étage courant après avoir remplit la cabine de l'ascenseur
    PersonList* new_waitingList = waitingList; // on initialise la nouvelle liste d'attente

    if(waitingList!=NULL){ // on vérifie qu'il y a bien des Person qui attendent pour prendre l'ascenseur
        while((taille_PL(e->persons) < e->capacity) && (new_waitingList != NULL)){ // lorsqu'il reste de la place dans l'ascenseur OU qu'il reste des gens qui attendent
            e->persons = insert(new_waitingList->person,e->persons); // on fait rentrer une Person dans l'ascenseur
            new_waitingList=new_waitingList->next; // on met à jour la liste d'attente
        }
    }
    return new_waitingList;
}

void stepElevator(Building *b){
    // Procédure qui fait l'itération du fonctionnement de l'ascenseur
    if(b->elevator->currentFloor > b->elevator->targetFloor){
        // l'ascenseur est plus haut que son étage Target
        b->elevator->currentFloor--;
    }
    else if(b->elevator->currentFloor<b->elevator->targetFloor){
        // l'ascenseur est plus bas que son étage Target
        b->elevator->currentFloor++;
    }
    else{ 
        // l'ascenseur est arrivé à destination
        if(b->elevator->persons == NULL){
            // l'ascenseur est vide, on le remplit avec les Person dans la file d'attente
            b->waitingLists[b->elevator->currentFloor] = enterElevator(b->elevator,b->waitingLists[b->elevator->currentFloor]);
            if(b->elevator->persons != NULL){
                // si des Person sont rentrées dans la cabine, on met à jour l'étage Taget (arbitrairement la destination du premier Person dans la cabine)
                b->elevator->targetFloor = b->elevator->persons->person->dest;
            }
            else if(iswlvide(b)!=-1){
                // l'ascensseur est toujours vide, mais il reste des Person dans les listes d'attente aux autres étages
                b->elevator->targetFloor = iswlvide(b); // on met à jour l'étage Target
            }
            else{
                // l'ascenseur revient au rdc à la fin
                b->elevator->targetFloor = 0;
            }
        }
        else{
            // l'ascenseur contient des Person
            b->elevator->persons = exitElevator(b->elevator); // il ne reste dans la cabine que les Person qui ne sont pas arrivées à destination
            b->waitingLists[b->elevator->currentFloor] = enterElevator(b->elevator,b->waitingLists[b->elevator->currentFloor]); // des Person rentrent dans l'ascenseur
            if(b->elevator->persons != NULL){
                // des Person sont dans la cabine, on peut mettre à jour l'étage Target
                b->elevator->targetFloor = b->elevator->persons->person->dest;
            }
            else if(iswlvide(b) != -1){
                // l'ascensseur est vide, mais il reste des Person dans les listes d'attente aux autres étages
                b->elevator->targetFloor = iswlvide(b); // on met à jour l'étage Target
            }
            else{
                // l'ascenseur revient au rdc à la fin
                b->elevator->targetFloor = 0;
            }
        }
    }
}