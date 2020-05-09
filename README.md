# Minesweeper

Student name: Chan King Yeung     
UID: 3035683045     
GitHub Username: ws2h02     

Student name: Kwun Tang Kwai     
UID: 3035709605     
GitHub Username: KwunTangKwai   

Problem statement:                       
We would like to recreate the famous game "Minesweeper" in C++ in word edition as simlarly as possible, while our game can run only with typing input.

Game description:         
This game is text-based minesweeper, where player will need to navigate safely through the minefield and locate the position of all the mines. After you safely opened all the safe slots, you win the game. However, if you ever opened a slot with mine, you lose!      
Whenever you opened a safe slot, it will show the number of mines next to it in all 8 directions. If you ever opened a slot with 0, the system will automatically opened all the slots of 0 connected to the slot you chose, and all the slots connected to them!

Code Requirement:
1. Generation of random game sets or events
2. Data structures for storing game status
3. Dynamic memory management
4. File input/output
5. Program codes in multiple files

Features (vis-a-vis each of the items 1 to 5 listed under coding requirements above):         
1. Generate random game sets everytime 
(Using ctime, cstdlib, iomanip, string)
2. Using struct to save game setting data         
3. a. Include 4 difficulty settings using dynamic 2-D arrays           
   b. Customize minefield size and number of mines using dynamic 2-D arrays         
4. Save and load function using file input/output (Using fstream)
5. Separating function by player command and system control
6. Show the amount of time spent when called
(Using chrono, ctime)              
7. Include step counter on screen            
8. Include restart function                     
9. Include flag system (Flag the mine) 
  
Additionay libraries:
1. string
2. fstream
3. cstdlib
4. ctime
5. iomanip
6. chrono

Compilation and execution instructions: 
1. Choosing "New Game" or "Load Game" by inputting 'N' or 'L'.
2. a. If you choose "Load Game", please input the file name, then please jump to 6.   
   b. If you choose "New Game", please read on.
3. a. Choosing "Difficulty" by inputting "Simple", "Normal", "Hard", "Customized".  
   b. If you choose "Customized", please input the height, width and number of mines.  
   c. The maximum of the height and width is 100 and The maximum of the number of mines is Size(height* width) - 9 since there are at least 9 safe slots.   
4. Take your first step by inputting the X and Y (two integer), your first step and the nearly 8 slots must not be mines.
5. Please wait because producing the Minefield need some time, more time if the size is bigger.
6. Choosing your next move by inputting these 5 commands.    
   a. "Open": This command will let you inputting the X and Y (two integer), then that slot will be opened.   
   b. "Flag": This command will let you inputting the X and Y (two integer), then that slot will be flagged. If you flag a flagged slot, that slot will be unflagged.   
   c. "Save": This command will let you inputting file name, your game is saved. Next time when you start the game choose "Load Game" and input the same file name then you will load your save.   
   d. "Time": This command will show how much time you spent on this game.   
   e. "Quit": This command will let you quit the game.   
7. Open all safe slots and flag all the mines. Then, you will win the game!   
