#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 300

int isFloat(char *str) {
    char *endptr;
    strtod(str, &endptr);
    if (*endptr == '\0' || (*endptr == '.' && *(endptr + 1) != '\0')) {
        return 1;
    }
    return 0;
}

int isInt(char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    if (*endptr == '\0') {
        return 1;
    }
    return 0;
}

int isCoordinate(char *str) {
    int len = strlen(str);
    if (len >= 3 && str[0] == '(' && str[len - 1] == ')' && strchr(str, ',') != NULL) {
        return 1;
    }
    return 0;
}

int main(){
  //Ler o arquivo
  FILE* file_in = fopen("../L0Q2.in","r");
  FILE* file_out = fopen("L0Q2.out","w");

  if(file_in == NULL || file_out == NULL){
    printf("Falha na criacao dos arquivos\n");
    return EXIT_FAILURE;
  }
  else{
    printf("Arquivos criados e abertos com sucesso\n");
  }

char * line = malloc(MAX_LINE * sizeof(char));

fgets(line, MAX_LINE, file_in);

char * token = strtok(line, " ");
    while (token != NULL) {
        if (isCoordinate(token)) {
            printf("Coordenadas: %s\n", token);
        } else if (isFloat(token)) {
            printf("Float: %s\n", token);
        } else if (isInt(token)) {
            printf("Inteiro: %s\n", token);
        } else {
            printf("String: %s\n", token);
        }
        token = strtok(NULL, " ");
    }
}