#include "gameLogic.h"
//CONSTANT GAME COLORS
const int DEFAULT_CELL_COLOR=15;
const int SELECTED_CELL_COLOR=240;
const int FLAG_CELL_COLOR=76;
const int QUES_CELL_COLOR=110;
const int BOMB_COLOR=12;
const int INITIAL_ADJ_CELL_COLOR=1;
const int FILLER_COLOR=0;

///                                             INIT FUNCTIONS
void initCell(cell** g /*g[][width]*/)
{
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            g[i][j].adjB=0;//TODO
            g[i][j].B=0;
            g[i][j].reveal=0;
            g[i][j].mark=0;
            g[i][j].checked=0;
            //initial game x,y position
            g[i][j].x=j;
            g[i][j].y=i;
        }
    }
}

cell** setup()
{
    flagCounter=0;
    quesCounter=0;
    droppedBombs=0;
    currentX=0;
    currentY=0;
    nMoves=0;
    unRevealed=width*height;
//Formula Given
    nMines=1+(width*height)/10;
    cell** g = (cell **)malloc(height * sizeof(cell *));
    if(g==NULL)
    {
        system("cls");
        gotoxy(0,0);
        printf("ERROR COULDNT ALLOCATE MEMORY FOR THE GRID");
        exit(1);
    }
    for (i=0; i<height; i++)
    {
        g[i] = (cell *)malloc(width * sizeof(cell));
        if(g[i]==NULL)
        {
            system("cls");
            gotoxy(0,0);
            printf("ERROR COULDNT ALLOCATE MEMORY FOR THE GRID");
            exit(1);
        }
    }

    initCell(g);//TO INIT EVERY CELL TO DEFAULT VALUES
    if(inGame)drawGame(g);
    timeInit=time(NULL);
    timeIdle=time(NULL);
    return g;

}

void dropBombs(cell** c,int nMines)
{
    while(nMines)
    {
        int posX=rand()%width;// random position
        int posY=rand()%height;
        //we wont to avoid currentX and Current Y Cause the mines are dropped after first open
        if(!c[posY][posX].B&&posY!=currentY&&posX!=currentX)
        {
            c[posY][posX].B++;
            nMines--;
        }
    }
}

void checkNeighbours(cell** c)
{
    int x,y;

    for(y=0; y<height; y++)
    {
        for(x=0; x<width; x++)
        {
            if(y==0)
            {
                if(x==0)
                {
                    /*
                    0,?
                    ?,?

                    */
                    if(checkCell(c[y+1][x+1]))c[y][x].adjB++;
                    if(checkCell(c[y][x+1]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x]))c[y][x].adjB++;

                }
                else if(x==width-1)
                {
                    /*
                    ?,0
                    ?,?
                    */
                    if(checkCell(c[y+1][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x]))c[y][x].adjB++;
                }
                else
                {
                    /*
                    ?,0,?
                    ?,?,?
                    */
                    if(checkCell(c[y+1][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x+1]))c[y][x].adjB++;
                    if(checkCell(c[y][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y][x+1]))c[y][x].adjB++;
                }
            }
            else if(y==height-1)
            {

                if(x==0)
                {
                    /*
                    ?,?
                    0,?
                    */
                    if(checkCell(c[y-1][x+1]))c[y][x].adjB++;
                    if(checkCell(c[y][x+1]))c[y][x].adjB++;
                    if(checkCell(c[y-1][x]))c[y][x].adjB++;

                }
                else if(x==width-1)
                {
                    /*
                    ?,?
                    ?,0
                    */
                    if(checkCell(c[y-1][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y-1][x]))c[y][x].adjB++;

                }
                else
                {
                    /*
                    ?,?,?
                    ?,0,?
                    */
                    if(checkCell(c[y-1][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y-1][x]))c[y][x].adjB++;
                    if(checkCell(c[y-1][x+1]))c[y][x].adjB++;
                    if(checkCell(c[y][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y][x+1]))c[y][x].adjB++;

                }
            }
            else
            {

                if(x==0)
                {

                    /*
                      ?,?
                      0,?
                      ?,?
                    */
                    if(checkCell(c[y-1][x]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x]))c[y][x].adjB++;
                    if(checkCell(c[y-1][x+1]))c[y][x].adjB++;
                    if(checkCell(c[y][x+1]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x+1]))c[y][x].adjB++;

                }
                else if(x==width-1)
                {
                    /*
                    ?,?
                    ?,0
                    ?,?
                    */
                    if(checkCell(c[y-1][x]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x]))c[y][x].adjB++;
                    if(checkCell(c[y-1][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x-1]))c[y][x].adjB++;

                }
                else
                {
                    /*
                        ?,?,?
                        ?,0,?
                        ?,?,?

                    */
                    if(checkCell(c[y-1][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y-1][x]))c[y][x].adjB++;
                    if(checkCell(c[y-1][x+1]))c[y][x].adjB++;
                    if(checkCell(c[y][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y][x+1]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x-1]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x]))c[y][x].adjB++;
                    if(checkCell(c[y+1][x+1]))c[y][x].adjB++;

                }
            }
        }
    }
}

