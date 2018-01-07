#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "menuEventHandler.h"

/*                GAME STRUCTURES                 */
typedef struct
{
    int adjB;//REPRESENTS NUMBER OF MINES IN THE AREA OF THAT CELL
    int B;//FLAG TO KNOW IF ITS A BOMB OR NOT
    int reveal;//FLAG TO KNOW IF ITS OPENED OR CLOSED CELL
    int mark;//FLAG TO KNOW WHICH TO DISPLAY (F-?-X) as F is FLAG-? is Question-X is DEFAULT CELL
    int checked;//FLAG TO KNOW IF OPEN NEIGHBOURS PASSED THROUGH THIS CELL OR NOT (COULD BE AS BASE CASE TO AVOID INFINITE RECURSION)
    int x;//CELL X POSITION (because i use gotoxy func. to access console window positions)
    int y;//CELL Y POSITION (because i use gotoxy func. to access console window positions)
} cell;
/*                            VARIABLES                 */
///GAME VARIABLES
cell **grid;//GRID POINTER TO POINTER
int currentX;//CURRENT CURSOR POSITION ON X-AXIS
int currentY;//CURRENT CURSOR POSITION ON Y-AXIS
int nMines;//NUMBER OF MINES ON THE GAME GRID
int flagCounter;//NUMBER OF FLAGS THE PLAYER MADE
int quesCounter;//NUMBER OF QUESTIONS THE PLAYER MADE
int droppedBombs;//FLAG TO CHECK IF ITS FIRST PLAYER MOVE OR NOT (TO DROP MINES AFTER FIRST MOVE)
int Increased;//FLAG TO NEVER INCREASE nMoves UNLESS SOMETHING OPENED FOR THE PLAYER
int nMoves;//TOTAL NUMBER OF MOVES THE PLAYER MADE
int unRevealed;//NUMBER OF UNREAVEALED CELLS ON THE GRID
char c;//TMP VAR. TO HOLD KEY PRESSES
/*                             FUNCTIONS                  */
///INIT FUNCTIONS
extern void initCell(cell** g );//INIT EACH CELL IN THE GRID WITH CERTAIN VALUES
extern cell** setup();//ALLOCATE MEMORY FOR THE GRID AND RUNS SERIES OF FUNCTIONS
extern void dropBombs(cell** c ,int nMines);//PUT MINES IN THE GAME
extern void checkNeighbours(cell** c );//PUT adjB VALUES FOR THE GAME CELLS

///SAVE&LOAD TO/FROM FILE
extern void save_game(char*fileName);//SAVES THE GAME
extern cell** load_game(char*fileName);//LOADS THE GAME

///GAME LOGIC STUFF
extern void gameLogic();
// CHECK IF THE USER LOST THE GAME and CALLS SERIES OF FUNCTIONS
extern int checkLosing(cell g);//g is the cell that made the player lose the game
extern int checkWining();//CHECK IF THE USER WON THE GAME USING check_Board FUNC. AND CALLS SERIES OF FUNCTIONS
extern int check_Board();//CHECK IF THE PLAYER WON THE GAME (unreavealed=nmines)
extern int check_Unrevealed(cell**g);//RETURNS THE NUMBER OF THE UNREVEALED CELLS
extern int checkCell(cell c);//RETURNS THE NUMBER OF BOMBS IN CERTAIN CELL
extern void sweep(cell g);//OPENING LOGIC
extern void openNeighbours(cell g);//RECURSION OPENING CELLS (REAL LOGIC OF THE GAME)
extern unsigned long long calculateScore();//CALCULATE THE PLAYER SCORE IF HE HAS WON

///DRAW FUNCTIONS
extern void drawGame(cell** g);// DRAWS THE WHOLE GAME WHEN THE GAME STARTS
extern void drawFrame();// DRAWS THE FRAME OF THE GAME
extern void drawCell(cell g,int nColor);//DRAW CERTAIN CELL WITH CERTAIN COLOR
extern void drawCell_DEFAULT(cell g);//DRAW CERTAIN CELL AS DEFAULT COLORS
extern void END_GAME_DEFEAT(cell**g,cell gr);//DRAWS CELL BY CELL USING THE drawCell_Defeated FUNC.
extern void drawCell_Defeated(cell g,cell gr);//DRAWS CERTAIN CELL AS THE GAME WAS LOST
extern void END_GAME_VICTORY(cell**g);//DRAWS THE GAME AS THE PLAYER HAS WON THE GAME

///DESTRUCTOR
extern void destructor(cell **g);//FREE MEMORY OF THE GAME GRID

///ERRORS MESSAGES HANDLING
extern void terminate();//FOR FILE CORRUPTION

#endif
