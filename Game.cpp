#include <iostream>
#include <string>
using namespace std;

void producemine(){
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
  cout << "Please input the game setting:" >> endl;
  cout << "Difficulty: ";
  cin >> diff;
  gamesetting(diff);
  // repeat step 2 and 3 until player win
  while( goingon() ){
  // system output: gameboard
    printgameboard();
  // player input: command (game control, save and load)
    cout << "Please input a command: ";
    cin >> player_input;
    scaninput(player_input);
    goingon = keepon();
  }
  // system output: gameboard, win or lose
  printgameboard();
  cout << "You " << result << "!" << endl;
  
}
