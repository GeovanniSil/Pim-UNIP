#include <stdio.h>

int main(){

    FILE *pim04 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Progamacao_Estruturada_em_C.csv", "r");
//("C:\\Users\\adilsondias\\OneDrive\\Desktop\\Pim\\Pim-UNIP\\Engenharia_de_Software_Agil.csv", "r");

    char nada[40];

    fgets(nada, sizeof(nada), pim04);


    while (fgets(nada, sizeof(nada), pim04) != NULL)
    {
        printf("%s\n", nada);
    }
    
}