///                                     SAVE&LOAD TO/FROM FILE(SO BAD TECHNIQUE DONT TRY TO UNDERSTAND THAT SHIT)

void save_game(char*fileName)
{
    FILE *f;
    f=fopen(fileName,"w");// i will write or overwrite only for each time i save
    char temp[10];//TEMP. JUST TO USE itoa FUNCTION INSTEAD OF IMPLEMENTING ONE
    fprintf(f,"%s\n",itoa(width,temp,10));
    fprintf(f,"%s\n",itoa(height,temp,10));
    fprintf(f,"%s\n",itoa(nMoves,temp,10));
    fprintf(f,"%s\n",itoa(nMines,temp,10));
    fprintf(f,"%s\n",itoa(flagCounter,temp,10));
    fprintf(f,"%s\n",itoa(quesCounter,temp,10));
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            //SAVING ALL THE ATTRIBUTES OF EACH CELL IN GAME
            fprintf(f,"%s\n",itoa( grid[i][j].adjB,temp,10));
            fprintf(f,"%s\n",itoa(grid[i][j].B,temp,10));
            fprintf(f,"%s\n",itoa( grid[i][j].reveal,temp,10));
            fprintf(f,"%s\n",itoa( grid[i][j].mark,temp,10));
            fprintf(f,"%s\n",itoa( grid[i][j].x,temp,10));
            fprintf(f,"%s\n",itoa( grid[i][j].y,temp,10));
            if(i==height-1&&j==width-1)fprintf(f,"%s",itoa(grid[i][j].checked,temp,10));
            else fprintf(f,"%s\n",itoa(grid[i][j].checked,temp,10));
        }
    }
    fclose(f);
}

