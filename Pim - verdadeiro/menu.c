#include <stdio.h>

int main(){
    FILE * pim01;
    pim01 = fopen("C:\\Users\\adilsondias\\OneDrive\\Desktop\\filtroAluno.txt", "r");

    int escolha = 2;
    switch (escolha)
    {
    case 1: //escolher qual aluno quer olhar
        printf("ok");
        break;
    case 2://escolher ver as notas por materias
        printf("ta");
        break;

    
    default:
        break;
    }
 
}