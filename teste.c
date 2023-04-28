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
    } else if (strcmp(vetor_palavras[meio], palavra) < 0) {
        return busca_dicionario(vetor_palavras, palavra, inicio, meio - 1);
    } else {
        return busca_dicionario(vetor_palavras, palavra, meio + 1, fim);
    }
}

void paraMinusculas(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void insere_palavra(char **palavras, char *palavra, int pos, int count) {
    if (pos == count) {
        palavras[count] = strdup(palavra);
        return;
    }
    if (strcmp(palavra, palavras[pos]) > 0) { // Alterada a condição aqui
        for (int i = count; i > pos; i--) {
            palavras[i] = palavras[i - 1];
        }
        palavras[pos] = strdup(palavra);
        return;
    }
    insere_palavra(palavras, palavra, pos + 1, count);
}

int main(){
    FILE *livro;
    char temp[MAX_LEN];
    int count = 0;

    livro = fopen("texto.txt", "r");
    if (livro == NULL){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    char **palavras = malloc(100 * sizeof(char*));
    while(fscanf(livro, "%s", temp) != EOF && count < 100){
        if (strcmp(temp, ".") != 0) {
            paraMinusculas(temp);
            if(busca_dicionario(palavras, temp, 0, count-1)){ // Se a palavra não foi encontrada
                insere_palavra(palavras, temp, 0, count);
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
