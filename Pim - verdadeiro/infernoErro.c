#include <stdio.h>

void exibirMenuPrincipal();
void exibaAluno(char *nome, char *turma, char *ra, char *materia, float n1, float n2, float n3, float nota);
int nomeValido(char *nome);
int buscarNosArquivos(FILE *pim01, FILE *pim02, FILE *pim03, FILE *pim04, char *nomeAluno);
void cores(int nota1);


int main()

    int main()
{

    FILE *pim04 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Progamacao_Estruturada_em_C.csv", "r");
    //("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Engenharia_de_Software_Agil.csv", "r");

    char nada[40];

    fgets(nada, sizeof(nada), pim04);

    while (fgets(nada, sizeof(nada), pim04) != NULL)
    {
        printf("%s\n", nada);
    }
}