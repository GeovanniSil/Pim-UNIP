#include <stdio.h>
#include <string.h>

int main() {
    FILE *pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\pim01.txt", "r");//coloque o caminho onde esta salvo o seu arquivo txt e salve nele dados parecidos com esse abaixo
        /* Geovanni;4.0;5.0;8;matematica
        andrade;4.0;5.0;7.0;portugues
        geovan;4.0;5.0;7.0;matematica
        cuca;4.0;5.0;7.0;portugues
        tu;4.0;5.0;7.0;portugues
        tatu;4.0;5.0;7.0;matematica
        acdc;7.0;54.0;7.0;quimica
        guns'n rose;4.0;5.0;7.0;quimica
        ttu;4.0;5.0;7.0;matematica
        nickelback;4.0;5.0;7.0;quimica */

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
    int novamente;
    switch (escolha) {
        case '1':
            printf("Buscar por aluno ainda não implementado.\n");
            break;

        case '2': { // case 2, serve para a gente escolher qual materia queremos olhar o relatorio, ainda nao esta completo, deixarei em loop para a gente olhar quantas vezes quisermos, porem, o caminho é esse
            do
            {
            char escolhaMateria[20];
            printf("Escolha a matéria (matematica, portugues, quimica): ");
            scanf("%s", escolhaMateria);

            // validação sobre qual materia a gente quer olhar, "strcmp" é uma função que compara strings, que bem util para a gente fazer a comparação entre as materias que esta no nosso arquivo txt. Ex, se eu escolher a opção 1, será feita a verificação ali embaixo, se a variavel "escolhaMateria" for igual a 1 e a variavel "materia" for igual a "matematica", o sistema exibira o relatorio sobre a meteria escolhida. Esse comportamento serve para os outros numeros.
            //caso a gente escolha uma materia que nao esteja dentro da condição, o sistema entrará no loop, vou acrescentar uma forma de sair do programa dentro desse loop aq, caso o usuario nao queira mais olhar as notas
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

                sscanf(linha, "%[^;];%f;%f;%f;%[^;\n]", nome, &n1, &n2, &n3, materia);//essa função faz a separação dos dados e guardamos em uma variavel, a separação é feita pelo o ";". Funciona assim, leita ate encontrar um ";" e salve em uma variavel, ex, Geovanni;19,anos, Geovanni = char nome[10], 19 = int idade;. anos = char anosIdade[10];. A cada ";" é guardado uma variavel

                if ((strcmp(escolhaMateria, materia) == 0)//aq fazemos a comparação entre oq a gente escreveu na hora de escolher a materia e oq esta dentro do nosso arquivo, se estiver a materia matematica dentro do arquivo, ent aparecerá o relatorio
                || 
                ((strcmp(escolhaMateria, "1") == 0) && (strcmp(materia, "matematica") == 0))//essa comparação é diferente pelo fato de nao de que, caso a gente escolha a opção 1, a comparação entre a variavel "escolhaMateria" e "materia" dará falso, pq nos escolhemos 1 e dentro da variavel "materia" tem somente os dados da materia. Entao, a comparação é a seguinte, SE a variavel "escolhaMateria" é igual a 1 E a variavel "materia" for igual a matematica, exiba o relatorio. O mesmo comportamento se aplica para as condições abaixo
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
            printf("novamente? ");
                scanf(" %i", &novamente);
            break;
        }
    
    } 
        
        
        
    
        default:
            printf("Opção inválida.\n");
            break;
    }while (novamente == 1);

    fclose(pim01);
    return 0;
}
