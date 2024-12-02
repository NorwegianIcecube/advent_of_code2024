#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

bool check_report_safety(vector<int> report)
{
    bool is_descending_or_ascending = false;
    bool is_difference_valid = true;

    bool is_descending = true;
    bool is_ascending = true;
    for (int j = 0; j < report.size() - 1; j++)
    {
        if (report[j] < report[j + 1])
        {
           is_descending = false;
        }
        if (report[j] > report[j + 1])
        {
            is_ascending = false;
        }


        if (abs(report[j] - report[j + 1]) > 3)
        {
            is_difference_valid = false;
        }
        if (abs(report[j] - report[j + 1]) < 1)
        {
            is_difference_valid = false;
        }
            
    }
    if (is_descending == true || is_ascending == true)
    {
        is_descending_or_ascending = true;
    }

    if (is_descending_or_ascending == true && is_difference_valid == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main() 
{
    vector<vector<int> > reports;

    ifstream infile("puzzle_input");
    string line;

    while (getline(infile, line))
    {
        vector<int> report;
        stringstream ss(line);
        string level;
        while (getline(ss, level, ' '))
        {
            report.push_back(stoi(level)); // Stoi is a function that converts a string to an integer
        }
        reports.push_back(report);
    }

    int number_of_safe_reports = 0;
    for (int i = 0; i < reports.size(); i++)
    {
        vector<int> report = reports[i];
        if (check_report_safety(report))
        {
            number_of_safe_reports++;
        }
        else
        {
            for (int j = 0; j < report.size(); j++)
            {
                vector<int> report_copy = report;
                report_copy.erase(report_copy.begin() + j); 
                if (check_report_safety(report_copy))
                {
                    number_of_safe_reports++; // Is it normal to nest code this much in c++ lol?
                    break;
                }
            }
        }
    }
    cout << number_of_safe_reports << endl;
}

    
