#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE 300

int isFloat(char *str){
    char *endptr;
    strtod(str, &endptr);
    if (*endptr == '\0' || (*endptr == '.' && *(endptr + 1) != '\0')) {
        return 1;
    }
    return 0;
}

int isInt(char *str){
    char *endptr;
    strtol(str, &endptr, 10);
    if (*endptr == '\0') {
        return 1;
    }
    return 0;
}

int isCoordinate(char *str){
    int len = strlen(str);
    if (len >= 3 && str[0] == '(' && strchr(str, ',') != NULL) {
        return 1;
    }
    return 0;
}

float distanciazero(float pX, float pY){
    float distance;
    float y0 = 0.0;
    float x0 = 0.0;
    
    distance = sqrt(pow((x0 - pX), 2) + pow((y0 - pY), 2));
    
    return distance;
}

struct auxiliar {
    char texto[50];
    char inteiro[50];
    char flutuante[50];
    char ponto[25];
    float distancia;
};

struct Coord {
    float x;
    float y;
    float distance;
};

/*
void ordenarstring(const char *a, const char *b){
    char aux[100];
    int r = strcmp(a, b);

    if(r > 0){
        strcpy(aux, a);
        strcpy(a, b);
        strcpy(b, aux);
    }
}
*/

int main() {
    FILE* file_in = fopen("L0Q2.in","r");
    FILE* file_out = fopen("L0Q2.out","w");

    if(file_in == NULL || file_out == NULL){
        printf("Falha na criacao dos arquivos\n");
        return EXIT_FAILURE;
    }
    else{
        printf("Arquivos criados e abertos com sucesso\n");
    }

    char * line = malloc(MAX_LINE * sizeof(char));

    //while vem aqui
    while (fgets(line, MAX_LINE, file_in)){

        struct auxiliar aux[100];
        int texto_count = 0;
        int inteiro_count = 0;
        int flutuante_count = 0;
        int ponto_count = 0;

        char * token = strtok(line, " ");
            while (token != NULL) {
                if (isCoordinate(token)) {
                    strcpy(aux[ponto_count].ponto, token);
                    ponto_count++;
                } else if (isInt(token)) {
                    strcpy(aux[inteiro_count].inteiro, token);
                    inteiro_count++;
                } else if (isFloat(token)) {
                    strcpy(aux[flutuante_count].flutuante, token);
                    flutuante_count++;
                } else {
                    strcpy(aux[texto_count].texto, token);
                    texto_count++;
                }
                token = strtok(NULL, " ");
            }
        
        //fazer ordenacao de strings aqui
        for (int i = 0; i < texto_count; i++){
            char key[80];
            strcpy(key, aux[i].texto);
            int j = i - 1;
            while (j >= 0 && strcmp(aux[j+1].texto, aux[j].texto) < 0){
                strcpy(aux[j+1].texto, aux[j].texto);
                j--;
            }
            strcpy(aux[j+1].texto, key);
        }

    // ordenacao inteiro
        int inteiro[80];

        for (int i = 0; i < inteiro_count; i++){
            inteiro[i] = atoi(aux[i].inteiro);
        }

        for (int i = 0; i < inteiro_count; i++){
            int key = inteiro[i];
            int j = i - 1;
            while (j >= 0 && inteiro[j] > key){
                inteiro[j+1] = inteiro[j];
                j--;
            }
            inteiro[j+1] = key;
        }

    // ordenacao flutuante
        float flutuante[80];

        for (int i = 0; i < inteiro_count; i++){
            flutuante[i] = atof(aux[i].flutuante);
        }

        for (int i = 1; i < inteiro_count; i++){
            float keyf = flutuante[i];
            int j = i - 1;
            while (j >= 0 && flutuante[j] > keyf){
                flutuante[j+1] = flutuante[j];
                j--;
            }
            flutuante[j+1] = keyf;
        }


        //fazer ordenacao de coordenadas aqui
        struct Coord coordenadas[100];
        struct Coord auxiliarponto;

        for (int i = 0; i < ponto_count; i++){
            sscanf(aux[i].ponto, "(%f, %f)", &auxiliarponto.x, &auxiliarponto.y);
            coordenadas[i] = auxiliarponto;
        }

        for(int i = 0; i < ponto_count; i++)
            coordenadas[i].distance = distanciazero(coordenadas[i].x, coordenadas[i].y);
        
        for(int i = 1; i < ponto_count; i++){
            float key = coordenadas[i].distance;
            float keyX = coordenadas[i].x;
            float keyY = coordenadas[i].y;
            int j = i - 1;
            while (j >= 0 && coordenadas[j].distance > key){
                coordenadas[j+1].distance = coordenadas[j].distance;
                coordenadas[j+1].x = coordenadas[j].x;
                coordenadas[j+1].y = coordenadas[j].y;
                j = j - 1;
            }
            coordenadas[j+1].distance = key;
            coordenadas[j+1].x = keyX;
            coordenadas[j+1].y = keyY;
            }


        fprintf(file_out, "str:");
        for (int i = 0; i < texto_count; i++){
            fprintf(file_out, "%s ", aux[i].texto);
        }

        fprintf(file_out, "int:");
        for (int i = 0; i < inteiro_count; i++){
            fprintf(file_out, "%d ", inteiro[i]);
        }

        fprintf(file_out, "float:");
        for (int i = 0; i < flutuante_count; i++){
            fprintf(file_out, "%.1f ", flutuante[i]);
        }

        fprintf(file_out, "p:");
        for (int i = 0; i < ponto_count; i++){
            fprintf(file_out, "(%.1f, %.1f) ", coordenadas[i].x, coordenadas[i].y);
        }

        if (!feof(file_in))
            fprintf(file_out, "\n");
    }
//fechar while do arquivo aqui

    fclose(file_in);
    fclose(file_out);

    printf("Arquivos fechados com sucesso!");

}