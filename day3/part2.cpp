#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

struct Number
{
    int num;
    int line;
    int col;
    int len;
    bool valid;
    Number(int num, int line, int col, int len, int valid) : num(num), line(line), col(col), len(len), valid(valid) {}
};

struct Asterisk
{
    int line;
    int col;
    set<int> numbers;
    Asterisk(int line, int col) : line(line), col(col) {}
};

vector<Asterisk> get_line_asterisks(string line, int line_n)
{
    vector<Asterisk> line_asterisks;
    for (int i = 0; i < line.size(); i++)
        if (line[i] == '*')
        {
            Asterisk a(line_n, i);
            line_asterisks.push_back(a);
        }
    return line_asterisks;
}

vector<Number> get_line_numbers(string line, int line_n)
{
    vector<Number> line_numbers;
    int k = 0, current_num = 0;

    for (int i = line.size() - 1; i >= 0; i--)
    {
        if (isdigit(line[i]))
            current_num += (line[i] - '0') * pow(10, k++);
        else
        {
            if (k > 0)
            {
                Number n(current_num, line_n, i + 1, k, false);
                line_numbers.push_back(n);
            }
            k = 0;
            current_num = 0;
        }
    }

    if (k > 0)
    {
        Number n(current_num, line_n, 0, k, false);
        line_numbers.push_back(n);
    }

    return line_numbers;
}

int main()
{
    const string filename = "input1.dat";
    fstream file(filename);

    vector<string> input_matrix;
    vector<Number> numbers;
    vector<Asterisk> asterisks;
    string line;

    int line_n = 0, total_sum = 0;

    while (getline(file, line))
    {
        input_matrix.push_back(line);
        for (Number n : get_line_numbers(line, line_n))
            numbers.push_back(n);

        for (Asterisk a : get_line_asterisks(line, line_n))
            asterisks.push_back(a);

        line_n++;
    }

    for (Number n : numbers)
        for (int i = n.col; i < n.col + n.len; i++)
            for (int j = -1; j <= 1; j++)
                for (int k = -1; k <= 1; k++)
                {
                    int row = n.line + j;
                    int col = i + k;

                    if (row >= 0 && row < input_matrix.size() && col >= 0 && col < input_matrix[0].size())
                    {
                        char current_char = input_matrix[row][col];
                        if (!isdigit(current_char) && current_char != '.')
                            n.valid = true;
                        // gear check
                        if (current_char == '*')
                            for (Asterisk &a : asterisks)
                                if (a.line == row && a.col == col)
                                    a.numbers.insert(n.num);
                    }
                }

    int gear_ratio;
    for (Asterisk a : asterisks)
    {
        gear_ratio = 1;
        if (!a.numbers.empty() && a.numbers.size() > 1)
        {
            for (int n : a.numbers)
                gear_ratio *= n;
            total_sum += gear_ratio;
        }
    }

    cout << total_sum << endl;

    return 0;
}