#include <stdio.h>
#include <string.h>

int main(){
    FILE * pim01;
    pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\pim01.txt", "r");

    FILE * pim02;
    pim02 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\filtroAluno.txt", "r");

    char escolha;
    //char frase[70];

    printf("escolher um aluno [1], escolher uma materia[2]\n");
    scanf("%c", &escolha);

    char linha[100];//variavel para guardar o texto do arquivo "pim01"
    char linha02[100];//variavel para guardar o texto do arquivo "filtroAluno"
    float t;//variavel teste
    char g[10];//variavel teste
    float f;//variavel teste
    char materia[100];
    int encontrou = 0;
    char nome[40];    

    char escolhaMateria[15];//materia escolhida
    switch (escolha)
    {
    case '1': //escolher qual aluno quer olhar

        break;
    case '2'://escolher ver as notas por materias
        printf("escolha a materia que deseja: ");
        scanf("%s", escolhaMateria);
        while (strcmp(escolhaMateria, "1") != 0
        && strcmp(escolhaMateria, "mate") != 0
        && strcmp(escolhaMateria, "2") != 0
        && strcmp(escolhaMateria, "portugues") != 0
        && strcmp(escolhaMateria, "3") != 0
        && strcmp(escolhaMateria, "quimica") != 0        
    )
    {
    while (getchar() != '\n');
    printf("Materia nao encontrada, tente novamente: ");
    scanf("%s", escolhaMateria);
    }

    while (fgets(linha, sizeof(linha), pim01) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';

        sscanf(linha, "%[^;];%f;%[^;]%f;%[^;]",nome, &t, g, &f, materia);

        if (((strcmp(escolha, "1") == 0) && (strcmp(materia, "portugues") == 0))
        ||
        ((strcmp(escolha, "2") == 0) && (strcmp(materia, "portugues") == 0)))
        {
            printf("------------------\n");
            printf("Nome: %s\n", nome);
            printf("Materia: %s\n", materia);
            printf("Nota: %.1f\n", f);
            printf("------------------\n");
            //printf("sua media é %f", media);
            encontrou = 1;

        }
        
    }
        break;
    default:
        break;
    }
}