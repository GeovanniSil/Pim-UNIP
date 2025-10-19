#include <stdio.h>
#include <string.h>

int main(){
    FILE * pim01;
    pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\filtroAluno.txt", "r");//coloque o caminho onde esta salvo o seu arquivo txt e salve nele dados parecidos com esse abaixo
    /* theo;4.4;geovanni;mae;carlos;
    tatu;4.0;5.0;7.0;matematica */
    //ainda vou comentar esse codigo

    if (pim01 == NULL)
    {
        printf("erro");
    }
    char frase[70];
    while (fgets(frase, sizeof(frase), pim01) != NULL)
    {
        printf("%s", frase);
    }
    
    char aluno[15];
    printf("digite o aluno: ");
    scanf("%s", aluno); 
    
    
    char * ponteiro;
    int encontrou = 0;

    //função strtok, strtok serve para separar uma string em partes menores usando um caractere delimitador. No seu código, ele está separando cada campo da linha do arquivo para comparar o nome do aluno
    fseek(pim01, 0, SEEK_SET);
    while (fgets(frase, sizeof(frase), pim01) != NULL)
    {
        frase[strcspn(frase, "\n")] = '\0';
        ponteiro = strtok(frase, ";\n");
        //printf("%s", frase);
        while (ponteiro != NULL)
        {           
            if (strcmp(aluno, ponteiro) == 0)
            {
                printf("encontrado %s\n", aluno);
                encontrou = 1;
                break;
            }
            ponteiro = strtok(NULL, ";\n"); 
            
        }
        if (encontrou)
        break;
    }
    if (!encontrou)
    {
        printf("nao encontrado");
       
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