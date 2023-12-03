#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct Game
{
    int id;
    vector<map<string, int>> subsets;
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

map<string, int> read_subset(string str_subset)
{
    map<string, int> current_subset = {{"red", 0}, {"green", 0}, {"blue", 0}};
    vector<string> str_cubes = split(str_subset, ',');

    for (auto str_cube : str_cubes)
        current_subset[split(str_cube, ' ')[2]] += stoi(split(str_cube, ' ')[1]);

    return current_subset;
}

Game read_game(string line)
{
    Game game;
    map<string, int> current_subset;

    vector<string> str_divided = split(line, ':');

    game.id = stoi(split(str_divided[0], ' ')[1]);

    for (auto str_subset : split(str_divided[1], ';'))
        game.subsets.push_back(read_subset(str_subset));

    return game;
}

int main()
{
    const string filename = "./input1.dat";
    ifstream file(filename);

    string line;
    int total_sum = 0;
    bool proper_game;

    map<string, int> target = {{"red", 12}, {"green", 13}, {"blue", 14}};

    while (getline(file, line))
    {
        Game current_game = read_game(line);
        proper_game = true;

        for (auto subset : current_game.subsets)
            if (subset["red"] > target["red"] || subset["blue"] > target["blue"] || subset["green"] > target["green"])
            {
                proper_game = false;
                break;
            }

        if (proper_game)
            total_sum += current_game.id;
    }

    cout << total_sum << endl;

    return 0;
}