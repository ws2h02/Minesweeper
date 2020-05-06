#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void producemine(){
  //first step must not lose, if player choose a bomb in his first step, replace it to other block.
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
    default:
      cout << "Invalid input" << endl;
      cout << "Reinput the difficulty: ";
      cin >> diff;
      gamesetting(diff);
    producegameboard(height, width, mines);
  }
}

void save(){
}

void load(){
}

void printgameboard(){
}

void scaninput(string player_input){
}

bool keepon(){
}
  
int main(){
  // player input: difficulty(number? or string?[simple/normal/hard/customized]), size(one number?[square], two number[rectangle]), number of mines[if player choose customized]
  string diff,player_input;
  bool goingon = true
  cout << "Welcome to Minesweeper: Word Edition !!"
  cout << "New Game?" << endl << "Load Game?" << endl << "(N/L)";
  cin >> game;
  while (game!="N" && game!="L"){
    cout << "invalid input! Please try again" << endl;
    cin >> game;
  }
  if (game=="N"){
    cout << "Difficulty?" << endl << "(simple / normal / hard / custom)";
    cin >> diff;
    gamesetting(diff);
    // repeat step 2 and 3 until player win
    while( goingon() ){
    // system output: gameboard
      printgameboard();
    // player input: command (game control, save and load)
      cout << "Please input a command (open / flag / : ";
      cin >> player_input;
      scaninput(player_input);
      goingon = keepon();
    }
   if (game=="L"){
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
  }
  // system output: gameboard, win or lose
  printgameboard();
  cout << "You " << result << "!" << endl;
  
}
