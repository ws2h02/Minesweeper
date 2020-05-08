#ifndef Control
#define Control
#include <iostream>
#include <string>
using namespace std;

void open(char **showboard, char **realboard, int open_height, int open_width, int height, int width){
    if(realboard[open_height][open_width] == '0' && showboard[open_height][open_width] == '-'){
      showboard[open_height][open_width] = ' ';
      if(open_height+1 < height){
        open(showboard, realboard, open_height+1, open_width, height, width);
      }
      if(open_height-1 >= 0){
        open(showboard, realboard, open_height-1, open_width, height, width);
      }
      if(open_width+1 < width){
        open(showboard, realboard, open_height, open_width+1, height, width);
      }
      if(open_width-1 >= 0){
        open(showboard, realboard, open_height, open_width-1, height, width);
      }
      if(open_height+1 < height && open_width+1 < width){
        open(showboard, realboard, open_height+1, open_width+1, height, width);
      }
      if(open_height+1 < height && open_width-1 >= 0){
        open(showboard, realboard, open_height+1, open_width-1, height, width);
      }
      if(open_height-1 >= 0 && open_width+1 < width){
        open(showboard, realboard, open_height-1, open_width+1, height, width);
      }
      if(open_height-1 >= 0 && open_width-1 >= 0){
        open(showboard, realboard, open_height-1, open_width-1, height, width);
      }
    }
    else{
      if(realboard[open_height][open_width] != '0'){
        showboard[open_height][open_width] = realboard[open_height][open_width];
      }
    }
}

void flag(char **showboard, int height, int width, int & mines){//what if flag a flaged block - unflagged or send error
  int flag_height, flag_width;
  cin >> flag_width >> flag_height;
  while(flag_height >= height || flag_width >= width){
    cout << "Out of range! Please try again." << endl;
    cin >> flag_width >> flag_height;
  }
  if(showboard[flag_height][flag_width] == 'P'){
    showboard[flag_height][flag_width] = '-';
    mines += 2;
  }
  else if(showboard[flag_height][flag_width] != '-'){
    cout << "That was opened! Please try again." << endl;
    flag(showboard, height, width, mines);
  }
  else{
    showboard[flag_height][flag_width] = 'P';
  }
}


void scaninput(string player_input,int height, int width, char **showboard, char **realboard, int & mines, int & step){
  int command;
  if(player_input == "Save"){
    command = 0;
  }
  else if(player_input == "Open"){
    command = 1;
    step += 1;
  }
  else if(player_input == "Flag"){
    command = 2;
    mines -= 1;
  }
  
  switch(command)
  {
    case 0:
      save(height, width, step, mines, showboard, realboard);
      break;
    case 1:
      int open_height, open_width;
      cout << "Please input your next move:" << endl << "(X Y): ";
      cin >> open_width >> open_height;
      while(open_height >= height || open_width >= width || showboard[open_height][open_width] != '-'){
        if(open_height >= height || open_width >= width){
          cout << "Out of range! Please try again." << endl;
          cin >> open_width >> open_height;
        }
        else if(showboard[open_height][open_width] == 'P'){
          cout << "That was flagged! Please try again." << endl;
          cin >> open_width >> open_height;
        }
        else if(showboard[open_height][open_width] != '-'){
          cout << "That was opened! Please try again." << endl;
          cin >> open_width >> open_height;
        }
      }
      open(showboard, realboard, open_height, open_width, height, width);
      break;
    case 2:
      cout << "Please input the position:" << endl << "(X, Y): ";
      flag(showboard, height, width, mines);
      break;
  }
}

#endif
