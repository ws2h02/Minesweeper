#include <iostream>
#include <string>
#include "control_function.h"
#include "system_function.h"
using namespace std;

struct Settingset{
  string diff;
  string game;
  int height;
  int width;
  int mines;
  int step;
};

int main(){
  // player input: difficulty(number? or string?[simple/normal/hard/customized]), size(one number?[square], two number[rectangle]), number of mines[if player choose customized]
  Settingset setting;
  cout << "Welcome to Minesweeper: Word Edition!!";
  cout << "New Game or Load Game?" << endl << "(N / L): ";
  cin >> setting.game;
  while (setting.game != "N" && setting.game != "L"){
    cout << "Invalid input! Please try again." << endl;
    cin >> setting.game;
  }
  if (setting.game=="N"){
    cout << "Difficulty?" << endl << "(Simple / Normal / Hard / Customized): ";
    cin >> setting.diff;
    while (setting.diff != "Simple" && setting.diff != "Normal" && setting.diff != "Hard" && setting.diff != "Customized"){
      cout << "Invalid input! Please try again." << endl;
      cin >> setting.diff;
    }
    gamesetting(setting.diff, setting.height, setting.width, setting.mines);
    
    char** showboard = new char*[setting.height];
    for(int i = 0; i < setting.height; ++i){
      showboard[i] = new char[setting.width];
      for(int j = 0; j < setting.width; ++j){
        showboard[i][j] = '-';
      }
    }//we show this board to player.
    
    char** realboard = new char*[setting.height];
    for(int i = 0; i < setting.height; ++i){
      realboard[i] = new char[setting.width];
      for(int j = 0;j < setting.width; ++j){
        realboard[i][j] = '-';
      }
    }//this board is for the program.
    setting.step = 0;
    printboard(showboard, setting.height, setting.width, setting.mines, setting.step);
    cout << "Please take your first step: " << endl << "(X Y): ";
    int firstheight, firstwidth;
    cin >> firstwidth >> firstheight;
    while(firstwidth >= setting.width || firstheight >= setting.height || firstwidth < 0 || firstheight < 0){
          cout << "Out of range! Please try again." << endl;
          cin >> firstwidth >> firstheight;
        }
    cout << "Creating minefield..." << endl;
    producemine(setting.height, setting.width, realboard, firstheight, firstwidth, setting.mines);
    producerealboard(realboard, setting.height, setting.width);
    open(showboard, realboard, firstheight, firstwidth, setting.height, setting.width);
    setting.step += 1;
    bool win=false;
    bool firststepwin = keepon(showboard, setting.height, setting.width, win, setting.mines);
    if (firststepwin==false){
      printboard(showboard, setting.height, setting.width, setting.mines, setting.step);
      cout << "You win!" << endl;
      return 0;
    }
    playgame(showboard, realboard, setting.height, setting.width, setting.mines, setting.step);
  }
  if (setting.game=="L"){
    load();
  }
}
