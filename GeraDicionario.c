#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50

int busca_dicionario() {

}   

int main(){
    FILE *livro;
    char temp[MAX_LEN];
    int count = 0;

    livro = fopen("texto.txt", "r");
    if (livro == NULL){
        printf("Erro");
        exit(1);
    }

    char **palavras = malloc(100 * sizeof(char*));
    while(fscanf(livro, "%s", temp) != EOF && count < 100){
        if (strcmp(temp, ".") != 0) {
            for(int i = 0; i < strlen(temp); i++){
                temp[i] = tolower(temp[i]);
            }
            if(busca_dicionario(palavras, temp, 0, count - 1)){
                palavras[count] = malloc((strlen(temp)+1) * sizeof(char));
                strcpy(palavras[count], temp);
                count++;
            }else{
                continue;
            }
        }
    }

    for(int i = 0; i < count; i++){
        printf("%s\n", palavras[i]);
    }

    for(int i = 0; i < count; i++){
        free(palavras[i]);
    }
    fclose(livro);
    free(palavras);
    return 0;
}
