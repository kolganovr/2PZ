#include <iostream>
#include <stdlib.h>
using namespace std;

// ПЗ1 второй сем проги
// https://docs.google.com/document/d/1Yh6SqeuZZLcbPdFe0Zmidrl3CLSAzBG01CuJPle_mt0/edit

// Класс динамического массива
class DynArr
{
public:
    // конструктор
    DynArr(int length)
    {
        _size = max(length, 0); // Минимальная длинна массива - 0
        _arr = new int[_size];
        FillWithNumber(0);
    }

    /// @brief Создает и заполняет масив числом
    /// @param length Длина нового массива
    /// @param value Число, которым заполням
    DynArr(int length, int value)
    {
        _size = max(length, 0); // Минимальная длинна массива - 0
        _arr = new int[_size];
        FillWithNumber(value);
    }

    // Деструктор
    ~DynArr()
    {
        delete[] _arr;
    }

    // Выводит весь массив
    void Print()
    {
        if (GetLength() <= 0) // Если массив нулевой длины
            return;

        for (int i = 0; i < _size; i++)
        {
            cout << _arr[i] << " ";
        }
        cout << endl;
    }

    /// @brief Получить длину массива
    /// @return unsigned int Длина
    unsigned int GetLength()
    {
        return _size;
    }

    /// @brief Изменяет значения элемента массива
    /// @param index Индекс элемента
    /// @param value Новое значение
    void SetValue(unsigned int index, int value)
    {
#pragma region Обработка ошибок
        if (GetLength() <= 0) // Если массив нулевой длины
        {
            cout << "Слишком малый размер массива" << endl;
            return;
        }
        if (index < 0 || index >= _size) // Индекс за границами массива
        {
            cout << "Неверный индекс массива" << endl;
            return;
        }
        if (value <= -100 || value >= 100) // Подходящее ли число
        {
            cout << "Неверное значение массива" << endl;
            return;
        }
#pragma endregion

        _arr[index] = value; // Записываем значение
    }

private:
    int *_arr;
    unsigned int _size = 0;

    /// @brief Создаёт массив и позволяет запонить его с клавиатуры
    /// @param length Длина массива
    void FillArrayFromKeyboard(unsigned int length)
    {
        cout << "Введите " << length << " элементов массива:" << endl;

        int newVal; // Временная переменная для записи ее в массив
        for (int i = 0; i < length; i++)
        {
            cin >> newVal;
            SetValue(i, newVal);
        }
    }

    /// @brief Заполняет весь массив одним числом
    /// @param value Число, которым заполняем
    void FillWithNumber(int value)
    {
        for (int i = 0; i < _size; i++)
        {
            _arr[i] = value;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "rus"); // Русский язык в консоли

    int length;
    cin >> length;
    DynArr array(length, 7);
    array.Print();

    array.SetValue(0, 59);
    array.Print();
}