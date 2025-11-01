#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> // precisa pra usar atoi()
#include <locale.h>

int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "pt_BR.UTF-8");

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

            // sscanf retorna 1 se conseguiu ler um n�mero inteiro corretamente
            if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 2)
            {
                printf("Entrada inválida! Digite apenas 0, 1 ou 2.\n");
                continue; // volta para o in�cio do loop
            }

            break; // entrada v�lida, sai do loop
        } while (1);

        char linha[100];   // variavel onde esta sendo salvo os dados do arquivo "pim01"
        char linha02[100]; // variavel onde esta sendo salvo os dados do arquivo "pim02"
        char linha03[100]; // variavel onde esta sendo salvo os dados do arquivo "pim03"
        char nome[40];
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
        int escolhaModuloCase1; // variavel que ser� a escolha do usuario no case 1
        switch (opcao)
        {
        case 1:

            printf("Buscar por aluno\n");
            printf("Qual modulo deseja ir?\n");
            printf(" [1] Materia especifica\n [2] Geral\n");
            // scanf("%i", &escolhaModuloCase1);
            // while (getchar() != '\n');

            while (1)
            {
                int resultado;
                printf("Digite sua escolha: ");

                // Tenta ler um n�mero inteiro
                resultado = scanf("%i", &escolhaModuloCase1); // Usamos dois int (var resultado e escolhamodulocase1)porque um guarda o valor digitado, e o outro guarda se a leitura deu certo. //S�o pap�is diferentes, embora ambos usem o mesmo tipo de dado.

                // Limpa o buffer de entrada
                while (getchar() != '\n')
                    ;

                // Verifica se a entrada � v�lida (n�mero e dentro do intervalo)
                if (resultado != 1)
                { // valida��o da entrada do usuario, se ele digitar uma letra, o sistema vai barrar e pedir novamente a escolha//estudar melhor sobre essa valida��o, joga no chat e pe�a para ele explicar e dps assitaa video no youtube sobre
                    printf("Entrada inv�lida! Digite apenas n�meros (1 ou 2).\n");
                    continue;
                }

                if (escolhaModuloCase1 != 1 && escolhaModuloCase1 != 2)
                {
                    printf("Op��o inv�lida! Escolha 1 ou 2.\n");
                    continue;
                }
                // Sai do loop se for v�lido
                break;
            }

            int escMateriaAluno;         // variavel para a escolha de qual materia voce deseja procurar o aluno
            if (escolhaModuloCase1 == 1) // busca aluno por materia especifica
            {
                printf("qual materia deseja olhar o aluno?\n");
                printf("1 Algoritmos_e_Estruturas_de_Dados_em_Python\n2 Analise_e_Projeto_de_Sistemas\n");
                // scanf("%i", &escMateriaAluno);

                int resultadoEscolhaMate;
                while (1)
                {
                    // scanf("%i", &escMateriaAluno);
                    resultadoEscolhaMate = scanf("%i", &escMateriaAluno);

                    while (getchar() != '\n');

                    if (resultadoEscolhaMate != 1)
                    {
                        printf("Entrada inv�lida! Digite apenas n�meros (1 ou 2).\n");
                        continue;
                    }
                    if (escMateriaAluno != 1 && escMateriaAluno != 2)
                    {
                        printf("Entrada inv�lida! Digite apenas n�meros (1 ou 2).\n");
                        continue;
                    }
                    break;
                }
                char nomeAlunoCase1[15];
                char dadosMateriaBusca[100]; // variavel que ser� guardado os dados dos arquivos assim que a gente ler ele
                char nomeMateriaCase1[20];   // variavel onde ser� guardado o nome da materia que a gente escolher aq em baixo
                FILE *materiaEscolinhaBusca; // ponteiro que ser� usado para abrir os arquivos la de cima
                if (escMateriaAluno == 1)
                {
                    materiaEscolinhaBusca = pim01;
                    strcpy(nomeMateriaCase1, "Algoritmos_e_Estruturas_de_Dados_em_Python");
                    printf("nome do aluno: ");
                    fgets(nomeAlunoCase1, sizeof(nomeAlunoCase1), stdin);
                }
                if (escMateriaAluno == 2)
                {
                    strcpy(nomeMateriaCase1, "Analise_e_Projeto_de_Sistemas");
                    materiaEscolinhaBusca = pim02;
                }
                if (escMateriaAluno == 3)
                {
                    strcpy(nomeMateriaCase1, "Engenharia_de_Software_Agil");
                    materiaEscolinhaBusca = pim03;
                }

                fseek(materiaEscolinhaBusca, 0, SEEK_SET); // reinicia o arquivo toda vez que a gente querer olhar o relatorio
                int encontrouCase1 = 0;
                fgets(dadosMateriaBusca, sizeof(dadosMateriaBusca), materiaEscolinhaBusca);
                while (fgets(dadosMateriaBusca, sizeof(dadosMateriaBusca), materiaEscolinhaBusca) != NULL)
                {
                    sscanf(dadosMateriaBusca, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, raAluno, materia, &n1, &n2, &n3, &nota);

                    nomeAlunoCase1[strcspn(nomeAlunoCase1, "\n")] = '\0'; // essa fun��o faz a limpeza da quebra de linha lida pelo o fgets, quando usamos o fgets ele le a \n no final do texto, por isso a valida��o no aluno aq de baixo nao estava pegando antes de usar esssa fun��o para tirar o \n, o fget lia assim "nomeAluno\n" e guardava na variavel "nomeAlunoCase1", quando ia para a compara��o aq de baixo, era sempre falsa pq a var "nomeAlunoCase1" esta guardando "nomeAluno\n" e a var "nome" guardava "nomeAluno" sem a quebra de linha
                    if (strcmp(nomeAlunoCase1, nome) == 0)
                    {
                        printf("\n------------------\n");
                    printf("Nome: %s\nMateria: %s\nNotas: %.1f %.1f %.1f\nMedia: %.1f\n------------------\n",
                           nome, materia, n1, n2, n3, (n1 + n2 + n3) / 3);
                        encontrouCase1 = 1;
                    }
                }
                if (encontrouCase1 == 0)
                {
                    while (getchar() != '\n');
                    printf("nao encontrdo");
                }
            }
            else if (escolhaModuloCase1 == 2) // busca aluno em todas as materias
            {
                printf("escolha 2");
            }

            break;
        case 2:
            do
            {
                fseek(pim01, 0, SEEK_SET); // reinicia o arquivo toda vez que a gente querer olhar o relatorio
                fseek(pim02, 0, SEEK_SET); // reinicia o arquivo toda vez que a gente querer olhar o relatorio
                fseek(pim03, 0, SEEK_SET); // reinicia o arquivo toda vez que a gente querer olhar o relatorio
                encontrou = 0;
                int contadorAlunos = 0; // variavel para contar os alunos dos arquivos, ela ser� incremetanda a cada vez que o while repetir na hora de mostrar o relatorio

                printf("\nEscolha uma materia:\n");
                printf("  [1] Algoritmos_e_Estruturas_de_Dados_em_Python\n");
                printf("  [2] Analise_e_Projeto_de_Sistemas\n");
                printf("  [3] Engenharia_de_Software_Agil\n");

                int escolhaInt;
                char entrada[10];
                do
                { // fun��o para fazer a valida��o da entrada do usuario
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
                    arquivoEscolhido = pim01;                                          // Determina qual arquivo ser� aberto
                    strcpy(nomeMateria, "Algoritmos_e_Estruturas_de_Dados_em_Python"); // fun��o "strcopy" Copia a string do nome da mat�ria para a vari�vel nomeMateria.ai podemos usar ela para exibir o nome do relatorio qnd ele for aberto
                }
                else if (escolhaInt == 2)
                {
                    arquivoEscolhido = pim02;                             // Determina qual arquivo ser� aberto
                    strcpy(nomeMateria, "Analise_e_Projeto_de_Sistemas"); // fun��o "strcopy" Copia a string do nome da mat�ria para a vari�vel nomeMateria. ai podemos usar ela para exibir o nome do relatorio qnd ele for aberto
                }
                else
                {
                    arquivoEscolhido = pim03;                           // Determina qual arquivo ser� aberto
                    strcpy(nomeMateria, "Engenharia_de_Software_Agil"); // fun��o "strcopy" Copia a string do nome da mat�ria para a vari�vel nomeMateria. ai podemos usar ela para exibir o nome do relatorio qnd ele for aberto
                }

                printf("\nRelatorio de %s:\n", nomeMateria);
                char linha[200], nome[50], turma[20], ra[20], materia[50];
                float n1, n2, n3, nota;

                fgets(linha, sizeof(linha), arquivoEscolhido);                // pula o cabe�alho
                while (fgets(linha, sizeof(linha), arquivoEscolhido) != NULL) // como a gente usou o ponteiro "arquivoEscolhido" nao foi preciso usar um while e fgets para abrir cada aquivo. Ele vai salvar na variavel "linha" o relatorio condizente a nossa escolha
                {
                    linha[strcspn(linha, "\n")] = '\0';
                    sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, ra, materia, &n1, &n2, &n3, &nota); // salva cada parte do arquivo em uma variavel, a cada ";" do csv, essa fun��o guarda nas variaveis

                    printf("\n------------------\n");
                    printf("Nome: %s\nMateria: %s\nNotas: %.1f %.1f %.1f\nMedia: %.1f\n------------------\n",
                           nome, materia, n1, n2, n3, (n1 + n2 + n3) / 3);

                    contadorAlunos++; // faz o incremento da variavel para saber o total de alunos exibidos por arquivo
                    encontrou = 1;
                    // A vari�vel "encontrou" funciona como uma flag, assim que eu encontro oq eu quero, ela muda para 1 e nao vai para a condi��o ali de baixo fora do while que esta lendoo arquivo.
                    // Ela come�a com valor 0 e muda para 1 quando o aluno � encontrado, isso significa que deu certo na nossa procura. Caso nao achar nada, a variavel vai continuar 0 (pq eu a iniciei como zero no come�o do codigo) e vai entrar na condi��o ali de baixo
                }

                if (encontrou == 0) // caso eu nao encontrar nenhum aluno no arquivo, a variavel nao vai mudar (pq ela esta iniciada com 0) e vai entrar nessa condi��o, que ser� verdadeira
                    printf("Nenhum aluno encontrado para esta materia.\n");
                printf("Total de alunos encontrados: %i\n", contadorAlunos);

                // Perguntar se deseja buscar outra mat�ria
                do
                {
                    printf("Deseja buscar outra materia? [1] Sim [0] Nao: ");
                    fgets(entrada, sizeof(entrada), stdin);
                    novamente = atoi(entrada);
                    if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 2)
                    {
                        printf("Entrada inv�lida! Digite apenas 0, 1 ou 2.\n");
                        continue;
                    }
                    break;
                } while (1);

            } while (novamente == 1);
            break;

        case 0:
            dnv = 0; // se no menu eu escolher 0, a sistema sair do programa pq a variavel "dnv" estara com o valor de 0, logo ela na cai na condi��o do primeiro do while, como visto ali em baixo
            // caso queira testar, mude essa variavel "dnv = 0" para "dnv = 1" o loop vai continuar pq a condi��o ali de baixo retornou true, logo, o loop se repete
            printf("Saindo do sistema...\n");
            break;

            // default:
            // printf("Opcao invalida. Tente novamente.\n");
        }

    } while (dnv == 1); // caso a gente escolher olhar novamente os relatorio, a variavel p�ssara a ser 1 e vai satisfazer a condi��o, fazendo com que o loop se repita e mostre novamente o menu de relatorio

    fclose(pim01);
    fclose(pim02);
    fclose(pim03);
    return 0;
    system("pause");
}