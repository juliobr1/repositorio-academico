#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_LINE 100

//funcao de calculo de distancia um ponto e a origem
float distanciazero(float pX, float pY){
    float distance;
    float y0 = 0.0;
    float x0 = 0.0;
    
    distance = sqrt(pow((x0 - pX), 2) + pow((y0 - pY), 2));
    
    return distance;
}

//funcao de calculo de distancia entre dois pontos
float distanciapontos(float pX, float pY, float pX1, float pY1){
    float distance;
    
    distance = sqrt(pow((pX - pX1), 2) + pow((pY - pY1), 2));
    
    return distance;
}

struct Coord {
    int x;
    int y;
    float distance;
};

int main(){
  //Ler o arquivo
  FILE* file_in = fopen("../L0Q1.in","r");
  FILE* file_out = fopen("L0Q1.out","w");

  if(file_in == NULL || file_out == NULL){
    printf("Falha na criacao dos arquivos\n");
    return EXIT_FAILURE;
  }
  else{
    printf("Arquivos criados e abertos com sucesso\n");
  }

  char * line = malloc(MAX_LINE * sizeof(char));
  while (fgets(line, MAX_LINE, file_in)){
      
      float x0, y0 = 0.0;
      struct Coord coordenadas[100];
      float distancepoint[100];
      float totaldistance = 0;
    
      //-- declaracoes
      int coordenadas_count = 0;
      char *coord_inicio = line;
      char *coord_fim = NULL;
      
      // inicio do encontro das coordenadas
      while ((coord_inicio = strchr(coord_inicio, '(')) != NULL){
          coord_fim = strchr(coord_inicio, ')');
          if(coord_fim == NULL){
              printf("Erro: parêntese de fechamento não encontrado.\n");
          }
          
          char temp[50];
          strncpy(temp, coord_inicio, coord_fim - coord_inicio + 1);
          temp[coord_fim - coord_inicio + 1] = '\0';
          
          struct Coord auxiliar;
          if(sscanf(temp, "(%d, %d)", &auxiliar.x, &auxiliar.y) == 2){
              coordenadas[coordenadas_count] = auxiliar;
              coordenadas_count++;
              fflush(stdin);
          } else{
              printf("Erro ao extrair coordenadas: %s \n", temp);
          }
          
          coord_inicio = coord_fim + 1;
      }
     
      //calculando distância entre o valor e 0;
        
        for(int i = 0; i < coordenadas_count; i++)
            coordenadas[i].distance = distanciazero(coordenadas[i].x, coordenadas[i].y);
      
      //calculando distância entre o ponto atual e o próximo;
    
        for(int i = 0; i < coordenadas_count-1; i++){
            distancepoint[i] = distanciapontos(coordenadas[i].x, coordenadas[i].y, coordenadas[i+1].x, coordenadas[i+1].y);
            totaldistance += distancepoint[i];
            fflush(stdin);
        }
      
      //calculo da distancia mais curta
        distancepoint[coordenadas_count-1] = distanciapontos(coordenadas[0].x, coordenadas[0].y,coordenadas[coordenadas_count-1].x, coordenadas[coordenadas_count-1].y);
      
      //ordenacao com base na distancia
        for(int i = 1; i < coordenadas_count; i++){
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
      
      // saída
        fprintf(file_out, "%s", "points ");
      
        for(int i = 0; i < coordenadas_count; i++)
          fprintf(file_out, "(%d,%d) ", coordenadas[i].x, coordenadas[i].y);
    
        fprintf(file_out, "distance %.2f shortcut %.2f", totaldistance, distancepoint[coordenadas_count-1]);
        
        if (!feof(file_in))
            fprintf(file_out, "\n");
  }
  
  //fechar arquivos
    
    
    fclose(file_in);
    fclose(file_out);
    
    printf("Arquivos fechados com sucesso!");
}