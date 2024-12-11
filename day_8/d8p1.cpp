#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        size_t h1 = hash<int>{}(p.first);
        size_t h2 = hash<int>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

int main() {
    ifstream infile("puzzle_input");
    string line;
    vector<vector<string>> map;

    while (getline(infile, line)) {
        vector<string> row;
        for (int i = 0; i < line.size(); i++) {
            row.push_back(string(1, line[i]));
        }
        map.push_back(row);
    }

    unordered_map<string, vector<pair<int, int>>> antenna_coords;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == ".") {
                continue;
            }
            string frequency = map[i][j];
            if (antenna_coords.find(frequency) == antenna_coords.end()) {
                antenna_coords[frequency] = {{i, j}};
            } else {
                antenna_coords[frequency].push_back({i, j});
            }
        }
    }
    
    unordered_set<pair<int, int>, PairHash> antinodes;

    // for each key in antenna_coords
    for (auto& it: antenna_coords) {
        string frequency = it.first;
        vector<pair<int, int>> coord_pairs = it.second;

        for (int i = 0; i < coord_pairs.size(); i++) {
            for (int j = i + 1; j < coord_pairs.size(); j++) {

                if (i == j) {
                    continue;
                }

                int x1 = coord_pairs[i].first;
                int y1 = coord_pairs[i].second;
                int x2 = coord_pairs[j].first;
                int y2 = coord_pairs[j].second;
                int x_diff = x2 - x1;
                int y_diff = y2 - y1;
                
                pair<int, int> antinode1 = {x1 - x_diff, y1 - y_diff};
                pair<int, int> antinode2 = {x2 + x_diff, y2 + y_diff};
                
                if (antinode1.first >= 0 && antinode1.first < map.size() && antinode1.second >= 0 && antinode1.second < map[0].size()) {                    
                    antinodes.insert(antinode1);
                }
                if (antinode2.first >= 0 && antinode2.first < map.size() && antinode2.second >= 0 && antinode2.second < map[0].size()) {
                    antinodes.insert(antinode2);
                }
            }
        }
    }
    cout << antinodes.size() << endl;
}