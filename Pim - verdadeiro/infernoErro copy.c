#include <stdio.h>  //funções de entrada e saída
#include <string.h> //manipulação de strings (strcmp, strcpy, etc.);
#include <ctype.h>  //funções de caracteres (como toupper, tolower).
#include <stdlib.h> // precisa pra usar atoi()
#include <locale.h> //permite usar acentuação em português (setlocale);

void exibirMenuPrincipal();                                                                                  // menu inicial
void exibaAluno(char *nome, char *turma, char *ra, char *materia, float n1, float n2, float n3, float nota); // função para printar o relatorio dos alunos
int nomeValido(char *nome);                                                                                  // função para validar a entrada do nome do aluno e que nao deixar passar numeros
int buscarNosArquivos(FILE *pim01, FILE *pim02, FILE *pim03, FILE *pim04, char *nomeAluno);                  // função que percorre os 3 arquivos para usar no busca por alunos geral
void cores(int nota1);                                                                                       // função para as cores nos relatorios
int main()
{
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
            // fgets(entrada, sizeof(entrada), stdin);
            //  sscanf retorna 1 se conseguiu ler um número inteiro corretamente
            /*if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 2)
            {
                printf("\x1b[31mEntrada inválida! Digite novamente.\x1b[0m\n");
                continue; // volta para o início do loop
            }*/

            if (scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 2)
            {
                while (getchar() != '\n')
                    ; // limpa o buffer do stdin
                printf("\x1b[31mEntrada inválida! Digite novamente.\x1b[0m\n");
                continue; // volta para o início do loop
            }
            break; // entrada válida, sai do loop

        } while (1);

        char linhaArqPim[100]; // variavel onde esta sendo salvo os dados do arquivo
        char escolhaStr[700];  // var para guardar a escolha do usuario
        int encontrou = 0;     // flag para controlar o aviso dos alunos nao encontrados
        int novamente;
        switch (opcao)
        {
        case 1:
        { // Busca por aluno
            int buscarNovamente = 1;
            while (getchar() != '\n')
                ; // limpa o buffer do stdin antes de entrar no loop para nao ir com lixo e dar erro na leitura e acabar entrando no loop infinito ou printando "entrada invalida! digite novamente" da condição ali de baixo
            while (buscarNovamente)
            {
                char nomeAluno[700];
                int tipoBusca = 0;

                // Escolha do tipo de busca
                do
                {
                    printf("\x1b[1;37mDeseja buscar por todas as matérias ou somente uma?\x1b[0m\n");
                    printf("\x1b[36m[1] - Materia especifica\n");
                    printf("[2] - Geral\n");
                    printf("\x1b[1;90m[0] - Sair\x1b[0m\n");
                    printf("\x1b[1;33mDigite sua escolha: \x1b[0m");
                    /*fgets(escolhaStr, sizeof(escolhaStr), stdin);

                    // sscanf retorna 1 se conseguiu ler um número inteiro corretamente
                    if (sscanf(escolhaStr, "%d", &tipoBusca) != 1 || tipoBusca < 0 || tipoBusca > 2)
                    {
                        //while (getchar() != '\n');
                        printf("\x1b[31mEntrada inválida! Digite novamente.\x1b[0m\n");
                        continue; // volta para o início do loop
                    }*/
                    if (scanf("%d", &tipoBusca) != 1 || tipoBusca < 0 || tipoBusca > 2)
                    {
                        while (getchar() != '\n')
                            ; // limpa o buffer do stdin
                        printf("\x1b[31mEntrada inválida! Digite novamente.\x1b[0m\n");
                        continue; // volta para o início do loop
                    }

                    break;
                } while (1);

                if (tipoBusca == 1)
                {
                    int materiaEscolhida = 0;
                    while (getchar() != '\n')
                        ;
                    do
                    { // Escolha da matéria
                        printf("\x1b[1;37m\nEscolha a materia:\x1b[0m\n");
                        printf("\x1b[36m[1] - Algoritmo e Estrutura de Dados em Python\n");
                        printf("[2] - Analise e Projeto de sistemas\n");
                        printf("[3] - Engenharia de Software Agil\n");
                        printf("[4] - Programação Estruturada em C\x1b[0m\n");
                        printf("\x1b[1;90m[0] - Sair\x1b[0m\n");
                        printf("\x1b[1;33mDigite sua escolha: \x1b[0m");
                        // fgets(escolhaStr, sizeof(escolhaStr), stdin);

                        /*if (sscanf(escolhaStr, "%d", &materiaEscolhida) != 1 || materiaEscolhida < 0 || materiaEscolhida > 4)
                        {
                            printf("\x1b[31mEntrada inválida! Digite novamente.\x1b[0m\n"); // validação da entrada do usuario
                            continue;
                        }*/
                        if (scanf("%d", &materiaEscolhida) != 1 || materiaEscolhida < 0 || materiaEscolhida > 4)
                        {
                            printf("\x1b[31mEntrada inválida! Digite novamente.\x1b[0m\n");
                            while (getchar() != '\n')
                                ;
                            continue;
                        }

                        break;
                    } while (1);

                    FILE *arquivo; // ponteiro que será usado para determinar qual arquivo vai ser aberto

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

                    char nomeMateria[50]; // variavel onde será atribuido os nomes das materias
                    if (materiaEscolhida == 1)
                        strcpy(nomeMateria, "Algorit. e Estruturas de Dados em Python"); // coloca o nome da materia dentra da var "nomeMateria"
                    else if (materiaEscolhida == 2)
                        strcpy(nomeMateria, "Analise e Projeto de Sistemas");
                    else if (materiaEscolhida == 3)
                        strcpy(nomeMateria, "Engenharia de Software Agil");
                    else
                        strcpy(nomeMateria, "Programação Estruturada em C");

                    char raTeclado[700];
                    do
                    {
                        /*  printf("\x1b[1;37m\nDigite o nome do aluno: \x1b[0m");
                         fgets(nomeAluno, sizeof(nomeAluno), stdin);
                         nomeAluno[strcspn(nomeAluno, "\n")] = 0; */
                        printf("digite o RA do aluno: ");
                        // fgets(raTeclado, sizeof(raTeclado), stdin);
                        // raTeclado[strcspn(raTeclado, "\n")] = '\0';
                        scanf("%s", raTeclado); //
                        while (getchar() != '\n')
                            ; // limpa o buffer do stdin
                        for (int i = 0; raTeclado[i] != '\0'; i++)
                        {
                            raTeclado[i] = tolower(raTeclado[i]); // faz a conversão para minusculo da entraadda do RA
                        }
                        break; // sai do loop se o nome for válido
                    } while (1);

                    rewind(arquivo); // reiniciaa o arquivo para a proxima leitura

                    int encontrou = 0; // flag para indicar que o aluno foi encontrado ou nao
                    char nome[700], turma[700], ra[700], materia[700];
                    float n1, n2, n3, media;

                    // fgets(linhaArqPim, sizeof(linhaArqPim), arquivo); // pula o cabeçalho
                    while (fgets(linhaArqPim, sizeof(linhaArqPim), arquivo))
                    {
                        sscanf(linhaArqPim, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, ra, turma, materia, &n1, &n2, &n3, &media); // essa parte guarda cada parte do csv separado por ";" e guarda dentro dessas var

                        for (int i = 0; ra[i] != '\0'; i++)
                        {
                            ra[i] = tolower(ra[i]);
                        }

                        if (strcmp(raTeclado, ra) == 0)
                        {
                            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
                            encontrou = 1;
                        }
                    }

                    if (!encontrou)
                        printf("\x1b[1;31maluno nao encontrado para a materia %s.\x1b[0m\n", nomeMateria);
                }

                int encontrouTipoBusca = 0; // variavel onde sera guardado o retorno da função buscarNosArquivos e faz a verificação se o aluno foi encontrado ou nao
                if (tipoBusca == 2)
                {
                    do
                    {
                        printf("\x1b[1;37m\nDigite o RA do aluno: \x1b[0m");
                        // fgets(nomeAluno, sizeof(nomeAluno), stdin);
                        // nomeAluno[strcspn(nomeAluno, "\n")] = 0;
                        scanf("%s", nomeAluno);
                        while (getchar() != '\n')
                            ; // limpa o buffer do stdin

                        for (int i = 0; i < nomeAluno[i]; i++)
                        {
                            nomeAluno[i] = tolower(nomeAluno[i]);
                        }

                        break; // sai do loop se o nome for válido
                    } while (1);

                    fgets(linhaArqPim, sizeof(linhaArqPim), pim01); // pula o cabeçalho
                    fgets(linhaArqPim, sizeof(linhaArqPim), pim02); // pula o cabeçalho
                    fgets(linhaArqPim, sizeof(linhaArqPim), pim03); // pula o cabeçalho
                    fgets(linhaArqPim, sizeof(linhaArqPim), pim04); // pula o cabeçalho

                    // função que abre todos os arquivos e faz a exibição do aluno que a gente quer olhar
                    encontrouTipoBusca = buscarNosArquivos(pim01, pim02, pim03, pim04, nomeAluno); // o dado de return na função "buscarNosArquivos" é guardado dentro da variavel "encontrouTipoBusca", ent, se encontrou um aluno ela mudará a variavel para , se nao encontrou um aluno, a variavel ficara com o valor de 0 e vai aparecer a mensagem "Aluno nao encontrado nos relatorios!!"
                }
                if (tipoBusca == 2 && !encontrouTipoBusca)
                {
                    printf("\x1b[1;33mAluno nao encontrado nos relatorios!!\x1b[0m\n");
                }

                if (tipoBusca == 0)
                {
                    break;
                }

                do
                {
                    // char teste[10];
                    printf("\x1b[1;33mDeseja buscar outro aluno? [1] Sim [0] Nao: \x1b[0m");

                    if (scanf("%d", &buscarNovamente) != 1 || (buscarNovamente != 0 && buscarNovamente != 1))
                    {
                        printf("\x1b[1;31mEntrada inválida! Digite novamente.\x1b[0m\n");
                        while (getchar() != '\n')
                            ;
                        continue;
                    }

                    // system("cls"); // limpa o terminal a cada vez que voltar para o menu novamente

                    break;
                } while (1);

                
            }
          
        }

        break;
        case 2:
            while (getchar() != '\n')
                ; // limpa o buffer do stdin antes de entrar no loop para nao ir com lixo e dar erro na leitura e acabar entrando no loop infinito ou printando "entrada invalida! digite novamente" da condição ali de baixo, esse while é necessario pq antes de entrar no case 2, a gente usou o scanf para ler a opção do menu, entao fica esse lixo no buffer do stdin
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
                {
                    printf("\x1b[1;33mDigite a materia da sua escolha: \x1b[0m");
                    /*fgets(entrada, sizeof(entrada), stdin);
                    if (sscanf(entrada, "%d", &escolhaInt) != 1 || escolhaInt < 0 || escolhaInt > 4)
                    {
                        printf("\x1b[1;31mEntrada inválida! Digite apenas 0 ou 1.\x1b[0m\n");
                        continue;
                    }*/
                    if (scanf("%d", &escolhaInt) != 1 || escolhaInt < 0 || escolhaInt > 4)
                    {
                        printf("\x1b[1;31mEntrada inválida!\x1b[0m\n");
                        while (getchar() != '\n')
                            ;
                        continue;
                    }
                    break;
                } while (1);

                // Determina qual arquivo e nome da materia
                FILE *arquivoEscolhido; // esse ponteiro aponta para os primeiros arquivos que abrimos no inicio do codigo
                char nomeMateria[70];

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
                    break; // break dentro  das chaves para pq o relatorio nao é exibido qnd escolhemos, se deixar sem as chaves, o relatorio nao é exibido e o sistema sai desse modulo
                }
                printf("\n\x1b[1;37m===================================================\n");
                printf("Relatorio de %s\n", nomeMateria);
                printf("===================================================\x1b[0m\n");
                char linhaArqPim[200], nome[25], turma[70], ra[20], materia[400];
                float n1, n2, n3, nota;
                char pulaLinha[40];

                fgets(pulaLinha, sizeof(pulaLinha), arquivoEscolhido);                    // pula o cabeçalho
                while (fgets(linhaArqPim, sizeof(linhaArqPim), arquivoEscolhido) != NULL) // como a gente usou o ponteiro "arquivoEscolhido" nao foi preciso usar um while e fgets para abrir cada aquivo. Ele vai salvar na variavel "linhaArqPim" o relatorio condizente a nossa escolha
                {
                    linhaArqPim[strcspn(linhaArqPim, "\n")] = '\0';
                    // sscanf(linhaArqPim, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &nota);

                    if (sscanf(linhaArqPim, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f",
                               nome, ra, turma, materia, &n1, &n2, &n3, &nota) == 8)
                    {
                        encontrou = 1;
                        exibaAluno(nome, turma, ra, materia, n1, n2, n3, nota);
                        contadorAlunos++; // faz o incremento da variavel para saber o total de alunos exibidos por arquivo
                    }

                    // encontrou = 1;
                    //  A variável "encontrou" funciona como uma flag, assim que eu encontro oq eu quero, ela muda para 1 e nao vai para a condição ali de baixo fora do while que esta lendoo arquivo.
                    //  Ela começa com valor 0 e muda para 1 quando o aluno é encontrado, isso significa que deu certo na nossa procura. Caso nao achar nada, a variavel vai continuar 0 (pq eu a iniciei como zero no começo do codigo) e vai entrar na condição ali de baixo
                }
                if (encontrou == 1)
                {
                    printf("\x1b[1;33mTotal de alunos encontrados: %i\n\x1b[0m", contadorAlunos);
                }

                if (encontrou == 0)
                { // caso eu nao encontrar nenhum aluno no arquivo, a variavel nao vai mudar (pq ela esta iniciada com 0) e vai entrar nessa condição, que será verdadeira
                    printf("\x1b[1;31mNenhum aluno encontrado para esta materia.\x1b[0m\n");
                }
                do
                {
                    while (getchar() != '\n')
                        ; // limpa o buffer do stdin
                    printf("\x1b[1;37mDeseja buscar outra materia? [1] Sim [0] Nao: \x1b[0m");
                    /*fgets(entrada, sizeof(entrada), stdin);
                    novamente = atoi(entrada);
                    if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 2)
                    {
                        printf("\x1b[1;31mEntrada inválida! Digite apenas 0 ou 1.\x1b[0m\n");
                        continue;
                    }*/
                    if (scanf("%d", &novamente) != 1 || (novamente != 0 && novamente != 1))
                    {
                        printf("\x1b[1;31mEntrada inválida! Digite apenas 0 ou 1.\x1b[0m\n");
                        while (getchar() != '\n')
                            ;
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

int nomeValido(char *nome) // função para saber se o usuario digitou algum numero, percorre cada caracter da variavel nome e faz a verificação, se for numero, retorna 0
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
int buscarNosArquivos(FILE *pim01, FILE *pim02, FILE *pim03, FILE *pim04, char *nomeAluno) // função para ler os arquivos
{
    char linhaArqPim[200], nome[700], turma[700], ra[700], materia[700];
    float n1, n2, n3, media;
    int encontrou = 0;

    rewind(pim01);
    while (fgets(linhaArqPim, sizeof(linhaArqPim), pim01))
    {
        sscanf(linhaArqPim, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, ra, turma, materia, &n1, &n2, &n3, &media);
        if (strcmp(nomeAluno, ra) == 0)
        {
            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
            encontrou = 1;
        }
    }

    rewind(pim02);
    while (fgets(linhaArqPim, sizeof(linhaArqPim), pim02))
    {
        sscanf(linhaArqPim, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, ra, turma, materia, &n1, &n2, &n3, &media);
        if (strcmp(nomeAluno, ra) == 0)
        {
            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
            encontrou = 1;
        }
    }

    rewind(pim03);
    while (fgets(linhaArqPim, sizeof(linhaArqPim), pim03))
    {
        sscanf(linhaArqPim, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, ra, turma, materia, &n1, &n2, &n3, &media);
        if (strcmp(nomeAluno, ra) == 0)
        {
            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
            encontrou = 1;
        }
    }

    rewind(pim04);
    while (fgets(linhaArqPim, sizeof(linhaArqPim), pim04))
    {
        sscanf(linhaArqPim, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, ra, turma, materia, &n1, &n2, &n3, &media);
        if (strcmp(nomeAluno, ra) == 0)
        {
            exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
            encontrou = 1;
        }
    }

    return encontrou;
}

void cores(int nota1) // função para colocar as cores qnd os relatorios for exibidos
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