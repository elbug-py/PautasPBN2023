#include <stdio.h>
#include <math.h>

float distancia(float x, float y){
    return sqrt(x*x+y*y);
}


int main() {

  FILE *archivo;
  archivo = fopen("equipos_s.txt", "r");

//CONTADOR DE LINEAS
    char c;
    int count=0;
    while ((c = fgetc(archivo)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    
    fclose(archivo);

    archivo = fopen("equipos_s.txt", "r");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo.\n");
            return 1;
        }

//GUARDADO DE DATOS EN ARRAYS (COORDENADAS X e Y, NOMBRES)
    char linea[1000];
    char nombres[count][1000];
    float X, Y;
    float coor_x[count+1];
    float coor_y[count+1];
    int equipo=0;
  
    while (fgets(linea, count, archivo) != NULL) {
        sscanf(linea, "%[^,],%f,%f", nombres[equipo], &X, &Y);
        coor_x[equipo] = X;
        coor_y[equipo] = Y;
        equipo++;
    }

    float adj_mtrx[count][count];
    int adya[count][count];
    

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {   
            adj_mtrx[i][j] = distancia(coor_x[i]-coor_x[j], coor_y[i]-coor_y[j]);
        }
        
    }

    /*for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {   
            printf("%f|",adj_mtrx[i][j]);
        }
        printf("\n");
    }*/

    
    int partidos[count][4];
    float min_dist = 99999999;
    int match = 99999999;
    int old_match = 99999999;
    int asignados[count];
    
    for (int i = 0; i < count; i++)
    {
        
        for (int part = 0; part < 4; part++)
        {
            for (int j = 0; j < count; j++)
            {   
                if (adj_mtrx[i][j] < min_dist && asignados[j] == 0 && i!=j && partidos[i][part] == 0)
                {
                    min_dist = adj_mtrx[i][j];
                    match = j;
                }
                
            }
            if (old_match != match)
            {
                partidos[i][part] = match;
                partidos[match][part] = i;
                asignados[match] = 1;
                asignados[i] = 1;
                old_match = match;
                adya[i][part] = 1;
                adya[part][i] = 1;
            }
            
            
            min_dist = 99999999;
            

        }
        


        
    }

    //printf("%d", partidos[0][0]);
    printf("%d\n", adya[1][1]);
    
    for (int i = 0; i < count; i++)
        {
            printf("%d|", i);
            for (int j = 0; j < 4; j++)
            {   
                printf("%d|",partidos[i][j]);
            }
            printf("\n");
        }
        
    printf("\n");
    

    /*for (int i = 0; i < count; i++)
    {
        printf("%d : %d\n", i, asignados[i]);
    }
    */
    





return 0;
}