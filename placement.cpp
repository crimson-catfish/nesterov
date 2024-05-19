#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

typedef int element;
typedef element *row;
typedef row *matrix;

int read_width()
{
    cout << "Enter half of matrix width: ";
    int n;
    cin >> n;
    return 2 * n + 1;
}

void read_matrix(int width, matrix m)
{
    char auto_or_manual;
    while (true)
    {
        cout << "Enter \"A\" to fill automaticly matrix, or \"M\" to fill manually: ";
        cin >> auto_or_manual;
        if (auto_or_manual == 'a' || auto_or_manual == 'A')
        {
            // fill automaticly
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    m[i][j] = i * width + j;
                }
            }
            return;
        }
        else if (auto_or_manual == 'm' || auto_or_manual == 'M')
        {
            // fill manually
            cout << "Enter matrix " << width << 'x' << width << "\n";
            for (int y = 0; y < width; y++)
            {
                for (int x = 0; x < width; x++)
                    cin >> m[y][x];
            }
            return;
        }
    }
}

// Сортировка по возрастанию методом выбора максимума
void sort_row(element **row, int row_length)
{
    for (int i = row_length - 1; i > 1 - 1; i--)
    {
        int max_elem = *row[i];
        int max_elem_index = i;
        for (int j = i - 1; j >= 0; j--)
        {
            if (*row[j] > max_elem)
            {
                max_elem = *row[j];
                max_elem_index = j;
            }
        }
        element buffer = *row[i];
        *row[i] = max_elem;
        *row[max_elem_index] = buffer;
    }
}

void crop(int *i, int low_bound, int high_bound)
{
    if (*i < low_bound)
        *i = 0;
    if (*i > high_bound)
        *i = high_bound;
}

void sort_matrix(int width, matrix m)
{
    element *row_to_sort[width * width];
    int row_to_sort_head = 0;

    for (int diagonal_index = 0; diagonal_index < 2 * width - 1; diagonal_index++)
    {
        int diagonal_length = -1 * abs(diagonal_index - width + 1) + width;

        if (diagonal_index % 2 == 1)
        {
            // from top-left to bottom-right
            int x = width - diagonal_index - 1;
            int y = diagonal_index - width + 1;
            crop(&x, 0, width - 1);
            crop(&y, 0, width - 1);

            for (int diagonal_element_index = 0; diagonal_element_index < diagonal_length; diagonal_element_index++)
            {
                row_to_sort[row_to_sort_head] = &m[y][x];
                row_to_sort_head++;
                x++;
                y++;
            }
        }
        else
        {
            // from bottom-right to top-left
            int x = 2 * width - diagonal_index - 2;
            int y = diagonal_index;
            crop(&x, 0, width - 1);
            crop(&y, 0, width - 1);

            for (int diagonal_element_index = 0; diagonal_element_index < diagonal_length; diagonal_element_index++)
            {
                row_to_sort[row_to_sort_head] = &m[y][x];
                row_to_sort_head++;
                x--;
                y--;
            }
        }
    }

    sort_row(row_to_sort, width * width);
}

void print_matrix(int width, matrix m)
{
    for (int i = 0; i < width; i++)
    {
        cout << endl;
        for (int j = 0; j < width; j++)
        {
            cout.width(4);
            cout << m[i][j];
        }
    }
}

int main()
{
    char quitOrRestart = 'r';

    do
    {
        quitOrRestart = 'r';
        int width = read_width();
        if (width <= 0)
        {
            cout << "Matrix width mast be positive";
            continue;
        }

        matrix m = new row[width];
        for (int i = 0; i < width; i++)
        {
            m[i] = new element[width];
        }

        read_matrix(width, m);

        cout << "\n\nOriginal matrix:";
        print_matrix(width, m);

        sort_matrix(width, m);

        cout << "\n\nSorted matrix:";
        print_matrix(width, m);

        cout << "\n\nEnter \"R\" to run again, or enter any other letter to quit programm: ";
        cin >> quitOrRestart;
    } while (quitOrRestart == 'r' || quitOrRestart == 'R');

    return 0;
}