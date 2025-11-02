#include <stdio.h>  //funções de entrada e saída
#include <string.h> //manipulação de strings (strcmp, strcpy, etc.);
#include <ctype.h>  //funções de caracteres (como toupper, tolower).
#include <stdlib.h> // precisa pra usar atoi()
#include <locale.h> //permite usar acentuação em português (setlocale);

void exibirMenuPrincipal();// menu inicial
void exibaAluno(char *nome, char *turma, char *ra, char *materia, float n1, float n2, float n3, float nota); // função para printar o relatorio dos alunos
int nomeValido(char *nome);// função para validar a entrada do nome do aluno e que nao deixar passar numeros
int buscarNosArquivos(FILE *pim01, FILE *pim02, FILE *pim03, FILE *pim04, char *nomeAluno); // função que percorre os 3 arquivos para usar no busca por alunos geral
// Chame a função buscarNosArquivos(), e guarde o valor que ela devolve dentro da variável encontrouIf2.”Chame a função buscarNosArquivos(), e guarde o valor que ela devolve dentro da variável encontrouTipoBusca. O retorno que a função "buscarNosArquivos" será guardada dentro dessa variavel "encontrouTipoBusca" e a gente vai usar ela no busca geral de aluno, para saber se foi encontrado aluno ou nao, se nao foi, essa variavel será usada para mostrar que noa tem o aluno que o usuario digitou nos relatorios
void cores(int nota1);
int main()
{ // abertura dos arquivos

    system("chcp 65001 > nul");
    setlocale(LC_ALL, "pt_BR.UTF-8");
    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Algoritmos_e_Estruturas_de_Dados_em_Python.csv", "r"); // caminho onde vc salvou o seu arquivo txt
    FILE *pim02 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Analise_e_Projeto_de_Sistemas.csv", "r");
    FILE *pim03 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Engenharia_de_Software_Agil.csv", "r");
    FILE *pim04 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Programacao_Estruturada_em_C.csv", "r");

    if (pim01 == NULL)
    {
        printf("\x1b[31mErro ao abrir o arquivo Algoritmos_e_Estruturas_de_Dados_em_Python\x1b[0m\n");
        return 1;
    }

    if (pim02 == NULL)
    {
        printf("\x1b[31mErro ao abrir o arquivo Analise_e_Projeto_de_Sistemas\x1b[0m\n");
        return 1;
    }

    if (pim03 == NULL)
    {
        printf("\x1b[31mErro ao abrir o arquivo Engenharia_de_Software_Agil.csv\x1b[0m\n");
        return 1;
    }

    if (pim04 == NULL)
    {
        printf("\x1b[31mErro ao abrir o arquivo Programação_Estruturada_em_C\x1b[0m\n");
        return 1;
    }

    int dnv = 1; // dps anotar sobre essa variavel e sua funcionalidade
    do
    {
        system("cls"); // limpa o terminal a cada vez que voltar para o menu novamente
        int opcao;
        char entrada[10];
        exibirMenuPrincipal(); // função para mostrar o menu principal
        do
        {
            printf("\x1b[1;33mDigite sua escolha: \x1b[0m");
            fgets(entrada, sizeof(entrada), stdin);

            // sscanf retorna 1 se conseguiu ler um número inteiro corretamente
            if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 2)
            {
                printf("\x1b[31mEntrada inválida! Digite novamente.\x1b[0m\n");
                continue; // volta para o início do loop
            }

            break; // entrada válida, sai do loop
        } while (1);

        char linha[100]; // variavel onde esta sendo salvo os dados do arquivo
        char escolhaStr[10];
        int encontrou = 0;
        int novamente;
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
                    printf("\x1b[1;37m\nDeseja buscar por todas as matérias ou somente uma?\x1b[0m\n");
                    printf("\x1b[36m[1] - Materia especifica\n");
                    printf("[2] - Geral\n");
                    printf("\x1b[1;90m[0] - Sair\x1b[0m\n");
                    printf("\x1b[1;33mDigite sua escolha: \x1b[0m");
                    fgets(escolhaStr, sizeof(escolhaStr), stdin);

                    // sscanf retorna 1 se conseguiu ler um número inteiro corretamente
                    if (sscanf(escolhaStr, "%d", &tipoBusca) != 1 || tipoBusca < 0 || tipoBusca > 2)
                    {
                        printf("\x1b[31mEntrada inválida! Digite novamente.\x1b[0m\n");
                        continue; // volta para o início do loop
                    }

                    break;
                } while (1);

                if (tipoBusca == 1)
                {
                    int materiaEscolhida = 0;

                    do
                    { // Escolha da matéria
                        printf("\x1b[1;37m\nEscolha a materia:\x1b[0m\n");
                        printf("\x1b[36m[1] - Algoritmo e Estrutura de Dados em Python\n");
                        printf("[2] - Analise e Projeto de sistemas\n");
                        printf("[3] - Engenharia de Software Agil\n");
                        printf("[4] - Programação Estruturada em C\x1b[0m\n");
                        printf("\x1b[1;90m[0] - Sair\x1b[0m\n");
                        printf("\x1b[1;33mDigite sua escolha: \x1b[0m");
                        fgets(escolhaStr, sizeof(escolhaStr), stdin);

                        if (sscanf(escolhaStr, "%d", &materiaEscolhida) != 1 || materiaEscolhida < 0 || materiaEscolhida > 4)
                        {
                            printf("\x1b[31mEntrada inválida! Digite novamente.\x1b[0m\n");
                            continue;
                        }

                        break;
                    } while (1);

                    FILE *arquivo;

                    if (materiaEscolhida == 1)
                        arquivo = pim01;
                    else if (materiaEscolhida == 2)
                        arquivo = pim02;
                    else if (materiaEscolhida == 3)
                        arquivo = pim03;
                    else if (materiaEscolhida == 4)
                        arquivo = pim04;

                    if (materiaEscolhida == 0)
                    {
                        printf("saindo");
                        break;
                    }

                    char nomeMateria[60]; // variavel onde será atribuido os nomes das materias
                    if (materiaEscolhida == 1)
                        strcpy(nomeMateria, "Algoritmos e Estruturas de Dados em Python");
                    else if (materiaEscolhida == 2)
                        strcpy(nomeMateria, "Analise e Projeto de Sistemas");
                    else if (materiaEscolhida == 3)
                        strcpy(nomeMateria, "Engenharia de Software Agil");
                    else
                        strcpy(nomeMateria, "Programação Estruturada em C");

                    do
                    {
                        printf("\x1b[1;37m\nDigite o nome do aluno: \x1b[0m");
                        fgets(nomeAluno, sizeof(nomeAluno), stdin);
                        nomeAluno[strcspn(nomeAluno, "\n")] = 0;
                        // converterMinusculas(nomeAluno);
                        if (!nomeValido(nomeAluno))
                        {
                            printf("\x1b[31mNome inválido! Use apenas letras .\x1b[0m\n");
                            continue; // volta para o início do loop se o nome for inválido
                        }

                        break; // sai do loop se o nome for válido
                    } while (1);

                    rewind(arquivo); // reinia o arquivo para a proxima leitura

                    int encontrou = 0; // flag para indicar que o aluno foi encontrado ou nao
                    char nome[50], turma[20], ra[20], materia[50];
                    float n1, n2, n3, media;

                    fgets(linha, sizeof(linha), arquivo); // pula o cabeçalho
                    while (fgets(linha, sizeof(linha), arquivo))
                    {
                        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &media);

                        if (_stricmp(nomeAluno, nome) == 0)

                        {
                            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
                            encontrou = 1;
                        }
                    }

                    if (!encontrou)
                        printf("\x1b[1;31maluno nao encontrado para a materia %s.\x1b[0m\n", nomeMateria);
                }

                int encontrouTipoBusca = 0;
                if (tipoBusca == 2)
                {
                    do
                    {
                        printf("\x1b[1;37m\nDigite o nome do aluno: \x1b[0m");
                        fgets(nomeAluno, sizeof(nomeAluno), stdin);
                        nomeAluno[strcspn(nomeAluno, "\n")] = 0;

                        if (!nomeValido(nomeAluno))
                        {
                            printf("\x1b[31mNome inválido! Use apenas letras e espaços.\x1b[0m\n");
                            continue; // volta para o início do loop se o nome for inválido
                        }

                        break; // sai do loop se o nome for válido
                    } while (1);

                    fgets(linha, sizeof(linha), pim01); // pula o cabeçalho
                    fgets(linha, sizeof(linha), pim02); // pula o cabeçalho
                    fgets(linha, sizeof(linha), pim03); // pula o cabeçalho
                    fgets(linha, sizeof(linha), pim04); // pula o cabeçalho

                    // buscarNosArquivos(pim01, pim02, pim03, nomeAluno); // função que abre todos os arquivos e faz a exibição do aluno que a gente quer olhar
                    encontrouTipoBusca = buscarNosArquivos(pim01, pim02, pim03, pim04, nomeAluno); // o dado de retorn na função "buscarNosArquivos" é guardado dentro da variavel "encontrouTipoBusca", ent, se encontrou um aluno ela mudará a variavel para , se nao encontrou um aluno, a variavel ficara com o valor de 0 e vai aparecer a mensagem "Aluno nao encontrado nos relatorios!!"
                }
                if (tipoBusca == 2 && !encontrouTipoBusca)
                {
                    printf("\x1b[1;33mAluno nao encontrado nos relatorios!!\x1b[0m\n");
                }

                if (tipoBusca == 0)
                {
                    // printf("\x1b[91msaindo\x1b[0m");
                    break;
                }

                do
                {
                    printf("\x1b[1;33mDeseja buscar outro aluno? [1] Sim [0] Nao: \x1b[0m");
                    fgets(escolhaStr, sizeof(escolhaStr), stdin);

                    if (sscanf(escolhaStr, "%d", &buscarNovamente) != 1 || (buscarNovamente != 0 && buscarNovamente != 1))
                    {
                        printf("\x1b[1;31mEntrada inválida! Digite novamente.\x1b[0m\n");
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
                fseek(pim04, 0, SEEK_SET); // reinicia o arquivo toda vez que a gente querer olhar o relatorio
                encontrou = 0;
                int contadorAlunos = 0; // variavel para contar os alunos dos arquivos, ela será incremetanda a cada vez que o while repetir na hora de mostrar o relatorio

                printf("\n\x1b[1;33mEscolha uma materia:\x1b[0m\n");
                printf("\x1b[36m[1] - Algoritmos e Estruturas de Dados em Python\n");
                printf("[2] - Analise e Projeto de Sistemas\n");
                printf("[3] - Engenharia de Software Agil \n");
                printf("[4] - Programação Estruturada em C \n");
                printf("\x1b[1;90m[0] - Sair \x1b[0m\n");

                int escolhaInt;
                char entrada[10];
                do
                { // função para fazer a validação da entrada do usuario
                    printf("\x1b[1;33mDigite a materia da sua escolha: \x1b[0m");
                    fgets(entrada, sizeof(entrada), stdin);
                    escolhaInt = atoi(entrada);

                    if (escolhaInt < 0 || escolhaInt > 4)
                    {
                        printf("\x1b[1;31mEntrada inválida! Tente novamente.\x1b[0m\n");
                    }
                } while (escolhaInt < 0 || escolhaInt > 4);

                // Determina qual arquivo e nome da materia
                FILE *arquivoEscolhido; // esse ponteiro aponta para os primeiros arquivos que abrimos no inicio do codigo
                char nomeMateria[50];

                if (escolhaInt == 1)
                {
                    arquivoEscolhido = pim01;                                        // Determina qual arquivo será aberto
                    strcpy(nomeMateria, "Algorit. e Estruturas de Dados em Python"); // função "strcopy" Copia a string do nome da matéria para a variável nomeMateria.ai podemos usar ela para exibir o nome do relatorio qnd ele for aberto
                }
                else if (escolhaInt == 2)
                {
                    arquivoEscolhido = pim02;                             // Determina qual arquivo será aberto
                    strcpy(nomeMateria, "Analise e Projeto de Sistemas"); // função "strcopy" Copia a string do nome da matéria para a variável nomeMateria. ai podemos usar ela para exibir o nome do relatorio qnd ele for aberto
                }
                else if (escolhaInt == 3)
                {
                    arquivoEscolhido = pim03;                           // Determina qual arquivo será aberto
                    strcpy(nomeMateria, "Engenharia de Software Agil"); // função "strcopy" Copia a string do nome da matéria para a variável nomeMateria. ai podemos usar ela para exibir o nome do relatorio qnd ele for aberto
                }
                else if (escolhaInt == 4)
                {
                    arquivoEscolhido = pim04;                            // Determina qual arquivo será aberto
                    strcpy(nomeMateria, "Programação Estruturada em C"); // função "strcopy" Copia a string do nome da matéria para a variável nomeMateria. ai podemos usar ela para exibir o nome do relatorio qnd ele for aberto
                }
                else
                {
                    // printf("Saindo");
                    break; // break dento de das chaves para pq o relatorio nao é exibido qnd escolhemos, se deixar sem as chaves, o relatorio nao é exibido e o sistema sai desse modulo
                }
                printf("\n\x1b[1;37m===================================================\n");
                printf("Relatorio de %s\n", nomeMateria);
                printf("===================================================\x1b[0m\n");
                char linha[200], nome[50], turma[20], ra[20], materia[50];
                float n1, n2, n3, nota;
                // float media;

                fgets(linha, sizeof(linha), arquivoEscolhido);                // pula o cabeçalho
                while (fgets(linha, sizeof(linha), arquivoEscolhido) != NULL) // como a gente usou o ponteiro "arquivoEscolhido" nao foi preciso usar um while e fgets para abrir cada aquivo. Ele vai salvar na variavel "linha" o relatorio condizente a nossa escolha
                {
                    linha[strcspn(linha, "\n")] = '\0';
                    sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f",
                           nome, turma, ra, materia, &n1, &n2, &n3, &nota);

                    exibaAluno(nome, turma, ra, materia, n1, n2, n3, nota);

                    contadorAlunos++; // faz o incremento da variavel para saber o total de alunos exibidos por arquivo
                    encontrou = 1;
                    // A variável "encontrou" funciona como uma flag, assim que eu encontro oq eu quero, ela muda para 1 e nao vai para a condição ali de baixo fora do while que esta lendoo arquivo.
                    // Ela começa com valor 0 e muda para 1 quando o aluno é encontrado, isso significa que deu certo na nossa procura. Caso nao achar nada, a variavel vai continuar 0 (pq eu a iniciei como zero no começo do codigo) e vai entrar na condição ali de baixo
                }

                if (encontrou == 0) // caso eu nao encontrar nenhum aluno no arquivo, a variavel nao vai mudar (pq ela esta iniciada com 0) e vai entrar nessa condição, que será verdadeira
                    printf("Nenhum aluno encontrado para esta materia.\n");
                printf("\x1b[1;33mTotal de alunos encontrados: %i\n\x1b[0m", contadorAlunos);

                // Perguntar se deseja buscar outra matéria
                do
                {
                    printf("\x1b[1;37mDeseja buscar outra materia? [1] Sim [0] Nao: \x1b[0m");
                    fgets(entrada, sizeof(entrada), stdin);
                    novamente = atoi(entrada);
                    if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 2)
                    {
                        printf("\x1b[1;31mEntrada inválida! Digite apenas 0 ou 1.\x1b[0m\n");
                        continue;
                    }
                    break;
                } while (1);

            } while (novamente == 1);
            break;

        case 0:
            dnv = 0; // se no menu eu escolher 0, a sistema sair do programa pq a variavel "dnv" estara com o valor de 0, logo ela na cai na condição do primeiro do while, como visto ali em baixo
            // caso queira testar, mude essa variavel "dnv = 0" para "dnv = 1" o loop vai continuar pq a condição ali de baixo retornou true, logo, o loop se repete
            printf("\x1b[91mSaindo do sistema...\x1b[0m\n");
            break;

            // default:
            // printf("Opcao invalida. Tente novamente.\n");
        }

    } while (dnv == 1); // caso a gente escolher olhar novamente os relatorio, a variavel pássara a ser 1 e vai satisfazer a condição, fazendo com que o loop se repita e mostre novamente o menu de relatorio

    fclose(pim01);
    fclose(pim02);
    fclose(pim03);
    fclose(pim04);
    return 0;
    system("pause");
}

