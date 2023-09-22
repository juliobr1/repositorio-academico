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

void ordenarstring(const void *a, const void *b){
    chat aux[100];
    int r = strcmp(a, b);

    if(r > 0){
        strcpy(aux, a);
        strcpy(a, b);
        strcpy(b, aux);
    }
}

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
    fgets(line, MAX_LINE, file_in);

    struct auxiliar aux[100];
    int texto_count = 0;
    int inteiro_count = 0;
    int flutuante_count = 0;
    int ponto_count = 0;

    char * token = strtok(line, " ");
        while (token != NULL) {
            if (isCoordinate(token)) {
                strncpy(aux[ponto_count].ponto, token, sizeof(aux[ponto_count].ponto));
                ponto_count++;
            } else if (isInt(token)) {
                strncpy(aux[inteiro_count].inteiro, token, sizeof(aux[inteiro_count].inteiro));
                inteiro_count++;
            } else if (isFloat(token)) {
                strncpy(aux[flutuante_count].flutuante, token, sizeof(aux[flutuante_count].flutuante));
                flutuante_count++;
            } else {
                strncpy(aux[texto_count].texto, token, sizeof(aux[texto_count].texto));
                texto_count++;
            }
            token = strtok(NULL, " ");
        }
    
    //fazer ordenacao de strings aqui



    //fazer ordenacao de coordenadas aqui




    printf("str: ");
    for (int i = 0; i < texto_count; i++){
        printf("%s ", aux[i].texto);
    }

    printf("int: ");
    for (int i = 0; i < inteiro_count; i++){
        printf("%s ", aux[i].inteiro);
    }

    printf("float: ");
    for (int i = 0; i < flutuante_count; i++){
        printf("%s ", aux[i].flutuante);
    }

    printf("p: ");
    for (int i = 0; i < ponto_count; i++){
        printf("%s ", aux[i].ponto);
    }

    fclose(file_in);
    fclose(file_out);

}