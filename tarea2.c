#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VEHICULOS 200

// Declaración de la estructura Vehiculo
struct Vehiculo {
    char patente[10];
    char modelo[50];
    char tipo[20];
    char marca[50];
    char color[20];
    char comuna[50];
    int deuda;
};

// Función para leer los datos de los vehículos y cargarlos en el arreglo de Vehiculos
void leerVehiculos(FILE *archivo, struct Vehiculo *vehiculos, int *num_vehiculos) {
    char linea[200];
    while (fgets(linea, 200, archivo) != NULL) {
        char *token = strtok(linea, ",");
        strcpy(vehiculos[*num_vehiculos].patente, token);
        token = strtok(NULL, ",");
        strcpy(vehiculos[*num_vehiculos].modelo, token);
        token = strtok(NULL, ",");
        strcpy(vehiculos[*num_vehiculos].tipo, token);
        token = strtok(NULL, ",");
        strcpy(vehiculos[*num_vehiculos].marca, token);
        token = strtok(NULL, ",");
        strcpy(vehiculos[*num_vehiculos].color, token);
        token = strtok(NULL, ",");
        strcpy(vehiculos[*num_vehiculos].comuna, token);
        vehiculos[*num_vehiculos].deuda = 0;
        (*num_vehiculos)++;
    }
}

// Función para leer los datos de las multas y actualizar la deuda de cada vehículo correspondiente
void leerMultas(FILE *archivo, struct Vehiculo *vehiculos, int num_vehiculos) {
    char linea[200];
    while (fgets(linea, 200, archivo) != NULL) {
        char patente[10];
        char monto_str[20];
        char pagada_str[5];
        char *token = strtok(linea, ",");
        strcpy(patente, token);
        token = strtok(NULL, ",");
        strcpy(monto_str, token);
        token = strtok(NULL, ",");
        strcpy(pagada_str, token);
        int monto = atoi(monto_str);
        for (int i = 0; i < num_vehiculos; i++) {
            if (strcmp(patente, vehiculos[i].patente) == 0) {
                
                if (strncmp(pagada_str, "No", 2) == 0) {
                    //printf("Monto: %d\n", monto);
                    vehiculos[i].deuda += monto;
                }
                break;
            }
        }
    }
}

// Función para imprimir la deuda total de un vehículo según su patente
void deuda_p(char patente[], struct Vehiculo *vehiculos, int num_vehiculos) {
    for (int i = 0; i < num_vehiculos; i++) {
        if (strcmp(patente, vehiculos[i].patente) == 0){
            printf("La deuda total de la patente %s es %d\n", vehiculos[i].patente, vehiculos[i].deuda);
            return;
        }
    }
    printf("No se encontró ningún vehículo con la patente %s\n", patente);
}


void deuda_patente(char patente[], struct Vehiculo *vehiculos, int num_vehiculos) {
    for (int i = 0; i < num_vehiculos; i++) {
        if (strncmp(patente, vehiculos[i].patente , strlen(patente)) == 0){
            printf("La deuda total de la patente %s es %d\n", vehiculos[i].patente, vehiculos[i].deuda);
            
        }
    }
    return;
    printf("No se encontró ningún vehículo con la patente %s\n", patente);
}

int compara_vehiculos(const void *a, const void *b) {
    struct Vehiculo *vehiculo_a = (struct Vehiculo *)a;
    struct Vehiculo *vehiculo_b = (struct Vehiculo *)b;
    return vehiculo_b->deuda - vehiculo_a->deuda;
}

// Función para obtener los n vehículos con mayor deuda
void obtener_mayor_deuda(struct Vehiculo *vehiculos, int num_vehiculos, int n) {
    // Ordenar los vehículos en orden descendente de deuda usando Quicksort
    qsort(vehiculos, num_vehiculos, sizeof(struct Vehiculo), compara_vehiculos);
    
    // Imprimir los n vehículos con mayor deuda
    printf("Los %d vehículos con mayor deuda son:\n", n);
    for (int i = 0; i < n && i < num_vehiculos; i++) {
        printf("%s, %d\n", vehiculos[i].patente, vehiculos[i].deuda);
    }
}

int main(){
    //printf("HOLAAAA\n");
    FILE *autos = fopen("vehiculos.txt","r");
    FILE *deudas = fopen("deudas.txt", "r");
    struct Vehiculo vehiculos[MAX_VEHICULOS];
    int numero = 0;
    leerVehiculos(autos, vehiculos, &numero);
    leerMultas(deudas, vehiculos, numero);
    fclose(autos);
    fclose(deudas);
    
    

    deuda_patente("BI", vehiculos, numero);
    obtener_mayor_deuda(vehiculos, numero, 10);
    deuda_p("UIYI85", vehiculos, numero);

    return 0;
}