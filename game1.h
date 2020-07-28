#pragma once
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#include<math.h>
#pragma warning(disable:4996)
#define ROW 3
#define COL 3
#define ROW1 12
#define COL1 12
#define player 'x'
#define computer 'o'
#define USER "WYG"
#define PSD "200079"
void game();//Èý×ÓÆå
void Game();//É¨À×
void GAme();//²ÂÊý×Ö
void Menu();
Init_board(char board[][COL],int row,int col);
Show_board(char board[][COL], int row, int col);
Computer(char board[][COL], int row, int col);
Judge(char board[][COL], int row, int col);
void set_mine(char board[][COL1],int row1,int col1,int *x_p,int *y_p);
void showboard(char board[][COL1], int row1, int col1);
int Getcount(char board[][COL1], int x, int y);