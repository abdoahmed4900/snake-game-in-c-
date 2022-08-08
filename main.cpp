#include <iostream>

#include <conio.h>

#include <ctime>

#include <windows.h>

using namespace std;

enum Direction { Top = 1, Down, Left, Right};

struct Snake{int headX;int headY;int tail_N;int tail_X[50];int tail_Y[50];Direction dir;};

struct Player{bool isOver;int score;};

struct Board{int width;int height;};

struct Food{int fruitX;int fruitY;bool isEaten;};

struct Board board;

struct Food food;

struct Snake snake;

struct Player player;

void generateFruit(){

    srand (time(NULL));

    food.fruitX = rand() % (board.width - 2) + 1 ;

    food.fruitY = rand() % (board.height - 2) + 1 ;

}

void shift_snake(int arr[],int length){

    for(int i = length - 2 ; i >= 0 ; i--){
        arr[i + 1] = arr[i];
    }

}

void setUp(){

    board.width = 50;

    board.height = 20;

    snake.headX = board.width / 2 ;

    snake.headY = board.height / 2 ;

    snake.tail_N = 0;

    snake.dir = Down;

    player.isOver = false;

    player.score = 0;

    food.isEaten = false;

    generateFruit();

}

void drawBoard(){

    system("cls");

    for(int i = 0 ; i < board.height ; i++){
        for(int x = 0 ; x < board.width ; x++){
            if(x == 0 || x == board.width - 1 || i == 0 || i == board.height - 1)
                cout << "*" ;
            else if(x == snake.headX && i == snake.headY)
                cout << "0" ;
            else if(x == food.fruitX && i == food.fruitY)
                cout << "$" ;
            else{
               bool printed = false;
               for(int z = 0 ; z < snake.tail_N ; z++){
                if(snake.tail_X[z] == x && snake.tail_Y[z] == i){
                    cout << "o" ;
                    printed = true;
                }
               }
               if(!printed) cout << " " ;
            }

        }
        cout << endl ;
    }

    cout << "Score : " << player.score ;

}

void input(){

    if(_kbhit()){
        char input = _getch();
        if(input == 'w' || input == 'W'){
           snake.dir = Top;
        }else if(input == 'S' || input == 's'){
            snake.dir = Down;
        }else if(input == 'A' || input == 'a'){
            snake.dir = Left;
        }else if(input == 'D' || input == 'd'){
            snake.dir = Right;
        }else if(input == 'X' || input == 'x'){
            exit(0);
        }
    }

}

void logic(){

    shift_snake(snake.tail_X,50);
    shift_snake(snake.tail_Y,50);

    snake.tail_X[0] = snake.headX;
    snake.tail_Y[0] = snake.headY;

    if(snake.dir == Top){
        snake.headY--;
    }else if(snake.dir == Down){
        snake.headY++;
    }else if(snake.dir == Left){
        snake.headX--;
    }else if(snake.dir == Right){
        snake.headX++;
    }

    if(snake.headX == food.fruitX && snake.headY == food.fruitY){
        player.score++;
        snake.tail_N++;
        generateFruit();
    }

    for(int i = 0 ; i < snake.tail_N ; i++){
        if(snake.headX == snake.tail_X[i] && snake.headY == snake.tail_Y[i])
            player.isOver = true;
    }

}

int main()
{
    setUp();
    while(!player.isOver){
        drawBoard();
        input();
        logic();
        Sleep(60);
    }
    return 0;
}
