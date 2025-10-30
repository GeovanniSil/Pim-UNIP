#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> // precisa pra usar atoi()
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");
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

    int dnv = 1; // dps anotar sobre essa variavel e sua funcionalidade
    do
    {
        int opcao;
        char entrada[10];
        printf("=====================================\n");
        printf("        RELATORIO DE NOTAS - UNIP      \n");
        printf("=====================================\n");
        printf("Selecione uma opcao:\n");
        printf("  [1] Buscar por aluno\n");
        printf("  [2] Buscar por materia\n");
        printf("  [0] Sair\n");
        do
        {
            printf("Digite sua escolha: ");
            fgets(entrada, sizeof(entrada), stdin);

            // sscanf retorna 1 se conseguiu ler um número inteiro corretamente
            if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 2)
            {
                printf("Entrada inválida! Digite apenas 0, 1 ou 2.\n");
                continue; // volta para o início do loop
            }

            break; // entrada válida, sai do loop
        } while (1);

        char linha[100];   // variavel onde esta sendo salvo os dados do arquivo "pim01"
        char linha02[100]; // variavel onde esta sendo salvo os dados do arquivo "pim02"
        char linha03[100]; // variavel onde esta sendo salvo os dados do arquivo "pim03"
        char nome[40], escolhaStr[10];
        char materia[40];
        float n1 = 0, n2 = 0, n3;
        int encontrou = 0;
        int novamente;
        char turma[20];
        char nomeAluno[20];
        float nota;
        char escolhaMateria[20]; //
        // int escolhaMateria; //
        /// int escolhaMateriaAluno; //
        char entradaMateria[10];
        char raAluno[10];
        int escolhaModuloCase1; // variavel que será a escolha do usuario no case 1
        switch (opcao)
        {
        case 1:
        { // Busca por aluno
            int buscarNovamente = 1;
            while (buscarNovamente)
            {
                char nomeAluno[50];
                int tipoBusca = 0;

                // Escolha do tipo de busca
                do
                {
                    printf("Deseja buscar por todas as materias ou somente uma?\n");
                    printf("[1] Materia especifica\n");
                    printf("[2] Geral\n");
                    fgets(escolhaStr, sizeof(escolhaStr), stdin);

                    // sscanf retorna 1 se conseguiu ler um número inteiro corretamente
                    if (sscanf(escolhaStr, "%d", &tipoBusca) != 1 || tipoBusca < 1 || tipoBusca > 2)
                    {
                        printf("Entrada inválida! Digite apenas 1 ou 2.\n");
                        continue; // volta para o início do loop
                    }

                    break; // entrada válida
                } while (1);

                if (tipoBusca == 1)
                {
                    int materiaEscolhida = 0;

                    // Escolha da matéria
                    do
                    {
                        printf("\nEscolha a materia:\n");
                        printf("[1] Algoritmos_e_Estruturas_de_Dados_em_Python\n");
                        printf("[2] Analise_e_Projeto_de_Sistemas\n");
                        printf("[3] Engenharia_de_Software_Agil\n");
                        fgets(escolhaStr, sizeof(escolhaStr), stdin);

                        if (sscanf(escolhaStr, "%d", &materiaEscolhida) != 1 || materiaEscolhida < 1 || materiaEscolhida > 3)
                        {
                            printf("Entrada inválida! Digite apenas 1, 2 ou 3.\n");
                            continue;
                        }

                        break;
                    } while (1);

                    /* FILE *arquivo = (materiaEscolhida == 1) ? pim01 : // operador ternário, mesma coisa que if e else abaixo, porem, menor
                                        (materiaEscolhida == 2) ? pim02 vou deixar ele aq para eu estudar mais no futuro
                                                                : pim03; */

                    FILE *arquivo;

                    if (materiaEscolhida == 1)
                        arquivo = pim01;
                    else if (materiaEscolhida == 2)
                        arquivo = pim02;
                    else
                        arquivo = pim03;

                    char nomeMateria[60];//variavel onde será atribuido os nomes das materias
                    if (materiaEscolhida == 1)
                        strcpy(nomeMateria, "Algoritmos_e_Estruturas_de_Dados_em_Python");
                    else if (materiaEscolhida == 2)
                        strcpy(nomeMateria, "Analise_e_Projeto_de_Sistemas");
                    else
                        strcpy(nomeMateria, "Engenharia_de_Software_Agil");

                    // Nome do aluno
                    printf("\nDigite o nome do aluno: ");
                    fgets(nomeAluno, sizeof(nomeAluno), stdin);
                    nomeAluno[strcspn(nomeAluno, "\n")] = 0;

                    rewind(arquivo);
                    fgets(linha, sizeof(linha), arquivo); // pula o cabeçalho

                    int encontrou = 0;
                    char nome[50], turma[20], ra[20], materia[50];
                    float n1, n2, n3, media;

                    while (fgets(linha, sizeof(linha), arquivo))
                    {
                        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f",
                               nome, turma, ra, materia, &n1, &n2, &n3, &media);

                        if (strcmp(nomeAluno, nome) == 0)
                        {
                            printf("\n------------------------------\n");
                            printf("Nome:    %s\n", nome);
                            printf("Matéria: %s\n", materia);
                            printf("Notas:   %.1f | %.1f | %.1f\n", n1, n2, n3);
                            printf("Média:   %.1f\n", (n1 + n2 + n3) / 3);
                            printf("------------------------------\n");
                            encontrou = 1;
                            break;
                        }
                    }

                    if (!encontrou)
                        printf("\nAluno nao encontrado para a materia %s.\n", nomeMateria);
                }
                else
                {
                    printf("Busca geral ainda não implementada.\n");
                }

                // Pergunta se deseja buscar outro aluno
                do
                {
                    printf("\nDeseja buscar outro aluno? [1] Sim [0] Nao: ");
                    fgets(escolhaStr, sizeof(escolhaStr), stdin);

                    if (sscanf(escolhaStr, "%d", &buscarNovamente) != 1 || (buscarNovamente != 0 && buscarNovamente != 1))
                    {
                        printf("Entrada inválida! Digite apenas 0 ou 1.\n");
                        continue;
                    }

                    break;
                } while (1);
            }
            break;
        }

        break;
        case 2:
            do
            {
                fseek(pim01, 0, SEEK_SET); // reinicia o arquivo toda vez que a gente querer olhar o relatorio
                fseek(pim02, 0, SEEK_SET); // reinicia o arquivo toda vez que a gente querer olhar o relatorio
                fseek(pim03, 0, SEEK_SET); // reinicia o arquivo toda vez que a gente querer olhar o relatorio
                encontrou = 0;
                int contadorAlunos = 0; // variavel para contar os alunos dos arquivos, ela será incremetanda a cada vez que o while repetir na hora de mostrar o relatorio

                printf("\nEscolha uma materia:\n");
                printf("  [1] Algoritmos_e_Estruturas_de_Dados_em_Python\n");
                printf("  [2] Analise_e_Projeto_de_Sistemas\n");
                printf("  [3] Engenharia_de_Software_Agil\n");

                int escolhaInt;
                char entrada[10];
                do
                { // função para fazer a validação da entrada do usuario
                    printf("Digite a materia da sua escolha: ");
                    fgets(entrada, sizeof(entrada), stdin);
                    escolhaInt = atoi(entrada);

                    if (escolhaInt < 1 || escolhaInt > 3)
                    {
                        printf("Materia nao encontrada. Tente novamente.\n");
                    }
                } while (escolhaInt < 1 || escolhaInt > 3);

                // Determina qual arquivo e nome da materia
                FILE *arquivoEscolhido; // esse ponteiro aponta para os primeiros arquivos que abrimos no inicio do codigo
                char nomeMateria[50];

                if (escolhaInt == 1)
                {
                    arquivoEscolhido = pim01;                                          // Determina qual arquivo será aberto
                    strcpy(nomeMateria, "Algoritmos_e_Estruturas_de_Dados_em_Python"); // função "strcopy" Copia a string do nome da matéria para a variável nomeMateria.ai podemos usar ela para exibir o nome do relatorio qnd ele for aberto
                }
                else if (escolhaInt == 2)
                {
                    arquivoEscolhido = pim02;                             // Determina qual arquivo será aberto
                    strcpy(nomeMateria, "Analise_e_Projeto_de_Sistemas"); // função "strcopy" Copia a string do nome da matéria para a variável nomeMateria. ai podemos usar ela para exibir o nome do relatorio qnd ele for aberto
                }
                else
                {
                    arquivoEscolhido = pim03;                           // Determina qual arquivo será aberto
                    strcpy(nomeMateria, "Engenharia_de_Software_Agil"); // função "strcopy" Copia a string do nome da matéria para a variável nomeMateria. ai podemos usar ela para exibir o nome do relatorio qnd ele for aberto
                }

                printf("\n==============================================\n");
                printf("           RELATORIO DE %s\n", nomeMateria);
                printf("==============================================\n");
                char linha[200], nome[50], turma[20], ra[20], materia[50];
                float n1, n2, n3, nota;

                fgets(linha, sizeof(linha), arquivoEscolhido);                // pula o cabeçalho
                while (fgets(linha, sizeof(linha), arquivoEscolhido) != NULL) // como a gente usou o ponteiro "arquivoEscolhido" nao foi preciso usar um while e fgets para abrir cada aquivo. Ele vai salvar na variavel "linha" o relatorio condizente a nossa escolha
                {
                    linha[strcspn(linha, "\n")] = '\0';
                    sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &nota); // salva cada parte do arquivo em uma variavel, a cada ";" do csv, essa função guarda nas variaveis

                    printf("-------------------------------------------------------------\n");
                    printf("   Nome:         %-40s\n", nome);
                    printf("   Turma:        %-40s\n", turma);
                    printf("   RA:           %-40s\n", ra);
                    printf("   Matéria:      %-40s\n", materia);
                    printf("   Notas:        %.1f | %.1f | %.1f\n", n1, n2, n3);
                    printf("   Média Final:  %.1f\n", nota);
                    printf("-------------------------------------------------------------\n");
                    contadorAlunos++; // faz o incremento da variavel para saber o total de alunos exibidos por arquivo
                    encontrou = 1;
                    // A variável "encontrou" funciona como uma flag, assim que eu encontro oq eu quero, ela muda para 1 e nao vai para a condição ali de baixo fora do while que esta lendoo arquivo.
                    // Ela começa com valor 0 e muda para 1 quando o aluno é encontrado, isso significa que deu certo na nossa procura. Caso nao achar nada, a variavel vai continuar 0 (pq eu a iniciei como zero no começo do codigo) e vai entrar na condição ali de baixo
                }

                if (encontrou == 0) // caso eu nao encontrar nenhum aluno no arquivo, a variavel nao vai mudar (pq ela esta iniciada com 0) e vai entrar nessa condição, que será verdadeira
                    printf("Nenhum aluno encontrado para esta materia.\n");
                printf("Total de alunos encontrados: %i\n", contadorAlunos);

                // Perguntar se deseja buscar outra matéria
                do
                {
                    printf("Deseja buscar outra materia? [1] Sim [0] Nao: ");
                    fgets(entrada, sizeof(entrada), stdin);
                    novamente = atoi(entrada);
                    if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 2)
                    {
                        printf("Entrada inválida! Digite apenas 0, 1 ou 2.\n");
                        continue;
                    }
                    break;
                } while (1);

            } while (novamente == 1);
            break;

        case 0:
            dnv = 0; // se no menu eu escolher 0, a sistema sair do programa pq a variavel "dnv" estara com o valor de 0, logo ela na cai na condição do primeiro do while, como visto ali em baixo
            // caso queira testar, mude essa variavel "dnv = 0" para "dnv = 1" o loop vai continuar pq a condição ali de baixo retornou true, logo, o loop se repete
            printf("Saindo do sistema...\n");
            break;

            // default:
            // printf("Opcao invalida. Tente novamente.\n");
        }

    } while (dnv == 1); // caso a gente escolher olhar novamente os relatorio, a variavel pássara a ser 1 e vai satisfazer a condição, fazendo com que o loop se repita e mostre novamente o menu de relatorio

    fclose(pim01);
    fclose(pim02);
    fclose(pim03);
    return 0;
    system("pause");
}
