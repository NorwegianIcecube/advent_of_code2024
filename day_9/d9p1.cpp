#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    ifstream infile("puzzle_input");
    string line;
    vector<int> disk_map;
    getline(infile, line);
    for (int i = 0; i < line.size(); i++){
        disk_map.push_back(line[i] - '0');
    }


    vector<string> disk_map_extended;
    int id = 0;
    for (int i = 0; i < disk_map.size(); i++){
        if (i % 2 == 0){
            for (int j = 0; j < disk_map[i]; j++){
                disk_map_extended.push_back(to_string(id));
            }
            if (disk_map[i] != 0){
                id++;
            }
        } else {
            for (int j = 0; j < disk_map[i]; j++){
                disk_map_extended.push_back(".");
            }
        }
    }

    // compress
    vector<string> compressed_disk_map;
    for (int i = 0; i < disk_map_extended.size(); i++){
        if (disk_map_extended[i] == "."){
            while (disk_map_extended[disk_map_extended.size() - 1] == "."){
                disk_map_extended.pop_back();
            }
            if (i >= disk_map_extended.size()){
                break;
            }
            compressed_disk_map.push_back(disk_map_extended[disk_map_extended.size() - 1]);
            disk_map_extended.pop_back();
        }
        else {
            compressed_disk_map.push_back(disk_map_extended[i]);
        }
    }

    // checksum
    long checksum = 0;
    for (int i = 0; i < compressed_disk_map.size(); i++){
        checksum+= i*stoi(compressed_disk_map[i]);
    }
    cout << checksum << endl;
}