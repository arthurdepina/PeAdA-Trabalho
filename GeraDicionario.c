#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50

int busca_dicionario(char **vetor_palavras, char *palavra, int i){
    if(vetor_palavras[i] == NULL){
        return 1;
    }
    if(strcmp(vetor_palavras[i], palavra) == 0){
        return 0;
    }
    return busca_dicionario(vetor_palavras, palavra, i+1);
}

void insere_palavra(char **lista_palavras, char *palavra, int tamanho_lista){
    if(strcmp(lista_palavras[0], palavra) >= 0){
        for(int i = tamanho_lista; i > 0; i--){
            lista_palavras[i] = lista_palavras[i - 1];
        }
    }
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
            if(busca_dicionario(palavras, temp, 0)){
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