cell** load_game(char*fileName)
{
    droppedBombs=1;
    currentX=0;
    currentY=0;
    timeInit=time(NULL);
    nMines=1+(width*height)/10;
    FILE *f;
    f=fopen(fileName,"r");// i will write or overwrite only for each time i save
    if(f==NULL)
    {
        system("CLS");
        setColor(12);
        printf("COULDN'T FIND THE REQUESTED FILE PLEASE RE-ENTER THE FILE NAME OR START A NEW GAME\n");
        setColor(8);
        system("pause");
        SYSTEM=MENU;
        inGame=0;
        esc=1;
        return setup();
    }
    else
    {
        char BUFFER[10];//TEMP. JUST TO USE itoa FUNCTION INSTEAD OF IMPLEMENTING ONE
        if(!fgets(BUFFER,10,f))
        {
            terminate();
            fclose(f);
            return setup();
        }
        else width=atoi(BUFFER);
        if(!fgets(BUFFER,10,f))
        {
            terminate();
            fclose(f);
            return setup();
        }
        else height=atoi(BUFFER);
        if(height>0&&height<151&&width>0&&width<41)
        {
            //MAKING THE GRID

            cell** g = (cell **)malloc(height * sizeof(cell *));
            if(g==NULL)
            {
                system("cls");
                printf("ERROR COULDNT ALLOCATE MEMORY FOR THE GRID\n");
                exit(1);
            }
            for (i=0; i<height; i++)
            {
                g[i] = (cell *)malloc(width * sizeof(cell));
                if(g[i]==NULL)
                {
                    system("cls");
                    printf("ERROR COULDNT ALLOCATE MEMORY FOR THE GRID\n");
                    exit(1);
                }
            }
            if(!fgets(BUFFER,10,f))
            {
                terminate();
                destructor(g);
                fclose(f);
                return setup();
            }
            else nMoves=atoi(BUFFER);
            if(!fgets(BUFFER,10,f))
            {
                terminate();
                destructor(g);
                fclose(f);
                return setup();
            }
            else if(nMines!=atoi(BUFFER))
            {
                terminate();
                destructor(g);
                fclose(f);
                return setup();
            }
            if(!fgets(BUFFER,10,f))
            {
                terminate();
                destructor(g);
                fclose(f);
                return setup();
            }
            else flagCounter=atoi(BUFFER);
            if(!fgets(BUFFER,10,f))
            {
                terminate();
                destructor(g);
                fclose(f);
                return setup();
            }
            else quesCounter=atoi(BUFFER);
            for(i=0; i<height; i++)
            {
                for(j=0; j<width; j++)
                {
                    //SAVING ALL THE ATTRIBUTES OF EACH CELL IN GAME
                    if(!fgets(BUFFER,10,f))
                    {
                        terminate();
                        destructor(g);
                        fclose(f);
                        return setup();
                    }
                    else g[i][j].adjB=atoi(BUFFER);
                    if(!fgets(BUFFER,10,f))
                    {
                        terminate();
                        destructor(g);
                        fclose(f);
                        return setup();
                    }
                    else g[i][j].B=atoi(BUFFER);
                    if(!fgets(BUFFER,10,f))
                    {
                        terminate();
                        destructor(g);
                        fclose(f);
                        return setup();
                    }
                    else g[i][j].reveal=atoi(BUFFER);
                    if(!fgets(BUFFER,10,f))
                    {
                        terminate();
                        destructor(g);
                        fclose(f);
                        return setup();
                    }
                    else g[i][j].mark=atoi(BUFFER);
                    if(!fgets(BUFFER,10,f))
                    {
                        terminate();
                        destructor(g);
                        fclose(f);
                        return setup();
                    }
                    else g[i][j].x=atoi(BUFFER);
                    if(!fgets(BUFFER,10,f))
                    {
                        terminate();
                        destructor(g);
                        fclose(f);
                        return setup();
                    }
                    else g[i][j].y=atoi(BUFFER);
                    if(!fgets(BUFFER,10,f))
                    {
                        terminate();
                        destructor(g);
                        fclose(f);
                        return setup();
                    }
                    else g[i][j].checked=atoi(BUFFER);
                }
            }

            if(fgets(BUFFER,10,f))
            {
                terminate();
                destructor(g);
                fclose(f);
                return setup();
            }
            fclose(f);
            unRevealed=check_Unrevealed(g);
            timeIdle=time(NULL);
            drawGame(g);
            return g;
        }
        else
        {
            terminate();
            fclose(f);
            return setup();
        }
    }

}

///                                     GAME LOGIC STUFF

