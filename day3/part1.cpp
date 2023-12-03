#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Number
{
    int num, line, col, len;
    bool valid;
    Number(int num, int line, int col, int len, int valid) : num(num), line(line), col(col), len(len), valid(valid) {}
};

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
    string line;

    int line_n = 0, total_sum = 0;

    while (getline(file, line))
    {
        input_matrix.push_back(line);
        for (Number n : get_line_numbers(line, line_n++))
            numbers.push_back(n);
    }

    for (Number n : numbers)
    {
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
                    }
                }
        if (n.valid)
            total_sum += n.num;
    }

    cout << total_sum << endl;

    return 0;
}