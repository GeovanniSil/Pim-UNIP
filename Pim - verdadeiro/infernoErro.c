#include <stdio.h>

void exibirMenuPrincipal();
void exibaAluno(char *nome, char *turma, char *ra, char *materia, float n1, float n2, float n3, float nota);
int nomeValido(char *nome);
int buscarNosArquivos(FILE *pim01, FILE *pim02, FILE *pim03, FILE *pim04, char *nomeAluno);
void cores(int nota1);

FILE *pim01 = fope("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Algoritmos_e_Estruturas_de_Dados_em_Pythocsv""r");
FILE *pim02 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Analise_e_Projeto_de_Sistemas.csv", "r");
FILE *pim03 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Engenharia_de_Software_Agil.csv", "r");
FILE *pim04 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Programacao_Estruturada_em_C.csv", "r");

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