void gameLogic()
{

    if(_kbhit())
    {
        buffer=_getch();
        timeIdle=time(NULL);
        switch(buffer)
        {
        /// ON EVERY MOVE WE DRAW THE PREVIOUS CELL WITH DEFAULT COLORS AND CHANGE THE NEW POSITION WITH THE NEW COLOR
    case (char)224:
        buffer=_getch();
        if(buffer==(char)72){
            drawCell_DEFAULT(grid[currentY][currentX]);
            if(currentY>0)currentY--;
            drawCell(grid[currentY][currentX],SELECTED_CELL_COLOR);
        }else if(buffer==(char)75){
            drawCell_DEFAULT(grid[currentY][currentX]);
            if(currentX>0)currentX--;
            drawCell(grid[currentY][currentX],SELECTED_CELL_COLOR);
        }else if(buffer==(char)80){
            drawCell_DEFAULT(grid[currentY][currentX]);
            if(currentY<height-1)currentY++;
            drawCell(grid[currentY][currentX],SELECTED_CELL_COLOR);
           }else if(buffer==(char)77){
            drawCell_DEFAULT(grid[currentY][currentX]);
            if(currentX<width-1)currentX++;
            drawCell(grid[currentY][currentX],SELECTED_CELL_COLOR);
           }
            break;
        case (char)13:


            //we are ready to drop bombs B) *Bad Eminem Joke :v*
            if(!droppedBombs)
            {
                dropBombs(grid,nMines);
                checkNeighbours(grid);
                droppedBombs=1;
            }
            sweep(grid[currentY][currentX]);
            drawCell(grid[currentY][currentX],SELECTED_CELL_COLOR);
            break;
        case 'm':
        case 'M':

            if(nMoves)///Why Would You Put Flags When u didnt open anycell ?
            {
                if(!grid[currentY][currentX].checked)
                {

                    if(grid[currentY][currentX].mark<2)
                    {

                        grid[currentY][currentX].reveal=1;
                        grid[currentY][currentX].mark++;
                        if(grid[currentY][currentX].mark==1)
                        {
                            nMoves++;
                            flagCounter++;
                        }
                        if(grid[currentY][currentX].mark==2)
                        {
                            quesCounter++;
                            flagCounter--;
                        }

                    }
                    else
                    {
                        grid[currentY][currentX].reveal=0;
                        grid[currentY][currentX].mark=0;
                        nMoves--;
                        quesCounter--;
                    }
                }
            }
            drawCell(grid[currentY][currentX],SELECTED_CELL_COLOR);
            break;
        case (char)27:

            system("cls");
            setColor(12);
            printf("Do You Want To Save The Game?\nclick y for yes anything else otherwise\n");
            setColor(13);
            c=_getch();

            if(c=='y'||c=='Y')
            {
                setColor(11);
                printf("Enter The File Name (e.g:test.txt)\nNote That if You didn't open at least one cell the Game wont be saved\nEnter \"Cancel\" To Cancel The Process\n");
                setColor(15);
                printf("File Name:");
                scanf("%s",fileName);
                if(nMoves&&strcmp(fileName,"cancel")&&strcmp(fileName,"Cancel"))save_game(fileName);

            }
            esc=1;
            inGame=0;
            SYSTEM=MENU;
            setColor(8);
            break;
        }
    }
}

int checkLosing(cell g)
{

    if(g.B==1)
    {
        gotoxy(0,0);
        setColor(12);
        printf("  You Died!!                          ");
        END_GAME_DEFEAT(grid,g);
        Sleep(1100);
        gotoxy(2,1);
        setColor(15);
        printf("                                                     ");//to clear the line
        gotoxy(2,1);
        system("pause");
        esc=1;
        inGame=0;
        SYSTEM=MENU;
        setColor(8);
        system("CLS");
        Sleep(200);
        return 1;
    }
    return 0;
}

int checkWining()
{
    if(check_Board())
    {
        score=calculateScore();
        gotoxy(0,0);
        setColor(9);
        printf("  Congratulations!! You Have Scored %llu                         ",score);
        END_GAME_VICTORY(grid);
        Sleep(1100);
        gotoxy(2,1);
        setColor(15);
        printf("                                                     ");//to clear the line
        gotoxy(2,1);
        save_score();
        system("pause");
        esc=1;
        inGame=0;
        SYSTEM=MENU;
        setColor(8);
        gotoxy(0,0);
        system("CLS");
        Sleep(200);
        return 1;
    }
    return 0;
}

int check_Board()
{
    if(unRevealed==nMines)return 1;
    else return 0;
}
/// THIS ONE IS USED WHEN I LOAD FILES CAUSE I DONT SAVE IT (TOLD YOU SHIT WAY TO HANDLE FILES)
int check_Unrevealed(cell**g)
{
    int x;
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            if(!g[i][j].checked)x++;
        }
    }
    return x;

}

int checkCell(cell c)
{
    return c.B;
}

