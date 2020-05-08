# Minesweeper

Student name: Chan King Yeung     
UID: 3035683045     
GitHub Username: ws2h02     

Student name: Kwun Tang Kwai     
UID: 3035709605     
GitHub Username: KwunTangKwai     

Game description:         
This game is text-based minesweeper, where player will need to navigate safely through the minefield and locate the position of all the mines. After you safely opened all the safe slots, you win the game. However, if you ever opened a slot with mine, you lose!      
Whenever you opened a safe slot, it will show the number of mines next to it in all 8 directions. If you ever opened a slot with 0, the system will automatically opened all the slots of 0 connected to the slot you chose, and all the slots connected to them!

Features:         
1. Generate random game sets everytime 
(using ctime, cstdlib, iomanip, string)   
2. Include 4 difficulty settings using dynamic 2-D arrays        
3. Customize minefield size and number of mines using dynamic 2-D arrays
4. Save and load function using file input/output
(using fstream)             
5. Show the amount of time spent when called
(using chrono, ctime)              
6. Include step counter on screen            
7. Include restart function                     
8. Include flag system (Flag the mine) 
(Flag again will remove the flag instead)
  
Additionay libraries:
1. string
2. fstream
3. cstdlib
4. ctime
5. iomanip
6. chrono

Compilation and execution instructions: 
