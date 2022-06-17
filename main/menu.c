#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//**********************************************************************************
/*
this struct represents a simple linked list with all the vehicles aviable
*/
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
        printf("\nNo vehicles aviable\n");
        return;
    }
    else{
        vehicle * actual = l->start;
        while(actual!=NULL){
            actual=actual->sig;
        }actual->sig=v;
    }
}

vehicle *search(linkedList *l, char* var){
    if(l==NULL){
        printf("\nNo vehicles aviable\n");
        return;
    }if(l->start==NULL){
        printf("\nNo vehicles aviable\n");
        return;
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
            printf("\n%s\n\tesfuerzo: %d\n\temision CO2: %f\n", actual->name,actual->effort, actual->co2Emission);
            actual=actual->sig;
        }
    }
}
//**********************************************************************************
void uploadData(){
    FILE *data;
 	char text[100];
 	data = fopen("data.txt","r");
 	if (data == NULL){
        exit(1);
    }else{
 	    /*printf("\nEl contenido del archivo de prueba es \n\n");
 	    while (feof(data) == 0)
 	    {
 	        fgets(text,100, data);
 	        printf("%s\n", text);
 	    }*/
    }
    fclose(data);

    linkedList* vehicles;


}
//It selects the shortest way between points A & B
void selectTrip(void* A, void* B){
    printf("\nNot Implemented yet\n");
}
//It prints the graph on screen
void deploy(){
    printf("\nNot Implemented yet\n");
}

void seekVehicles(){
    printf("\nNot Implemented yet\n");
}

void menu(){
    printf("Menu\nOpciones\n\t1.Seleccionar Viaje\n\t2.Ver Mapa\n\t3.Ver medios de transporte\n\t4.salir\n");
    printf("Seleccione una opcion: ");
    int option;
    scanf("%d", &option);
    char* a[100];
    char* b[100];
    switch (option)
    {
    case 1:
        printf("\n");
        
        printf("Ingrese punto de partida >>");
        scanf("%s", &a);
        
        printf("\n\n");
        printf("Ingrese punto de llegada >>");
        
        scanf("%s", &a);
        
        selectTrip(a,b);
        break;
    case 2:
        printf("\n\n");
        deploy();
        break;
    case 3:
        printf("\n\n");
        seekVehicles();
        break;
    case 4:
        exit(0);
    default:
        printf("\nSeleccione una de las opciones disponibles\n");
        break;
    }
}

int main(){
    uploadData();
    while(true){
        menu();
    }
    return 0;
}