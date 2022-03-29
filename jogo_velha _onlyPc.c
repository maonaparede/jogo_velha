#include <stdio.h>

    int jogada_usuario(int lin, int col, char jog);
    void jogada_computador(char jog, int nivel);
    int alternar_usuario(char jog);
    int menu();
    void escolha_simb(char *jog1, char *jog2);
    void inicializa_velha();
    int verifica_ganhador(char jog);
    int verifica_jogada_valida(int lin, int col);
    void desenhar();

    int max(int a, int b);
    int min(int a, int b);
    int empatou();
    int minimax(int profundidade , char jog);
    void achaMelhorMov(int *lin, int *col, char jog);
    evaluate(char b[3][3]);

    char matriz[3][3] = {
        {'X', '-', 'X'},
        {'-', '-', '-'},
        {'O', '-', 'O'}
         };
    char vazio = '-';
    char jog1 = 'X';
    char jog2 = 'O';
    char jog_atual = ' ';

void main(){

    //modo_computador();
    int lin, col;
    lin = 0;
    col = 0;
    achaMelhorMov(&lin, &col, jog1);
}

int verifica_ganhador(char jog){
    //linhas
    for(int i = 0; i < 3; i++){
        if(matriz[i][0] == matriz[i][1] && matriz[i][2] == matriz[i][0] && matriz[i][0] == jog){
            return 1;
        }
    }
    //colunas
    for(int i = 0; i < 3; i++){
        if(matriz[0][i] == matriz[1][i] && matriz[2][i] == matriz[0][i] && matriz[0][i] == jog){
            return 1;
        }
    }
    //diagonais
    if(matriz[0][0] == matriz[1][1] && matriz[2][2] == matriz[0][0] && matriz[0][0] == jog){return 1;}
    if(matriz[0][2] == matriz[1][1] && matriz[2][0] == matriz[0][2] && matriz[0][2] == jog){return 1;}

    return 0;
}


void achaMelhorMov(int *lin, int *col, char jog){

    int profundidade = 0;
    int melhorPont = -100;
    *lin = 0;
    *col = 0;

     for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(matriz[i][j]==vazio){

                    matriz[i][j] = jog2;
                    int pontos = minimax(profundidade, jog1);
                    matriz[i][j] = vazio;

                    if(pontos >= melhorPont){
                        *lin = i;
                        *col = j;
                         printf("\n melho pont %d %d %d %d %d\n", *lin, *col, pontos, i ,j);
                        melhorPont = pontos;
                    }
                }

            }
        }
    printf("O melhor mov e : %d %d", *lin, *col);
}

int minimax(int profundidade , char jog){


    int score = evaluate(matriz);

    printf("\n profundidade %d \n", profundidade);
    if (score == 10){
            printf("\nteste 10\n");
        return score - profundidade;
    }


    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10){
            printf("\nteste\n");
        return score + profundidade;
    }


    if(empatou()){
        return 0;
    }


    if(jog == jog2){
        int melhorPontos = -1000;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(matriz[i][j] == vazio){

                    matriz[i][j] = jog2;
                    melhorPontos = max(melhorPontos , minimax(profundidade + 1, jog1));
                    matriz[i][j] = vazio;
                }
            }
        }
        return melhorPontos;
    }
    //troca de turno
    else
    {
        int melhorPontos = 1000;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(matriz[i][j] == vazio){

                    matriz[i][j] = jog1;
                    melhorPontos = min(melhorPontos , minimax(profundidade + 1, jog2));
                    matriz[i][j] = vazio;
                }
            }
        }
        return melhorPontos;
    }//*/
}

int empatou(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(matriz[i][j] != vazio){
              return 0;
            }
        }
    }
    return 1;
}

int min(int a, int b){
    return (a > b) ? b : a;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

void desenhar(){
    //system("cls");
    printf("\n\n =========== Jogo da Velha ===========\n\n");
    printf("\n  %c | %c | %c \n", matriz[0][0], matriz[0][1], matriz[0][2]);
    printf(" -----------");
    printf("\n  %c | %c | %c \n", matriz[1][0], matriz[1][1], matriz[1][2]);
    printf(" -----------");
    printf("\n  %c | %c | %c \n", matriz[2][0], matriz[2][1], matriz[2][2]);
}

int evaluate(char b[3][3])
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row<3; row++)
    {
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==jog1)
                return +10;
            else if (b[row][0]==jog2)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==jog1)
                return +10;

            else if (b[0][col]==jog2)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==jog1)
            return +10;
        else if (b[0][0]==jog2)
            return -10;
    }

    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==jog1)
            return +10;
        else if (b[0][2]==jog2)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}
