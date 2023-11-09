#include <iostream>
#include <string>
#include <random>
#include <deque>
#include <conio.h>
#include <dos.h>
#include <algorithm>
#include "windows.h"
using namespace std;

// КОНСТАНТЫ

const string HELLO = "Hello it`s a Snake game)\n";
const string WIDTH_ENTER = "Please enter a width of field: ";
const string HEIGHT_ENTER = "Please enter a height of field: ";
const string GAME_OVER = "The game is over(\n    You lost";
const char SNAKE_HEAD = 'O';
const char SNAKE_BODY = 'o';
const char APPLE = '@';
const char CELL = '.';
const char SPACE = ' ';
const int DELAY = 300;

const char ESC = ']';
const char UP = 'w';
const char LEFT = 'a';
const char DOWN = 's';
const char RIGHT = 'd';


struct coordinates
{
    int x;
    int y;
};

void MoveCursor(int x, int y)
{
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void PrintField(vector<vector<char>> field)
{
    for (vector<char> i : field)
    {
        for (char j : i)
            cout << j << SPACE;
        cout << endl;
    }
    cout << endl;
}

struct vector<vector<char>> AddApple(vector<vector<char>> field, int fieldHeight, int fieldWidth)
{
    random_device random_device;        // Источник энтропии.
    mt19937 generator(random_device()); // Генератор случайных чисел.
    uniform_int_distribution<> distribution(0, fieldHeight - 1);
    uniform_int_distribution<> distributionn(0, fieldWidth - 1);
    int x;
    int y;
    do
    {
        x = distributionn(generator);
        y = distribution(generator);
    } while (field[x][y] != CELL);

    field[x][y] = APPLE;
    return(field);
};

struct deque<coordinates> SnakeMove(deque<coordinates> positions, char direction, vector<vector<char>> field, bool& play)
{
    coordinates coord;
    if (direction == UP)
    {
        coord.x = positions[0].x - 1;
        coord.y = positions[0].y;
    };
    if (direction == LEFT)
    {
        coord.x = positions[0].x;
        coord.y = positions[0].y - 1;
    };
    if (direction == DOWN)
    {
        coord.x = positions[0].x + 1;
        coord.y = positions[0].y;
    };
    if (direction == RIGHT)
    {
        coord.x = positions[0].x;
        coord.y = positions[0].y + 1;
    };

    if ((coord.x == -1) or (coord.y == -1) or (coord.x == field.size()) or (coord.y == field[0].size()) or (field[coord.x][coord.y] == SNAKE_BODY))
    {
        system("cls");
        cout << GAME_OVER << endl;
        play = false;
    }
    else
    {
        if (field[coord.x][coord.y] == APPLE)
            positions.push_back(coord);
        positions.push_front(coord);
    }
    return(positions);
};

struct vector<vector<char>> FirstSnakeDraw(vector<vector<char>> field, deque<coordinates> positions)
{
    field[positions[0].x][positions[0].y] = SNAKE_HEAD;
    for (int q = 1; q < positions.size(); q++)
        field[positions[q].x][positions[q].y] = SNAKE_BODY;
    return(field);
};

void SnakeDraw(vector<vector<char>>& field, deque<coordinates>& positions)
{
    field[positions[0].x][positions[0].y] = SNAKE_HEAD;
    for (int q = 1; q < positions.size() - 1; q++)
        field[positions[q].x][positions[q].y] = SNAKE_BODY;
    if (field[positions[positions.size() - 1].x][positions[positions.size() - 1].y] != SNAKE_HEAD)
        field[positions[positions.size() - 1].x][positions[positions.size() - 1].y] = CELL;
    positions.pop_back();
};

int main()
{
    int fieldWidth, fieldHeight;

    cout << HELLO;
    cout << WIDTH_ENTER;
    cin >> fieldWidth;
    cout << HEIGHT_ENTER;
    cin >> fieldHeight;

    // Создание поля
    vector<char> v;
    for (int j = 0; j < fieldWidth; j++)
        v.push_back(CELL);
    vector<vector<char>> field;
    for (int i = 0; i < fieldHeight; i++)
        field.push_back(v);

    deque<coordinates> snake;   // Массив с координатами змейки

    // Создание начальной змейки
    coordinates coordinates;
    coordinates.x = fieldHeight / 2;
    coordinates.y = fieldWidth / 2;
    snake.push_back(coordinates);
    coordinates.x = (fieldHeight / 2) + 1;
    snake.push_back(coordinates);

    // Добавление змейки
    field = FirstSnakeDraw(field, snake);

    // Добавление яблока
    field = AddApple(field, fieldHeight, fieldWidth);

    // Вывод поля
    system("cls");
    PrintField(field);

    int size;
    char command = UP;
    char tempCommand = UP;
    bool play = true;

    while (play)
    {
        if (_kbhit())
            tempCommand = _getch();
        if ((tempCommand == UP) or (tempCommand == LEFT) or (tempCommand == DOWN) or (tempCommand == RIGHT) or (tempCommand == ESC))
            command = tempCommand;
        if (command == ESC)
            break;

        MoveCursor(0, 0);
        size = snake.size();
        snake = SnakeMove(snake, command, field, play);
        if (play)
            SnakeDraw(field, snake);
        if (snake.size() != size)
        {
            field = AddApple(field, fieldHeight, fieldWidth);
            size = snake.size();
        }
        PrintField(field);
        Sleep(DELAY);
    }
}