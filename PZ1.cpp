#include <iostream>
using namespace std;

// ��1 ������ ��� �����
// https://docs.google.com/document/d/1Yh6SqeuZZLcbPdFe0Zmidrl3CLSAzBG01CuJPle_mt0/edit

class DynArr
{
public:
    // �����������
    DynArr(int size)
    {
        FillArrayFromKeyboard(size);
    }
    // ����������
    ~DynArr()
    {
        delete[] arr;
    }

    // ������� ���� ������
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

    /// @brief ������ ������ � ��������� �������� ��� � ����������
    /// @param length ����� �������
    void FillArrayFromKeyboard(int length)
    {
        cout << "������� " << length << " ��������� �������:" << endl;

        size = length;
        arr = new int[length];
        int newVal; // ��������� ���������� ��� ������ �� � ������
        for (int i = 0; i < length; i++)
        {
            cin >> newVal;
            arr[i] = newVal;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "rus"); // ������� ���� � �������

    int length;
    cin >> length;
    DynArr array(length);
    array.Print();
}