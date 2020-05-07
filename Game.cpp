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
  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      if(realboard[i][j] == '-'){
        int count = 0;
        if(realboard[i-1][j] == '*'){
          count += 1;
        }
        if(realboard[i+1][j] == '*'){
          count += 1;
        }
        if(realboard[i][j-1] == '*'){
          count += 1;
        }
        if(realboard[i][j+1] == '*'){
          count += 1;
        }
        if(realboard[i-1][j-1] == '*'){
          count += 1;
        }
        if(realboard[i-1][j+1] == '*'){
          count += 1;
        }
        if(realboard[i+1][j-1] == '*'){
          count += 1;
        }
        if(realboard[i+1][j-1] == '*'){
          count += 1;
        }
        realboard[i][j] = count;
      }
  }
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
    if(realboard[open_height][open_width] == '0'){
      showboard[open_height][open_width] = ' ';
      open(showboard, realboard, open_height+1, open_width);
      open(showboard, realboard, open_height-1, open_width);
      open(showboard, realboard, open_height, open_width+1);
      open(showboard, realboard, open_height, open_width-1);
    }
    else{
      showboard[open_height][open_width] = realboard[open_height][open_width];
    }
}

void flag(char showboard[]){//what if flag a flaged block - unflagged or send error
  int flag_height, flag_width;
  cin >> flag_height >> flag_width;
  while(flag_height >= height || flag_width >= width){
    cout << "Out of range! Please try again." << endl;
    cin >> flag_height >> flag_width;
  }
  if(showboard[flag_height][flag_width] == 'P'){
    showboard[flag_height][flag_width] = '-';
  }
  else if(showboard[flag_height][flag_width] != '-'){
    cout << "That was opened! Please try again." << endl;
    flag(showboard);
  }
  else{
    showboard[flag_height][flag_width] = 'P';
  }
}

void scaninput(string player_input,int height, int width, char showboard[], char realboard[]){
  switch(command)
  {
    case "Save":
      save();
    case "Restart"://asking are you sure to give it up and start a new game
      
    case "Open":
      int open_height, open_width;
      cin >> open_height >> open_width;
      while(open_height >= height || open_width >= width || showboard[open_height][open_width] != '-'){
        if(open_height >= height || open_width >= width){
          cout << "Out of range! Please try again." << endl;
          cin >> open_height >> open_width;
        }
        else if(showboard[open_height][open_width] == 'P'){
          cout << "That was flagged! Please try again." << endl;
          cin >> open_height >> open_width;
        }
        else if(showboard[open_height][open_width] != '-'){
          cout << "That was opened! Please try again." << endl;
          cin >> open_height >> open_width;
        }
      }
      open(showboard, realboard, open_height, open_width);
    case "Flag":
      flag(showboard)
    case "Time":
      
    case "Quit":
  }
}

bool keepon(char showboard[],int height, int width){//checking showboard have '*' or not
  int notopen = 0;
  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      if(showboard[i][j] == '*'){
        return false,false;
      }
      else if(showboard[i][j] == '-'){
        notopen += 1;
      }
    }
  }
  if(notopen == 0){
    return false,true;
  }
  else{
    return true,false;
  }
}
  
int main(){
  // player input: difficulty(number? or string?[simple/normal/hard/customized]), size(one number?[square], two number[rectangle]), number of mines[if player choose customized]
  string diff,player_input,game;
  int height, width, mines;
  bool goingon = true;
  bool win;
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
      for(int j = 0;j < width; ++j){
        realboard[i][j] = '-';
      }
    }
    producerealboard(realboard, height, width);
    printboard(showboard, height, width);
    cout << "Please take your first step: " << endl << "First Step: (Height, Width)";
    int firstheight, firstwidth;
    cin >> firstheight >> firstwidth;
    int tmp_mines = mines;
    while(tmp_mines > 0){
      producemine(height, width, realboard, firstheight, firstwidth);
      tmp_mines -= 1;
    }
    open(showboard, realboard, firstheight, firstwidth);
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
    cout << "Please input a command." << endl << "(Open / Flag / Save / Restart / Quit)"//ALL command;
    cin >> player_input;
    while (player_input != "Open" && player_input != "Flag" && player_input != "Save" && player_input != "Restart" && player_input != "Quit"){
      cout << "Invalid input! Please try again." << endl;
      cin >> player_input;
    }
    scaninput(player_input, height, width, showboard, realboard);
    goingon,win = keepon(showboard, height, width);
    if(goingon){
      printboard(showboard, height, width);
    }
  }
  if(win){
    printboard(showboard);
    cout << "You win!";
  }
  else{
    printboard(showboard);
    cout << "You lose!";
  }
  
}
