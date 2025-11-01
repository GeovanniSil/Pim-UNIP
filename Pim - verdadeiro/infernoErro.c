#include <stdio.h>

int main(){
    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Analise_e_Projeto_de_Sistemas.csv", "r");

    char linha[100], nome[100], ra[100], materia[100], turma[100];
    float n1, n2, n3, media;

    fgets(linha, sizeof(linha), pim01);
    
    while (fgets(linha, sizeof(linha), pim01))
    {
       printf("\n------------------\n");
                    printf("Nome: %s\nMateria: %s\nNotas: %.1f %.1f %.1f\nMedia: %.1f\n------------------\n",
                           nome, materia, n1, n2, n3, (n1 + n2 + n3) / 3);
    }
    
}