void exibirMenuPrincipal()
{
    printf("\n\x1b[1;37m===========================================\n");
    printf("         RELATÓRIO DE NOTAS - UNIP\n");
    printf("===========================================\n");
    printf("\n--- Selecione uma opção ---\x1b[0m\n");
    printf("\x1b[36m[1] - Buscar por aluno\n");
    printf("[2] - Busca por matéria\n");
    printf("\x1b[1;90m[0] - Sair\x1b[0m\n");
}

void exibaAluno(char *nome, char *turma, char *ra, char *materia, float n1, float n2, float n3, float nota)
{
    cores(nota);
    printf("--------------------------------------\n");
    printf("Nome: %s\n", nome);
    printf("Turma: %s\n", turma);
    printf("RA: %s\n", ra);
    printf("Matéria: %s\n", materia);
    printf("Notas: %.2f | %.2f | %.2f\n", n1, n2, n3);
    printf("Média Final: %.2f\n", nota);
    printf("--------------------------------------\x1b[0m\n");
}

int nomeValido(char *nome)
{
    for (int i = 0; nome[i] != '\0'; i++)
    {
        if (!isalpha(nome[i]) && nome[i] != ' ')
        {
            return 0; // nome inválido
        }
    }
    return 1; // nome válido
}
int buscarNosArquivos(FILE *pim01, FILE *pim02, FILE *pim03, FILE *pim04, char *nomeAluno)
{
    char linha[100], nome[50], turma[20], ra[20], materia[50];
    float n1, n2, n3, media;
    int encontrou = 0;

    // Busca no primeiro arquivo
    rewind(pim01);
    while (fgets(linha, sizeof(linha), pim01))
    {
        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &media);
        if (strcmp(nomeAluno, nome) == 0)
        {
            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
            encontrou = 1;
        }
    }

    // Busca no segundo arquivo
    rewind(pim02);
    while (fgets(linha, sizeof(linha), pim02))
    {
        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &media);
        if (strcmp(nomeAluno, nome) == 0)
        {
            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
            encontrou = 1;
        }
    }

    // Busca no terceiro arquivo
    rewind(pim03);
    while (fgets(linha, sizeof(linha), pim03))
    {
        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &media);
        if (strcmp(nomeAluno, nome) == 0)
        {
            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
            encontrou = 1;
        }
    }
    rewind(pim04);
    while (fgets(linha, sizeof(linha), pim04))
    {
        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &media);
        if (strcmp(nomeAluno, nome) == 0)
        {
            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
            encontrou = 1;
        }
    }

    return encontrou;
}
void cores(int nota1)
{

    if (nota1 == 6)
    {
        printf("\x1b[1;33m");
    }
    else if (nota1 > 6)
    {
        printf("\x1b[32m");
    }
    else
        printf("\x1b[91m");
}