#include <stdio.h>
#include <string.h>

int main() {
    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\pim01.txt", "r");
    FILE *pim02 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\pim02.txt", "r");
    FILE *pim03 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\ESTUDOS\\faculdade\\PROGRAMACAO ESTRUTURADA EM C\\Algoritmos_e_Estruturas_de_Dados.csv", "r");
    if (pim01 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    if (pim02 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int dnv = 1;
    do {
        char escolha;
        printf("=====================================\n");
        printf("        RELATORIO DE NOTAS - UNIP      \n");
        printf("=====================================\n");
        printf("Selecione uma opcao:\n");
        printf("  [1] Buscar por aluno\n");
        printf("  [2] Buscar por materia\n");
        printf("  [0] Sair\n");
        printf("Digite sua escolha: ");

        scanf(" %c", &escolha);

        char linha[100];//variavel onde esta sendo salvo os dados do arquivo "pim01"
        char linha02[100];//variavel onde esta sendo salvo os dados do arquivo "pim02"
        char linha03[100];//variavel onde esta sendo salvo os dados do arquivo "pim03"
        char nome[40];
        char materia[40];
        float n1 = 0, n2 = 0, n3;
        int encontrou = 0;
        int novamente;
        char pulaCabecalho[200];
        char turma[20];
        char teste[40];
        float t, f, nota;
        char escolhaMateria[20];
        int testeSub;
        switch (escolha) {
            case '1':
                
                printf("Busca por aluno ainda nao implementada.\n");

                printf("teste de sub menu ");
                scanf("%i", &testeSub);

                switch (testeSub)
                {
                case 1:
                    while (fgets(linha02, sizeof(linha02), pim02) != NULL)
                    {
                        printf("%s\n", linha02);
                    }
                        


                    break;
                
                default:
                    break;
                }
                break;

            case '2':// case 2, serve para a gente escolher qual materia queremos olhar o relatorio, ainda nao esta completo, deixarei em loop para a gente olhar quantas vezes quisermos, porem, o caminho é esse
                do {
                    fseek(pim01, 0, SEEK_SET);
                    fseek(pim02, 0, SEEK_SET);
                    fseek(pim03, 0, SEEK_SET);
                    encontrou = 0;
                    
                    printf("\nEscolha uma materia:\n");
                    printf("  [1] Matematica\n");
                    printf("  [2] Portugues\n");
                    printf("  [3] Química\n");
                    printf("Digite o nome ou o numero da materia: ");

                    scanf("%s", escolhaMateria);

                    while (strcmp(escolhaMateria, "1") != 0
                        && strcmp(escolhaMateria, "matematica") != 0
                        && strcmp(escolhaMateria, "2") != 0
                        && strcmp(escolhaMateria, "portugues") != 0
                        && strcmp(escolhaMateria, "3") != 0
                        && strcmp(escolhaMateria, "quimica") != 0) {
                        printf("Materia não encontrada. Tente novamente: ");
                        scanf("%s", escolhaMateria);
                        // validação sobre qual materia a gente quer olhar, "strcmp" é uma função que compara strings, que bem util para a gente fazer a comparação entre as materias que esta no nosso arquivo txt. Ex, se eu escolher a opção 1, será feita a verificação ali embaixo, se a variavel "escolhaMateria" for igual a 1 e a variavel "materia" for igual a "matematica", o sistema exibira o relatorio sobre a meteria escolhida. Esse comportamento serve para os outros numeros.
                        //caso a gente escolha uma materia que nao esteja dentro da condição, o sistema entrará no loop, vou acrescentar uma forma de sair do programa dentro desse loop aq, caso o usuario nao queira mais olhar as notas
                    }
                    
                    fgets(pulaCabecalho, sizeof(pulaCabecalho), pim01);//essa função pula o cabeçalho do meu arquivo txt, ex, na primiera linha terá id;nome e a nas linhas de baixo terá, 1;geovanni;unip, essa função vai pular o id;nome e seguir apenas com as linhas de baixo
                    //a função fgets le apenas a primeira linha de um arquivo
                    
                    if (strcmp(escolhaMateria, "1") == 0)
                    {
                        printf("ta\n");
                        encontrou = 1;

                        while (fgets(linha, sizeof(linha), pim01) != NULL)
                        {
                            printf("%s", linha);
                        }
                        

                    }else if ((strcmp(escolhaMateria, "2") == 0) || (strcmp(escolhaMateria, "portugues") == 0))
                    {
                        printf("\nRelatorio de portugues:\n");
                        encontrou = 1;
                        
                        fgets(linha02, sizeof(linha02), pim02);//pular o cabeçalho
                        while (fgets(linha02, sizeof(linha02), pim02) != NULL)
                        {
                            linha02[strcspn(linha02, "\n")] = '\0';
                           

                            sscanf(linha02, "%[^;];%[^;];%[^;];%f;%f,%f,%f", nome, turma, teste, materia, &n1, &n2, &n3, &nota);                             
                            printf("\n------------------\n");
                            printf("Nome: %s\n", nome);
                            printf("Materia: %s\n", materia);
                            printf("Notas: %.1f %.1f %.1f\n", n1, n2, n3);
                            printf("Media: %.1f\n", (n1 + n2 + n3) / 3);
                            printf("------------------\n");
                            encontrou = 1;
                        }
                        
                    }else if (strcmp(escolhaMateria, "3") == 0)
                    {
                        printf("ataaaaa\n");
                        encontrou = 1;
                        fgets(linha03, sizeof(linha03), pim03);
                        while (fgets(linha03, sizeof(linha03), pim03) != NULL)
                        {
                            linha03[strcspn(linha03, "\n")] = '\0';
                           

                            sscanf(linha03, "%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, materia, &n1, &n2, &n3, &nota);
                                                        
                            printf("\n------------------\n");
                            printf("Nome: %s\n", nome);
                            printf("Materia: %s\n", materia);
                            printf("Notas: %.1f %.1f %.1f\n", n1, n2, n3);
                            printf("Media: %.1f\n", (n1 + n2 + n3) / 3);
                            printf("------------------\n");
                            encontrou = 1;
                        }
                    }
                    

                    if (encontrou == 0) {
                        printf("Nenhum aluno encontrado para a materia '%s'.\n", escolhaMateria);
                    }

                    printf("Deseja buscar outra materia? Digite 1 para SIM ou 0 para NAO: ");
                    scanf("%d", &novamente);

                } while (novamente == 1);
                break;

            case '0':
                dnv = 0;//se no menu eu escolher 0, a sistema sair do programa pq a variavel "dnv" estara com o valor de 0, logo ela na cai na condição do primeiro do while, como visto ali em baixo
                //caso queira testar, mude essa variavel "dnv = 0" para "dnv = 1" o loop vai continuar pq a condição ali de baixo retornou true, logo, o loop se repete
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (dnv == 1);

    fclose(pim01);
    return 0;
}
/* 
                    while (fgets(linha, sizeof(linha), pim01) != NULL) {
                        linha[strcspn(linha, "\n")] = '\0';

                        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f,%f,%f", nome, turma, teste, materia, &t, &f, &t, &nota);//essa função faz a separação dos dados e guardamos em uma variavel, a separação é feita pelo o ";". Funciona assim, leita ate encontrar um ";" e salve em uma variavel, ex, Geovanni;19,anos, Geovanni = char nome[10], 19 = int idade;. anos = char anosIdade[10];. A cada ";" é guardado uma variavel

                        if ((strcmp(escolhaMateria, materia) == 0)
                        //aq fazemos a comparação entre oq a gente escreveu na hora de escolher a materia e oq esta dentro do nosso arquivo, se estiver a materia matematica dentro do arquivo, ent aparecerá o relatorio
                            || ((strcmp(escolhaMateria, "1") == 0) && (strcmp(materia, "matematica") == 0))
                            || ((strcmp(escolhaMateria, "2") == 0) && (strcmp(materia, "portugues") == 0))
                            || ((strcmp(escolhaMateria, "3") == 0) && (strcmp(materia, "quimica") == 0))
                            //essa comparação é diferente pelo fato de nao de que, caso a gente escolha a opção 1, a comparação entre a variavel "escolhaMateria" e "materia" dará falso, pq nos escolhemos 1 e dentro da variavel "materia" tem somente os dados da materia. Entao, a comparação é a seguinte, SE a variavel "escolhaMateria" é igual a 1 E a variavel "materia" for igual a matematica, exiba o relatorio. O mesmo comportamento se aplica para as condições abaixo
                        ) {
                            printf("\n------------------\n");
                            printf("Nome: %s\n", nome);
                            printf("Materia: %s\n", materia);
                            printf("Notas: %.1f, %.1f, %.1f\n", n1, n2, n3);
                            printf("Media: %.1f\n", (n1 + n2 + n3) / 3);
                            printf("------------------\n");
                            encontrou = 1;
                        }
                    }
 */