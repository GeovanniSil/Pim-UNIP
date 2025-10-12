#include <stdio.h>
#include <string.h>

int main(){
    FILE * pim01;
    pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\filtroAluno.txt", "r");//colocar o caminho que esta salvo o seu txt

    if (pim01 == NULL)
    {
        printf("erro");
    }
    
    //char aluno[15];
    //printf("digite o aluno:\n");
    //scanf("%s", aluno);
    
    char frase[70];
    char * ponteiro;
    //int encontrou = 0;

    //função strtok, strtok serve para separar uma string em partes menores usando um caractere delimitador. No seu código, ele está separando cada campo da linha do arquivo para comparar o nome do aluno
    while (fgets(frase, sizeof(frase), pim01) != NULL)
    {
        ponteiro = strtok(frase, ";\n");
        frase[strcspn(frase, "\n")] = '\0';
        while (ponteiro)
        {
            printf("%s\n", ponteiro);
            ponteiro = strtok(NULL, ";\n");
            
        }
}
fclose(pim01);
} 

/* #include <stdio.h>
#include <string.h>

int main(){
//aprendendo sobre a função strtok

    char palavra[50] = "Bom dia cinderela!";
    char *ponteiro;

    ponteiro = strtok(palavra, " "); //recebe 2 parametro, primeiro parametro é qual é a string que eu quero dividir e o segundo é de que forma queremos dividir essa string 

    while (ponteiro)//usamos o loop para fazer com que ele divida a string toda e nao somente a primeira palavra, sem usar o loop, ela vai dividr apenas a primeira palavra
    {
        printf("token %s\n", ponteiro);
        ponteiro = strtok(NULL, " ");
    }
    

    return 0;
}
 */