#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void producemine(int height,int width, char board[], int firstheight, int firstwidth){
  //first step must not lose, if player choose a bomb in his first step, replace it to other block.
  bool bury = true;
  while(bury){
    srand(time(NULL));
    int x = rand() % height;
    int y = rand() % width;
    if(x != firstheight && y != firstwidth){
      if(board[x][y] != '*'){
        board[x][y] = '*';
        bury = false;
      }
    }
  }
}
  
void producerealboard(char realboard[], int height, int width){//maybe useless
  
}

void gamesetting(string diff, int & height, int & width, int & mines;){
  switch(diff)
  {
    case "simple":
      height = 9;
      width = 9;
      mines = 10;
    case "normal":
      height = 16;
      width = 16;
      mines = 40;
    case "hard":
      height = 16;
      width = 30;
      mines = 99;
    case "customized":
      cout << "Height: ";
      cin >> height;
      cout << "Width: ";
      cin >> width;
      cout << "Mines: ";
      cin >> mines;
  }
}

void save(){
}

void load(){
  ofstream fout;
  string savefile;
  cout << "Loading file name: ";
  cin >> savefile;
  fout.open(savefile);
  while ( fout.fail() ) {
    cout << "Error in file opening!" << endl;
    exit(1);
    cout << "Loading file name: ";
    cin >> savefile;
    fout.open(savefile);
  }
  //how to load the board
  
  fout.close();
}

void printboard(char board[], int height, int width){
}
  
void open(char showboard[], char realboard[], int open_height, int open_width){
}

void flag(char showboard[], int flag_height, int flag_width){//what if flag a flaged block - unflagged or send error
}

void scaninput(string player_input,int height, int width, char showboard[], char realboard[]){
  switch(command)
  {
    case "Save & Quit":
      save();
    case "StartANewGame"://asking are you sure to give it up and start a new game
      
    case "Open":
      int open_height, open_width;
      cin >> open_height >> open_width;
      while(open_height >= height || open_width >= width){
        cout << "Invalid input! Please try again." << endl;
        cin >> open_height >> open_width;
      }
      open(showboard, realboard, open_height, open_width);
    case "Flag":
      int flag_height, flag_width;
      cin >> flag_height >> flag_width;
      while(flag_height >= height || flag_width >= width){
        cout << "Invalid input! Please try again." << endl;
        cin >> flag_height >> flag_width;
      }
      flag(showboard, flag_height, flag_width)
    case "Time":
      
    case "Quit without Saving":
  }
}

bool keepon(){
}
  
int main(){
  // player input: difficulty(number? or string?[simple/normal/hard/customized]), size(one number?[square], two number[rectangle]), number of mines[if player choose customized]
  string diff,player_input,game;
  int height, width, mines;
  bool goingon = true
  cout << "Welcome to Minesweeper: Word Edition!!"
  cout << "New Game or Load Game?" << endl << "(N / L)";
  cin >> game;
  while (game != "N" && game != "L"){
    cout << "Invalid input! Please try again." << endl;
    cin >> game;
  }
  if (game=="N"){
    cout << "Difficulty?" << endl << "(Simple / Normal / Hard / Custom)";
    cin >> diff;
    while (diff != "Simple" && diff != "Normal" && diff != "Hard" && diff != "Custom"){
      cout << "Invalid input! Please try again." << endl;
      cin >> diff;
    }
    gamesetting(diff, height, width, mines);
    
    char** showboard = new char*[height];
    for(int i = 0; i < height; ++i){
      showboard[i] = new int[width];
      for(int j = 0; j < width; ++j){
        showboard[i][j] = '-';
      }
    }
    
    char** realboard = new char*[height];
    for(int i = 0; i < height; ++i){
      realboard[i] = new int[width];
      for(int j = 0;j < width; ++j0{
        realboard[i][j] = ' ';
      }
    }
    producerealboard(realboard, height, width)
    printboard(showboard, height, width);
    cout << "Please take your first step: " << endl << "First Step: (Height, Width)";
    int firstheight, firstwidth;
    cin >> firstheight >> firstwidth;
    int tmp_mines = mines;
    while(tmp_mines > 0){
      producemine(height, width, realboard, firstheight, firstwidth);
      tmp_mines -= 1;
    }
    open(showboard,realboard, firstheight, firstwidth);
  }
  if (game=="L"){
    load();
  }

  // repeat step 2 and 3 until player win
` 
  printboard(showboard, height, width);
  while( goingon ){
    // system output: gameboard
    // player input: command (game control, save and load)
    cout << "Please input a command." << endl << "(Open / Flag / Save)"//ALL command;
    cin >> player_input;
    while (player_input != those command){
      cout << "Invalid input! Please try again." << endl;
      cin >> player_input;
    }
    scaninput(player_input, height, width, showboard, realboard);
    goingon = keepon();
    if(goingon){
      printboard(showboard, height, width);
    }
  }
  // system output: gameboard, win or lose
  // winning and losing situation
  printgameboard();//printrealboard
  cout << "You " << result << "!" << endl;
  
}
