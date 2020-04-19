// COMPILE THIS FILE WITH g++ -std=c++11

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include <algorithm>    // std::find

using namespace std;

  struct State goal_state;


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

String print_state(struct State state){
  return  to_string(state.l_bank.chickens)+ ", " + to_string(state.l_bank.wolves) + ", " + to_string(state.l_bank.boat) +"\n" +to_string(state.r_bank.chickens)+ ", " + to_string(state.r_bank.wolves)+", " + to_string(state.r_bank.boat) + "\n";
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
  cout<<"l: chicken, wolves,boat"<<state.l_bank.chickens<<state.l_bank.wolves<<state.l_bank.boat<<endl;
  cout<<"r: chicken, wolves,boat"<<state.r_bank.chickens<<state.r_bank.wolves<<state.r_bank.boat<<endl;

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
  read_file(1, argv, init_state);
  read_file(2, argv, goal_state);
  frontier.push_back(init_state);
  print_state(frontier.back());
  succ(init_state);
  bfs();
  return 0;
}

bool bfs(struct State init_state){
	queue<struct State> frontier;
	queue<struct State> explored;
	frontier.push(init_state);
	cout<<loop(frontier,explored);
}

String loop(queue<struct State> &frontier,queue<struct State> &explored){
	//isgoal() check if is the goal;reture success:true
	isempty(frontier);
	
	//: then pop frontier to explored
	struct State poped=frontier.pop();
	explored.push(poped);
	if (isgoal(poped)){
		print_state(pop);
	}
	vector<struct State> tep=succ(poped);
	pull(tep);
	return print_state(pop)+loop(frontier,explored);
	//isfailure() check if more wolves than chickens;return fail
	//expand() 5 possible not in both set-> insert frontier 
}

void pull(queue<struct State> &frontier,queue<struct State> explored,vector<struct State> tep){
	for(int i;i<tep.size();i++){
		if(!isInsets(frontier,explored,tep.at(i))){
			frontier.push(tep.at(i));
		}
	}
}

bool isInsets(queue<struct State> frontier,queue<struct State> explored,struct State tep){
	for(int i=0;i<frontier.size();i++){
		if(tep==frontier.at(i)){
			return false;
		}
	}
	for(int n=0;n<explored.size();n++){
		if(tep==explored.at(n)){
			return false;
		}
	}
	return true;

}

void isempty(queue<struct State> frontier){
	if (frontier.size()<=0){
		cout<<"no way to finish the goal";
		exit(1);
	}	
}

bool isgoal(struct State poped){
	
	if(poped==goal_state){
		return true;
	}

}

bool isfailure(queue<struct State> frontier,queue<struct State> explored){
	if(frontier.l_bank.wolves>frontier.l_bank.chicken||frontier.r_bank.wolves>frontier.r_bank.chicken){
		return false;
	}
}

void expand(struct State frontier,struct State explored){
	
}
