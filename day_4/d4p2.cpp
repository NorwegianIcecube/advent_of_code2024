#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


vector<vector<char>> rotate_window_90(vector<vector<char>> window){
    vector<vector<char>> rotated_window;
    for (int i = 0; i < window.size(); i++){
        vector<char> row;
        for (int j = 0; j < window[0].size(); j++){
            row.push_back(window[window.size() - j - 1][i]);
        }
        rotated_window.push_back(row);
    }
    return rotated_window;
}

bool check_window(vector<vector<char>> window){
    if (window[0][0] == 'M' && window[0][2] == 'M' && window[2][0] == 'S' && window[2][2] == 'S'){
        return true;
    }
    return false;
}

int check_masmas(vector<vector<char>> puzzle_input, int num_rows, int num_cols, int i, int j){
    vector<vector<char>> window;
    for (int k = -1; k <= 1; k++){
        vector<char> row;
        for (int l = -1; l <= 1; l++){
            if (i + k < 0 || i + k >= num_rows || j + l < 0 || j + l >= num_cols){
                return 0;
            }
            row.push_back(puzzle_input[i + k][j + l]);
        }
        window.push_back(row);
    }
    if (check_window(window) || check_window(rotate_window_90(window)) || check_window(rotate_window_90(rotate_window_90(window))) || check_window(rotate_window_90(rotate_window_90(rotate_window_90(window))))){
        return 1;
    }
    return 0;
}

int main() {
    ifstream infile("puzzle_input");
    string line;
    vector<vector<char>> puzzle_input;
    while (getline(infile, line)) {
        vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        puzzle_input.push_back(row);
    }

    
    int num_rows = puzzle_input.size();
    int num_cols = puzzle_input[0].size();

    int total_xmas = 0;
    
    for (int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            if (puzzle_input[i][j] == 'A'){
                total_xmas += check_masmas(puzzle_input, num_rows, num_cols, i, j);
            }
        }
    }
    cout << total_xmas << endl;
}
