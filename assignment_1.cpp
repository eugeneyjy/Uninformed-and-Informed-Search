// COMPILE THIS FILE WITH g++ -std=c++11

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct Bank{
  int chickens;
  int wolves;
  bool boat;
};

struct State{
  struct Bank l_bank; // Left bank
  struct Bank r_bank; // Right bank
  struct State* parent = NULL; // keep track on parent state
};

// Validate command line arguments count
void valid_argc(int argc){
  if(argc != 5){
    cout << "Wrong number of argument." << endl;
    cout << "command line arguments:" << endl;
    cout << "<initial state file> <goal state file> <mode> <output file>" << endl;
    exit(0);
  }
}

void print_state(struct State& state){
  cout << state.l_bank.chickens << ", " << state.l_bank.wolves << ", " << state.l_bank.boat << endl;
  cout << state.r_bank.chickens << ", " << state.r_bank.wolves << ", " << state.r_bank.boat << endl;
}

void parse_line(string line, struct Bank& bank){
  stringstream ss(line);
  string word;
  getline(ss, word, ','); // Get word by comma delimiter
  bank.chickens = stoi(word); // Put word into struct field
  getline(ss, word, ',');
  bank.wolves = stoi(word);
  getline(ss, word);
  bank.boat = stoi(word);
}

// Read file info to state from file at index of argv
void read_file(int index, char* argv[], struct State& state){
  ifstream infile;
  infile.open(argv[index]);
  string line;
  getline(infile, line);  // Read line from infile
  parse_line(line, state.l_bank); // Parse line info to left bank in state
  getline(infile, line);
  parse_line(line,state.r_bank);
  infile.close();
}

// actions to generate successor according to act given in arguments
void actions(struct State& state, int act){
  if(act == 1){
    // Put one chickens in the boat
  }else if(act == 2){
    // Put two chickens in the boat
  }else if(act == 3){
    // Put one wolf in the boat
  }else if(act == 4){
    // Put one wolf one chicken in the boat
  }else if(act == 5){
    // Put two wolves in the boat
  }
}

// Generate successor states reachable from state
struct State* succ(struct State state){
  struct State states[5];
  struct State* successors;
  // Do action to each successor, put into successors if valid
  return successors;
}

// Write result to file at index position of argv
void write_file(int index, char* argv[], struct State* states){
  ofstream outfile;
  outfile.open(argv[index]);
  // Write result to file
  outfile.close();
}

int main(int argc, char* argv[]){
  valid_argc(argc);
  struct State init_state;
  struct State goal_state;
  read_file(1, argv, init_state);
  read_file(2, argv, goal_state);
  succ(init_state);
  return 0;
}
