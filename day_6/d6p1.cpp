#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string turn(string direction){
        if (direction == "up"){
            return "right";
        }
        else if (direction == "right"){
            return "down";
        }
        else if (direction == "down"){
            return "left";
        }
        else {
            return "up";
        }
    }
bool check_for_edge(vector<vector<int>> map, int player_position[2], string direction){
    if (direction == "up"){
        return player_position[0] == 0;
    }
    else if (direction == "right"){
        return player_position[1] == map[0].size() - 1;
    }
    else if (direction == "down"){
        return player_position[0] == map.size() - 1;
    }
    else {
        return player_position[1] == 0;
    }
}

bool check_for_obstacle(vector<vector<int>> map, int player_position[2], string direction){
    if (direction == "up"){
        return map[player_position[0] - 1][player_position[1]] == 1;
    }
    else if (direction == "right"){
        return map[player_position[0]][player_position[1] + 1] == 1;
    }
    else if (direction == "down"){
        return map[player_position[0] + 1][player_position[1]] == 1;
    }
    else {
        return map[player_position[0]][player_position[1] - 1] == 1;
    }
}

int main(){
    ifstream infile("puzzle_input");
    string line;
    vector<vector<int>> map;
    int player_position [2];
    string direction = "up";

    while (getline(infile, line)){
        vector<int> row;
        for (int i = 0; i < line.size(); i++){
            if (line[i] == '.'){
                row.push_back(0);
            }
            else if (line[i] == '#'){
                row.push_back(1);
            }
            else {
                player_position[0] = map.size();
                player_position[1] = i;
                row.push_back(0);
            }
        }
        map.push_back(row);
    }

    

    int step_count = 0;
    while (player_position[0] < map.size() && player_position[0] >= 0 && player_position[1] < map[0].size() && player_position[1] >= 0){
        map[player_position[0]][player_position[1]]--;
        if (map[player_position[0]][player_position[1]] >= -1){
            step_count++;
        }
        if (check_for_edge(map, player_position, direction)){
            break;
        }
        if (check_for_obstacle(map, player_position, direction)){
            direction = turn(direction);
        }
        if (direction == "up"){
            player_position[0]--;
        }
        else if (direction == "right"){
            player_position[1]++;
        }
        else if (direction == "down"){
            player_position[0]++;
        }
        else {
            player_position[1]--;
        }
    }
    cout << step_count << endl;
    
}