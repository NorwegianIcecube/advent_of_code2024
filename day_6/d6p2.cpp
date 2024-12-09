#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <functional>
#include <string>

using namespace std;

struct State {
    int x;
    int y;
    string direction;
    bool operator==(const State& other) const {
        return x == other.x && y == other.y && direction == other.direction;
    }
};

struct StateHash {
    size_t operator()(const State& state) const {
        size_t h1 = hash<int>{}(state.x);
        size_t h2 = hash<int>{}(state.y);
        size_t h3 = hash<string>{}(state.direction);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};


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

unordered_set<State, StateHash> get_visisted_states(vector<vector<int>> map, int player_position[2], string direction){
    std::unordered_set<State, StateHash> visited_states;

    int player_position_copy [2];
    player_position_copy[0] = player_position[0];
    player_position_copy[1] = player_position[1];
    // State is playerx, playery, direction
    while (player_position[0] < map.size() && player_position[0] >= 0 && player_position[1] < map[0].size() && player_position[1] >= 0){
        State current_state = {player_position[0], player_position[1], direction};
        visited_states.insert(current_state);
        

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
    return visited_states;
}

int check_for_loop(vector<vector<int>> map, int player_position[2], string direction){
    std::unordered_set<State, StateHash> visited_states;
    while (player_position[0] < map.size() && player_position[0] >= 0 && player_position[1] < map[0].size() && player_position[1] >= 0){
        State current_state = {player_position[0], player_position[1], direction};
        if (visited_states.find(current_state) != visited_states.end()){
            // cout the map
            /*
            for (int i = 0; i < map.size(); i++){
                for (int j = 0; j < map[0].size(); j++){
                    if (player_position[0] == i && player_position[1] == j){
                        cout << "X";
                    }
                    else if (map[i][j] == 1){
                        cout << "#";
                    }
                    else {
                        cout << ".";
                    }
                }
                cout << endl;
            }
            cout << endl;
            */
            return 1;
        }
        visited_states.insert(current_state);

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
    return 0;
}

int main(){
    ifstream infile("puzzle_input");
    string line;
    vector<vector<int>> map;
    int player_position [2];
    string direction = "up";

    // Reading map
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
    int player_position_copy [2];
    player_position_copy[0] = player_position[0];
    player_position_copy[1] = player_position[1];
    string direction_copy = direction;

    // Set of each visited state
    unordered_set<State, StateHash> visited_states = get_visisted_states(map, player_position_copy, direction_copy);
    
    int loop_count = 0;
    float init_size = visited_states.size();
    unordered_set<long> map_ids;
    while (visited_states.size() > 0)
    {
        long map_id = 0;
        if (visited_states.size() % 100 == 0){
            cout << 1-visited_states.size()/init_size << endl;
        }
        // Copying map to add an obstacle
        vector<vector<int>> map_copy = map;
        State current_state = *visited_states.begin();
        visited_states.erase(visited_states.begin());
        if (current_state.x == player_position[0] && current_state.y == player_position[1]){
            continue;
        }

        direction_copy = direction;
        map_copy[current_state.x][current_state.y] = 1;
        // Create an xor of the map and map_copy
        for (int i = 0; i < map.size(); i++){
            for (int j = 0; j < map[0].size(); j++){
                if (map[i][j] != map_copy[i][j]){
                    // map id is 8 digit number with 4 digits for i and 4 digits for j
                    map_id = i * 10000 + j;
                    break;
                }
            }
            if (map_id != 0){
                break;
            }
        }
        // Skipping current obstacle if we've already checked it.
        if (map_ids.find(map_id) != map_ids.end()){
            continue;
        }
        
        map_ids.insert(map_id);

        player_position_copy[0] = player_position[0];
        player_position_copy[1] = player_position[1];
        loop_count += check_for_loop(map_copy, player_position_copy, direction_copy);
    }
    cout << "Loop count: " << loop_count << endl;
}

// I'm not sure why this isn't working, with several days spent on this problem, and not clear on what the issue is or how to find it. I'm going to move on to the next problem.