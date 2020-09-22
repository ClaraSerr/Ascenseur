#include <stdlib.h>
#include "elevator.h"


Elevator* create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator* res = (Elevator*) malloc(sizeof(Elevator));
    res->capacity = capacity;
    res->currentFloor = currentFloor;
    res->persons = persons;
    res->targetFloor = persons?persons->person->dest:0;
    return res;
}

Building* create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building* res = (Building*) malloc(sizeof(Building));
    res->nbFloor = nbFloor;
    res->elevator = elevator;
    res->waitingLists = waitingLists;
    return res;
}

PersonList* exitElevator(Elevator *e){
    PersonList* res = (PersonList*) malloc(sizeof(PersonList));
    res->next = NULL;
    PersonList* personnes_dedans = e->persons;
    while(personnes_dedans!=NULL){
        if(personnes_dedans->person->dest!=e->currentFloor){
            res->person = personnes_dedans->person;
            res->next = res;
        }
        personnes_dedans = personnes_dedans->next;
    }
    return res;

}

PersonList* enterElevator(Elevator *e, PersonList *waitingList){
    PersonList* new_waitingList=waitingList;
    if(waitingList!=NULL){   
        while((taille_PersonList(e->persons)<e->capacity) || (new_waitingList!=NULL)){
            if(new_waitingList->person->src==e->currentFloor){
                PersonList* new_cabine = insert(new_waitingList->person,e->persons);
                e->persons=new_cabine;
            }
            new_waitingList=new_waitingList->next;
        }
    }
    return new_waitingList;
}

void stepElevator(Building *b){
    b->elevator->persons=exitElevator(b->elevator);
    *b->waitingLists=enterElevator(b->elevator,*b->waitingLists);
  if(b->elevator->currentFloor==b->elevator->targetFloor && b->elevator->persons!=0){
    //des gens sortent de la cabine
    
    b->elevator->targetFloor=b->elevator->persons->person->dest;
    
  }
  else{
      
      if(b->elevator->currentFloor>b->elevator->targetFloor){
          b->elevator->currentFloor--;
      }
        else{
            b->elevator->currentFloor++;
        }
  }
}