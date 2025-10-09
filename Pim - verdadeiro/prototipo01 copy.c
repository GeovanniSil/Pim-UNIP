#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    FILE * pim; //estamsos apenas indicando que temos um arquivo para ser aberto e tbm indicando para a maquina onde esta o arquivo para ser lido ou escrito
    pim = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\prototipo.txt", "r"); // "r" ler informações do arquivo // numeros01 //prototipo2

    //int a, b, c;
    //fscanf(pim, "%i %i %i", &a, &b, &c); // usando o fscanf a gente pega as informações do nosso arquivo e guardando em uma variavel correspondente ao tipo de dado que estou lendo

    //printf("%i %i %i", a, b, c);//aq eu printo os dados que eu peguei do fscanf ali de cima

    
    if (pim == NULL)
    {
        printf("erro");
        return 0; //caso o arquivo nao exista, ou melhor, o arquivo nao pode ser aberto por algum motivo, o programa encerra aq e nao executa as coisas de baixo
    }
    int escolha;
    scanf(" %d\n", &escolha);
    char frase[100];

    while (fgets(frase, 100, pim) != NULL){
    char nome[50], id[50], turma[50], materia[50];
    float nota;

    sscanf(frase, "%[^;];%[^;];%[^;];%[^;];%f", nome, id, turma, materia, &nota);
    
    if ((escolha == 1 && strcmp(materia, "portugue") == 0) ||
    (escolha == 2 && strcmp(materia, "matematic") ==0 ))
    {
        printf("%s", nome);
        printf("%s", id);
        printf("%s", turma);
        printf("%s", materia);
        printf("%2f", nota);
    }
    }//essa função le todo texto do meu arquivo, ja o fgets, lia ate encontrar a primeira quebra de linha, ent quando o texto do arquivo quebrava uma linha, ele nao lia o resto, apenas a primeira linha antes da quebra
    // o fscanf le apenas a primeira palavra antes de econtrar um espaço, ex, Geoavanni Andrade, só printará o Geovanni
    //fscanf é otimo quando sabemos exatamente oq virá do arquivo

    //fgets sempre converterá os dados pegos do arquivo em string, ent se no meu arquivo tiver numero, esses numeros vao virar strings. Se eu quiser usar os numeros no codigo, terei que converter essas string (numeros) em int
    {
        //printf("%s", frase);
    }
    
   

    // 1 = matematica 2 = portugues

    while(escolha != 1 && escolha != 2)
    {
        printf("invalido");
        scanf(" %d", &escolha);
    }
    

   
    


    pim = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\prototipo2.txt", "a");//usando o "a = append", nos adicionamos algo no final da linha no texto 

    fprintf(pim, "\nOi Geovanni Andrade");//eu coloco o arquivo que esta sendo apontado (pim) todas as vezes que eu querer manipular o meu arquivo

    char fraser[] = "segunda linha";

    fputs(fraser, pim);

    char caractere = '3';

    fputc(caractere, pim);//fputc adiciona um unico caractere

    fclose(pim);
    return 0;
}
