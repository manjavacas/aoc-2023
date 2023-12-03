#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <limits>

using namespace std;

struct Digit
{
    int value;
    int position;
    Digit(int v, int p) : value(v), position(p) {}
};

int main()
{
    const string filename = "input2.dat";
    ifstream file(filename);

    string line;

    map<string, int> digits = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
        {"zero", 0}};

    int total_sum = 0;

    while (getline(file, line))
    {
        list<Digit> line_digits;

        // actual digits
        for (int i = 0; i < line.size(); i++)
            if (isdigit(line[i]))
            {
                Digit d(line[i] - '0', i);
                line_digits.push_back(d);
            }

        // string digits
        for (auto x : digits)
        {
            string key = x.first;
            int pos = line.find(key);
            while (pos != string::npos)
            {
                Digit d(digits[key], pos);
                line_digits.push_back(d);
                pos = line.find(key, pos + 1);
            }
        }

        // get lowest and highest positioned
        int min_pos = INT16_MAX, max_pos = -1, first, second;
        for (auto d : line_digits)
        {
            if (d.position <= min_pos)
            {
                first = d.value;
                min_pos = d.position;
            }
            if (d.position > max_pos)
            {
                second = d.value;
                max_pos = d.position;
            }
        }

        total_sum += first * 10 + second;
    }

    cout << total_sum << endl;

    return 0;
}