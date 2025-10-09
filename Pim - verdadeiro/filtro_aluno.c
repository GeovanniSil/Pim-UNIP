#include <stdio.h>
#include <string.h>

int main(){
    FILE * pim01;
    pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\filtroAluno.txt", "r");//colocar o caminho que esta salvo o seu txt

    if (pim01 == NULL)
    {
        printf("erro");
    }
    
    char frase[15];
    char aluno[15];
    printf("digite o aluno: ");
    scanf("%s", aluno);

    //char alunotxt1[15];
    //char alunotxt2[15];
    //char alunotxt3[15];
    //char alunotxt4[15];
    //int encontrou = 0;
    //char alunotxt2[15];
    while (fgets(frase, sizeof(frase), pim01) != NULL)
    {

        if (strcmp(frase, aluno) == 0)
        {
            printf("ta");
            break;
        }else 
            printf("nao ta");
            break;
        
        /* sscanf(frase, "%[^;];%[^;];%[^;];%[^;\n]", alunotxt1 ,alunotxt2, alunotxt3, alunotxt4);
        if (strcmp(frase, alunotxt1) == 0)
        {
            printf("%s", frase);
            break;
        }else if (strcmp(frase, alunotxt2) == 0)
        {
            printf("%s", alunotxt2);
            break;
        }else if (strcmp(frase, alunotxt3) == 0)
        {
            printf("%s", alunotxt3);
            break;
        }else if (strcmp(frase, alunotxt4) == 0)
        {
            printf("%s", alunotxt4);
            break;
        }else 
            printf("pq nao deu certo?");
            break; */
        
        
        

    }
    
    

}