void sweep(cell g)
{
    Increased=1;
    //BASE CASE
    //if(g.checked)return;
    if(g.adjB&&g.reveal)
    {
        int flagCount=0;
        int notReaveledCount=0;///to never increase nMoves if notreaveled = flag count
        // int totalFlags=g.adjB;
        ///FROM LEFT TOP TO RIGHT BOTTOM (top to bottom per col.)
        if(g.x>0&&g.y>0){
            if(grid[g.y-1][g.x-1].mark==1)
                flagCount++;

                if(grid[g.y-1][g.x-1].reveal==0||grid[g.y-1][g.x-1].mark==1)
                notReaveledCount++;
        }

        if(g.x>0){
            if(grid[g.y][g.x-1].mark==1)
                flagCount++;
                if(grid[g.y][g.x-1].reveal==0||grid[g.y][g.x-1].mark==1)
                    notReaveledCount++;
        }
        if(g.x>0&&g.y<height-1){
            if(grid[g.y+1][g.x-1].mark==1)
                flagCount++;
                if(grid[g.y+1][g.x-1].reveal==0||grid[g.y+1][g.x-1].mark==1)
                notReaveledCount++;
        }

        if(g.y>0){
            if(grid[g.y-1][g.x].mark==1)
                flagCount++;
                if(grid[g.y-1][g.x].reveal==0||grid[g.y-1][g.x].mark==1)
                    notReaveledCount++;
        }
        if(g.y<height-1){
            if(grid[g.y+1][g.x].mark==1)
                flagCount++;
             if(grid[g.y+1][g.x].reveal==0||grid[g.y+1][g.x].mark==1)
                notReaveledCount++;
        }
        if(g.y>0&&g.x<width-1){
            if(grid[g.y-1][g.x+1].mark==1)
                flagCount++;
                if(grid[g.y-1][g.x+1].reveal==0||grid[g.y-1][g.x+1].mark==1)
                    notReaveledCount++;

        }
        if(g.x<width-1){
            if(grid[g.y][g.x+1].mark==1)
                flagCount++;
                if(grid[g.y][g.x+1].reveal==0||grid[g.y][g.x+1].mark==1)
                    notReaveledCount++;

        }
        if(g.y<height-1&&g.x<width-1){
            if(grid[g.y+1][g.x+1].mark==1)
                flagCount++;
                if(grid[g.y+1][g.x+1].reveal==0||grid[g.y+1][g.x+1].mark==1)
                notReaveledCount++;
        }
        if(g.adjB==flagCount)
        {
            /*
                  ?,?,?
                  ?,0,?
                  ?,?,?
            *////FROM LEFT TOP TO RIGHT BOTTOM top to bottom per col
            if(g.x>0&&g.y>0)openNeighbours(grid[g.y-1][g.x-1]);
            if(g.x>0)openNeighbours(grid[g.y][g.x-1]);
            if(g.x>0&&g.y<height-1)openNeighbours(grid[g.y+1][g.x-1]);

            if(g.y>0)openNeighbours(grid[g.y-1][g.x]);
            if(g.y<height-1)openNeighbours(grid[g.y+1][g.x]);

            if(g.y>0&&g.x<width-1)openNeighbours(grid[g.y-1][g.x+1]);
            if(g.x<width-1)openNeighbours(grid[g.y][g.x+1]);
            if(g.y<height-1&&g.x<width-1)openNeighbours(grid[g.y+1][g.x+1]);
            ///nMoves++ if user opened cell using flag number method if its already open wont increase
           if(Increased&&notReaveledCount!=flagCount){
           nMoves++;
            Increased=0;
           }

            return;
        }
    }
    grid[g.y][g.x].checked=1;
    grid[g.y][g.x].reveal=1;
    openNeighbours(g);


    drawCell(g,SELECTED_CELL_COLOR);

}

