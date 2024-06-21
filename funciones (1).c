#include <stdio.h>
#include <string.h>
#include "funciones.h"

void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char tipo[40];
    printf("Ingrese el tamaño de habitacion que desea buscar: ");
    scanf("%s", tipo);
    printf("\n-------------------DATOS--------------------\n#\t\tTamaño\t\tHotel\t\t\tPrecio\n--------------------------------------------\n");

    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][1], tipo) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n--------------------------------------------\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);

        }
    }
}

void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    int Noencontrado = 1;
    char NomHotel[40];
    printf("Ingrese el nombre del hotel: ");
    scanf(" %39[^\n]", NomHotel);
    printf("\n-------------------DATOS--------------------\n#\t\tTamaño\t\tHotel\t\t\tPrecio\n--------------------------------------------\n");

    for (int i = 0; i < 9; i++) {
        char hotel[40];
        strcpy(hotel, habitaciones[i][2]);
        if (strcasecmp(hotel, NomHotel) == 0) {
            Noencontrado = 0;
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n--------------------------------------------\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);


        }

    }
    if (Noencontrado) {
        printf("*** No se encontraron habitaciones para ese hotel ***\n");
    }
}

void realizarReserva(int *numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][4]) {
    char nombreCliente[40];
    char cedulaCliente[40];
    int habitacionSeleccionada;

    printf("Ingrese su nombre: ");
    scanf("%s", nombreCliente);

    printf("Ingrese su cedula: ");
    scanf("%s", cedulaCliente);

    printf("Elija el numero de habitacion que desea reservar (1-9): ");
    scanf("%d", &habitacionSeleccionada);

    if (habitacionSeleccionada < 1 || habitacionSeleccionada > 9) {
        printf("Número de habitación inválido\n");
        return;
    }

    int indiceCliente = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedulaCliente) == 0) {
            indiceCliente = i;
            break;
        }
    }
    if (indiceCliente == -1) {
        for (int i = 0; i < 5; i++) {
            if (clientes[i][0][0] == '\0') {
                strcpy(clientes[i][0], nombreCliente);
                strcpy(clientes[i][1], cedulaCliente);
                indiceCliente = i;
                break;
            }
        }

        if (indiceCliente == -1) {
            printf("No hay espacio para más clientes\n");
            return;
        }
    }
    if (reservas[habitacionSeleccionada - 1][3] == 0) {
        reservas[habitacionSeleccionada - 1][3] = 1;            
        reservas[habitacionSeleccionada - 1][0] = indiceCliente; 
        reservas[habitacionSeleccionada - 1][1] = habitacionSeleccionada - 1; 
        *numHabitacion = habitacionSeleccionada;
        printf("\n¡Reserva realizada con éxito!\n");
        printf("*** Habitación seleccionada %d ***\n", *numHabitacion);
    } else {
        printf("\n*** La habitación %d ya está reservada ***\n", habitacionSeleccionada);
    }
}


void buscarReservaPorCedula(int *numReserva, char clientes[][2][40], int reservas[][4]) {
    char cedula[40];
    int reservasEncontradas = 0;

    printf("Ingrese el número de cédula del cliente: ");
    scanf("%s", cedula);

    int indiceCliente = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            indiceCliente = i;
            break;
        }
    }

    if (indiceCliente == -1) {
        printf("Cliente no encontrado\n");
        *numReserva = -1;  
        return;
    }

    for (int j = 0; j < 10; j++) {
        if (reservas[j][3] == 1 && reservas[j][0] == indiceCliente) {
            *numReserva = j + 1; 
            reservasEncontradas++;
        }
    }

    if (reservasEncontradas == 0) {
        printf("No se encontraron reservas para el cliente con cédula %s\n", cedula);
        *numReserva = -1;  
        return;
    }
}
void imprimirReserva(int *numReserva, int reservas[][4], char habitaciones[][3][40], double precios[], char clientes[][2][40]) {
    int indiceReserva = *numReserva - 1; 

    if (indiceReserva < 0 || indiceReserva >= 10) {
        printf("Número de reserva inválido.\n");
        return;
    }

    if (reservas[indiceReserva][3] == 0) {
        printf("La reserva seleccionada no está activa.\n");
        return;
    }

    int indiceCliente = reservas[indiceReserva][0];
    int indiceHabitacion = reservas[indiceReserva][1];
    double precioReserva = precios[indiceHabitacion];
    char tipoHabitacion[40];
    char nombreHotel[40];

    strcpy(tipoHabitacion, habitaciones[indiceHabitacion][1]);
    strcpy(nombreHotel, habitaciones[indiceHabitacion][2]);

    printf("\n=======Detalles de la reserva:=======\n");
    printf("Nombre del cliente: %s\n", clientes[indiceCliente][0]);
    printf("Cédula del cliente: %s\n", clientes[indiceCliente][1]);
    printf("Número de reserva: %d\n", *numReserva);
    printf("Hotel: %s\n", nombreHotel);
    printf("Tipo de habitación: %s\n", tipoHabitacion);
    printf("Precio por noche: %.2lf\n", precioReserva);
}

void pagarReserva(int *numReserva, int reservas[][4], char habitaciones[][3][40], double precios[]) {



}