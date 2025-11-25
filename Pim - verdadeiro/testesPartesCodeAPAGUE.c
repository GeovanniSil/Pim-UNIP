#include <stdio.h>

int main(){

   
    int teste = 1;

    while (teste)
    {
        int buscarNovamente;
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
                if (buscarNovamente == 1)
                {
                    printf("teste\n");
                }
                
        //teste = 0;
        break;

    }
    
}