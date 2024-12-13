#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <utility>

using namespace std;

vector<pair<int, int>> get_neighbors(vector<vector<int>>& map, int i, int j) {
    vector<pair<int, int>> neighbors;
    vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}}; // up, down, left, right
    
    for (auto& dir : directions) {
        int new_i = i + dir.first;
        int new_j = j + dir.second;
        
        if (new_i >= 0 && new_i < map.size() && 
            new_j >= 0 && new_j < map[0].size() && 
            map[new_i][new_j] == map[i][j] + 1) {
            neighbors.push_back({new_i, new_j});
        }
    }
    return neighbors;
}

int get_trailhead_score(vector<vector<int>>& map, int start_i, int start_j) {
    set<pair<int, int>> nines;
    queue<pair<int, int>> q;
    set<pair<int, int>> visited;
    
    q.push({start_i, start_j});
    visited.insert({start_i, start_j});
    
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        
        if (map[i][j] == 9) {
            nines.insert({i, j});
            continue;
        }
        
        for (auto& next : get_neighbors(map, i, j)) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
    
    return nines.size();
}

int main(){
    ifstream infile("puzzle_input");
    string line;
    vector<vector<int>> map;

    while (getline(infile, line)){
        vector<int> row;
        for (int i = 0; i < line.size(); i++){
            row.push_back(line[i] - '0');
        }
        map.push_back(row);
    }

    int sum_scores =0;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            if (map[i][j] == 0){
                sum_scores += get_trailhead_score(map, i, j);
            }
        }
    }
    cout << sum_scores << endl;
}