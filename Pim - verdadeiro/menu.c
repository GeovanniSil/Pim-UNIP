#include <stdio.h>
#include <string.h>

int main() {
    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Algoritmos_e_Estruturas_de_Dados_em_Python.csv", "r");
    FILE *pim02 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Analise_e_Projeto_de_Sistemas.csv", "r");
    FILE *pim03 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Engenharia_de_Software_Agil.csv", "r");
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
        int escolha;
        printf("=====================================\n");
        printf("        RELATORIO DE NOTAS - UNIP      \n");
        printf("=====================================\n");
        printf("Selecione uma opcao:\n");
        printf("  [1] Buscar por aluno\n");
        printf("  [2] Buscar por materia\n");
        printf("  [0] Sair\n");
        printf("Digite sua escolha: ");

        scanf(" %i", &escolha);
        if (escolha != 1) {
            printf("Entrada inválida! Digite um número.\n");

            // Limpar o buffer
            while (getchar() != '\n'); // descarta até o Enter
            //continue; // volta pro início do loop
        }

        char linha[100];//variavel onde esta sendo salvo os dados do arquivo "pim01"
        char linha02[100];//variavel onde esta sendo salvo os dados do arquivo "pim02"
        char linha03[100];//variavel onde esta sendo salvo os dados do arquivo "pim03"
        char nome[40];
        char materia[40];
        float n1 = 0, n2 = 0, n3;
        int encontrou = 0;
        int novamente;
        char turma[20];
        char nomeAluno[20];
        float t, f, nota;
        char escolhaMateria[20];//
        int escolhaMateriaAluno;//
        //int escolhaMateriaAluno;
        int testeSub;
        char raAluno[10];
        switch (escolha) {
            case 1:
                            
                printf("Busca por aluno.\n");
                do{
                printf("Deseja fazer uma busca por todas as meterias ou somente uma?\n");
                printf(" [1] Materia especifica\n");
                printf(" [2] Geral\n");
                scanf("%i", &escolhaMateriaAluno);

                switch (escolhaMateriaAluno)
                {
                case 1:
                    printf("Escolha uma materia:\n");
                    printf("[1] Algoritmos_e_Estruturas_de_Dados_em_Python\n");
                    scanf("%i", &escolhaMateriaAluno);

                    if (escolhaMateriaAluno == 1)
                    {
                        printf("Algoritmos_e_Estruturas_de_Dados_em_Python\n");
                        printf("digite o nome dele: ");
                        fgets(linha, sizeof(linha), pim01);
                        rewind(pim01);
                        scanf("%s", nomeAluno);
                        while (fgets(linha, sizeof(linha), pim01) != NULL)
                        {
                            sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, raAluno, materia, &n1, &n2, &n3, &nota);
                            if (strcmp(nomeAluno, nome) == 0)
                            {
                                printf("deu certo\n");  
                                encontrou = 1;// A variável "encontrou" funciona como uma flag, assim que eu encontro oq eu quero, ela muda para 1 e nao vai para a condição ali de baixo fora do while que esta lendoo arquivo. 
                                            // Ela começa com valor 0 e muda para 1 quando o aluno é encontrado, isso significa que deu certo na nossa procura. Caso nao achar nada, a variavel vai continuar 0 (pq eu a iniciei como zero no começo do codigo) e vai entrar na condição ali de baixo 
                                            // eu nao coloco esse if de baixo pq ele vai printar toda hora que o while passar por uma linha e a condição do if de cima nao for satisfeita, vai printar "aluno nao encontrado" todas as vezes que ele passar por uma linha e nao encontrar o aluno que eu quero saber
                                
                            }    
                        }
                        if (encontrou == 0)
                        {
                            printf("aluno nao encontrado para essa materia\n");
                        }
                        
                    }
 
                    printf("Deseja buscar outro aluno? Digite 1 para SIM ou 0 para NAO: ");
                    scanf("%i", &novamente);
                    
                    if (novamente == 0)
                        break;

                    while (novamente != 1)
                    {
                        printf("Escolha errada, digite novamente: ");//força o usuario digitar 1 ou 0, para continuar ou sair do menu de relatorio
                        scanf("%i", &novamente);
                        while (getchar() != '\n'); // essa função faz a limpeza do buffer, caso o usuario digitar uma letra nessa validação o programa vai entrar em um loop eterno, pq o programa esta esperando um int e nao um char, ai essa variavel fazer a limpeza para nao ocorrer o loop
                        continue;
                    }
                    break;
                case 2:
                    printf("ainda nao imprementando\n");
                    printf("Deseja buscar outro aluno? Digite 1 para SIM ou 0 para NAO: ");
                    scanf("%i", &novamente);
                    
                    if (novamente == 0)
                        break;

                    while (novamente != 1)
                    {
                        printf("Escolha errada, digite novamente: ");//força o usuario digitar 1 ou 0, para continuar ou sair do menu de relatorio
                        scanf("%i", &novamente);
                        while (getchar() != '\n'); // essa função faz a limpeza do buffer, caso o usuario digitar uma letra nessa validação o programa vai entrar em um loop eterno, pq o programa esta esperando um int e nao um char, ai essa variavel fazer a limpeza para nao ocorrer o loop
                        continue;
                    }
                default:
                    break;
                }
                }while (novamente == 1);
                
                
                

                /* printf("Escolha uma materia:\n");
                printf("[1] Algoritmos_e_Estruturas_de_Dados_em_Python\n");
                //scanf("%s", escolhaMateriaAluno); */
                    
                    /* if (strcmp(escolhaMateriaAluno, "1") == 0)
                    {
                        printf("nome do aluno? ");
                        scanf("%s", nomeAluno);
                        fgets(linha, sizeof(linha), pim01);
                        rewind(pim01);//A função rewind(arquivo); reposiciona o ponteiro de leitura/escrita do arquivo para o início. Ou seja: depois de ler o arquivo até o fim (ou parte dele), o ponteiro está “lá embaixo”.O rewind() faz ele voltar para o começo — como se você estivesse rebobinando uma fita.
                        //semelhante ao fseek(pim01, 0, SEEK_SET); que usamo ali em baixo                        
                        while (fgets(linha, sizeof(linha), pim01) != NULL)
                        {
                            sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, raAluno, materia, &n1, &n2, &n3, &nota);
                            if (strcmp(nomeAluno, nome) == 0)
                            {
                                printf("deu certo\n");  
                                encontrou = 1;// A variável "encontrou" funciona como uma flag, assim que eu encontro oq eu quero, ela muda para 1 e nao vai para a condição ali de baixo fora do while que esta lendoo arquivo. 
                                            // Ela começa com valor 0 e muda para 1 quando o aluno é encontrado, isso significa que deu certo na nossa procura. Caso nao achar nada, a variavel vai continuar 0 (pq eu a iniciei como zero no começo do codigo) e vai entrar na condição ali de baixo 
                                            // eu nao coloco esse if de baixo pq ele vai printar toda hora que o while passar por uma linha e a condição do if de cima nao for satisfeita, vai printar "aluno nao encontrado" todas as vezes que ele passar por uma linha e nao encontrar o aluno que eu quero saber
                                //break;
                            }    
                        }
                        rewind(pim02);//A função rewind(arquivo); reposiciona o ponteiro de leitura/escrita do arquivo para o início. Ou seja: depois de ler o arquivo até o fim (ou parte dele), o ponteiro está “lá embaixo”.O rewind() faz ele voltar para o começo — como se você estivesse rebobinando uma fita.
                        //semelhante ao fseek(pim01, 0, SEEK_SET); que usamo ali em baixo 
                        fgets(linha02, sizeof(linha02), pim02);
                        while (fgets(linha02, sizeof(linha02), pim02) != NULL)
                        {
                            sscanf(linha02, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, raAluno, materia, &n1, &n2, &n3, &nota);
                            if (strcmp(nomeAluno, nome) == 0)
                            {
                                printf("deu certo\n");  
                                encontrou = 1;// A variável "encontrou" funciona como uma flag, assim que eu encontro oq eu quero, ela muda para 1 e nao vai para a condição ali de baixo fora do while que esta lendoo arquivo. 
                                            // Ela começa com valor 0 e muda para 1 quando o aluno é encontrado, isso significa que deu certo na nossa procura. Caso nao achar nada, a variavel vai continuar 0 (pq eu a iniciei como zero no começo do codigo) e vai entrar na condição ali de baixo 
                                            // eu nao coloco esse if de baixo pq ele vai printar toda hora que o while passar por uma linha e a condição do if de cima nao for satisfeita, vai printar "aluno nao encontrado" todas as vezes que ele passar por uma linha e nao encontrar o aluno que eu quero saber
                            }    
                        }
                        if (encontrou == 0)
                        {
                            printf("aluno nao encontrado");
                        }
                    } */
                   
            break;                                
            case 2:// case 2, serve para a gente escolher qual materia queremos olhar o relatorio, ainda nao esta completo, deixarei em loop para a gente olhar quantas vezes quisermos, porem, o caminho é esse
                do {
                    fseek(pim01, 0, SEEK_SET);
                    fseek(pim02, 0, SEEK_SET);
                    fseek(pim03, 0, SEEK_SET);
                    encontrou = 0;
                    int contadorAlunos = 0;
                    printf("\nEscolha uma materia:\n");
                    printf("  [1] Algoritmos_e_Estruturas_de_Dados_em_Python\n");
                    printf("  [2] Analise_e_Projeto_de_Sistemas\n");
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
                    
                    //essa função pula o cabeçalho do meu arquivo txt, ex, na primiera linha terá id;nome e a nas linhas de baixo terá, 1;geovanni;unip, essa função vai pular o id;nome e seguir apenas com as linhas de baixo
                    //a função fgets le apenas a primeira linha de um arquivo
                    
                    if ((strcmp(escolhaMateria, "1") == 0) || (strcmp(escolhaMateria, "Algoritmos_e_Estruturas_de_Dados_em_Python") == 0))
                    {
                        printf("\nRelatorio de Algoritmos_e_Estruturas_de_Dados_em_Python:\n");
                        fgets(linha, sizeof(linha), pim01);//essa função pula o cabeçalho do meu arquivo txt, ex, na primiera linha terá id;nome e a nas linhas de baixo terá, 1;geovanni;unip, essa função vai pular o id;nome e seguir apenas com as linhas de baixo
                        //a função fgets le apenas a primeira linha de um arquivo
                        while (fgets(linha, sizeof(linha), pim01) != NULL)
                        {
                            linha[strcspn(linha, "\n")] = '\0';//serve para limpar o enter que fica, as vezes nao entrara na condição ali de baixo pelo fato de o arquivo estar indo com o \n, e a condição é "geovannisilva" porem, o fgets esta lendo "geovannisilva\n", a função serve para tirar esse \n do texto

                            sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, raAluno, materia, &n1, &n2, &n3, &nota);
                                  
                            printf("\n------------------\n");
                            printf("Nome: %s\n", nome);
                            printf("Materia: %s\n", materia);
                            printf("Notas: %.1f %.1f %.1f\n", n1, n2, n3);
                            printf("Media: %.1f\n", (n1 + n2 + n3) / 3);
                            printf("------------------\n");
                            encontrou = 1;
                            contadorAlunos ++;
                        }
                        printf("\nTotal de alunos encontrados para essa materia: %i\n", contadorAlunos);
                        
                    }else if ((strcmp(escolhaMateria, "2") == 0) || (strcmp(escolhaMateria, "portugues") == 0))
                    {
                        printf("\nRelatorio de Analise e Projeto de Sistemas:\n");
                        
                        fgets(linha02, sizeof(linha02), pim02);//pular o cabeçalho
                        while (fgets(linha02, sizeof(linha02), pim02) != NULL)
                        {
                            linha02[strcspn(linha02, "\n")] = '\0';//serve para limpar o enter que fica, as vezes nao entrara na condição ali de baixo pelo fato de o arquivo estar indo com o \n, e a condição é "geovannisilva" porem, o fgets esta lendo "geovannisilva\n", a função serve para tirar esse \n do texto
                           

                            sscanf(linha02, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, raAluno, materia, &n1, &n2, &n3, &nota);      
                            printf("\n------------------\n");
                            printf("Nome: %s\n", nome);
                            printf("Materia: %s\n", materia);
                            printf("Notas: %.1f %.1f %.1f\n", n1, n2, n3);
                            printf("Media: %.1f\n", nota);
                            printf("------------------\n");
                            encontrou = 1;
                            contadorAlunos ++;
                        }
                        printf("\nTotal de alunos encontrados para essa materia: %i\n", contadorAlunos);

                    }else if (strcmp(escolhaMateria, "3") == 0)
                    {
                        printf("\nRelario de \n");
                        fgets(linha03, sizeof(linha03), pim03);
                        //int contadorAlunos = 0;//se eu cololocar essa variavel dentro do loop while, ela sempre vai voltar a ser 0 e nao fará a logica que eu quero, que no caso seria a cada aluno achado, incrementar 1 a variavel contador, isso é para a gente saber quantos alunos tem em cada relatorio. Vou inicializar essa variavel
                        while (fgets(linha03, sizeof(linha03), pim03) != NULL)
                        {    
                            linha03[strcspn(linha03, "\n")] = '\0';//serve para limpar o enter que fica, as vezes nao entrara na condição ali de baixo pelo fato de o arquivo estar indo com o \n, e a condição é "geovannisilva" porem, o fgets esta lendo "geovannisilva\n", a função serve para tirar esse \n do texto
                            sscanf(linha03, "%[^;];%[^;];%[^;];%[^;];%f;%f;%f;%f", nome, turma, raAluno, materia, &n1, &n2, &n3, &nota);
                            printf("\n------------------\n");
                            printf("Nome: %s\n", nome);
                            printf("Materia: %s\n", materia);
                            printf("Notas: %.1f %.1f %.1f\n", n1, n2, n3);
                            printf("Media: %.1f\n", nota);
                            printf("------------------\n");
                            encontrou = 1;
                            contadorAlunos ++;
                        }
                        printf("\nTotal de alunos encontrados para essa materia: %i\n", contadorAlunos);
                    }
                    
                    if (encontrou == 0) {
                        printf("Nenhum aluno encontrado para esta materia .\n");
                    }

                    printf("Deseja buscar outra materia? Digite 1 para SIM ou 0 para NAO: ");
                    scanf("%i", &novamente);
                    
                    if (novamente == 0)
                        break;

                    while (novamente != 1)
                    {
                        printf("Escolha errada, digite novamente: ");//força o usuario digitar 1 ou 0, para continuar ou sair do menu de relatorio
                        scanf("%i", &novamente);
                        while (getchar() != '\n'); // essa função faz a limpeza do buffer, caso o usuario digitar uma letra nessa validação o programa vai entrar em um loop eterno, pq o programa esta esperando um int e nao um char, ai essa variavel fazer a limpeza para nao ocorrer o loop
                        continue;
                    }

                } while (novamente == 1);
            break;

            case 0:
                dnv = 0;//se no menu eu escolher 0, a sistema sair do programa pq a variavel "dnv" estara com o valor de 0, logo ela na cai na condição do primeiro do while, como visto ali em baixo
                //caso queira testar, mude essa variavel "dnv = 0" para "dnv = 1" o loop vai continuar pq a condição ali de baixo retornou true, logo, o loop se repete
                printf("Saindo do sistema...\n");
            break;

            //default:
                //printf("Opcao invalida. Tente novamente.\n");
        }

    } while (dnv == 1);// caso a gente escolher olhar novamente os relatorio, a variavel pássara a ser 1 e vai satisfazer a condição, fazendo com que o loop se repita e mostre novamente o menu de relatorio

    fclose(pim01);
    fclose(pim02);
    fclose(pim03);
    return 0;
    //system("pause");
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