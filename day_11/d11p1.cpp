#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

int main(){
    ifstream infile("puzzle_input");
    string line;
    vector<long> stones;

    getline(infile, line);

    for (int i = 0; i < line.size(); i++){
        int j = i;
        while (line[j] != ' ' && j < line.size()){
            j++;
        }
        stones.push_back(stol(line.substr(i, j-i)));
        i = j;
    }

    int number_of_updates = 25;
    for (int i = 0; i < number_of_updates; i++){
        vector<long> copy_vector;
        for (int j = 0; j < stones.size(); j++){
            if (stones[j] == 0){
                copy_vector.push_back(1);
            }
            else if (((int)log10(stones[j])+1) % 2 == 0){
                string s = to_string(stones[j]);
                string first_half = s.substr(0, s.size()/2);
                string second_half = s.substr(s.size()/2, s.size());
                long first_half_long = stol(first_half);
                long second_half_long = stol(second_half);
                copy_vector.push_back(first_half_long);
                copy_vector.push_back(second_half_long);
            }
            else {
                copy_vector.push_back(stones[j]*2024);
            }
        }
        stones = copy_vector;
    }
    cout << stones.size() << endl;
}