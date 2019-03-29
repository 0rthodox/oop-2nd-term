#include <iostream>
#include <string>
#include <map>
#include <utility>

using namespace std;

// Сюда m передали как const reference.
// Логически это: 'вот данные, их можно читать, но нельзя менять'.
void function_one(const map<string,float>& m)
{
    // Обойти map-у можно, но итератор нужно тоже получить как const_iterator,
    // что логически дальше всем кодом воспринимается как 
    // 'вот итератор, по нему можно читать, но писать нельзя'.
    for (map<string,float>::const_iterator it = m.begin(); it != m.end(); it++)
    {
        // Это ок - чтение из const_iterator.
        cout << it->first << ": " << it->second << endl;
        // Так нельзя - итератор же const, нельзя по нему обращаться на запись.
        // Эта строчка упадёт на этапе компиляции.
        //it->second = 0;
    }

    // Попробуем получить не-const итератор - упс, так тоже нельзя.
    // Эта строчка упадёт на этапе компиляции.
    //map<string,float>::iterator it = m.begin();

    // Попробуем добавить данных в map-у - упс, так тоже нельзя, она же const.
    //m["test"] = 0.0;
}

// А вот сюда m передали как reference, но без const.
// Логически это: 'вот данные, с ними можно делать всё'.
void function_two(map<string,float>& m)
{
    // Попробуем добавить данных в map-у - теперь так можно.
    m["test"] = 0.0;

    // Попробуем получить не-const итератор - тоже можно.
    // Дальше по этому итератору можно, например, умножить все значения на 2.
    for (map<string,float>::iterator it = m.begin(); it != m.end(); it++)
    {
        it->second *= 2;
    }

    // Получить const_iterator при желании тоже можно, так как
    // наше желание только читать вполне допустимо (при разрешённых всех операциях)
    for (map<string,float>::const_iterator it = m.begin(); it != m.end(); it++)
    {
        cout << it->first << ": " << it->second << endl;
    }
}

int main()
{
    // Какие-то данные
    map<string,float> keywords;
    keywords["foo"] = 0.1;
    keywords["bar"] = 0.2;
    keywords["baz"] = 0.3;

    // Сюда keywords передаются как const reference.
    // Тот факт, что оно будет const, определяется функцией, а не map-ой.
    cout << "===== Test 1 =====" << endl;
    function_one(keywords);

    // А сюда те же самые keywords передаются как reference, но уже не const
    // Такая передача продиктована опять же объявлением функции.
    cout << "===== Test 2 =====" << endl;
    function_two(keywords);

    // Что во всём этом ценно - глядя на *чужую* функцию, которую собираетесь вызвать,
    // можно сразу сказать, может ли она в принципе изменить переданный объект
    // (и тогда стоит сразу подумать насчёт того, не нужна ли вам его копия)
    // или вызов 'совсем безопасен', потому что параметр передаётся как const
    // (и тогда переданный объект точно не будет никак изменён).

    // Можно и наоборот - свои *данные* отметить как const, то есть
    // потребовать гарантий, что они не будут меняться после инита.

    // Тут, например, у нас const map.
    const map<string,float> ckeywords = {{"hello", 1.0}};

    // Этот пример сработает успешно - const map передаётся как const reference, всё ок.
    cout << "===== Test 3 =====" << endl;
    function_one(ckeywords);

    // А вот это будет запрещено на этапе компиляции, так как
    // функция хочет получить reference (по которому можно менять объект),
    // но const map требует гарантий, что объект не будет изменён.
    //cout << "===== Test 4 =====" << endl;
    //function_two(ckeywords);

    return 0;
}
