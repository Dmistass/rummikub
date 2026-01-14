#include <iostream> // Подключение библиотеки для консольного ввода-вывода
#include <cstdlib>  // Подключение библиотеки для генерации случайных чисел и управления памятью

using namespace std; // Использование пространства имен std

// Глобальные указатели для динамических массивов
int* pool_val = NULL;     // Значения плиток в колоде (1-13)
int* pool_col = NULL;     // Цвета плиток в колоде (0-3)
bool* pool_jok = NULL;    // Флаги джокеров в колоде
int poolSize = 106;       // Текущее количество плиток в пуле

int** hand_val = NULL;    // Значения плиток в руках игроков [игрок][плитка]
int** hand_col = NULL;    // Цвета плиток в руках игроков
bool** hand_jok = NULL;   // Флаги джокеров в руках игроков
int* handCount = NULL;    // Количество плиток у каждого игрока
bool* firstMoveDone = NULL; // Флаг: выполнил ли игрок первый ход (>= 30 очков)

int** board_val = NULL;   // Значения плиток на столе [набор][плитка]
int** board_col = NULL;   // Цвета плиток на столе
bool** board_jok = NULL;  // Флаги джокеров на столе
int* boardSetSize = NULL; // Количество плиток в каждом наборе на столе
int boardTotalSets = 0;   // Общее количество наборов на столе



// Функция для очистки памяти
void cleanup(int playersCount) {
    delete[] pool_val; 
    delete[] pool_col; 
    delete[] pool_jok; // Удаляем колоду
    for (int i = 0; i < playersCount; i++) { // Удаляем руки каждого игрока
        delete[] hand_val[i]; 
        delete[] hand_col[i]; 
        delete[] hand_jok[i];
    }
    delete[] hand_val; 
    delete[] hand_col; 
    delete[] hand_jok; // Удаляем массивы указателей рук
    delete[] handCount; 
    delete[] firstMoveDone; // Удаляем служебные массивы
    for (int i = 0; i < 500; i++) { // Очищаем потенциальные наборы на столе
        if (board_val[i] != NULL) { 
            delete[] board_val[i]; 
            delete[] board_col[i]; 
            delete[] board_jok[i]; 
        }
    }
    delete[] board_val; 
    delete[] board_col; 
    delete[] board_jok; 
    delete[] boardSetSize; // Удаляем структуру стола
}


// Функция отрисовки плитки цветом
void printTile(int v, int c, bool j) {
    if (j) { // Если джокер
        if (c == 1) {
            cout << "\033[31m[ J ]\033[0m ";
        } // Красный джокер
        else {
            cout << "\033[30;1m[ J ]\033[0m ";
        } // Черный джокер
        return;
    }
    switch (c) { // Выбор цвета ANSI
        case 0: {
            cout << "\033[33m"; 
            break;
        } // Оранжевый
        case 1: {
            cout << "\033[31m"; 
            break;
        } // Красный
        case 2: {
            cout << "\033[34m"; 
            break;
        } // Синий
        case 3: {
            cout << "\033[30;1m"; 
            break;
        } // Черный
    }
    cout << "[" << v << "]\033[0m "; // Печать значения и сброс цвета
}


int main() {
    int seed; 
    cout << "Seed: "; 
    cin >> seed; 
    srand(seed); // Инициализация рандома
    pool_val = new int[106]; 
    pool_col = new int[106]; 
    pool_jok = new bool[106]; // Создание колоды
    int pi = 0; // Индекс заполнения
    for (int c = 0; c < 4; c++) {
        for (int v = 1; v <= 13; v++) {
            for (int r = 0; r < 2; r++) {
                pool_val[pi] = v; 
                pool_col[pi] = c; 
                pool_jok[pi] = false; 
                pi++;
            }
        }
    }
    pool_val[pi] = 0; 
    pool_col[pi] = 1; 
    pool_jok[pi] = true; 
    pi++; // Джокер 1
    pool_val[pi] = 0; 
    pool_col[pi] = 3; 
    pool_jok[pi] = true; 
    pi++; // Джокер 2
    for (int i = 0; i < 106; i++) { // Перемешивание
        int r = rand() % 106;
        int tv = pool_val[i]; 
        pool_val[i] = pool_val[r]; 
        pool_val[r] = tv;
        int tc = pool_col[i]; 
        pool_col[i] = pool_col[r]; 
        pool_col[r] = tc;
        bool tj = pool_jok[i]; 
        pool_jok[i] = pool_jok[r]; 
        pool_jok[r] = tj;
    }

    int playerCount; 
    cout << "Players (2-4): "; 
    cin >> playerCount; // Количество игроков
    hand_val = new int*[playerCount]; 
    hand_col = new int*[playerCount]; 
    hand_jok = new bool*[playerCount]; // Инициализация рук
    handCount = new int[playerCount]; 
    firstMoveDone = new bool[playerCount];
    for (int i = 0; i < playerCount; i++) {
        hand_val[i] = new int[106]; 
        hand_col[i] = new int[106]; 
        hand_jok[i] = new bool[106];
        handCount[i] = 14; 
        firstMoveDone[i] = false;
        for (int j = 0; j < 14; j++) {
            hand_val[i][j] = pool_val[--poolSize]; 
            hand_col[i][j] = pool_col[poolSize]; 
            hand_jok[i][j] = pool_jok[poolSize];
        }
    }

    board_val = new int*[500]; 
    board_col = new int*[500]; 
    board_jok = new bool*[500]; // Создание стола
    boardSetSize = new int[500]; 
    for (int i = 0; i < 500; i++) {
        board_val[i] = NULL;
    } // Обнуление указателей стола
    int turn = 0; // Текущий ход

    printTile(5, 1, false);
}