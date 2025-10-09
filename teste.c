/* #include <stdio.h>
#include <string.h>

int main(){

    char texto[40];

    
        printf("teste validação por numero e texto ");
        scanf("%s", texto);

        

    while ((strcmp(texto, "1") != 0) && (strcmp(texto, "geo") != 0) && (strcmp(texto, "quimica") != 0))
    {
        printf("erro\n");
        printf("teste validação por numero e texto ");
        scanf("%s", texto);
    }
    

        if ((strcmp(texto, "1") == 0) || (strcmp(texto, "geo") == 0) || (strcmp(texto, "quimica") == 0))
        {
            printf("deu certo");

        }else  
            printf("erro");
        
    
    

} */

#include <stdio.h>
#include <string.h>

int main(){
    FILE * pim01;
    pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\pim01.txt", "r");//colocar o caminho que esta salvo o seu txt

    if (pim01 == NULL)
    {
        printf("erro");
    }
    
    char escolha[15];
    //int resultado;
    printf("Qual materia voce deseja visualizar as notas, 1 [Mate] 2 [Port] 3 [Quimica]\n");
    //resultado = 
    scanf("%s", escolha);
    while (strcmp(escolha, "1") != 0
        && strcmp(escolha, "mate") != 0
        && strcmp(escolha, "2") != 0
        && strcmp(escolha, "portugues") != 0
        && strcmp(escolha, "3") != 0
        && strcmp(escolha, "quimica") != 0
    ) //essa parte faz a filtragem das materias que eu quero ver, com o usuario digitando numero ou letra, vai ser verdadeira a condição
        //int resultado, resultado == scanf("%d", &escolha); e resultado != 1, serve para verificar se o usuario digitou alguma letra, se ele digitou, cai no loop e pede para ele digitar novamente
    {
        while (getchar() != '\n');
        printf("Materia nao encontrada, tente novamente: ");
        scanf("%s", escolha);
    }
     
    

    char nome[40];/* 
    fscanf(pim01, "%s", nome);
    printf("%s\n", nome); */
    char linha[100];
    float t;
    char g[10];
    float f;
    char materia[100];
    int encontrou = 0; // serve para verificar se a materia que a gente escolher existe dentro do arquivo txt, ex o usuário escolheu “química” ✅, mas o arquivo não tem nenhuma linha com “química”, então o programa deve mostrar algum alerta

    while (fgets(linha, sizeof(linha), pim01) != NULL)
    {
      //  printf("%s", nome);
        linha[strcspn(linha, "\n")] = '\0';//serve para limpar o enter que fica, as vezes nao entrara na condição ali de baixo pelo fato de o arquivo estar indo com o \n, e a condição é "geovannisilva" porem, o fgets esta lendo "geovannisilva\n", a função serve para tirar esse \n do texto
        //sscanf(linha, "%s %s %s %s %s", nome, t, g, f, materia);
        sscanf(linha, "%[^;];%f;%[^;];%f;%[^;]", nome, &t, g, &f, materia);

        if ((strcmp(escolha, "1") == 0 && strcmp(materia, "matematica") == 0 || strcmp(escolha, "mate") == 0 && strcmp(materia, "matematica") == 0) )
        {
            float media = t + f;
            //dps apague essa variavel acima e o ultimo print da media, isso é apenas um teste sobre a media, preciso confimar se eu vou fazer o calculo da media ou o python     
            printf("------------------\n");
            printf("Nome: %s\n", nome);
            printf("Materia: %s\n", materia);
            printf("Nota: %.1f\n", f);
            printf("------------------\n");
            printf("sua media é %f", media);
            encontrou = 1;
            // serve para verificar se a materia que a gente escolher existe dentro do arquivo txt, ex o usuário escolheu “química” ✅, mas o arquivo não tem nenhuma linha com “química”, então o programa deve mostrar algum alerta

            //caso a condição que esta dentro do laço for verdadeira, vai executar o bloco de codigo que esta abaixo, sendo assim, mundando a variavel "encontrou para 1", fazendo com que qnd a condição for falsa, ela nao será alterada e ficará com o mesmo valor. Sendo assim, entrará na condição de "encontrou = 0" la embaixo, se for verdadeira, printara o texto 

        }
        else if ((strcmp(escolha, "2") == 0 && strcmp(materia, "portugues") == 0) || strcmp(escolha, "portugues") == 0 && strcmp(materia, "portugues") == 0)
        {
                    
            printf("------------------\n");
            printf("Nome: %s\n", nome);
            printf("Materia: %s\n", materia);
            printf("Nota: %s\n", f);
            printf("------------------\n");
            encontrou = 1;// serve para verificar se a materia que a gente escolher existe dentro do arquivo txt, ex o usuário escolheu “química” ✅, mas o arquivo não tem nenhuma linha com “química”, então o programa deve mostrar algum alerta

        }else if ((strcmp(escolha, "3") == 0 && strcmp(materia, "quimica") == 0) || strcmp(escolha, "quimica") == 0 && strcmp(materia, "quimica") == 0)
        {
            printf("------------------\n");
            printf("Nome: %s\n", nome);
            printf("Materia: %s\n", materia);
            printf("Nota: %s\n", f);
            printf("------------------\n");
            encontrou = 1;// serve para verificar se a materia que a gente escolher existe dentro do arquivo txt, ex o usuário escolheu “química” ✅, mas o arquivo não tem nenhuma linha com “química”, então o programa deve mostrar algum alerta

        }
        
    }
    if (encontrou == 0) {
    printf("------------------------------\n");
    printf("Nenhuma nota encontrada para a\nmateria desejada.\n");//caso a condição que esta dentro do laço for verdadeira, vai executar o bloco de codigo que esta abaixo, sendo assim, mundando a variavel "encontrou para 1", fazendo com que qnd a condição for falsa, ela nao será alterada e ficará com o mesmo valor. Sendo assim, entrará na condição de "encontrou = 0" la embaixo, se for verdadeira, printara o texto 
    }
    
    fclose(pim01);

    printf("testanto o o Git, sempre esqueço como usar esse trem :0");
    return 0;
}


