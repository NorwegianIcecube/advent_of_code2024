#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct PairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

int build_area_recursive(unordered_map<pair<int, int>, int, PairHash> &tile_region_ids, vector<vector<string>> &map, int i, int j, int region_id){
    vector<pair<int,int>> neigbors = {{i-1, j}, {i+1, j}, {i, j-1}, {i, j+1}};
    int area = 1;
    for (int n = 0; n < neigbors.size(); n++){
        if (neigbors[n].first < 0 || neigbors[n].first >= map.size() || neigbors[n].second < 0 || neigbors[n].second >= map[i].size()){
            continue;
        }
        if (map[i][j] == map[neigbors[n].first][neigbors[n].second] && tile_region_ids.find(neigbors[n]) == tile_region_ids.end()){
            tile_region_ids[neigbors[n]] = region_id;
            area += build_area_recursive(tile_region_ids, map, neigbors[n].first, neigbors[n].second, region_id);
        }
    }
    return area;
}

int main(){
    ifstream infile("puzzle_input");
    string line;
    vector <vector<string>> map;

    while (getline(infile, line)){
        vector<string> row;
        for (int i = 0; i < line.size(); i++){
            row.push_back(string(1, line[i]));
        }
        map.push_back(row);
    }

    unordered_map<pair<int, int>, int, PairHash> tile_region_ids;
    unordered_map<int, int> region_sizes;
    unordered_map<int, int> region_perimeters;

    int region_id = 0;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            vector<pair<int, int>> neighbors = {{i-1, j}, {i+1, j}, {i, j-1}, {i, j+1}};
            
            int number_of_perimeters = 0;
            for (int n = 0; n < neighbors.size(); n++){
                if (neighbors[n].first < 0 || neighbors[n].first >= map.size() || neighbors[n].second < 0 || neighbors[n].second >= map[i].size()){
                    number_of_perimeters++;
                    continue;
                }
                
                if (map[i][j] != map[neighbors[n].first][neighbors[n].second]){
                    number_of_perimeters++;
                }
            }

            if (tile_region_ids.find({i, j}) == tile_region_ids.end()){
                tile_region_ids[{i, j}] = region_id;
                region_sizes[region_id] = build_area_recursive(tile_region_ids, map, i, j, region_id);
                region_id++;
            }
            region_perimeters[tile_region_ids[{i, j}]] += number_of_perimeters;
        }
    }

    int fence_cost = 0;
    for (auto const& [key, val] : region_sizes){
        fence_cost += val*region_perimeters[key];
    }
    cout << fence_cost << endl;
}