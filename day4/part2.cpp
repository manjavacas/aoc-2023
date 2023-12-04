#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

struct Card
{
    int id, matches;
    vector<int> winning;
    vector<int> player;

    bool operator<(const Card &c) const
    {
        return id < c.id;
    }
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
    Card c;

    vector<string> aux = split(line, ':');

    // id
    for (auto x : split(aux[0], ' '))
        if (x != "" && x != "  " && x != "Card")
            c.id = stoi(x);

    // numbers, points, matches
    aux = split(aux[1], '|');

    for (auto x : split(aux[0], ' '))
        if (x != "")
            c.winning.push_back(stoi(x));

    for (auto x : split(aux[1], ' '))
        if (x != "")
            c.player.push_back(stoi(x));

    vector<int> intersect;

    sort(c.winning.begin(), c.winning.end());
    sort(c.player.begin(), c.player.end());

    set_intersection(c.winning.begin(), c.winning.end(),
                     c.player.begin(), c.player.end(),
                     back_inserter(intersect));

    c.matches = intersect.size();

    return c;
}

Card get_card(vector<Card> cards, int id)
{
    Card c;
    for (Card x : cards)
        if (x.id == id)
        {
            c = x;
            break;
        }
    return c;
}

int main()
{
    const string filename = "./input1.dat";
    fstream file(filename);

    string line;

    vector<Card> cards;
    map<int, int> card_counter;

    int total_sum = 0;

    while (getline(file, line))
    {
        Card c = read_card(line);
        cards.push_back(c);
        card_counter[c.id]++;
        total_sum++;
    }

    for (auto c : cards)
        while (card_counter[c.id] != 0)
        {
            for (int i = 1; i <= c.matches; i++)
            {
                card_counter[c.id + i]++;
                total_sum++;
            }
            card_counter[c.id]--;
        }

    cout << total_sum << endl;

    return 0;
}