#include <stdio.h>

int main()
{

    FILE *pim04 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Programacao_Estruturada_em_C.csv", "r");

    if (!pim04)
    {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    char linha[200];
    char nome[40], ra[40], turma[40], materia[40];
    float n1, n2, n3, nota;

    int temAlunos = 0; // <--- MARCADOR DE SE TEM ALUNOS OU NÃO

    // Ignorar cabeçalho
    fgets(linha, sizeof(linha), pim04);

    while (fgets(linha, sizeof(linha), pim04) != NULL)
    {

        if (sscanf(linha, "%39[^;];%39[^;];%39[^;];%39[^;];%f;%f;%f;%f",
               nome, ra, turma, materia, &n1, &n2, &n3, &nota) == 8) {
        temAlunos = 1;
        printf("deu");
    }
    }

    // Se NÃO encontrou nenhum aluno válido no arquivo:
    if (temAlunos == 0)
    {
        printf("nao deu\n"); // <--- ESTA É A LINHA QUE FALTAVA
    }

    fclose(pim04);
    return 0;
}
