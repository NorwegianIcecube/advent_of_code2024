#include <iostream>
#include <fstream>
#include <map>
#include <math.h>

using namespace std;

int main(){
    ifstream infile("puzzle_input");
    string line;
    map<long,long> stones;

    getline(infile, line);

    for (int i = 0; i < line.size(); i++){
        int j = i;
        while (line[j] != ' ' && j < line.size()){
            j++;
        }
        long stone = stol(line.substr(i, j-i));
        if (stones.find(stone) == stones.end()){
            stones[stone] = 1;
        }
        else {
            stones[stone]++;
        }
        i = j;
    }

    int number_of_updates = 75;
    for (int i = 0; i < number_of_updates; i++){
        map<long, long> new_stones;
        
        for (auto const& [key, val] : stones){
            if (key == 0){
                if (new_stones.find(1) == stones.end()){
                    new_stones[1] = val;
                }
                else {
                    new_stones[1] += val;
                }
            }
            else if (((int)log10(key)+1) % 2 == 0){
                string s = to_string(key);
                string first_half = s.substr(0, s.size()/2);
                string second_half = s.substr(s.size()/2, s.size());
                long first_half_long = stol(first_half);
                long second_half_long = stol(second_half);
                if (new_stones.find(first_half_long) == new_stones.end()){
                    new_stones[first_half_long] = val;
                }
                else {
                    new_stones[first_half_long] += val;
                }
                if (new_stones.find(second_half_long) == new_stones.end()){
                    new_stones[second_half_long] = val;
                }
                else {
                    new_stones[second_half_long] += val;
                }
            }
            else {
                if (new_stones.find(key*2024) == new_stones.end()){
                    new_stones[key*2024] = val;
                }
                else {
                    new_stones[key*2024] += val;
                }
            }
        }

        stones = new_stones;
    }
    long stone_sum = 0;
    for (auto const& [key, val] : stones){
        stone_sum += val;
    }
    cout << stone_sum << endl;
}