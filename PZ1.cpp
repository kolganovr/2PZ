#include <iostream>
#include <array>
#include <stdlib.h>
using namespace std;

// ��1 ������ ��� �����
// https://docs.google.com/document/d/1Yh6SqeuZZLcbPdFe0Zmidrl3CLSAzBG01CuJPle_mt0/edit

// ����� ������������� �������
class DynArr
{
private:
    int *_arr;
    unsigned int _size = 0;

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
    // ~DynArr()
    // {
    //     delete[] _arr;
    // }

    // ������� ���� ������
    void Print(ostream &out = cout)
    {
        if (GetLength() <= 0) // ���� ������ ������� �����
            return;

        for (int i = 0; i < _size; i++)
        {
            out << _arr[i] << " ";
        }
        out << endl;
    }

    /// @brief �������� ����� �������
    /// @return unsigned int �����
    unsigned int GetLength()
    {
        return _size;
    }

    /// @brief ���������� ������
    /// @return ������������ ������
    int *GetArray()
    {
        return _arr;
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

    /// @brief ���������� �������� �������� �������
    /// @param index ������ ��������
    /// @return �������� ������
    int GetValue(int index)
    {
        return _arr[index];
    }

    /// @brief �������� � ������
    /// @param arrayFrom �� ������ ������� ����������
    void CopyPastArray(DynArr arrayFrom)
    {
        int minLength = min(arrayFrom.GetLength(), _size);

        int *array = arrayFrom.GetArray();
        memcpy(_arr, array, sizeof(int) * minLength);
    }

    DynArr ExpandArray(DynArr arrayToExpand, int sizeToAdd){
        DynArr tmp(_size + sizeToAdd);
        tmp.CopyPastArray(arrayToExpand);
        delete[] _arr;
        return tmp;
    }
private:
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
    inline void FillWithNumber(int value)
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

    DynArr array2(length);
    array2.Print();
    array2.CopyPastArray(array);
    array2.Print();

    array2 = array2.ExpandArray(array2, 3);
    array2.Print();

    array2.SetValue(1, 1);
    array.CopyPastArray(array2);
    array.Print();
}
