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

vector<int> re_order_safety_manual(vector<int> safety_manual, unordered_map<int, vector<int>> page_order_rules){
    vector<int> new_safety_manual = {safety_manual[safety_manual.size()-1]};
    safety_manual.pop_back();
    while (safety_manual.size() > 0){
        int new_page = safety_manual[safety_manual.size()-1];
        safety_manual.pop_back();

        if (page_order_rules.find(new_page) == page_order_rules.end()){
            new_safety_manual.push_back(new_page);
            continue;
        }
        
        bool added = false;
        for (int i = new_safety_manual.size(); i > 0; i-=1){
            vector<int> potential_new_safety_manual(new_safety_manual);
            potential_new_safety_manual.insert(potential_new_safety_manual.begin() + i, new_page);
            if (check_if_rules_are_followed_for_current_number(i, potential_new_safety_manual, page_order_rules[new_page])){
                new_safety_manual.insert(new_safety_manual.begin() + i, new_page);
                added = true;
                break;
            }
        }
        if (!added){
            new_safety_manual.insert(new_safety_manual.begin(), new_page);
            
        }
    }
    return new_safety_manual;
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
            continue;
        }
        else{
            safety_manual = re_order_safety_manual(safety_manual, page_order_rules);
            int middle_page_number = safety_manual[(safety_manual.size()-1) / 2];
            middle_page_number_sum += middle_page_number;
        }
    }
    cout << middle_page_number_sum << endl;
}