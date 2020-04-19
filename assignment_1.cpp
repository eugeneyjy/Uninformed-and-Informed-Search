// COMPILE THIS FILE WITH g++ -std=c++11

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <deque>
#include <algorithm>    // std::find
#include <limits.h>

using namespace std;

struct Bank{
  int chickens;
  int wolves;
  bool boat;
};

struct State{
  int depth = 0;
  struct Bank l_bank; // Left bank
  struct Bank r_bank; // Right bank
  struct State* parent = NULL; // keep track on parent state
};

struct State goal_state;
vector<struct State*> graph;

// Validate command line arguments count
void valid_argc(int argc){
  if(argc != 5){
    cout << "Wrong number of argument." << endl;
    cout << "command line arguments:" << endl;
    cout << "<initial state file> <goal state file> <mode> <output file>" << endl;
    exit(0);
  }
}


string print_state(struct State state){
  return  to_string(state.l_bank.chickens)+ ", " + to_string(state.l_bank.wolves) + ", " + to_string(state.l_bank.boat) +"\n" +to_string(state.r_bank.chickens)+ ", " + to_string(state.r_bank.wolves)+", " + to_string(state.r_bank.boat) + "\n";
}

void print_states(vector<struct State> states){
  for(int i = states.size()-1; i >= 0; i--){
    cout << print_state(states[i]) << endl;
  }
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

void move_chick(struct State& state, int amount){
  if(state.l_bank.boat == 1){
    state.l_bank.chickens -= amount;
    state.r_bank.chickens+= amount;
  }else{
    state.r_bank.chickens -= amount;
    state.l_bank.chickens+= amount;
  }
}

void move_wolves(struct State& state, int amount){
  if(state.l_bank.boat == 1){
    state.l_bank.wolves -= amount;
    state.r_bank.wolves+= amount;
  }else{
    state.r_bank.wolves -= amount;
    state.l_bank.wolves+= amount;
  }
}

// actions to generate successor according to act given in arguments
void actions(struct State& state, int act){
  if(act == 0){
    // Put one chickens in the boat
    move_chick(state, 1);
  }else if(act == 1){
    // Put two chickens in the boat
    move_chick(state, 2);
  }else if(act == 2){
    // Put one wolf in the boat
    move_wolves(state, 1);
  }else if(act == 3){
    // Put one wolf one chicken in the boat
    move_chick(state, 1);
    move_wolves(state, 1);
  }else if(act == 4){
    // Put two wolves in the boat
    move_wolves(state, 2);
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

void cp_state(struct State* state_1, struct State state_2){
  state_1->l_bank.chickens = state_2.l_bank.chickens;
  state_1->l_bank.wolves = state_2.l_bank.wolves;
  state_1->l_bank.boat = state_2.l_bank.boat;
  state_1->r_bank.chickens = state_2.r_bank.chickens;
  state_1->r_bank.wolves = state_2.r_bank.wolves;
  state_1->r_bank.boat = state_2.r_bank.boat;
  state_1->parent = state_2.parent;
  state_1->depth = state_2.depth;
}

// Generate successor states reachable from state
 vector<struct State> succ(struct State* state){
  struct State states[5];
  vector<struct State> successors;
  for(int i = 0; i < 5; i++){
    cp_state(&states[i], *state);
    states[i].parent = state;
    states[i].depth = state->depth + 1;
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

bool cmp_bank(struct Bank bank_1, struct Bank bank_2){
  if(bank_1.chickens == bank_2.chickens && bank_1.wolves == bank_2.wolves
    && bank_1.boat == bank_2.boat){
      return true;
    }
    return false;
}

bool cmp_state(struct State state_1, struct State state_2){
  if(cmp_bank(state_1.l_bank, state_2.l_bank) && cmp_bank(state_1.r_bank, state_2.r_bank)){
      return true;
  }
  return false;
}

bool isempty(deque<struct State> frontier){
	if (frontier.size()<=0){
		return true;
	}
  return false;
}

bool isgoal(struct State poped){
	if(cmp_state(poped, goal_state)){
		return true;
	}

}

bool isInsets(deque<struct State> frontier,deque<struct State> explored,struct State tep){
	for(int i=0;i<frontier.size();i++){
		if(cmp_state(tep, frontier.at(i))){
			return true;
		}
	}
	for(int n=0;n<explored.size();n++){
		if(cmp_state(tep, explored.at(n))){
			return true;
		}
	}
	return false;
}

void pull(deque<struct State> &frontier,deque<struct State> explored,vector<struct State> tep){
	for(int i = 0;i<tep.size();i++){
		if(!isInsets(frontier,explored,tep.at(i))){
			frontier.push_back(tep.at(i));
		}
	}
}

vector<struct State> form_solution(){
  vector<struct State> solution;
  struct State* curr_state = graph.back();
  while(curr_state != NULL){
    solution.push_back(*curr_state);
    curr_state = curr_state->parent;
  }
  return solution;
}

void delete_graph(){
  for(int i = 0; i < graph.size(); i++){
    delete graph[i];
  }
  graph.clear();
}

bool bfs(struct State init_state, int& count){
  deque<struct State> frontier;
  deque<struct State> explored;
  struct State* curr_state;
  frontier.push_back(init_state);
  while(1){
    if(isempty(frontier)){
      return false;
    }
    curr_state = new struct State;
    cp_state(curr_state, frontier.front());
    graph.push_back(curr_state);
    frontier.pop_front();
    if(isgoal(*(graph.back()))){
      return true;
    }
    count++;
    explored.push_back(*(graph.back()));
    vector<struct State> temp = succ(graph.back());
    pull(frontier, explored, temp);
  }
}

bool dls(struct State init_state, int& count, int limit){
  deque<struct State> frontier;
  deque<struct State> explored;
  int depth = 0;
  struct State* curr_state;
  frontier.push_back(init_state);
  while(1){
    if(frontier.empty()){
      return false;
    }
    curr_state = new struct State;
    cp_state(curr_state, frontier.back());
    graph.push_back(curr_state);
    frontier.pop_back();
    if(isgoal(*(graph.back()))){
      return true;
    }
    count++;
    explored.push_back(*(graph.back()));
    if(curr_state->depth < limit){
      vector<struct State> temp = succ(graph.back());
      pull(frontier, explored, temp);
    }
  }
}


bool dfs(struct State init_state, int& count){
  return dls(init_state, count, INT_MAX);
}

bool iddfs(struct State init_state, int& count){
  int curr_limit = 0;
  int limit = INT_MAX;
  bool success;
  while(curr_limit < limit){
    cout << "curr_limit: " << curr_limit << endl;
    success = dls(init_state, count, curr_limit);
    if(success){
      return true;
    }else{
      curr_limit++;
      delete_graph();
    }
  }
}

void print_result(bool success, vector<struct State> solution, int expanded){
  if(success){
    print_states(solution);
    cout << expanded << " nodes expanded" << endl;
  }else{
    cout << "No solution found" << endl;
  }
}

int main(int argc, char* argv[]){
  valid_argc(argc);
  struct State init_state;
  vector<struct State> solution;
  bool success;
  int count = 0;
  read_file(1, argv, init_state);
  read_file(2, argv, goal_state);
  // success = bfs(init_state, count);
  // success = dfs(init_state, count);
  success = iddfs(init_state, count);
  solution = form_solution();
  print_result(success, solution, count);
  delete_graph();
  return 0;
}
