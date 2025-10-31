#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

#define RESET "\x1b[0m"
#define NEGRITO "\x1b[1m"
#define AZUL "\x1b[34m"
#define CIANO "\x1b[36m"
#define VERDE "\x1b[32m"
#define VERMELHO "\x1b[31m"
#define AMARELO "\x1b[33m"
#define FUNDO_PRETO "\x1b[40m"
#define FUNDO_AZUL "\x1b[44m"
#define FUNDO_CINZA "\x1b[47m"

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Algoritmos_e_Estruturas_de_Dados_em_Python.csv", "r");
    FILE *pim02 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Analise_e_Projeto_de_Sistemas.csv", "r");
    FILE *pim03 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Engenharia_de_Software_Agil.csv", "r");

    if (!pim01 || !pim02 || !pim03)
    {
        printf(VERMELHO NEGRITO "\n[ERRO] " RESET "Falha ao abrir um ou mais arquivos CSV!\n");
        return 1;
    }

    int dnv = 1;
    do
    {
        int opcao;
        char entrada[10];

        printf(FUNDO_AZUL NEGRITO "\n===========================================\n");
        printf("          RELATÓRIO DE NOTAS - UNIP\n");
        printf("===========================================\n" RESET);
        printf(CIANO NEGRITO "\nSelecione uma opção:\n" RESET);
        printf("  " AMARELO "[1]" RESET " Buscar por aluno\n");
        printf("  " AMARELO "[2]" RESET " Buscar por matéria\n");
        printf("  " AMARELO "[0]" RESET " Sair\n");

        do
        {
            printf(AZUL NEGRITO "\nDigite sua escolha: " RESET);
            fgets(entrada, sizeof(entrada), stdin);

            if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 2)
            {
                printf(VERMELHO "Entrada inválida! Digite apenas 0, 1 ou 2.\n" RESET);
                continue;
            }
            break;
        } while (1);

        char linha[200];
        char escolhaStr[10];
        int encontrou = 0;
        int novamente;

        switch (opcao)
        {
        case 1:
        {
            int buscarNovamente = 1;
            while (buscarNovamente)
            {
                char nomeAluno[50];
                int tipoBusca = 0;

                do
                {
                    printf(CIANO NEGRITO "\nDeseja buscar por todas as matérias ou somente uma?\n" RESET);
                    printf("  [1] Matéria específica\n");
                    printf("  [2] Geral\n");
                    printf(AZUL "Escolha: " RESET);
                    fgets(escolhaStr, sizeof(escolhaStr), stdin);

                    if (sscanf(escolhaStr, "%d", &tipoBusca) != 1 || tipoBusca < 1 || tipoBusca > 2)
                    {
                        printf(VERMELHO "Entrada inválida! Digite apenas 1 ou 2.\n" RESET);
                        continue;
                    }
                    break;
                } while (1);

                if (tipoBusca == 1)
                {
                    int materiaEscolhida = 0;
                    FILE *arquivo;
                    char nomeMateria[60];

                    do
                    {
                        printf("\nEscolha a matéria:\n");
                        printf("  [1] Algoritmos e Estruturas de Dados em Python\n");
                        printf("  [2] Análise e Projeto de Sistemas\n");
                        printf("  [3] Engenharia de Software Ágil\n");
                        printf(AZUL "Escolha: " RESET);
                        fgets(escolhaStr, sizeof(escolhaStr), stdin);

                        if (sscanf(escolhaStr, "%d", &materiaEscolhida) != 1 || materiaEscolhida < 1 || materiaEscolhida > 3)
                        {
                            printf(VERMELHO "Entrada inválida! Digite apenas 1, 2 ou 3.\n" RESET);
                            continue;
                        }
                        break;
                    } while (1);

                    if (materiaEscolhida == 1)
                    {
                        arquivo = pim01;
                        strcpy(nomeMateria, "Algoritmos e Estruturas de Dados em Python");
                    }
                    else if (materiaEscolhida == 2)
                    {
                        arquivo = pim02;
                        strcpy(nomeMateria, "Análise e Projeto de Sistemas");
                    }
                    else
                    {
                        arquivo = pim03;
                        strcpy(nomeMateria, "Engenharia de Software Ágil");
                    }

                    printf(CIANO "\nDigite o nome do aluno: " RESET);
                    fgets(nomeAluno, sizeof(nomeAluno), stdin);
                    nomeAluno[strcspn(nomeAluno, "\n")] = 0;

                    rewind(arquivo);

                    char nome[50], turma[20], ra[20], materia[50];
                    float n1, n2, n3, media;

                    fgets(linha, sizeof(linha), arquivo);
                    while (fgets(linha, sizeof(linha), arquivo))
                    {
                        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f",
                               nome, turma, ra, materia, &n1, &n2, &n3, &media);

                        if (strcmp(nomeAluno, nome) == 0)
                        {
                            printf(VERDE "\n--------------------------------------\n" RESET);
                            printf(NEGRITO "Nome:    " RESET "%s\n", nome);
                            printf(NEGRITO "Matéria: " RESET "%s\n", materia);
                            printf(NEGRITO "Notas:   " RESET "%.1f | %.1f | %.1f\n", n1, n2, n3);
                            printf(NEGRITO "Média:   " RESET "%.1f\n", (n1 + n2 + n3) / 3);
                            printf(VERDE "--------------------------------------\n" RESET);
                            encontrou = 1;
                        }
                    }

                    if (!encontrou)
                        printf(VERMELHO "\nAluno não encontrado para a matéria %s.\n" RESET, nomeMateria);
                }

                if (tipoBusca == 2)
                {
                    printf(CIANO "\nDigite o nome do aluno: " RESET);
                    fgets(nomeAluno, sizeof(nomeAluno), stdin);
                    nomeAluno[strcspn(nomeAluno, "\n")] = 0;

                    FILE *arquivos[] = {pim01, pim02, pim03};
                    char *nomesMaterias[] = {"Algoritmos e Estruturas de Dados em Python",
                                             "Análise e Projeto de Sistemas",
                                             "Engenharia de Software Ágil"};

                    for (int i = 0; i < 3; i++)
                    {
                        rewind(arquivos[i]);
                        fgets(linha, sizeof(linha), arquivos[i]);

                        char nome[50], turma[20], ra[20], materia[50];
                        float n1, n2, n3, media;

                        while (fgets(linha, sizeof(linha), arquivos[i]))
                        {
                            sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f",
                                   nome, turma, ra, materia, &n1, &n2, &n3, &media);

                            if (strcmp(nomeAluno, nome) == 0)
                            {
                                printf(VERDE "\n--------------------------------------\n" RESET);
                                printf(NEGRITO "Nome:    " RESET "%s\n", nome);
                                printf(NEGRITO "Matéria: " RESET "%s\n", materia);
                                printf(NEGRITO "Notas:   " RESET "%.1f | %.1f | %.1f\n", n1, n2, n3);
                                printf(NEGRITO "Média:   " RESET "%.1f\n", (n1 + n2 + n3) / 3);
                                printf(VERDE "--------------------------------------\n" RESET);
                                encontrou = 1;
                            }
                        }
                    }

                    if (!encontrou)
                        printf(VERMELHO "\nAluno não encontrado em nenhuma matéria.\n" RESET);
                }

                do
                {
                    printf(AMARELO "\nDeseja buscar outro aluno? [1] Sim [0] Não: " RESET);
                    fgets(escolhaStr, sizeof(escolhaStr), stdin);

                    if (sscanf(escolhaStr, "%d", &buscarNovamente) != 1 || (buscarNovamente != 0 && buscarNovamente != 1))
                    {
                        printf(VERMELHO "Entrada inválida! Digite apenas 0 ou 1.\n" RESET);
                        continue;
                    }

                    break;
                } while (1);
            }
            break;
        }

        case 2:
        {
            do
            {
                fseek(pim01, 0, SEEK_SET);
                fseek(pim02, 0, SEEK_SET);
                fseek(pim03, 0, SEEK_SET);
                encontrou = 0;
                int contadorAlunos = 0;

                printf(CIANO "\nEscolha uma matéria:\n" RESET);
                printf("  [1] Algoritmos e Estruturas de Dados em Python\n");
                printf("  [2] Análise e Projeto de Sistemas\n");
                printf("  [3] Engenharia de Software Ágil\n");

                int escolhaInt;
                do
                {
                    printf(AZUL "Digite sua escolha: " RESET);
                    fgets(entrada, sizeof(entrada), stdin);
                    escolhaInt = atoi(entrada);
                    if (escolhaInt < 1 || escolhaInt > 3)
                        printf(VERMELHO "Matéria inválida. Tente novamente.\n" RESET);
                } while (escolhaInt < 1 || escolhaInt > 3);

                FILE *arquivoEscolhido;
                char nomeMateria[60];

                if (escolhaInt == 1)
                {
                    arquivoEscolhido = pim01;
                    strcpy(nomeMateria, "Algoritmos e Estruturas de Dados em Python");
                }
                else if (escolhaInt == 2)
                {
                    arquivoEscolhido = pim02;
                    strcpy(nomeMateria, "Análise e Projeto de Sistemas");
                }
                else
                {
                    arquivoEscolhido = pim03;
                    strcpy(nomeMateria, "Engenharia de Software Ágil");
                }

                printf(NEGRITO "\n==============================================\n" RESET);
                printf(AZUL NEGRITO "         RELATÓRIO DE %s\n" RESET, nomeMateria);
                printf(NEGRITO "==============================================\n" RESET);

                char nome[50], turma[20], ra[20], materia[50];
                float n1, n2, n3, nota;

                fgets(linha, sizeof(linha), arquivoEscolhido);
                while (fgets(linha, sizeof(linha), arquivoEscolhido))
                {
                    sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f",
                           nome, turma, ra, materia, &n1, &n2, &n3, &nota);

                    printf(VERDE "-------------------------------------------------------------\n" RESET);
                    printf("   " NEGRITO "Nome:        " RESET "%-40s\n", nome);
                    printf("   " NEGRITO "Turma:       " RESET "%-40s\n", turma);
                    printf("   " NEGRITO "RA:          " RESET "%-40s\n", ra);
                    printf("   " NEGRITO "Matéria:     " RESET "%-40s\n", materia);
                    printf("   " NEGRITO "Notas:       " RESET "%.1f | %.1f | %.1f\n", n1, n2, n3);
                    printf("   " NEGRITO "Média Final: " RESET "%.1f\n", nota);
                    contadorAlunos++;
                    encontrou = 1;
                }

                if (!encontrou)
                    printf(VERMELHO "Nenhum aluno encontrado para esta matéria.\n" RESET);

                printf(AMARELO "\nTotal de alunos: %d\n" RESET, contadorAlunos);

                printf(AMARELO "\nDeseja buscar outra matéria? [1] Sim [0] Não: " RESET);
                fgets(entrada, sizeof(entrada), stdin);
                novamente = atoi(entrada);

            } while (novamente == 1);
            break;
        }

        case 0:
            printf(VERMELHO NEGRITO "\nSaindo do sistema...\n" RESET);
            dnv = 0;
            break;
        }

    } while (dnv == 1);

    fclose(pim01);
    fclose(pim02);
    fclose(pim03);
    return 0;
}
