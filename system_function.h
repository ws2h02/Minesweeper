#ifndef System
#define System
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
using namespace std;

void producemine(int height,int width, char **board, int firstheight, int firstwidth, int mines){
  //first step must be a '0' slot.
  int startslot = 0;
  for (int y=0;y<height;y++){
      for (int x=0;x<width;x++){
          if (y >= firstheight-1 && y <= firstheight+1 && x >= firstwidth-1 && x <= firstwidth+1) {
              startslot+=1;
              continue;
          }
      }
  }
  int count=0;
  int *slot = new int[height*width-startslot];
  for (int y=0;y<height;y++){
      for (int x=0;x<width;x++){
          if (y >= firstheight-1 && y <= firstheight+1 && x >= firstwidth-1 && x <= firstwidth+1) {
              count+=1;
              continue;
          }
          else slot[y*width+x-count]=y*width+x;
      }//creating a array withour starting slot and its neighbour.
  }
  srand((int)time(NULL));
  for (int i=0;i<height*width*15;i++){
      //shuffle the values many times inside the slot array.
      int random1=(rand() % (width*height-startslot));
      int random2=(rand() % (width*height-startslot));
      
      int temp=slot[random1];
      slot[random1]=slot[random2];
      slot[random2]=temp;
  }
  
  for (int i=0;i<mines;i++){
      //take numbers from slot array to be mines.
      int y=slot[i]/width;
      int x=slot[i]%width;
      board[y][x]='*';
  }
}
  
void producerealboard(char **realboard, int height, int width){
  //make the board with every slots labled with numbers.
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
  if(mines < 0){
    cout << "You flag too many mines!" << endl;
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
    //if player opens up all safe slots, they win.
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
        else {//make a new gameboard.
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
            producemine(height, width, realboard, firstheight, firstwidth, mines);
            producerealboard(realboard, height, width);
            open(showboard, realboard, firstheight, firstwidth, height, width);
            step += 1;
            bool win=false;
            bool firststepwin = keepon(showboard, height, width, win, mines);
            if (firststepwin==false){
              printboard(showboard, height, width, mines, step);
              cout << "You win!" << endl;
              return;
            }
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
    cout << "You win!" << endl;
  }
  else{
    printboard(showboard, height, width, mines, step);
    cout << "You lose!" << endl;
  }
  delete [] showboard;
  delete [] realboard;
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


#endif
