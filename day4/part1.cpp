#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Card
{
    int points;
    vector<int> winning;
    vector<int> player;
};

vector<string> split(const string &s, char delimiter)
{
    vector<string> substrings;
    size_t start = 0;
    size_t end = s.find(delimiter);

    while (end != std::string::npos)
    {
        substrings.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(delimiter, start);
    }

    substrings.push_back(s.substr(start, end));

    return substrings;
}

Card read_card(string line)
{
    vector<string> aux = split(line, ':');
    aux = split(aux[1], '|');

    Card c;

    // numbers
    for (auto x : split(aux[0], ' '))
        if (x != "")
            c.winning.push_back(stoi(x));

    for (auto x : split(aux[1], ' '))
        if (x != "")
            c.player.push_back(stoi(x));

    // points
    vector<int> intersect;

    sort(c.winning.begin(), c.winning.end());
    sort(c.player.begin(), c.player.end());

    set_intersection(c.winning.begin(), c.winning.end(),
                     c.player.begin(), c.player.end(),
                     back_inserter(intersect));

    c.points = pow(2, intersect.size() - 1);

    return c;
}

int main()
{
    const string filename = "./input1.dat";
    fstream file(filename);

    string line;
    int total_sum = 0;

    while (getline(file, line))
        total_sum += read_card(line).points;

    cout << total_sum << endl;

    return 0;
}