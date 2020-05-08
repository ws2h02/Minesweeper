#include <iostream>
#include <string>
#include <chrono>
#include "control_function.h"
#include "system_function.h"
using namespace std;

int main(){
  // player input: difficulty(number? or string?[simple/normal/hard/customized]), size(one number?[square], two number[rectangle]), number of mines[if player choose customized]
  string diff,game;
  int height, width, mines, step;
  cout << "Welcome to Minesweeper: Word Edition!!";
  cout << "New Game or Load Game?" << endl << "(N / L): ";
  cin >> game;
  while (game != "N" && game != "L"){
    cout << "Invalid input! Please try again." << endl;
    cin >> game;
  }
  if (game=="N"){
    cout << "Difficulty?" << endl << "(Simple / Normal / Hard / Customized): ";
    cin >> diff;
    while (diff != "Simple" && diff != "Normal" && diff != "Hard" && diff != "Customized"){
      cout << "Invalid input! Please try again." << endl;
      cin >> diff;
    }
    gamesetting(diff, height, width, mines);
    
    char** showboard = new char*[height];
    for(int i = 0; i < height; ++i){
      showboard[i] = new char[width];
      for(int j = 0; j < width; ++j){
        showboard[i][j] = '-';
      }
    }
    
    char** realboard = new char*[height];
    for(int i = 0; i < height; ++i){
      realboard[i] = new char[width];
      for(int j = 0;j < width; ++j){
        realboard[i][j] = '-';
      }
    }
    step = 0;
    printboard(showboard, height, width, mines, step);
    cout << "Please take your first step: " << endl << "(X Y): ";
    int firstheight, firstwidth;
    cin >> firstwidth >> firstheight;
    while(firstwidth >= width || firstheight >= height || firstwidth < 0 || firstheight < 0){
          cout << "Out of range! Please try again." << endl;
          cin >> firstwidth >> firstheight;
        }
    cout << "Creating minefield..." << endl;
    int tmp_mines = mines;
    while(tmp_mines > 0){
      producemine(height, width, realboard, firstheight, firstwidth);
      tmp_mines -= 1;
    }
    producerealboard(realboard, height, width);
    open(showboard, realboard, firstheight, firstwidth, height, width);
    step += 1;
    playgame(showboard, realboard, height, width, mines, step);
  }
  if (game=="L"){
    load();
  }
}
