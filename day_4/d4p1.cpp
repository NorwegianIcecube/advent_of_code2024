#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int count_xmas(vector<vector<char>> puzzle_input, int num_rows, int num_cols, int i, int j){
    int count = 0;
    if (i < 0 || i >= num_rows || j < 0 || j >= num_cols){
        return 0;
    }
    if (puzzle_input[i][j] == 'X'){
        for (int k = -1; k <= 1; k++){
            for (int l = -1; l <= 1; l++){
                if ((k == 0 && l == 0)||(i + k*3 < 0 || i + k*3 >= num_rows || j + l*3 < 0 || j + l*3 >= num_cols)){
                    continue;
                }
                if (puzzle_input[i + k][j + l] == 'M'){
                    if (puzzle_input[i + k*2][j + l*2] == 'A'){
                        if (puzzle_input[i + k*3][j + l*3] == 'S'){
                                count++;
                        }
                    }
                }
            }
        }

    }
    return count;
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
            if (puzzle_input[i][j] == 'X'){
                total_xmas += count_xmas(puzzle_input, num_rows, num_cols, i, j);                
            }
        }
    }
    cout << total_xmas << endl;

}
