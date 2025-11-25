#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

void exibirMenuPrincipal(); // Função que exibe o menu principal
void exibaAluno(char *nome, char *turma, char *ra, char *materia, float n1, float n2, float n3, float media); // Função para exibir dados de um aluno
int buscarNosArquivos(FILE *pim01, FILE *pim02, FILE *pim03, FILE *pim04, char *nomeAluno); // Função para buscar aluno nos arquivos
void removeEspacos(char *str); // Função para remover espaços extras de uma string

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Habilita acentuação corretamente no terminal

    // Abre os arquivos CSV de diferentes matérias
    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Algoritmos_e_Estruturas_de_Dados_em_Python.csv", "r");
    FILE *pim02 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Analise_e_Projeto_de_Sistemas.csv", "r");
    FILE *pim03 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Engenharia_de_Software_Agil.csv", "r");
    FILE *pim04 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Programacao_Estruturada_em_C.csv", "r");

    if (!pim01 || !pim02 || !pim03 || !pim04)
    {
        printf("\x1b[31mErro ao abrir os arquivos!\x1b[0m\n");
        return 1;
    }

    int continuar = 1;
    while (continuar)
    {
        int opcao;
        char entrada[10];
        exibirMenuPrincipal();
        
        // Solicita a opção do usuário
        printf("\x1b[1;33mDigite sua escolha: \x1b[0m");
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%d", &opcao) != 1 || opcao < 0 || opcao > 2)
        {
            printf("\x1b[31mOpção inválida! Tente novamente.\x1b[0m\n");
            continue;
        }

        switch (opcao)
        {
        case 1: // Busca por aluno
        {
            char nomeAluno[50];
            printf("\x1b[1;37mDigite o nome do aluno: \x1b[0m");
            fgets(nomeAluno, sizeof(nomeAluno), stdin);
            nomeAluno[strcspn(nomeAluno, "\n")] = 0;  // Remove o '\n' que vem com fgets

            int alunoEncontrado = buscarNosArquivos(pim01, pim02, pim03, pim04, nomeAluno);

            if (!alunoEncontrado)
            {
                printf("\x1b[31mAluno não encontrado.\x1b[0m\n");
            }

            printf("\nDeseja realizar outra busca? [1] - Sim [0] - Não: ");
            fgets(entrada, sizeof(entrada), stdin);
            sscanf(entrada, "%d", &continuar);
            break;
        }
        case 0:
            continuar = 0;
            break;
        default:
            printf("\x1b[31mOpção inválida! Tente novamente.\x1b[0m\n");
            break;
        }
    }

    fclose(pim01);
    fclose(pim02);
    fclose(pim03);
    fclose(pim04);

    return 0;
}

void exibirMenuPrincipal()
{
    printf("\x1b[1;36m===== Menu Principal =====\x1b[0m\n");
    printf("[1] - Buscar aluno\n");
    printf("[0] - Sair\n");
}

void exibaAluno(char *nome, char *turma, char *ra, char *materia, float n1, float n2, float n3, float media)
{
    printf("\x1b[1;37m\nAluno: %s\n", nome);
    printf("RA: %s\n", ra);
    printf("Turma: %s\n", turma);
    printf("Matéria: %s\n", materia);
    printf("Notas: %.2f, %.2f, %.2f\n", n1, n2, n3);
    printf("Média: %.2f\n", media);
}

/* void removeEspacos(char *str)
{
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && str[i] != '\t') // Remove espaços e tabulações
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Finaliza a string
} */

// Função para buscar nos arquivos e encontrar o aluno
int buscarNosArquivos(FILE *pim01, FILE *pim02, FILE *pim03, FILE *pim04, char *nomeAluno)
{
    FILE *arquivos[] = {pim01, pim02, pim03, pim04};
    const char *materias[] = {"Algoritmos e Estruturas de Dados em Python", "Análise e Projeto de Sistemas", 
                               "Engenharia de Software Ágil", "Programação Estruturada em C"};
    char linhaArq[200], nome[50], turma[50], ra[20], materia[50];
    float n1, n2, n3, media;
    int alunoEncontrado = 0;

    for (int i = 0; i < 4; i++)
    {
        rewind(arquivos[i]); // Reinicia a leitura do arquivo
        fgets(linhaArq, sizeof(linhaArq), arquivos[i]); // Pula o cabeçalho

        while (fgets(linhaArq, sizeof(linhaArq), arquivos[i]))
        {
            sscanf(linhaArq, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, ra, turma, materia, &n1, &n2, &n3, &media);
            /* removeEspacos(nome); // Remove espaços extras do nome
            removeEspacos(nomeAluno); // Remove espaços extras da entrada do nome do aluno */

            // Verifica se o nome do aluno corresponde ao RA no arquivo
            if (strcmp(nomeAluno, ra) == 0)
            {
                exibaAluno(nome, turma, ra, materia, n1, n2, n3, media);
                alunoEncontrado = 1;
                break; // Encerra a busca se o aluno for encontrado
            }
        }
    }
    
    return alunoEncontrado;
}
