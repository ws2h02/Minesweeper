#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

void producemine(int height,int width, char **board, int firstheight, int firstwidth){
  //first step must not lose, if player choose a bomb in his first step, replace it to other block.
  bool bury = true;
  while(bury){
    srand(time(NULL));
    int x = rand() % height;
    int y = rand() % width;
    if(x != firstheight && y != firstwidth){
      if(x != firstheight-1 && y != firstwidth){
        if(x != firstheight+1 && y != firstwidth){
          if(x != firstheight && y != firstwidth-1){
            if(x != firstheight && y != firstwidth+1){
              if(x != firstheight-1 && y != firstwidth-1){
                if(x != firstheight-1 && y != firstwidth+1){
                  if(x != firstheight+1 && y != firstwidth-1){
                    if(x != firstheight+1 && y != firstwidth+1){
                      if(board[x][y] != '*'){
                        board[x][y] = '*';
                        bury = false;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
  
void producerealboard(char **realboard, int height, int width){
  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      if(realboard[i][j] == '-'){
        int count = 0;
        if(i-1 >= 0){
          if(realboard[i-1][j] == '*'){
            count += 1;
          }
        }
        if(i+1 < height){
          if(realboard[i+1][j] == '*'){
            count += 1;
          }
        }
        if(j-1 >= 0){
          if(realboard[i][j-1] == '*'){
            count += 1;
          }
        }
        if(j+1 < width){
          if(realboard[i][j+1] == '*'){
            count += 1;
          }
        }
        if(i-1 >= 0 && j-1 >= 0){
          if(realboard[i-1][j-1] == '*'){
            count += 1;
          }
        }
        if(i-1 >= 0 && j+1 < width){
          if(realboard[i-1][j+1] == '*'){
            count += 1;
          }
        }
        if(i+1 < height && j-1 >= 0){
          if(realboard[i+1][j-1] == '*'){
            count += 1;
          }
        }
        if(i+1 < height && j+1 < width){
          if(realboard[i+1][j+1] == '*'){
            count += 1;
          }
        }
        realboard[i][j] = count + '0';
      }
    }
  }
}

void gamesetting(string diff, int & height, int & width, int & mines){
  int n;
  if(diff == "Simple"){
    n = 0;
  }
  else if(diff == "Normal"){
    n = 1;
  }
  else if(diff == "Hard"){
    n = 2;
  }
  else if(diff == "Customized"){
    n = 3;
  }
  switch(n)
  {
    case 0:
      height = 9;
      width = 9;
      mines = 10;
      break;
    case 1:
      height = 16;
      width = 16;
      mines = 40;
      break;
    case 2:
      height = 16;
      width = 30;
      mines = 99;
      break;
    case 3:
      cout << "Height: ";
      cin >> height;
      while(height <= 0 || height > 100){
        cout << "Invaild input! Please try again.";
        cin >> height;
      }
      cout << "Width: ";
      cin >> width;
      while(width <= 0 || height > 100){
        cout << "Invaild input! Please try again.";
        cin >> width;
      }
      cout << "Mines: ";
      cin >> mines;
      while(mines <= 0 || mines > height*width){
        cout << "Invaild input! Please try again.";
        cin >> mines;
      }
      break;
  }
}

void showtime(){
}

void quit(){
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

void printboard(char **board, int height, int width){
  cout << "    ";
  for(int a = 0; a < width; ++a){
    cout << setw(3) << a << " ";
  }
  cout << endl;
  for(int i = 0; i < height; ++i){
    cout << setw(3) << i << " ";
    for(int j = 0; j < width; ++j){
      cout << setw(3) << board[i][j] << " ";  
    }
    cout << endl;
  }
}
  
void open(char **showboard, char **realboard, int open_height, int open_width, int height, int width){
    if(realboard[open_height][open_width] == '0' && showboard[open_height][open_width] == '-'){
      showboard[open_height][open_width] = '0';
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
      showboard[open_height][open_width] = realboard[open_height][open_width];
    }
}

void flag(char **showboard, int height, int width){//what if flag a flaged block - unflagged or send error
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
    flag(showboard, height, width);
  }
  else{
    showboard[flag_height][flag_width] = 'P';
  }
}

void scaninput(string player_input,int height, int width, char **showboard, char **realboard){
  int command;
  if(player_input == "Save"){
    command = 0;
  }
  else if(player_input == "Restart"){
    command = 1;
  }
  else if(player_input == "Open"){
    command = 2;
  }
  else if(player_input == "Flag"){
    command = 3;
  }
  else if(player_input == "Time"){
    command = 4;
  }
  else if(player_input == "Quit"){
    command = 5;
  }
  
  switch(command)
  {
    case 0:
      save();
      break;
    case 1://asking are you sure to give it up and start a new game
      break;
    case 2:
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
      open(showboard, realboard, open_height, open_width, height, width);
      break;
    case 3:
      flag(showboard, height, width);
      break;
    case 4:
      showtime();
      break;
    case 5:
      quit();
      break;
  }
}

bool keepon(char **showboard, int height, int width, bool & win){//checking showboard have '*' or not
  int notopen = 0;
  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      if(showboard[i][j] == '*'){
        win = false;
        return false;
      }
      else if(showboard[i][j] == '-'){
        notopen += 1;
      }
    }
  }
if(notopen == 0){
    win = true;
    return false;
  }
  else{
    win = false;
    return true;
  }
}

void playgame(char **showboard, char **realboard, int height, int width){
  // repeat step 2 and 3 until player win
  bool goingon = true;
  bool win;
  string player_input;
  printboard(showboard, height, width);
  while( goingon ){
    // system output: gameboard
    // player input: command (game control, save and load)
    cout << "Please input a command." << endl << "(Open / Flag / Save / Restart / Quit): ";//ALL command
    cin >> player_input;
    while (player_input != "Open" && player_input != "Flag" && player_input != "Save" && player_input != "Restart" && player_input != "Quit"){
      cout << "Invalid input! Please try again." << endl;
      cin >> player_input;
    }
    scaninput(player_input, height, width, showboard, realboard);
    goingon = keepon(showboard, height, width, win);
    if(goingon){
      printboard(showboard, height, width);
    }
  }
  if(win){
    printboard(showboard, height, width);
    cout << "You win!";
  }
  else{
    printboard(showboard, height, width);
    cout << "You lose!";
  }
}
  
int main(){
  // player input: difficulty(number? or string?[simple/normal/hard/customized]), size(one number?[square], two number[rectangle]), number of mines[if player choose customized]
  string diff,game;
  int height, width, mines;
  cout << "Welcome to Minesweeper: Word Edition!!";
  cout << "New Game or Load Game?" << endl << "(N / L): ";
  cin >> game;
  while (game != "N" && game != "L"){
    cout << "Invalid input! Please try again." << endl;
    cin >> game;
  }
  if (game=="N"){
    cout << "Difficulty?" << endl << "(Simple / Normal / Hard / Custom): ";
    cin >> diff;
    while (diff != "Simple" && diff != "Normal" && diff != "Hard" && diff != "Custom"){
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
    printboard(showboard, height, width);
    cout << "Please take your first step: " << endl << "First Step (Height, Width): ";
    int firstheight, firstwidth;
    cin >> firstheight >> firstwidth;
    int tmp_mines = mines;
    while(tmp_mines > 0){
      producemine(height, width, realboard, firstheight, firstwidth);
      tmp_mines -= 1;
    }
    producerealboard(realboard, height, width);
    open(showboard, realboard, firstheight, firstwidth, height, width);
    playgame(showboard, realboard, height, width);
  }
  if (game=="L"){
    load();
  }
}
