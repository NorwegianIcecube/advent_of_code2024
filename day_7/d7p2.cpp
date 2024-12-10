#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long concat_cumbers(long a, long b){
    string a_str = to_string(a);
    string b_str = to_string(b);
    string ab_str = a_str + b_str;
    return stol(ab_str);
}

int main(){
    ifstream infile("puzzle_input");
    string line;
    const vector<string> operators = {"+", "*", "||"};
    long ans_sum = 0;
    while (getline(infile, line)){        
        long target_num = stol(line.substr(0, line.find(":")));
        line = line.substr(line.find(":") + 2);
        vector<int> component_nums;
        while (line.find(" ") != string::npos){
            component_nums.push_back(stoi(line.substr(0, line.find(" "))));
            line = line.substr(line.find(" ") + 1);
        }
        component_nums.push_back(stoi(line));

        long root = component_nums[0];
        vector<vector<long>> binary_tree = {{root}};
        for (int i = 1; i < component_nums.size(); i++){
            vector<long> row;
            for (int j = 0; j < binary_tree[i-1].size(); j++){
                for (int k = 0; k < operators.size(); k++){
                    if (operators[k] == "+"){
                        row.push_back(binary_tree[i-1][j] + component_nums[i]);
                    }
                    else if (operators[k] == "*"){ 
                        row.push_back(binary_tree[i-1][j] * component_nums[i]);         
                    }                                                                       
                    else{
                        row.push_back(concat_cumbers(binary_tree[i-1][j], component_nums[i]));
                    }
                    
                }
            }
            binary_tree.push_back(row);
        }
        if (find(binary_tree[binary_tree.size()-1].begin(), binary_tree[binary_tree.size()-1].end(), target_num) != binary_tree[binary_tree.size()-1].end()){
            ans_sum += target_num;
        }
    }
    cout << ans_sum << endl;
}