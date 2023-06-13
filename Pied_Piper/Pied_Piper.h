#pragma once
#include<stdio.h>
#include <stdlib.h>
#include<Windows.h>
#include<conio.h>
#include <time.h>
#include<math.h>
#include <process.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>


void main();

void showScore(int);
enum Color
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

//Ű���� ����
#define UP  10
#define DOWN  11
#define RIGHT  13
#define LEFT  14
#define SPACE 15
#define ESC 27

