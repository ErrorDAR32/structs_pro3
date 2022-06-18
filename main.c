#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
/**
  * Instituto Tecnologico de Costa Rica
  * main file of the program
  * Dariem Hidalgo Arias
  * Kevin Salazar Valles
  */

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
