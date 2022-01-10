#include <iostream>
#include <random>
#include <fstream>
#include <ctime>

using namespace std;

// дата и время
void date_time()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    ofstream file("log.txt", ios_base::app);
    file << dt;
}

// одновременная запись
void dual_write(const string& text)
{
    // вывод в консоль
    cout << text;

    // запись в файл
    ofstream file("log.txt", ios_base::app);
    file << "OUTPUT: " << text;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int amount;
    ofstream file("log.txt", ios_base::app);

    while (true)
    {
        date_time();
        dual_write("Введите количество бочек (ЦЕЛОЕ ПОЛОЖИТЕЛЬНОЕ ЧИСЛО): \n");
        cin >> amount;

        date_time();
        file << "INPUT: " << amount << endl;

        // обработка ввода неверного типа данных
        if (cin.fail() || cin.get() != '\n')
        {
            date_time();
            dual_write("\nНекорректный ввод. Повторите попытку.\n");
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // обработка ввода числа, выходящего за пределы диапазона
        else if (amount < 1)
        {
            date_time();
            dual_write("\nВведено число за пределами заданного диапазон. Повторите попытку.\n");
        }

        else
        {
            break;
        }
    }

    int* bag = new int[amount];

    // заполнение массива
    for (int i = 0; i < amount; i++) 
    {
        bag[i] = i + 1;
    }

    // перемешивание массива
    random_shuffle(bag, bag + amount);

    date_time();
    dual_write( "Результат жеребьевки: \n");

    // вывод
    for (int i = 0; i < amount; i++)
    {
        date_time();
        cout << i + 1 << ") " << bag[i] << endl;
        file << "OUTPUT: " << i + 1 << ") " << bag[i] << endl;
    }

    file.close();
    delete[] bag;
    return 0;
}

