#include <stdio.h>
#include <string.h>

int main(){
    FILE * pim01;
    pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\filtroAluno.txt", "r");//colocar o caminho que esta salvo o seu txt

    if (pim01 == NULL)
    {
        printf("erro");
    }
    
    char frase[70];
    char aluno[15];
    printf("digite o aluno:\n");
    scanf("%s", aluno);

    //char alunotxt1[15];
    //char alunotxt2[15];
    //char alunotxt3[15];
    //char alunotxt4[15];
    int encontrou = 0;
    //char alunotxt2[15];
    while (fgets(frase, sizeof(frase), pim01) != NULL)
    {
        frase[strcspn(frase, "\n")] = '\0';
        char *nome = strtok(frase, ";");
        //função strtok, strtok serve para separar uma string em partes menores usando um caractere delimitador. No seu código, ele está separando cada campo da linha do arquivo para comparar o nome do aluno
        while (nome != NULL) {
            if (strcmp(nome, aluno) == 0) {
                printf("Aluno encontrado: %s\n", nome);
                encontrou = 1;
                break;
            }/* else
                printf("nao encontrado");    
                encontrou = 1;
                break; */
            nome = strtok(NULL, ";");
            if(!encontrou);
                printf("nao");
                break;
    }
    if (encontrou) break; // sai do loop principal
}
fclose(pim01);
}