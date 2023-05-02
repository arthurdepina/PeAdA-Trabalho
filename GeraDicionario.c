// Arthur de Pina Balduino Leitão - 32207840
// Cesar Hideki Imai - 32255659

/*                        
                           Explicação Geral:

    O programa começa abrindo o arquivo, que recebe o nome "livro".
    Se livro retornar NULL, uma mensagem de erro é impressa e o
    programa é finalizado. 
    
    Em seguida é alocado uma lista para armazenar as palavras do livro,
    a lista "palavras". O tamanho é 100, pois o enunciado especifica
    que não haverão mais de 100 palavras na lista.
    
    O loop while coloca as palavras do texto na lista "palavras". Para
    isso, itera-se sobre as palavras do arquivo e a palavra atual é
    chamada de "temp". "temp" é comparada com ".", para saber se o
    arquivo chegou ao fim. Em seguida, todas as letras da palavra são
    transformadas em minúsculas na função "para_minusculas". Então, é
    utilizada a função "busca_dicionario" para verificar se a palavra
    já consta na lista "palavras". Se a palavra ainda não consta em
    "palavras", é chamada a função "insere_palavra", que insere a palavra
    na lista em ordem alfabética decrescente. Se a palavra já está na
    lista, ela não é adicionada e o programa passa para a próxima palavra
    (se houver).
    
    Terminado o loop, temos uma lista com todas as palavras do texto
    em ordem alfabética decrescente. Então criamos (ou abrimos) o arquivo
    "dicionario.txt" na variável "dicionario" e escrevemos cada palavra
    da lista "palavra" em cada linha de "dicionario.txt". Escrevemos também
    uma última linha com o número de palavras do dicionario.
    
    Feito isso, libera-se o espaço utilizado por "palavras", e fechamos
    os arquivos "livro" e "palavra".


                        Explicação das Funções:

    para_minusculas --> A função recebe uma string e faz um loop pelos
    caracteres, usando o tolower() do ctype.h para transformar cada um
    em letra minúscula.

    busca_dicionario --> A função recebe uma lista de palavra, uma
    palavra, a posição do início da lista e posição do final da lista
    e realiza busca binária de forma recursiva para verificar se uma
    palavra já consta na lista, retornando 0 se a palavra já consta e 1
    se a palavra não consta. Inicialmente, a função verifica se inicio
    é maior que fim, e se for, a palavra não foi encontrada e retorna-se 1.
    Caso contrário, a função calcula o índice do elemento do meio e
    compara a palavra passada com o elemento do meio. Se a palavra for
    encontrada, a função retorna 0. Se a palavra for menor que o elemento
    central, a função chama a si mesma com os parâmetros: vetor de palavras,
    palavra buscada, índice inicial e índice anterior ao do elemento do
    meio. Se a palavra for maior que o elemento central, a função chama a
    si mesma com parâmetros: vetor de palavras, palavra buscada, índice do
    elemento seguinte ao elemento do meio e índice final. 

    insere_palavra --> A função é recursiva e recebe uma lista de palavras,
    uma palavra, uma posição e o número de palavras na lista. A função
    primeiro verifica se a palavra pode ser inserida na primeira posição
    da lista e, se for possível, insere. Se não for possível a função
    compara a palavra a ser inserida, com a palavra que já consta na posição
    passada como parâmetro. Se a palavra a ser inserida for maior
    lexicograficamente que a palavra que já consta, todas as palavras a
    partir da posição passada são deslocadas para direita a fim de inserir
    a palavra desejada de modo que função fique em ordem alfabética
    descrescente. Se a palavra a ser inserida não for maior lexicograficamente,
    a função se chama recursivamente com a posição incrementada em um. Assim,
    a função avança no vetor até encontrar a posição adequada para inserir
    a palavra. A função utiliza strdup() da string.h que aloca memória para
    string e copia a string para o espaço de memória alocado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50

void para_minusculas(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

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

void insere_palavra(char **palavras, char *palavra, int pos, int count) {
    if (pos == count) {
        palavras[count] = strdup(palavra);
        return;
    }
    if (strcmp(palavra, palavras[pos]) > 0) {
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
            para_minusculas(temp);
            if(busca_dicionario(palavras, temp, 0, count-1)){ // Se a palavra não foi encontrada
                insere_palavra(palavras, temp, 0, count);
                count++;
            }
        }
    }

    char ultima_linha[] = "total de palavras diferentes no dicionario: ";

    FILE *dicionario;
    dicionario = fopen("dicionario.txt", "w");
    for(int i = 0; i < count; i++){
        fprintf(dicionario, "%s\n", palavras[i]);
    }
    fprintf(dicionario, "%s%d\n", ultima_linha, count);

    for(int i = 0; i < count; i++){
        free(palavras[i]);
    }
    fclose(livro);
    fclose(dicionario);
    free(palavras);
    return 0;
}
