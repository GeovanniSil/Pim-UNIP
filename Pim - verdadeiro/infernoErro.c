#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exibaAluno(char *nome, char *turma, char *ra, char *materia, float n1, float n2, float n3, float nota)
{
    //cores(nota);
    printf("--------------------------------------\n");
    printf("Nome: %s\n", nome);
    printf("Turma: %s\n", turma);
    printf("RA: %s\n", ra);
    printf("Matéria: %s\n", materia);
    printf("Notas: %.2f | %.2f | %.2f\n", n1, n2, n3);
    printf("Média Final: %.2f\n", nota);
    printf("--------------------------------------\x1b[0m\n");
}

int main(){
    char str[40];

    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Algoritmos_e_Estruturas_de_Dados_em_Python.csv", "r");
    char teste[70];
    char nome[50], turma[20], ra[20], materia[50];
                    float n1, n2, n3, media;
char minusculo[40];

                    printf("nome: ");
                    scanf("%s", str);
                
                            int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    for (int i = 0; i <  strlen(str); i++)
                    {
                       minusculo = tolower(str);
                        //tolower(str[i]);
                        printf("nome %s para %s", str, minusculo);
                    }

    fgets(teste, sizeof(teste), pim01);
    while (fgets(teste, sizeof(teste), pim01))
                    {
                        sscanf(teste, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &media);

                        if (strcmp(str, nome) == 0)
                        {
                            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
                            //encontrou = 1;
                        }
                    }
    
}
