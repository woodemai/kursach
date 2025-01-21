#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale.h>

using namespace std;

// Функция для вывода матрицы на экран
void printMatrix(const vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int elem : row)
        {
            cout << elem << "\t";
        }
        cout << endl;
    }
}

// Функция для сортировки строки матрицы по возрастанию
void sortRowAscending(vector<int> &row)
{
    sort(row.begin(), row.end());
}

// Функция для сортировки строки матрицы по убыванию
void sortRowDescending(vector<int> &row)
{
    sort(row.begin(), row.end(), [](int a, int b)
         { return a > b; });
}

int main()
{
    setlocale(LC_ALL, "Russian");

    const int N = 5;
    vector<vector<int>> matrix(N, vector<int>(N));
    vector<vector<int>> resultMatrix(N, vector<int>(N));
    int mainDiagonalValue, aboveDiagonalValue, belowDiagonalValue;
    int choice;

    // Меню программы
    string menu[] = {
        "====================================",
        "=== ВОЗМОЖНЫЕ ДЕЙСТВИЯ ПРОГРАММЫ ===",
        "====================================",
        "1. Ввод элементов матрицы",
        "2. Вывод матрицы на экран",
        "3. Сортировка элементов строк матрицы по возрастанию",
        "4. Сортировка элементов строк матрицы по убыванию",
        "5. Запись элементов матрицы в файл",
        "6. Чтение чисел из файла в матрицу",
        "7. Сумма диагоналей",
        "8. Выход из программы"};

    while (true)
    {
        // Вывод меню
        for (const auto &line : menu)
        {
            cout << line << endl;
        }
        cout << "Выберите действие: ";
        cin >> choice;

        if (choice == 1)
        {
            // Ввод элементов матрицы
            cout << "Введите элементы матрицы 5x5 (по строкам):" << endl;
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    cin >> matrix[i][j];
                }
            }
        }
        else if (choice == 2)
        {
            // Вывод матрицы на экран
            cout << "\nТекущая матрица:" << endl;
            printMatrix(matrix);
        }
        else if (choice == 3)
        {
            // Сортировка элементов строк матрицы по возрастанию
            for (int i = 0; i < N; ++i)
            {
                sortRowAscending(matrix[i]);
            }
            cout << "Строки матрицы отсортированы по возрастанию." << endl;
        }
        else if (choice == 4)
        {
            // Сортировка элементов строк матрицы по убыванию
            for (int i = 0; i < N; ++i)
            {
                sortRowDescending(matrix[i]);
            }
            cout << "Строки матрицы отсортированы по убыванию." << endl;
        }
        else if (choice == 5)
        {
            // Запись элементов матрицы в файл
            ofstream outFile("matrix.txt");
            if (outFile.is_open())
            {
                for (int i = 0; i < N; ++i)
                {
                    for (int j = 0; j < N; ++j)
                    {
                        outFile << matrix[i][j] << " ";
                    }
                    outFile << endl;
                }
                outFile.close();
                cout << "Матрица записана в файл 'matrix.txt'." << endl;
            }
            else
            {
                cout << "Ошибка открытия файла для записи!" << endl;
            }
        }
        else if (choice == 6)
        {
            // Чтение чисел из файла в матрицу
            ifstream inFile("matrix.txt");
            if (inFile.is_open())
            {
                for (int i = 0; i < N; ++i)
                {
                    for (int j = 0; j < N; ++j)
                    {
                        inFile >> matrix[i][j];
                    }
                }
                inFile.close();
                cout << "Матрица считана из файла 'matrix.txt'." << endl;
            }
            else
            {
                cout << "Ошибка открытия файла для чтения!" << endl;
            }
        }
        else if (choice == 7)
        {
            if (matrix.empty())
            {
                cout << "Введите элементы матрицы 5x5 (по строкам):" << endl;
                for (int i = 0; i < N; ++i)
                {
                    for (int j = 0; j < N; ++j)
                    {
                        cin >> matrix[i][j];
                    }
                }
            }
            cout << matrix.empty();
            cout << "Введите значение для добавления к элементам главной диагонали: ";
            cin >> mainDiagonalValue;
            cout << "Введите значение для добавления к элементам выше главной диагонали: ";
            cin >> aboveDiagonalValue;
            cout << "Введите значение для добавления к элементам ниже главной диагонали: ";
            cin >> belowDiagonalValue;

            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    resultMatrix[i][j] = matrix[i][j];

                    if (i == j)
                    {
                        resultMatrix[i][j] += mainDiagonalValue;
                    }
                    if (i < j)
                    {
                        resultMatrix[i][j] += aboveDiagonalValue;
                    }
                    if (i > j)
                    {
                        resultMatrix[i][j] += belowDiagonalValue;
                    }
                }
            }

            cout << "\nИсходная матрица:" << endl;
            printMatrix(matrix);

            cout << "\nРезультирующая матрица:" << endl;
            printMatrix(resultMatrix);

            // Запись сумм в файл
            ofstream outFile("sums.txt");
            if (outFile.is_open())
            {
                int sum = 0, sumResult = 0;
                for (int i = 0; i < N; ++i)
                {
                    for (int j = 0; j < N; ++j)
                    {
                        sumResult += resultMatrix[i][j];
                        sum += matrix[i][j];
                    }
                }
                outFile << "Сумма всех элементов результирующей матрицы: " << sumResult << endl;
                outFile << "Сумма всех элементов исходной матрицы: " << sum << endl;
                outFile.close();
                cout << "Суммы записаны в файл 'sums.txt'." << endl;
            }
            else
            {
                cout << "Ошибка открытия файла для записи!" << endl;
            }

            // Чтение из файла и вывод содержимого
            ifstream inFile("sums.txt");
            if (inFile.is_open())
            {
                string line;
                cout << "\nСодержимое файла 'sums.txt':" << endl;
                while (getline(inFile, line))
                {
                    cout << line << endl;
                }
                inFile.close();
            }
            else
            {
                cout << "Ошибка открытия файла для чтения!" << endl;
            }
        }
        else if (choice == 8)
        {
            // Выход из программы
            cout << "До свидания!" << endl;
            break;
        }
        else
        {
            cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
        }

        cout << endl;
    }

    // Добавление значений к диагоналям

    return 0;
}