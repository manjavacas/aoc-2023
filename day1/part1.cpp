#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main()
{
    const string filename = "input1.dat";
    ifstream file(filename);

    queue<char> line_digits;
    string line, number;

    int total_sum = 0;

    while (getline(file, line))
    {
        line_digits = {};
        for (char c : line)
            if (isdigit(c))
                line_digits.push(c);

        number = {line_digits.front(), line_digits.back()};
        total_sum += stoi(number);
    }

    cout << total_sum << endl;

    return 0;
}