#include <stdio.h>
#include <string.h>


int main(){
    FILE * pim01;
    pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\pim01.txt", "r");

    if (pim01 == NULL)
    {
        printf("erro");
    }
    
    int escolha;
    int resultado;
    printf("Qual materia voce deseja visualizar as notas, 1 [Mate] 2 [Port] 3 [Quimica]\n");
    resultado = scanf("%d", &escolha);
    while (resultado != 1 && (escolha != 1 && escolha !=2 && escolha != 3)) //int resultado, resultado == scanf("%d", &escolha); e resultado != 1, serve para verificar se o usuario digitou alguma letra, se ele digitou, cai no loop e pede para ele digitar novamente
    {
        while (getchar() != '\n');
        printf("Materia nao encontrada, tente novamente: ");
        scanf(" %d", &escolha);
    }
     
    char nome[40];/* 
    fscanf(pim01, "%s", nome);
    printf("%s\n", nome); */
    char linha[100];
    char t[10];
    char g[10];
    char f[10];
    char materia[20];
    //int encontrou = 0;

    while (fgets(linha, sizeof(linha), pim01) != NULL)
    {
      //  printf("%s", nome);
        linha[strcspn(linha, "\n")] = '\0';//serve para limpar o enter que fica, as vezes nao entrara na condição ali de baixo pelo fato de o arquivo estar indo com o \n, e a condição é "geovannisilva" porem, o fgets esta lendo "geovannisilva\n", a função serve para tirar esse \n do texto
        sscanf(linha, "%s %s %s %s %s", nome, t, g, f, materia);
        if ((escolha == 1 && strcmp(materia, "matematica") ==0) || 
        (escolha == 2 && strcmp(materia, "portugues") == 0) || (escolha == 3 && strcmp(materia, "quimica") == 0))
        {
            printf("------------------\n");
            printf("Nome: %s\n", nome);
            printf("Materia: %s\n", materia);
            printf("Nota: %s\n", f);
            printf("------------------\n");
        }
    }
    
    fclose(pim01);
    return 0;
}


