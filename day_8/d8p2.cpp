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
                
                int antninode_number = 0;
                while (true) {
                    int antinode_x = x2 + x_diff*antninode_number;
                    int antinode_y = y2 + y_diff*antninode_number;
                    if (antinode_x < 0 || antinode_x >= map.size() || antinode_y < 0 || antinode_y >= map[0].size()) {
                        break;
                    }
                    antinodes.insert({antinode_x, antinode_y});
                    antninode_number++;
                }
                antninode_number = 0;
                while (true) {
                    int antinode_x = x1 - x_diff*antninode_number;
                    int antinode_y = y1 - y_diff*antninode_number;
                    if (antinode_x < 0 || antinode_x >= map.size() || antinode_y < 0 || antinode_y >= map[0].size()) {
                        break;
                    }
                    antinodes.insert({antinode_x, antinode_y});
                    antninode_number++;
                }
            }
        }
    }
    cout << antinodes.size() << endl;
}