///THE REAL GAME LOGIC
void openNeighbours(cell g) /*     USING FLOOD FILL ALGORITHM OR FLOODING WHATEVER YOU CALL IT */
{

    ///base case
    if(g.checked||g.mark==1)return;



    /* BODY OF THE ALGORITHM*/
    grid[g.y][g.x].reveal=1;
    unRevealed--;
    //CHECKING IF THE PLAYER WON THE GAME
    if(checkWining())return;

// TO MAKE SURE NOT TO PRINT ?
    grid[g.y][g.x].mark=0;
//TO MAKE SURE NEVER CHECK IT AGAIN
    grid[g.y][g.x].checked=1;
    //CHECK LOSING
    if(checkLosing(g))return;

    drawCell_DEFAULT(grid[g.y][g.x]);
    ///ANOTHER CASE AFTER CHANGING ATTRIBUTES
    //if it holds number return
    if(g.adjB){
            if(Increased){nMoves++;
                        Increased=0;
            }
            return;
    }
//RECURSION
    if(g.x>0&&g.y>0)openNeighbours(grid[g.y-1][g.x-1]);
    if(g.x>0)openNeighbours(grid[g.y][g.x-1]);
    if(g.x>0&&g.y<height-1)openNeighbours(grid[g.y+1][g.x-1]);

    if(g.y>0)openNeighbours(grid[g.y-1][g.x]);
    if(g.y<height-1)openNeighbours(grid[g.y+1][g.x]);

    if(g.y>0&&g.x<width-1)openNeighbours(grid[g.y-1][g.x+1]);
    if(g.x<width-1)openNeighbours(grid[g.y][g.x+1]);
    if(g.y<height-1&&g.x<width-1)openNeighbours(grid[g.y+1][g.x+1]);
   ///GLOBAL VARIABLE CHANGED THROUGH SWEEP (TO INCREASE nMoves ONCE IN WHOLE ALGORITHM)
    if(Increased){
            nMoves++;
            Increased=0;
    }

}

unsigned long long calculateScore()
{
//USING GIVEN FORMULA
///SO BIG NUMBER EVEN UNSIGNED LONG LONG WONT HOLD IT ON BIG BOARDS SO IM REDUCING IT INSTEAD OF MAKING A STRUCTURE FOR IT
/// making it row^3 * cols ^3 instead of row^4 * cols ^4
    return (height*height*height*/**height*/width*width*width/**width*/)/((time(NULL)-timeInit)*nMoves);
}


///                                         DRAW FUNCTIONS

void drawGame(cell** g )
{

    drawFrame();
    ///BETTER IMPLEMENTATION
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            drawCell_DEFAULT(g[i][j]);
        }
    }
    drawCell(g[currentY][currentX],SELECTED_CELL_COLOR);
}

void drawFrame()
{
    setColor(136);
    gotoxy(2,2);
    for(i=-1; i<=width; i++)
    {
        printf(" ");
    }
    for(i=-1; i<height; i++)
    {
        gotoxy(2,i+3);
        printf(" ");
        gotoxy(width+3,i+3);
        printf(" ");
    }
    gotoxy(2,height+3);
    for(i=-1; i<=width; i++)
    {
        printf(" ");
    }
    setColor(8);
}

void drawCell(cell g,int nColor)
{
    gotoxy(g.x+3,g.y+3);
    setColor(nColor);
    if(!g.reveal)
    {
        printf("X");
    }
    else if(g.mark==1)
    {
        setColor(nColor);
        printf("F");
    }
    else if(g.mark==2)
    {
        setColor(nColor);
        printf("?");
    }
    else
    {
        if( !g.B)
        {

            if(g.adjB)
            {

                if(g.adjB<=2)
                {
                    setColor(nColor);
                    printf("%d",g.adjB);
                }
                else if(g.adjB<=4)
                {
                    setColor(nColor);
                    printf("%d",g.adjB);
                }
                else if(g.adjB<=6)
                {
                    setColor(nColor);
                    printf("%d",g.adjB);
                }
                else
                {
                    setColor(nColor);
                    printf("%d",g.adjB);
                }

            }
            else
            {
                printf(" ");
            }
        }
        else
        {
            setColor(nColor);
            printf("*");
        }
    }
    setColor(8);
}

