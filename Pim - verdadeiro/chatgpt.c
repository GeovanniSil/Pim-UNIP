#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int ehNumero(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0; // se tiver algo que não seja dígito
    }
    return 1;
}

int main() {
    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Algoritmos_e_Estruturas_de_Dados_em_Python.csv", "r");
    FILE *pim02 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Analise_e_Projeto_de_Sistemas.csv", "r");
    FILE *pim03 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Engenharia_de_Software_Agil.csv", "r");

    if (!pim01 || !pim02 || !pim03) {
        printf("Erro ao abrir um dos arquivos.\n");
        return 1;
    }

    char linha[200], escolhaStr[10];
    int continuar = 1;

    while (continuar) {
        printf("=====================================\n");
        printf("        RELATORIO DE NOTAS - UNIP      \n");
        printf("=====================================\n");
        printf("[1] Buscar por aluno\n[2] Relatorio por materia\n[0] Sair\n");

        int escolhaMenu = -1;
        while (1) {
            printf("Digite sua escolha: ");
            fgets(escolhaStr, sizeof(escolhaStr), stdin);
            escolhaStr[strcspn(escolhaStr, "\n")] = 0;

            if (ehNumero(escolhaStr)) {
                escolhaMenu = atoi(escolhaStr);
                if (escolhaMenu == 0 || escolhaMenu == 1 || escolhaMenu == 2) break;
            }
            printf("Entrada invalida! Digite apenas 0, 1 ou 2.\n");
        }

        switch (escolhaMenu) {
            case 1: { // Busca por aluno
                int buscarNovamente = 1;
                while (buscarNovamente) {
                    char nomeAluno[50];
                    int tipoBusca = 0;

                    // Escolha tipo de busca
                    while (1) {
                        printf("Deseja buscar por todas as materias ou somente uma?\n[1] Materia especifica\n[2] Geral\n");
                        fgets(escolhaStr, sizeof(escolhaStr), stdin);
                        escolhaStr[strcspn(escolhaStr, "\n")] = 0;
                        if (ehNumero(escolhaStr)) {
                            tipoBusca = atoi(escolhaStr);
                            if (tipoBusca == 1 || tipoBusca == 2) break;
                        }
                        printf("Entrada invalida! Digite apenas 1 ou 2.\n");
                    }

                    if (tipoBusca == 1) {
                        int materiaEscolhida = 0;
                        while (1) {
                            printf("Escolha a materia:\n[1] Algoritmos_e_Estruturas_de_Dados_em_Python\n[2] Analise_e_Projeto_de_Sistemas\n[3] Engenharia_de_Software_Agil\n");
                            fgets(escolhaStr, sizeof(escolhaStr), stdin);
                            escolhaStr[strcspn(escolhaStr, "\n")] = 0;
                            if (ehNumero(escolhaStr)) {
                                materiaEscolhida = atoi(escolhaStr);
                                if (materiaEscolhida >= 1 && materiaEscolhida <= 3) break;
                            }
                            printf("Materia invalida! Digite 1, 2 ou 3.\n");
                        }

                        FILE *arquivo = (materiaEscolhida == 1) ? pim01 :
                                        (materiaEscolhida == 2) ? pim02 : pim03;
                        char nomeMateria[50];
                        strcpy(nomeMateria, (materiaEscolhida == 1) ? "Algoritmos_e_Estruturas_de_Dados_em_Python" :
                                         (materiaEscolhida == 2) ? "Analise_e_Projeto_de_Sistemas" :
                                                                    "Engenharia_de_Software_Agil");

                        // Nome do aluno
                        printf("Digite o nome do aluno: ");
                        fgets(nomeAluno, sizeof(nomeAluno), stdin);
                        nomeAluno[strcspn(nomeAluno, "\n")] = 0;

                        rewind(arquivo);
                        fgets(linha, sizeof(linha), arquivo); // pular cabeçalho
                        int encontrou = 0;
                        char nome[50], turma[20], ra[20], materia[50];
                        float n1, n2, n3, media;

                        while (fgets(linha, sizeof(linha), arquivo)) {
                            sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &media);
                            if (strcmp(nomeAluno, nome) == 0) {
                                printf("\n------------------\nNome: %s\nMateria: %s\nNotas: %.1f %.1f %.1f\nMedia: %.1f\n------------------\n",
                                       nome, materia, n1, n2, n3, (n1+n2+n3)/3);
                                encontrou = 1;
                                break;
                            }
                        }

                        if (!encontrou) printf("Aluno nao encontrado para a materia %s.\n", nomeMateria);
                    } else {
                        printf("Busca geral nao implementada ainda.\n");
                    }

                    // Pergunta se deseja buscar outro aluno
                    while (1) {
                        printf("Deseja buscar outro aluno? [1] Sim [0] Nao: ");
                        fgets(escolhaStr, sizeof(escolhaStr), stdin);
                        escolhaStr[strcspn(escolhaStr, "\n")] = 0;
                        if (ehNumero(escolhaStr)) {
                            buscarNovamente = atoi(escolhaStr);
                            if (buscarNovamente == 0 || buscarNovamente == 1) break;
                        }
                        printf("Entrada invalida! Digite apenas 0 ou 1.\n");
                    }
                }
                break;
            }

            case 2: { // Relatorio por materia
                int materiaEscolhida = 0;
                while (1) {
                    printf("Escolha a materia para relatorio:\n[1] Algoritmos_e_Estruturas_de_Dados_em_Python\n[2] Analise_e_Projeto_de_Sistemas\n[3] Engenharia_de_Software_Agil\n");
                    fgets(escolhaStr, sizeof(escolhaStr), stdin);
                    escolhaStr[strcspn(escolhaStr, "\n")] = 0;
                    if (ehNumero(escolhaStr)) {
                        materiaEscolhida = atoi(escolhaStr);
                        if (materiaEscolhida >= 1 && materiaEscolhida <= 3) break;
                    }
                    printf("Materia invalida! Digite 1, 2 ou 3.\n");
                }

                FILE *arquivo = (materiaEscolhida == 1) ? pim01 :
                                (materiaEscolhida == 2) ? pim02 : pim03;
                char nomeMateria[50];
                strcpy(nomeMateria, (materiaEscolhida == 1) ? "Algoritmos_e_Estruturas_de_Dados_em_Python" :
                                 (materiaEscolhida == 2) ? "Analise_e_Projeto_de_Sistemas" :
                                                            "Engenharia_de_Software_Agil");

                rewind(arquivo);
                fgets(linha, sizeof(linha), arquivo); // pular cabeçalho
                int contadorAlunos = 0;
                char nome[50], turma[20], ra[20], materia[50];
                float n1, n2, n3, media;

                printf("\nRelatorio de %s:\n", nomeMateria);
                while (fgets(linha, sizeof(linha), arquivo)) {
                    sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &media);
                    printf("\n------------------\nNome: %s\nMateria: %s\nNotas: %.1f %.1f %.1f\nMedia: %.1f\n------------------\n", nome, materia, n1, n2, n3, (n1+n2+n3)/3);
                    contadorAlunos++;
                }
                printf("\nTotal de alunos na materia %s: %d\n", nomeMateria, contadorAlunos);
                break;
            }

            case 0:
                printf("Saindo do sistema...\n");
                continuar = 0;
                break;

            default:
                printf("Opcao invalida.\n");
        }
    }

    fclose(pim01);
    fclose(pim02);
    fclose(pim03);
    return 0;
}



