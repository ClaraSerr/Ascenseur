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
    PersonList* stay = NULL;
    PersonList* exit = NULL;
    PersonList* cabine = e-> persons;
  
    while(cabine!=NULL){
        if(cabine->person->dest==e->currentFloor){
            exit=insert(cabine->person,exit);
            
        }
        else{
            
            stay=insert(cabine->person,stay);
            
        }
        cabine=cabine->next;
    }
    return stay;
    }

PersonList* enterElevator(Elevator *e, PersonList *waitingList){
    PersonList* new_waitingList=waitingList;
    if(waitingList!=NULL){   
        while((taille_PL(e->persons)<e->capacity) && (new_waitingList!=NULL)){
            e->persons = insert(new_waitingList->person,e->persons);
            new_waitingList=new_waitingList->next;
        }
    }
    return new_waitingList;
}
int iswlvide(Building *b){
    
    for(int j=0;j<=4;j++){
        if(b->waitingLists[j]!=NULL){
            return b->waitingLists[j]->person->dest;
        }
    }
    return -1;
}

void stepElevator(Building *b){
    
  if(b->elevator->currentFloor>b->elevator->targetFloor){
      b->elevator->currentFloor--;

  }
  else if(b->elevator->currentFloor<b->elevator->targetFloor){
          b->elevator->currentFloor++;
}
else if(b->elevator->persons==0){
        b->waitingLists[b->elevator->currentFloor]=enterElevator(b->elevator,b->waitingLists[b->elevator->currentFloor]);
        if(b->elevator->persons!=0 ){
    
            b->elevator->targetFloor=b->elevator->persons->person->dest;
        }
        else if(iswlvide(b)!=-1){
            b->elevator->targetFloor=iswlvide(b);
        }
}
    else{
        
        //des gens sortent de la cabine
    b->elevator->persons=exitElevator(b->elevator);
    b->waitingLists[b->elevator->currentFloor]=enterElevator(b->elevator,b->waitingLists[b->elevator->currentFloor]);
    if(b->elevator->persons!=0){
    
    b->elevator->targetFloor=b->elevator->persons->person->dest;
    }
    else if(iswlvide(b)!=-1){
            b->elevator->targetFloor=iswlvide(b);
        }
    }
    }