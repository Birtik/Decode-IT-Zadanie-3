#include <iostream>

using namespace std;

class Task
{
    unsigned int a;
    int count_of_operation;
    int* convertedInputNumber;
    int* clone_convertedInputNumber;


public:

    void SetValues()
    {
        try
        {
            cin >> a;

            if (a < 1000 || a > 9999)
                throw 1;
        }
        catch (int x) {
            cout << "Incorrect input data!";
            exit(0);
        }

        count_of_operation = 0;
        convertedInputNumber = new int[4];
        clone_convertedInputNumber = new int[4];

    }

    void ConvertInputNumber()
    {
        for (int i = 3; i >= 0; i--) {
            convertedInputNumber[i] = a % 10;
            clone_convertedInputNumber[i] = convertedInputNumber[i];
            a /= 10;
        }
    }

    void SortNumber(int mode) //mode: 1 - ASC // 2 - DESC
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 1 + i; j < 4; j++)
            {
                if (mode == 1 && convertedInputNumber[i] > convertedInputNumber[j])
                {
                    int temp = convertedInputNumber[i];
                    convertedInputNumber[i] = convertedInputNumber[j];
                    convertedInputNumber[j] = temp;
                }
                else if (mode == 2 && clone_convertedInputNumber[i] < clone_convertedInputNumber[j])
                {
                    int temp = clone_convertedInputNumber[i];
                    clone_convertedInputNumber[i] = clone_convertedInputNumber[j];
                    clone_convertedInputNumber[j] = temp;
                }
            }
        }
    }

    void Substract()
    {
        for (int i = 3; i >= 0; i--)
        {
            int position = i;
            bool flag = false;

            while (clone_convertedInputNumber[position] < convertedInputNumber[position])
            {
                position--;
                flag = true;
            }

            if (flag)
            {
                clone_convertedInputNumber[position]--;

                for (int j = (position + 1); j <= i; j++)
                    clone_convertedInputNumber[j] += (j == i ? 10 : 9);
            }

            clone_convertedInputNumber[i] -= convertedInputNumber[i];
        }

        for (int i = 0; i < 4; i++)
            convertedInputNumber[i] = clone_convertedInputNumber[i];
    }

    void inc_counter() { count_of_operation++; }

    bool CheckNumber()
    {
        if (clone_convertedInputNumber[0] == 6 &&
            clone_convertedInputNumber[1] == 1 &&
            clone_convertedInputNumber[2] == 7 &&
            clone_convertedInputNumber[3] == 4
            ) return true;

        return false;
    }

    int GetCounter() { return count_of_operation; }

};


int main()
{
    unsigned int t;

    try
    {
        cin >> t;
        if (t > 100) throw 1;
    }
    catch (int x) {
        cout << "Too much Tests!";
        exit(0);
    }

    Task** task = new Task * [t];


    for (int i = 0; i < t; i++)
    {
        task[i] = new Task;
        task[i]->SetValues();
        task[i]->ConvertInputNumber();

        while (!task[i]->CheckNumber())
        {
            task[i]->inc_counter();

            task[i]->SortNumber(1);
            task[i]->SortNumber(2);
            task[i]->Substract();
        }
    }

    for (int i = 0; i < t; i++)
    {
        cout << task[i]->GetCounter() << endl;
        delete task[i];
    }

    delete[] task;

}

