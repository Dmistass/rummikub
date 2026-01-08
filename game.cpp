#include <iostream> // Подключение библиотеки для консольного ввода-вывода
#include <cstdlib>  // Подключение библиотеки для генерации случайных чисел и управления памятью

using namespace std; // Использование пространства имен std

// Глобальные указатели для динамических массивов
int* pool_val = NULL;     // Значения плиток в колоде (1-13)
int* pool_col = NULL;     // Цвета плиток в колоде (0-3)
bool* pool_jok = NULL;    // Флаги джокеров в колоде
const int poolSize = 106;       // Текущее количество плиток в пуле



// Функция для очистки памяти
void cleanup(int nP) {
    delete[] pool_val; 
    delete[] pool_col; 
    delete[] pool_jok; // Удаляем колоду
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

    cout << pool_val[0] << endl << pool_col[0] << endl << pool_jok[0] << endl;
}