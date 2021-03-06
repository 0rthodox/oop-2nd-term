#include <iostream>

using namespace std;

// Считаем, что 0 - код успешного завершения
int func1() {
    // Тут происходит какая-то работа

    // Делаем вид, что всё сломалось
    return -1;

    // Дальше какая-то работа

    return 0;
}

int func2() {
    // Что-то делаем

    int f1_res = func1();
    if(f1_res != 0) {
        return f1_res;
    }

    // Что-то делаем дальше

    return 0;
}

int func3() {
    // Что-то делаем

    int f2_res = func2();
    if(f2_res != 0) {
        return f2_res;
    }

    // Что-то делаем дальше

    return 0;
}

// И так ещё 5 слоёв вызовов. Контрольные вопросы:
// - как вернуть ошибку, если функция при нормальной работе возвращает не int?
// - как вернуть ошибку, если функция при нормальной работе возвращает произвольный int?
// - точно не забудете везде вставить if(res != 0) { return res; } ?
//     - правда в C всегда проверяли, что вернулось из scanf, malloc и аналогов?
// - читать такое спагетти удобно?

int main() {
    int res = func3();
    if(res != 0) {
        cerr << "Calling func3() failed!" << endl;
        return -1;
    }

    // Тут идёт какая-то работа дальше

    return 0;
}
