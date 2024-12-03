#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

int main() {
    ifstream infile("puzzle_input");
    string line;
    string puzzle_input;
    while (getline(infile, line)) {
        puzzle_input += line + "\n";
    }

    long sum = 0;
    bool do_mul = true;
    
    regex re("(do\\(\\)|don't\\(\\)|mul\\(\\d{1,3},\\d{1,3}\\))");
    
    for (sregex_iterator i = sregex_iterator(puzzle_input.begin(), puzzle_input.end(), re); i != sregex_iterator(); i++) {
        smatch match = *i;
        string match_str = match.str();
        if (match_str == "do()") {
            do_mul = true;
        }
        else if (match_str == "don't()") {
            do_mul = false;
        }
        else if (regex_match(match_str, regex("mul\\(\\d{1,3},\\d{1,3}\\)"))) {
            int num1 = stoi(match_str.substr(4, match_str.find(",") - 4));
            int num2 = stoi(match_str.substr(match_str.find(",") + 1, match_str.size() - match_str.find(",") - 2));
            if (do_mul == true) {
                sum += num1 * num2;
            }
        }
    }
    cout << sum << endl;
}