void drawCell_DEFAULT(cell g)
{
    ///AVOIDING EMPTY SPACE AND FRAME
    gotoxy(g.x+3,g.y+3);
    setColor(DEFAULT_CELL_COLOR);
    if(!g.reveal)
    {
        printf("X");
    }
    else if(g.mark==1)
    {
        setColor(FLAG_CELL_COLOR);
        printf("F");
    }
    else if(g.mark==2)
    {
        setColor(QUES_CELL_COLOR);
        printf("?");
    }
    else
    {
        if( !g.B)
        {

            if(g.adjB)
            {

                if(g.adjB<=2)
                {
                    setColor(INITIAL_ADJ_CELL_COLOR+1);
                    printf("%d",g.adjB);
                }
                else if(g.adjB<=4)
                {
                    setColor(INITIAL_ADJ_CELL_COLOR+2);
                    printf("%d",g.adjB);
                }
                else if(g.adjB<=6)
                {
                    setColor(INITIAL_ADJ_CELL_COLOR+3);
                    printf("%d",g.adjB);
                }
                else
                {
                    setColor(INITIAL_ADJ_CELL_COLOR+4);
                    printf("%d",g.adjB);
                }

            }
            else
            {
                printf(" ");
            }
        }
        else
        {
            setColor(BOMB_COLOR);
            printf("*");
        }
    }
}

void END_GAME_DEFEAT(cell** g,cell gr)
{
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            g[i][j].reveal=1;
        }
    }
    for(i=0; i<height; i++)
    {
        setColor(FILLER_COLOR);
        for(j=0; j<width; j++)
        {
            drawCell_Defeated(grid[i][j],gr);
        }
        printf("\n");
    }
}

void drawCell_Defeated(cell g,cell gr)
{
    gotoxy(g.x+3,g.y+3);
    setColor(DEFAULT_CELL_COLOR);
    if(g.x==gr.x&&g.y==gr.y)
    {
        setColor(BOMB_COLOR);
        printf("!");
        return;
    }
    if(g.mark&&!g.B)
    {
        setColor(FLAG_CELL_COLOR);
        printf("-");
    }
    else if(g.mark&&g.B)
    {
        setColor(BOMB_COLOR);
        printf("*");
    }
    else
    {
        if( !g.B)
        {

            if(g.adjB)
            {

                if(g.adjB<=2)
                {
                    setColor(INITIAL_ADJ_CELL_COLOR+1);
                    printf("%d",g.adjB);
                }
                else if(g.adjB<=4)
                {
                    setColor(INITIAL_ADJ_CELL_COLOR+2);
                    printf("%d",g.adjB);
                }
                else if(g.adjB<=6)
                {
                    setColor(INITIAL_ADJ_CELL_COLOR+3);
                    printf("%d",g.adjB);
                }
                else
                {
                    setColor(INITIAL_ADJ_CELL_COLOR+4);
                    printf("%d",g.adjB);
                }

            }
            else
            {
                printf(" ");
            }
        }
        else
        {
            setColor(BOMB_COLOR);
            printf("M");
        }
    }


}

void END_GAME_VICTORY(cell**g)
{
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            g[i][j].reveal=1;
            g[i][j].mark=0;
            g[i][j].checked=1;

        }
    }
    gotoxy(0,3);
    for(i=0; i<height; i++)
    {
        setColor(FILLER_COLOR);
        printf("  ");
        // setColor(113);
        for(j=0; j<width; j++)
        {
            if(g[i][j].B)
            {
                setColor(FLAG_CELL_COLOR);
                printf("F");
            }
            else
            {
                drawCell_DEFAULT(g[i][j]);
            }
        }
        printf("\n");
    }
}

///                                     DESTRUCTOR
void destructor(cell **g)
{
    for(i=0; i<height; i++)
    {
        free(g[i]);
    }
    free(g);
}

///                             ERROR MESSAGES HANDLING IN FILES (IF FILE WAS CORRUPTED)

void terminate()
{
    system("CLS");
    setColor(12);
    printf("WRONG FILE FORMAT OR THE FILE WAS CORRUPTED\nCOULDNT LOAD THE GAME\nRETURNING TO MAIN MENU\n");
    setColor(8);
    system("pause");
    SYSTEM=MENU;
    inGame=0;
    esc=1;
}
