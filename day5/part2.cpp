#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <limits.h>

using namespace std;

struct Map
{
    string id;
    vector<vector<long>> cases;
};

map<long, long> read_seeds(string first_line)
{
    map<long, long> seeds;
    istringstream iss(first_line);

    iss.ignore(first_line.find(":") + 2);

    long seed, rep;
    while (iss >> seed)
    {
        iss >> rep;
        seeds[seed] = rep;
    }

    return seeds;
}

vector<Map> read_maps(fstream &file)
{
    Map current_map;
    string line;
    vector<long> current_case;
    vector<Map> maps;

    while (getline(file, line))
    {
        if (line.find("map:") != string::npos)
        {
            for (int i = 0; i < 4; ++i)
                line.pop_back();
            current_map.id = line;
        }
        else if (line != "")
        {
            long value;
            istringstream iss(line);
            while (iss >> value)
                current_case.push_back(value);
            current_map.cases.push_back(current_case);
            current_case = {};
        }
        else
        {
            maps.push_back(current_map);
            current_map = {};
        }
    }
    maps.push_back(current_map);

    return maps;
}

int main()
{
    const string filename = "./input1.dat";
    fstream file(filename);

    string line;
    long lowest_n = INT64_MAX;

    // read seeds
    getline(file, line); // blank
    map<long, long> seeds = read_seeds(line);

    // read maps
    getline(file, line); // blank
    vector<Map> maps = read_maps(file);

    long current_n;
    for (auto seed : seeds)
    {
        for (long n = 0; n < seed.second; ++n)
        {
            current_n = seed.first + n;
            for (auto map : maps)
                for (auto map_case : map.cases)
                    if (current_n >= map_case[1] && current_n < (map_case[1] + map_case[2]))
                    {
                        current_n = map_case[0] + (current_n - map_case[1]);
                        break;
                    }
            if (current_n < lowest_n)
                lowest_n = current_n;
        }
    }

    cout << lowest_n << endl;

    return 0;
}