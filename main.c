#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "graph.c"
#include "load_data.c"
//#include "graph_loading.c"
/**
  * Instituto Tecnologico de Costa Rica
  * main file of the program
  * Dariem Hidalgo Arias
  * Kevin Salazar Valles
  */

void loadingData(linkedList * l){
    if(l == NULL){
    }else{
        vehicle * v1 = new_vehicle("Carro",1,15);
        insert(l, v1);
        vehicle * v2 = new_vehicle("Bicicleta",10,0.7);
        
        printf("\nVehiculos cargados exitosamente\n");
    }

}

//It selects the shortest way between points A & B
void selectTrip(void* A, void* B){
    printf("\n*******************************************************\n");
    printf("\nNot Implemented yet\n");
}
//It prints the graph on screen
void deploy(){
    printf("\n*******************************************************\n");
    printf("\nNot Implemented yet\n");
}

void seekVehicles(linkedList * l){
    printf("\n*******************************************************\n");
    if(l==NULL){
        return;
    }
    if(l->start==NULL){
        return;
    }
    else{
        printLList(l);
    }
}

void menu(linkedList* l){
    printf("*******************************************************\nMenu\nOpciones\n\t1.Seleccionar Viaje\n\t2.Ver Mapa\n\t3.Ver medios de transporte\n\t4.salir\n");
    printf("Seleccione una opcion: ");
    int option;
    scanf("%d", &option);
    char* a[100];
    char* b[100];
    switch (option){
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
        printf("\n");
        deploy();
        break;
    case 3:
        printf("\n");
        seekVehicles(l);
        break;
    case 4:
        exit(0);
    default:
        printf("\nSeleccione una de las opciones disponibles\n");
        break;
    }
}

int main(){
    linkedList * vehiculos = new_list();
    loadingData(vehiculos);

    while(true){
        menu(vehiculos);
    }
    return 0;
}
