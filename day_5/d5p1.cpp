#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

bool check_if_rules_are_followed_for_current_number(int current_index, vector<int> safety_manual, vector<int> page_order){
    int current_number = safety_manual[current_index];
    for (int i = 0; i < current_index; i++){
        for (int j = 0; j < page_order.size(); j++){
            if (safety_manual[i] == page_order[j]){
                return false;
            }
        }
    }
    return true;
}

int main(){
    ifstream infile("puzzle_input_1");
    string line;
    unordered_map<int, vector<int>> page_order_rules;

    while (getline(infile, line)){
        int first_page = stoi(line.substr(0, line.find("|")));
        int second_page = stoi(line.substr(line.find("|") + 1));

        if (page_order_rules.find(first_page) == page_order_rules.end()){
            page_order_rules[first_page] = {second_page};
        }
        else{
            page_order_rules[first_page].push_back(second_page);
        }
    }
    
    int middle_page_number_sum = 0;
    ifstream infile2("puzzle_input_2");

    while (getline(infile2, line)){
        vector<int> safety_manual;
        int first_page = stoi(line.substr(0, line.find(",")));
        safety_manual.push_back(first_page);
        while (line.find(",") != string::npos){
            line = line.substr(line.find(",") + 1);
            safety_manual.push_back(stoi(line.substr(0, line.find(","))));
        }

        bool is_valid = true;
        for (int i = 0; i < safety_manual.size(); i++){
            if (page_order_rules.find(safety_manual[i]) == page_order_rules.end()){
                continue;
            }
            if (!check_if_rules_are_followed_for_current_number(i, safety_manual, page_order_rules[safety_manual[i]])){
                is_valid = false;
                break;
            }
        }
        if (is_valid){ 
            int middle_page_number = safety_manual[(safety_manual.size()-1) / 2];
            middle_page_number_sum += middle_page_number;
        }
    }
    cout << middle_page_number_sum << endl;
}