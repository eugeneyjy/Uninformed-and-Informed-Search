// COMPILE THIS FILE WITH g++ -std=c++11

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
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

void print_state(struct State state){
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
  if(act == 0){
    // Put one chickens in the boat
    state.r_bank.chickens -= 1;
    state.l_bank.chickens += 1;
  }else if(act == 1){
    // Put two chickens in the boat
    state.r_bank.chickens -= 2;
    state.l_bank.chickens += 2;
  }else if(act == 2){
    // Put one wolf in the boat
    state.r_bank.wolves -= 1;
    state.l_bank.wolves += 1;
  }else if(act == 3){
    // Put one wolf one chicken in the boat
    state.r_bank.wolves -= 1;
    state.r_bank.chickens -= 1;
    state.l_bank.wolves += 1;
    state.l_bank.chickens += 1;
  }else if(act == 4){
    // Put two wolves in the boat
    state.r_bank.wolves -= 2;
    state.l_bank.wolves += 2;
  }
  state.l_bank.boat = !state.l_bank.boat;
  state.r_bank.boat = !state.r_bank.boat;
}

bool check_state(struct State state){
  if(state.l_bank.chickens < 0 || state.r_bank.chickens < 0 || state.l_bank.wolves < 0 || state.r_bank.wolves < 0){
    return false;
  }
  if(state.l_bank.chickens != 0){
    if(state.l_bank.chickens < state.l_bank.wolves){
      return false;
    }
  }
  if(state.r_bank.chickens != 0){
    if(state.r_bank.chickens < state.r_bank.wolves){
      return false;
    }
  }
  return true;
}

// Generate successor states reachable from state
 vector<struct State> succ(struct State state){
  struct State states[5];
  vector<struct State> successors;
  for(int i = 0; i < 5; i++){
    states[i] = state;
    states[i].parent = &state;
  }
  // Do action to each successor, put into successors if valid
  for(int i = 0; i < 5; i++){
    actions(states[i], i);
    if(check_state(states[i]) == true){
      successors.push_back(states[i]);
    }
  }
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
  vector<struct State> expanded;
  read_file(1, argv, init_state);
  read_file(2, argv, goal_state);
  expanded = succ(init_state);
  for(int i = 0; i < expanded.size(); i++){
    print_state(expanded[i]);
  }
  return 0;
}
