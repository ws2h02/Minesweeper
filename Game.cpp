#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void producemine(int height,int width, int & mines, char board[][]){
  //first step must not lose, if player choose a bomb in his first step, replace it to other block.
  bool bury = true;
  while(bury){
    srand(time(NULL));
    int x = rand() % height;
    int y = rand() % width;
    if(x != firststepheight && y != firststepwidth){
      if(board[x][y] != ''){
        board[x][y] = '';
        bury = false;
      }
    }
}

void producegameboard(int height, int width, int mines){
  
}

void gamesetting(string diff){
  int height, width, mines;
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
  //input?
  cout << "Please choose your starting slot: ";
  int firstmove;
  cin >> firstmove;
  producegameboard(height, width, mines, firstmove);
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
}

void printgameboard(){
}

void scaninput(string player_input){
  string command = ;//input first X letter
  string value = ;//input letter left
  switch(player_input)
  {
    case "Save & Quit":
      
    case "StartANewGame"://asking are you sure to give it up and start a new game
      
    case "Open":
      
    case "Flag"://what if flag a flaged block - unflagged or send error
    
    case "Time":
      
    case "Quit without Saving":
}

bool keepon(){
}
  
int main(){
  // player input: difficulty(number? or string?[simple/normal/hard/customized]), size(one number?[square], two number[rectangle]), number of mines[if player choose customized]
  string diff,player_input,game;
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
    gamesetting(diff);
  }
  if (game=="L"){
    load();
  }

  // repeat step 2 and 3 until player win

  printgameboard();//May be need to separate game board and show board
  while( goingon ){
    // system output: gameboard
    // player input: command (game control, save and load)
    cout << "Please input a command." << endl << "(Open(o) / flag(f) / save&quit(s))";
    cin >> player_input;
    scaninput(player_input);
    goingon = keepon();
    if(goingon){
      printgameboard();
    }
  }
  // system output: gameboard, win or lose
  printgameboard();//printrealboard
  cout << "You " << result << "!" << endl;
  
}
