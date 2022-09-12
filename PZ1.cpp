#include <iostream>
#include <stdlib.h>
using namespace std;

// ��1 ������ ��� �����
// https://docs.google.com/document/d/1Yh6SqeuZZLcbPdFe0Zmidrl3CLSAzBG01CuJPle_mt0/edit

// ����� ������������� �������
class DynArr
{
public:
    // �����������
    DynArr(int length)
    {
        _size = max(length, 0); // ����������� ������ ������� - 0
        _arr = new int[_size];
        FillWithNumber(0);
    }

    /// @brief ������� � ��������� ����� ������
    /// @param length ����� ������ �������
    /// @param value �����, ������� ��������
    DynArr(int length, int value)
    {
        _size = max(length, 0); // ����������� ������ ������� - 0
        _arr = new int[_size];
        FillWithNumber(value);
    }

    // ����������
    ~DynArr()
    {
        delete[] _arr;
    }

    // ������� ���� ������
    void Print()
    {
        if (GetLength() <= 0) // ���� ������ ������� �����
            return;

        for (int i = 0; i < _size; i++)
        {
            cout << _arr[i] << " ";
        }
        cout << endl;
    }

    /// @brief �������� ����� �������
    /// @return unsigned int �����
    unsigned int GetLength()
    {
        return _size;
    }

    /// @brief �������� �������� �������� �������
    /// @param index ������ ��������
    /// @param value ����� ��������
    void SetValue(unsigned int index, int value)
    {
#pragma region ��������� ������
        if (GetLength() <= 0) // ���� ������ ������� �����
        {
            cout << "������� ����� ������ �������" << endl;
            return;
        }
        if (index < 0 || index >= _size) // ������ �� ��������� �������
        {
            cout << "�������� ������ �������" << endl;
            return;
        }
        if (value <= -100 || value >= 100) // ���������� �� �����
        {
            cout << "�������� �������� �������" << endl;
            return;
        }
#pragma endregion

        _arr[index] = value; // ���������� ��������
    }

private:
    int *_arr;
    unsigned int _size = 0;

    /// @brief ������ ������ � ��������� �������� ��� � ����������
    /// @param length ����� �������
    void FillArrayFromKeyboard(unsigned int length)
    {
        cout << "������� " << length << " ��������� �������:" << endl;

        int newVal; // ��������� ���������� ��� ������ �� � ������
        for (int i = 0; i < length; i++)
        {
            cin >> newVal;
            SetValue(i, newVal);
        }
    }

    /// @brief ��������� ���� ������ ����� ������
    /// @param value �����, ������� ���������
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
    setlocale(LC_ALL, "rus"); // ������� ���� � �������

    int length;
    cin >> length;
    DynArr array(length, 7);
    array.Print();

    array.SetValue(0, 59);
    array.Print();
}