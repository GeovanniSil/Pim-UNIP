/* #include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_NOME 30
#define N 10 //numero de alunos
#define TRUE 1
#define FALSE 0


struct cadastroAluno
{
    int ativo;
    char nome[TAM_NOME];
    int matricula;
    float media;
};

typedef struct cadastroAluno aluno;


int main() {
    FILE*pim = pim = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\prototipo.txt", "r");

    int id_nome, i;
    float id_nota, nota1, nota2, nota3;
    char nome[TAM_NOME];
    int contador = 0;
    aluno a[N];

    for ( i = 0; i < N; i++)
    {
        a[i].ativo=0;
    }


    if (pim != NULL)
    {
        while (fscanf(pim, "%d %[^\n]s", &id_nome, nome) != EOF)
        {
            strcpy(a[contador].nome, nome);

            FILE* pimNota = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\string.txt", "r");

            if (pimNota != NULL)
            {
                while (fscanf(pimNota, "%d %f %f %f", &id_nota, &nota1, &nota2, &nota3) != EOF)
                {
                    printf(pimNota);
                }

            }

            contador ++;
        }

    }


    fclose(pim);
    return 0;
}
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Algoritmos_e_Estruturas_de_Dados_em_Python.csv", "r");
    FILE *pim02 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Analise_e_Projeto_de_Sistemas.csv", "r");
    FILE *pim03 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Engenharia_de_Software_Agil.csv", "r");
    if (pim01 == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    if (pim02 == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    if (pim03 == NULL)
    {
        printf("Erro ao abrir o arquivo Engenharia_de_Software_Agil.csv\n");
        return 1;
    }

    int qntAlunoRelatorio = 0;
    printf("quantos alunos quer saber do relatorio? ");
    scanf("%d", &qntAlunoRelatorio);
    while (getchar() != '\n')
        ;

    char dadosMateriaBusca2[40], dadosMateriaBusca3[40];
    char nomeAlunoCase1[40];
    char nome[40], turma[40], raAluno[40], materia[40];
    float n1, n2, n3, nota;
    char nomeAluno[10];
    for (int i = 0; i < qntAlunoRelatorio; i++)
    {
        fseek(pim01, 0, SEEK_SET);
        fseek(pim02, 0, SEEK_SET);
        printf("digite nome do aluno: \n");
        scanf("%s", nomeAluno);
        // printf("%s\n", nomeAluno);
        int flag = 0;
        fgets(dadosMateriaBusca2, sizeof(dadosMateriaBusca2), pim01); // pula cabeçalho
        while (fgets(dadosMateriaBusca2, sizeof(dadosMateriaBusca2), pim01) != NULL)
        {
            sscanf(dadosMateriaBusca2, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, raAluno, materia, &n1, &n2, &n3, &nota);
            nomeAlunoCase1[strcspn(nomeAlunoCase1, "\n")] = '\0';
            if (strcmp(nomeAluno, nome) == 0)
            {
                printf("\n------------------\n");
                printf("Nome: %s\nMateria: %s\nNotas: %.1f %.1f %.1f\nMedia: %.1f\n------------------\n",
                       nome, materia, n1, n2, n3, nota);
                flag = 1;
            }
        }
        char nomeAlunoCase1[40];

        while (fgets(dadosMateriaBusca3, sizeof(dadosMateriaBusca3), pim02) != NULL)
        {
            sscanf(dadosMateriaBusca3, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, raAluno, materia, &n1, &n2, &n3, &nota);
            nomeAlunoCase1[strcspn(nomeAlunoCase1, "\n")] = '\0';
            if (strcmp(nomeAluno, nome) == 0)
            {
                printf("\n------------------\n");
                printf("Nome: %s\nMateria: %s\nNotas: %.1f %.1f %.1f\nMedia: %.1f\n------------------\n",
                       nome, materia, n1, n2, n3, nota);
                flag = 1;
            }
        }

        // char nomeAlunoCase1[40];

        /*     while (fgets(dadosMateriaBusca3, sizeof(dadosMateriaBusca3), pim02) != NULL)
            {
                sscanf(dadosMateriaBusca2, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, raAluno, materia, &n1, &n2, &n3, &nota);
                nomeAlunoCase1[strcspn(nomeAlunoCase1, "\n")] = '\0';
                if (strcmp(nomeAluno, nome) == 0)
                {
                    printf("\n------------------\n");
                    printf("Nome: %s\nMateria: %s\nNotas: %.1f %.1f %.1f\nMedia: %.1f\n------------------\n",
                           nome, materia, n1, n2, n3, nota);
                    flag = 1;
                }
            } */
    }}