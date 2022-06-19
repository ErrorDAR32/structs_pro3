#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//**********************************************************************************
/*
this struct represents a simple linked list with all the vehicles aviable
*/

#define MAX 1000

typedef struct vehicle{
    char* name;
    int effort;
    double co2Emission;
    struct vehicle* sig;
}vehicle;

typedef struct linkedList{
    struct vehicle* start;
}linkedList;

vehicle *new_vehicle(char* pName, int pEffort, double co2){
    vehicle *n = calloc(1, sizeof(vehicle));
    n->name=pName;
    n->effort=pEffort;
    n->co2Emission=co2;
    n->sig=NULL;
    return n;

}

linkedList *new_list(){
    linkedList *n = calloc(1, sizeof(linkedList));
    n->start=NULL;
    return n;
}

void insert(linkedList *l, vehicle * v){
    if(l==NULL){
        printf("\nNo vehicles aviable\n");
        return;
    }if(l->start==NULL){
        l->start=v;
        return;
    }
    else{
        vehicle * actual = l->start;
        while(actual->sig!=NULL){
            actual=actual->sig;
        }actual->sig=v;
    }
}

vehicle *search(linkedList *l, char* var){
    if(l==NULL){
        printf("\nNo vehicles aviable\n");
        return NULL;
    }if(l->start==NULL){
        printf("\nNo vehicles aviable\n");
        return NULL;
    }
    else{
        vehicle * actual = l->start;
        while(actual!=NULL){
            if(strcmp(actual->name, var)){
                return actual;
            }
            actual=actual->sig;
        }
    }
    return NULL;
}

void printLList(linkedList* l){
    if(l==NULL){
        printf("\nNo vehicles aviable\n");
        return;
    }if(l->start==NULL){
        printf("\nNo vehicles aviable\n");
        return;
    }
    else{
        vehicle* actual = l->start;
        while(actual!=NULL){
            printf("\n%s\n\teffort: %d\n\tCO2 emission: %f\n", actual->name,actual->effort, actual->co2Emission);
            actual=actual->sig;
        }
    }
}
//**********************************************************************************
//returns the content of the file opened
void* uploadData(){
    FILE *data;
 	char* res = calloc(MAX, sizeof(char));
    data = fopen("data.txt","r"); //open file in reading mode (we know the name of the file, so it's not necessary bring it as func_args)
 	if (data == NULL){
        exit(1);//error
    }else{
 	    while (feof(data) == 0){
 	        fgets(res,MAX, data);
 	        printf("%s\n",res);
 	    }
    }
    fclose(data);
    return res;
}
