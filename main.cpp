#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <conio.h>
//#include <termios.h>
//#include <unistd.h>
#include <chrono>
#include <thread>
using namespace std;

const int height=20;
const int width=20;
const int maxn=100;
int headx,heady;
char board[width][height];
int snakex[maxn],snakey[maxn];
int direction;
int foodx,foody;
int snakel;

bool foodg(int foodx,int foody,int snakel){
    for(int i=0;i<snakel;i++){
        if(foodx==snakex[i]&&foody==snakey[i]) return false;
    }
    if(foodx==headx&&foody==heady) return false;
    if(foodx==0||foodx==width-1||foody==0||foody==height-1) return false;
    return true;
}
void boardg(int foodx,int foody,int snakel){
    for(int i=1;i<width-1;i++){
        for(int j=1;j<height-1;j++){
            board[i][j]=' ';
        }
    }
    board[foodx][foody]='$';
    for(int i=0;i<snakel;i++){
        board[snakex[i]][snakey[i]]='*';
    }
}
void init(){
    headx=width/2;
    heady=height/2;
    snakex[0]=headx;
    snakey[0]=heady;
    direction=0;
    snakel=1;
    srand(time(NULL));
    while(true){
        foodx=rand()%(width);
        foody=rand()%(height);
        if(foodg(foodx,foody,snakel)) break;
    }
    for(int i=0;i<width;i++){
    for(int j=0;j<height;j++){
        if(i==0||i==width-1||j==0||j==height-1){
            board[i][j]='#';
        }
        else board[i][j]=' ';
        }
}
    boardg(foodx,foody,snakel);
}
void gameend(int tmpx,int tmpy,int snakel){
    if(tmpx==0||tmpx==width-1||tmpy==0||tmpy==height-1){
        printf("Game Over!\n");
        exit(0);
    }
    for(int i=0;i<snakel;i++){
        if(tmpx==snakex[i]&&tmpy==snakey[i]){
            printf("Game Over!\n");
            exit(0);
        }
    }
}
void draw(){
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            printf("%c",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void input(int& direction) {
    if (_kbhit()) {
        char c = _getch();
        if (c == 'w') {
            if (direction != 2) direction = 0;
        } else if (c == 'd') {
            if (direction != 3) direction = 1;
        } else if (c == 's') {
            if (direction != 0) direction = 2;
        } else if (c == 'a') {
            if (direction != 1) direction = 3;
        }
    }
}


void algorithm(int direction,int& headx,int& heady,int& snakel){
    int tmpx=headx,tmpy=heady;
    if(direction==0) tmpx--;
    else if(direction==1) tmpy++;
    else if(direction==2) tmpx++;
    else if(direction==3) tmpy--;

    gameend(tmpx,tmpy,snakel);

    if(foodx==tmpx&&foody==tmpy){
        snakel++;
        for(int i=snakel-1;i>=1;i--){
            snakex[i]=snakex[i-1];
            snakey[i]=snakey[i-1];
        }
        snakex[0]=tmpx;
        snakey[0]=tmpy;
        headx=tmpx;
        heady=tmpy;
        while (true) {
            foodx = rand() % width;
            foody = rand() % height;
            if (foodg(foodx, foody, snakel)) break;
        }
    }
    else{
        for(int i=snakel-1;i>=1;i--){
            snakex[i]=snakex[i-1];
            snakey[i]=snakey[i-1];
        }
        snakex[0]=tmpx;
        snakey[0]=tmpy;
        headx=tmpx;
        heady=tmpy;
    }
}



int main(){

    init();
    while(true){
        draw();
        input();
        algorithm(direction,headx,heady,snakel);
        boardg(foodx,foody,snakel);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");
    }



    return 0;
}
