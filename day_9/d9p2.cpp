#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool check_next_n_spaces_empty(vector<string> &disk_map, int index, int n){
    for (int i = 0; i < n; i++){
        if (index+i+1 >= disk_map.size()){
            return false;
        }
        if (disk_map[index+i+1] != "."){
            return false;
        }
    }
    return true;
}

vector<string> move_file(vector<string> &disk_map, int file_begin_index, int file_end_index, int new_start_index){
    for (int i = file_begin_index; i <= file_end_index; i++){
        disk_map[new_start_index+i-file_begin_index] = disk_map[i];
        disk_map[i] = ".";
    }
    return disk_map;
}

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
    vector<string> compressed_disk_map = disk_map_extended;
    string last_file_id = "";
    for (int i = compressed_disk_map.size()-1; i >= 0; i--){
        string file_id = compressed_disk_map[i];
        if (compressed_disk_map[i] == "." || file_id == last_file_id){
            continue;
        }
        int file_end_index = i;
        int file_begin_index = i;
        while (compressed_disk_map[file_begin_index-1] == file_id){
            file_begin_index--;
        }
        int file_size = file_end_index-file_begin_index;
        for (int j = 0; j < file_begin_index; j++){
            if (compressed_disk_map[j] == "."){
                bool next_n_spaces_empty = check_next_n_spaces_empty(compressed_disk_map, j, file_size);
                if (next_n_spaces_empty){
                    compressed_disk_map = move_file(compressed_disk_map, file_begin_index, file_end_index, j);
                    break;
                }
            }
        }
        last_file_id = file_id;

    }

    // checksum
    long checksum = 0;
    for (int i = 0; i < compressed_disk_map.size(); i++){
        if (compressed_disk_map[i] == "."){
            continue;
        }
        checksum+= i*stoi(compressed_disk_map[i]);
    }
    cout << checksum << endl;
}