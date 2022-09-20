#include <iostream>
#include <array>
#include <stdlib.h>
using namespace std;

// ПЗ1 второй сем проги
// https://docs.google.com/document/d/1Yh6SqeuZZLcbPdFe0Zmidrl3CLSAzBG01CuJPle_mt0/edit

// Класс динамического массива
class DynArr
{
private:
    int *_arr;
    unsigned int _size = 0;

public:
    /// @brief Создает и заполняет масив числом
    /// @param length Длина нового массива
    /// @param value Число, которым заполням
    DynArr(int length, int value = 0)
    {
        _size = max(length, 0); // Минимальная длинна массива - 0
        _arr = new int[_size];
        FillWithNumber(value);
    }

    /// @brief Создает копию массива
    /// @param arrayFrom Из какого массива копируем
    DynArr(DynArr &arrayFrom)
    {
        _size = arrayFrom.GetLength();
        _arr = new int[_size];
        CopyPastArray(arrayFrom);
    }

    // Деструктор
    // ~DynArr()
    // {
    //     delete[] _arr;
    // }

    // Выводит весь массив
    void Print(ostream &out = cout)
    {
        if (GetLength() <= 0) // Если массив нулевой длины
            return;

        for (int i = 0; i < _size; i++)
        {
            out << _arr[i] << " ";
        }
        out << endl;
    }

    /// @brief Получить длину массива
    /// @return unsigned int Длина
    unsigned int GetLength()
    {
        return _size;
    }

    /// @brief Возвращает массив
    /// @return Динамический массив
    int *GetArray()
    {
        return _arr;
    }

    /// @brief Изменяет значения элемента массива
    /// @param index Индекс элемента
    /// @param value Новое значение
    void SetValue(unsigned int index, int value)
    {
#pragma region Обработка ошибок
        if (GetLength() == 0) // Если массив нулевой длины
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

    /// @brief Возвращает значение элемента массива
    /// @param index Индекс элемента
    /// @return Значение масива
    int GetValue(int index)
    {
        if (index < 0 || index >= _size) // Индекс за границами массива
        {
            cout << "Неверный индекс массива" << endl;
            return 0;
        }
        return _arr[index];
    }

    /// @brief Копирует в массив
    /// @param arrayFrom Из какого массива копировать
    void CopyPastArray(DynArr arrayFrom)
    {
        int minLength = min(arrayFrom.GetLength(), _size);

        int *array = arrayFrom.GetArray();
        memcpy(_arr, array, sizeof(int) * minLength);
    }

    /// @brief Добавляет в массив нули
    /// @param sizeToAdd количество новых элементов
    void ExpandArray(int sizeToAdd)
    {
        DynArr tmp(_size + sizeToAdd);
        tmp.CopyPastArray(_arr, _size);
        _arr = tmp.GetArray();
        _size += sizeToAdd;
    }

    /// @brief Добавляет число в конец массива
    /// @param value Число, которое добовляем
    void PushBack(int value)
    {
        ExpandArray(1);
        SetValue(_size - 1, value);
    }

    /// @brief Складывает массивы поэлементно
    /// @param secondArr Массив, с которым складываем
    void ArrayPlus(DynArr secondArr)
    {
        int minLength = min(secondArr.GetLength(), _size);

        for (int i = 0; i < minLength; i++)
        {
            _arr[i] += secondArr.GetValue(i); // Складываем массивы
        }
    }

private:
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
    inline void FillWithNumber(int value)
    {
        for (int i = 0; i < _size; i++)
        {
            _arr[i] = value;
        }
    }

    /// @brief Копирует в массив
    /// @param arrayFrom Из какого массива копировать
    /// @param sizeFrom Размер исходного массива
    void CopyPastArray(int arrayFrom[], unsigned int sizeFrom)
    {
        int minLength = min(sizeFrom, _size);

        int *array = arrayFrom;
        memcpy(_arr, array, sizeof(int) * minLength);
    }
};

int main()
{
    setlocale(LC_ALL, "rus"); // Русский язык в консоли

    int length;
    cin >> length;
    DynArr array(length, 7);
    array.Print();

    array.SetValue(0, 35);
    array.Print();

    DynArr array2(length);
    array2.Print();
    array2.CopyPastArray(array);
    array2.Print();

    array2.ExpandArray(3);
    array2.Print();

    array2.SetValue(1, 1);
    array.CopyPastArray(array2);

    array.PushBack(9);
    array.Print();

    array.ArrayPlus(array2);
    array.Print();
}
