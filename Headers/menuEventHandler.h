#ifndef MENUEVENTHANDLER_H
#define MENUEVENTHANDLER_H
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "gameLogic.h"
#include "cmdNavigation.h"
/*                      SYSTEM ENUMS                                 */
enum gameState {MENU,OPTIONS,EXIT,GAME,LOAD,LEADERBOARD} SYSTEM;

/*                      VARIABLES                                 */
///SYSTEM VARIABLES
int esc;// flag to check whether im still in the menu or i entered another one
int RUNNING;//MAIN PROGRAM LOOP FLAG
int inGame;//FLAG TO KNOW IF THE USER IN GAME OR NOT
int i,j;//loop counters I KNOW ITS BAD TO PUT LOOP COUNTERS AS GLOBAL VARIABLES -> I'M SO LAZY xD
char fileName[20];//NAME OF THE FILE USER WANTS TO LOAD
char buffer; // to never lose clicked button on keyboard
int LOADED;//flag to check if the game was loaded or not
int CHOOSEN;//to scroll through main menu
int board_length;//LEADERBOARD HEIGHT
unsigned long long leaderboard_scores[256];//all scores in the leader board
char leaderboard_names[256][20];//all names in the leader board (String Array)
int found_name[256];//indicies of the line the player exists in file /* TOLD YOU WEIRD FILE HANDLING STUFF */
int found_length;//MAX LINE OF ABOVE ARRAY(MAX NUMBER IN IT)
char fileName[20];//FILE NAME TO LOAD FILE
int totalLines;//used in saving cause i did weird saving method

///PLAYER VARIABLES
// to initialize array of cells x is length
int height,width;//GAME WIDTH & HEIGHT MANAGABLE THROUGH OPTIONS
char playerName[20];//PLAYER NAME
unsigned long long score;//SCORE OF THE PLAYER AFTER HE WINS THE GAME

///time variables to handle time UI
time_t timeInit;//THE STARTING TIME OF THE GAME
time_t timeDif;//TIME USER SPENT IN GAME (current time - timeInit)
time_t timeIdle;//TO CHECK IF THE USER IS IDLE OR NOT

/*                           FUNCTIONS                         */
///SYSTEM INIT FUNCTIONS
extern void progStart();

///MENU HANDLING AND LOGIC
extern void menuHandler();//STARTS THE MAIN MENU AND ITS STUFF OF LOGIC
extern void menuLogic();//CHECK USER KEY PRESSES AND MOVES CURSOR TO CHOOSEN LINE
extern void optionsLogic() ;//SAME AS ABOVE BUT FOR OPTIONS
extern void leaderboardLogic();
extern void emptyName(char*str,int n);//EMPTIES A STRING GIVEN TO IT(by putting spaces)

///GAME STUFF
extern unsigned int checkLevel(unsigned long long x);//CHECK PLAYER LEVEL
extern unsigned long long final_score();//RETURNS THE FINAL SCORE FOR THE PLAYER AFTER HE FINISHES THE GAME
extern void updateUI();//PRINTS THE UI AROUND THE GAME WHILE GAME IS RUNNING

///SEARCHING AND SORTING STUFF
extern int search_leaderboard_names(char* pname);//searches for the given  string in the leaderboard_names array
extern void bubbleSort(unsigned long long arr[],size_t s);//BUBBLE SORT FOR THE LEADERBOARD
extern void swap(unsigned long long *pr1,unsigned long long* pr2);

///SAVING AND LOADING STUFF
/*   SORRY I USED REALLY BAD AND WEIRD METHOD TO SAVE AND LOAD BECAUSE I KNEW SO LITTLE ABOUT FILES IN C WHEN I MADE THIS PROJECT*/
extern void save_score();//SAVES SCORE
extern void load_score(char *PlayerName);//LOADS PLAYER SCORE LINE BY LINE


#endif // MENUEVENTHANDLER_H
