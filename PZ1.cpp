#include <iostream>
using namespace std;

// ПЗ1 второй сем проги
// https://docs.google.com/document/d/1Yh6SqeuZZLcbPdFe0Zmidrl3CLSAzBG01CuJPle_mt0/edit

class DynArr
{
public:
    // конструктор
    DynArr(int size)
    {
        FillArrayFromKeyboard(size);
    }
    // Деструктор
    ~DynArr()
    {
        delete[] arr;
    }

    // Выводит весь массив
    void Print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

private:
    int *arr;
    int size = 0;

    /// @brief Создаёт массив и позволяет запонить его с клавиатуры
    /// @param length Длина массива
    void FillArrayFromKeyboard(int length)
    {
        cout << "Введите " << length << " элементов массива:" << endl;

        size = length;
        arr = new int[length];
        int newVal; // Временная переменная для записи ее в массив
        for (int i = 0; i < length; i++)
        {
            cin >> newVal;
            arr[i] = newVal;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "rus"); // Русский язык в консоли

    int length;
    cin >> length;
    DynArr array(length);
    array.Print();
}