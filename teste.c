#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50

int busca_dicionario(char **vetor_palavras, char *palavra, int inicio, int fim){
    if (inicio > fim) {
        return 1;
    }
    int meio = (inicio + fim) / 2;
    if (strcmp(vetor_palavras[meio], palavra) == 0) {
        return 0;
    } else if (strcmp(vetor_palavras[meio], palavra) > 0) {
        return busca_dicionario(vetor_palavras, palavra, inicio, meio - 1);
    } else {
        return busca_dicionario(vetor_palavras, palavra, meio + 1, fim);
    }
}

void insere_palavra(char **vetor_palavras, char *palavra){
    
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
            if(busca_dicionario(palavras, temp, 0, count-1)){
                // desloca as palavras maiores para o final do vetor
                int j = count - 1;
                while (j >= 0 && strcmp(palavras[j], temp) > 0) {
                    palavras[j+1] = palavras[j];
                    j--;
                }
                palavras[j+1] = malloc((strlen(temp)+1) * sizeof(char));
                strcpy(palavras[j+1], temp);
                count++;
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
