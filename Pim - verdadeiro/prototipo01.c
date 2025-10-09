#include <stdio.h>
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
