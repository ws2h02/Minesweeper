#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>
using namespace std;

void producemine(int height,int width, char **board, int firstheight, int firstwidth){
  //first step must not lose, if player choose a bomb in his first step, replace it to other block.
  bool bury = true;
  while(bury){
    srand(time(NULL));
    int x = rand() % height;
    int y = rand() % width;
    if (x >= firstheight-1 && x <= firstheight+1 && y >= firstwidth-1 && y <= firstwidth+1) bury = true;
    else if (board[x][y] == '*') bury = true;
    else {
        board[x][y] = '*';
        bury = false;
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
      cout << "Height (Maximum 100): ";
      cin >> height;
      while(height <= 0 || height > 100){
        cout << "Invaild input! Please try again." << endl;
        cin >> height;
      }
      cout << "Width (Maximum 100): ";
      cin >> width;
      while(width <= 0 || width > 100){
        cout << "Invaild input! Please try again." << endl;
        cin >> width;
      }
      cout << "Mines (At least 9 safe slots): ";
      cin >> mines;
      while(mines <= 0 || mines > height*width-9){
        cout << "Invaild input! Please try again." << endl;
        if(mines > height*width-9){
          cout << "Too many mines!" << endl;
        }
        cin >> mines;
      }
      break;
  }
}

void save(int height, int width, int step, int mines, char **showboard, char **realboard){
    ofstream fout;
    string filename;
    cout << "Please set the name for this savefile: ";
    cin >> filename;
    filename.append(".txt");
    fout.open(filename);
    fout << height << " " << width << " " << step << " " << mines << endl;
    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            if (showboard[i][j]==' ') fout << "0 ";
            else fout << showboard[i][j] << " ";
        }
    }
    fout << endl;
    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            fout << realboard[i][j] << " ";
        }
    }
    fout.close();
}

void printboard(char **board, int height, int width, int mines, int step){
  cout << "Mines Remained: " << mines << "   " << "Step Counter: " << step;
  cout << endl;
  cout << left;
  cout << "   ";
  for(int a = 0; a < width; ++a){
    cout << setw(3) << a;
  }
  cout << endl;
  for(int i = 0; i < height; ++i){
    cout << setw(3) << i;
    for(int j = 0; j < width; ++j){
      cout << setw(3) << board[i][j];  
    }
    cout << endl;
  }
}
  
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
    mines += 1
  }
  else if(showboard[flag_height][flag_width] != '-'){
    cout << "That was opened! Please try again." << endl;
    flag(showboard, height, width);
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

bool keepon(char **showboard, int height, int width, bool & win, int mines){//checking showboard have '*' or not
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
if(notopen == mines){
    win = true;
    return false;
  }
  else{
    win = false;
    return true;
  }
}

void playgame(char **showboard, char **realboard, int height, int width, int mines, int step){
  // repeat step 2 and 3 until player win
  bool goingon = true;
  bool win;
  string player_input;
  printboard(showboard, height, width, mines, step);
  auto start = chrono::system_clock::now();
  while( goingon ){
    // system output: gameboard
    // player input: command (game control, save and load)
    cout << "Please input a command." << endl << "(Open / Flag / Time / Save / Restart / Quit): ";//ALL command
    cin >> player_input;
    while (player_input != "Open" && player_input != "Flag" && player_input != "Time" && player_input != "Save" && player_input != "Restart" && player_input != "Quit"){
      cout << "Invalid input! Please try again." << endl;
      cin >> player_input;
    }
    if (player_input=="Time"){
        auto current = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = current-start;
        cout << "Time spent: ";
        int t = elapsed_seconds.count();
        int m = t/60;
        int s = t%60;
        cout << m << " minutes " << s << " seconds." << endl;
        continue;
    }
    if (player_input=="Restart"){
        cout << "Are you sure you want to restart?" << endl << "(Y/N): ";
        string confirm;
        cin >> confirm;
        while (confirm!="Y" && confirm!="N"){
            cout << "Invalid input! Please try again." << endl;
            cin >> confirm;
        }
        if (confirm=="N") continue;
        else {
            string diff;
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
            return;
        }
    }
    if (player_input=="Quit"){
        cout << "Are you sure?" << endl << "(Y/N): ";
        string confirm;
        cin >> confirm;
        while (confirm!="Y" && confirm!="N"){
            cout << "Invalid input! Please try again." << endl;
            cin >> confirm;
        }
        if (confirm=="Y") break;
        else continue;
    }
    scaninput(player_input, height, width, showboard, realboard , mines, step);
    goingon = keepon(showboard, height, width, win, mines);
    if(goingon){
      printboard(showboard, height, width, mines, step);
    }
  }
  if (player_input=="Quit") cout << "You quit successfully. See you next time!" << endl;
  else if(win){
    printboard(showboard, height, width, mines, step);
    cout << "You win!";
  }
  else{
    printboard(showboard, height, width, mines, step);
    cout << "You lose!";
  }
}

void load(){
  ifstream fin;
  string savefile;
  cout << "Loading file name: ";
  cin >> savefile;
  savefile.append(".txt");
  fin.open(savefile);
  while ( fin.fail() ) {
    cout << "Error in file opening!" << endl;
    exit(1);
    cout << "Loading file name: ";
    cin >> savefile;
    savefile += ".txt";
    fin.open(savefile);
  }
  //how to load the board
  int height, width, step, mines;
  fin >> height >> width >> step >> mines;
  char** showboard = new char*[height];
  for(int i = 0; i < height; ++i){
    showboard[i] = new char[width];
    for(int j = 0; j < width; ++j){
      char slot;
      fin >> slot;
      if (slot=='0') showboard[i][j]=' ';
      else showboard[i][j]=slot;
    }
  }
    
  char** realboard = new char*[height];
  for(int i = 0; i < height; ++i){
    realboard[i] = new char[width];
    for(int j = 0;j < width; ++j){
      fin >> realboard[i][j];
    }
  }
  fin.close();
  playgame(showboard, realboard, height, width, mines, step);
}

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
    while(firstwidth >= width || firstheight >= height){
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
