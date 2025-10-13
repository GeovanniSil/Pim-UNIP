#include <stdio.h>
#include <string.h>

int main() {
    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\pim01.txt", "r");

    if (pim01 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char escolha;
    printf("Escolher um aluno [1], escolher uma matéria [2]: ");
    scanf(" %c", &escolha);  // espaço ignora Enter

    char linha[100];
    char nome[40];
    char materia[40];
    float n1, n2, n3;
    int encontrou = 0;

    switch (escolha) {
        case '1':
            printf("Buscar por aluno ainda não implementado.\n");
            break;

        case '2': {
            char escolhaMateria[20];
            printf("Escolha a matéria (matematica, portugues, quimica): ");
            scanf("%s", escolhaMateria);

            // Validação
            while (strcmp(escolhaMateria, "1") != 0
                && strcmp(escolhaMateria, "matematica") != 0
                && strcmp(escolhaMateria, "2") != 0
                && strcmp(escolhaMateria, "portugues") != 0
                && strcmp(escolhaMateria, "3") != 0
                && strcmp(escolhaMateria, "quimica") != 0) {
                printf("Matéria não encontrada. Tente novamente: ");
                scanf("%s", escolhaMateria);
            }

            while (fgets(linha, sizeof(linha), pim01) != NULL) {
                linha[strcspn(linha, "\n")] = '\0';

                sscanf(linha, "%[^;];%f;%f;%f;%[^;\n]", nome, &n1, &n2, &n3, materia);

                if ((strcmp(escolhaMateria, materia) == 0) 
                || 
                ((strcmp(escolhaMateria, "1") == 0) && (strcmp(materia, "matematica") == 0))
                ||
                ((strcmp(escolhaMateria, "2") == 0) && (strcmp(materia, "portugues") == 0))
                ||
                ((strcmp(escolhaMateria, "3") == 0) && (strcmp(materia, "quimica") == 0))
                    )
                
                {
                    printf("\n------------------\n");
                    printf("Nome: %s\n", nome);
                    printf("Matéria: %s\n", materia);
                    printf("Notas: %.1f, %.1f, %.1f\n", n1, n2, n3);
                    printf("Média: %.1f\n", (n1 + n2 + n3) / 3);
                    printf("------------------\n");
                    encontrou = 1;
                }
            }

            if (!encontrou) {
                printf("Nenhum aluno encontrado para a matéria '%s'.\n", escolhaMateria);
            }

            break;
        }

        default:
            printf("Opção inválida.\n");
            break;
    }

    fclose(pim01);
    return 0;
}
