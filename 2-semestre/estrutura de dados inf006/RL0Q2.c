int main(){
  //Ler o arquivo
  FILE* file_in = fopen("L0Q2.in","r");
  FILE* file_out = fopen("L0Q2.out","w");

  if(file_in == NULL || file_out == NULL){
    printf("Falha na criacao dos arquivos\n");
    return EXIT_FAILURE;
  }
  else{
    printf("Arquivos criados e abertos com sucesso\n");
  }

