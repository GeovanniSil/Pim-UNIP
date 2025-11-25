#include <stdio.h>  //funções de entrada e saída
#include <string.h> //manipulação de strings (strcmp, strcpy, etc.);
#include <ctype.h>  //funções de caracteres (como toupper, tolower).
#include <stdlib.h> // precisa pra usar atoi()
#include <locale.h> //permite usar acentuação em português (setlocale);

void exibaAluno(char *nome, char *turma, char *ra, char *materia, float n1, float n2, float n3, float nota);

int main()
{
    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Algoritmos_e_Estruturas_de_Dados_em_Python.csv", "r"); // caminho onde vc salvou o seu arquivo txt
    FILE *pim02 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Analise_e_Projeto_de_Sistemas.csv", "r");
    FILE *pim03 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Engenharia_de_Software_Agil.csv", "r");
    FILE *pim04 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Programacao_Estruturada_em_C.csv", "r");
    char nome[250], turma[200], ra[200], materia[200],nomeAluno[200];
    float n1, n2, n3, media;
    char linhaArqPim[700];
    fgets(linhaArqPim, sizeof(linhaArqPim), pim01); 
    char raTeclado[700];
    printf("digite o ra do aluno: ");
    fgets(raTeclado, sizeof(raTeclado), stdin);
    raTeclado[strcspn(raTeclado, "\n")] = '\0'; 
    /*fgets(nomeAluno, sizeof(nomeAluno), stdin);
                         nomeAluno[strcspn(nomeAluno, "\n")] = 0; */

    for (int i = 0; raTeclado[i] != '\0'; i++)
    {
        raTeclado[i] = tolower(raTeclado[i]);
    }
    printf("RA digitado em minusculo: %s\n", raTeclado);

    while (fgets(linhaArqPim, sizeof(linhaArqPim), pim01))
    {
        sscanf(linhaArqPim, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, ra, turma, materia, &n1, &n2, &n3, &media); // essa parte guarda cada parte do csv separado por ";" e guarda dentro dessas var
        char baixo[700];
        printf("ra do aluno: %s\n", ra);
        for (int i = 0; ra[i] != '\0'; i++)
        {
            baixo[i] = tolower(ra[i]);
        }
        baixo[strlen(ra)] = '\0';
        printf("ra do aluno minusculo: %s\n", baixo);

        /*if (strcmp(raTeclado, baixo) == 0)
        {
            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
        }*/
       printf("%s\n", linhaArqPim);

        // exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);

        /*if (strcmp(raTeclado, baixo) == 0)
        {
            printf("Aluno encontrado: %s\n", nome);
        }*/
    }
}

void exibaAluno(char *nome, char *turma, char *ra, char *materia, float n1, float n2, float n3, float nota)
{
    // cores(nota);
    printf("--------------------------------------\n");
    printf("Nome: %s\n", nome);
    printf("Turma: %s\n", turma);
    printf("RA: %s\n", ra);
    printf("Matéria: %s\n", materia);
    printf("Notas: %.2f | %.2f | %.2f\n", n1, n2, n3);
    printf("Média Final: %.2f\n", nota);
    printf("--------------------------------------\x1b[0m\n");
}
