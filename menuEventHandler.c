#include "menuEventHandler.h"
//CONST
int debugflag=0;
const int LEVEL_EXP=1000;
/*                               FUNCTIONS                              */
///                         SYSTEM INIT FUNCTIONS
void progStart()
{
    srand(time(NULL));
    system("title MineSweeper Game");
    SYSTEM = MENU;
    ShowConsoleCursor(0);//to hide visibility of the cursor
    board_length=0;//height of the leaderboard
    leaderboardLogic();//TO PREPARE SCORE IF PLAYER WANT TO SEE IT and check if files exist
    esc=0;// flag to check whether im still in the menu or i entered another one
    RUNNING=1;
    inGame=0;
    CHOOSEN = 1;//to scroll through main menu
    buffer='\0';//making sure initial buffer is empty not having garbage


    strcpy(playerName,"nameless player");
    strcpy(fileName,"NOFILE");
    //GAME WIDTH & HEIGHT MANAGABLE THROUGH OPTIONS
        //20x20 for default width and height
    height=20;
    width=20;
    score=0;
    LOADED=0;
}
///                         MENU HANDLING AND LOGIC
void menuHandler()
{
    switch (SYSTEM)
    {
    case MENU:
        ShowConsoleCursor(0);///IF USER RESIZE IT THEN IT WILL BE RESET
        CHOOSEN=1;
        esc=0;
        system("mode 80,25");
        system("cls");
        while (!esc)
        {

            setColor(11);
            gotoxy(1, 0);
            printf("Developed by Omar Nasr(lort)-4730");
            setColor(12);
            gotoxy(1, 1);
            printf("**Up/Down -Enter To choose**");

            for ( i = 1; i < 6; i++)
            {
                if (i == CHOOSEN) setColor(15);
                else setColor(8);
                switch (i)
                {
                case 1:
                    gotoxy(1, i+1);
                    printf("Start");
                    break;
                case 2:
                    gotoxy(1, i+1);
                    printf("Load Game");
                    break;
                case 3:
                    gotoxy(1, i+1);
                    printf("Leaderboard");
                    break;
                case 4:
                    gotoxy(1, i+1);
                    printf("Options");
                    break;
                case 5:
                    gotoxy(1, i+1);
                    printf("Exit");
                    break;
                }
            }

            buffer = _getch();
            if (buffer == (char)13)
            {
                switch (CHOOSEN)
                {
                case 1:
                    SYSTEM = GAME;
                    esc =1;
                    break;
                case 2:
                    SYSTEM = LOAD;
                    esc = 1;
                    break;
                case 3:
                    SYSTEM = LEADERBOARD;
                    esc = 1;
                    break;
                case 4:
                    SYSTEM= OPTIONS;
                    esc=1;
                    break;
                case 5:
                    SYSTEM = EXIT;
                    esc = 1;
                    break;

                }
            }
            menuLogic();

        }
        break;
    case OPTIONS:
        CHOOSEN = 0;
        system("CLS");
        setColor(7);
        esc = 0;
        while (!esc)
        {
            setColor(12);
            gotoxy(1, 0);
            printf("**up/down &left/right to change setting(ESC to back)**");
            for ( i = 0; i < 3; i++)
            {
                if (i == CHOOSEN) setColor(15);
                else setColor(8);
                switch (i)
                {
                case 0:
                    gotoxy(1, i + 1);
                    printf("Width:%.03d",width);
                    break;
                case 1:
                    gotoxy(1, i + 1);
                    printf("Height:%.03d",height);
                    break;
                case 2:
                    if(CHOOSEN!=2)setColor(8);
                    gotoxy(1, i + 1);
                    printf("Name:%s",playerName);
                    setColor(3);
                    printf("\n(click Enter to change name)");
                    break;
                }
            }
            buffer=_getch();
            optionsLogic();


        }
        break;
    case GAME:
        //RESIZING CMD FOR GOOD GAME PERFORMANCE

        if(width<=30&&height<=25){
        system("mode 55,30");
        }else if(width<=60&&height<=40){
        system("mode 65,45");
        }else if(width<=100){
        system("mode 105,45");
        }else{
        system("mode 155,45");
        }

        inGame=1;
        esc=0;
        if(!LOADED)
        {
            grid=setup();
        }
        else
        {
            grid=load_game(fileName);
            LOADED=0;
        }
        Sleep(200);
        while(inGame)
        {
            gameLogic();
            updateUI();
        }
        destructor(grid);
        break;
    case EXIT:
        RUNNING=0;
        esc=1;
        break;
    case LEADERBOARD:
        system("cls");
        setColor(8);//TO DELETE THE SCREEN and remove colors
        esc=0;
        unsigned int lvl;
        leaderboardLogic();
        while(!esc)
        {
            setColor(12);
            gotoxy(2,0);
            printf("Name");
            gotoxy(32,0);
            printf("Score");
            gotoxy(62,0);
            printf("Level");

            for(i=0; i<board_length; i++)
            {
                lvl=checkLevel(leaderboard_scores[i]);
                gotoxy(0,i+2);
                setColor(12);
                printf("%d.",i+1);
                ///this gotoxy method to eliminate "\n" problem from names
                setColor(15);
                gotoxy(2,i+2);
                printf("%s",leaderboard_names[i]);
                gotoxy(32,i+2);
                printf("%llu",leaderboard_scores[i]);
                gotoxy(62,i+2);
                printf("%u",lvl);
            }
            buffer=_getch();
            if(buffer==(char)27)esc=1;
        }
        SYSTEM=MENU;
        break;
    case LOAD:
        esc=0;
        system("cls");
        while(!esc)
        {
            gotoxy(1,0);
            setColor(12);
            printf("Enter The Name of The Saved File Followed by the Extension\n TYPE \"Cancel\" to Cancel");
            gotoxy(1,2);
            setColor(15);
            printf("File Name(e.g.:test.txt):");
            scanf("%s",fileName);
            SYSTEM=MENU;
            if(strcmp("NOFILE",fileName)&&strcmp("\n",fileName)&&strcmp("Cancel",fileName)&&strcmp("cancel",fileName))
            {
                LOADED=1;
                SYSTEM=GAME;
            }
            else
            {
                system("cls");
                setColor(12);
                printf("You Canceled the Loading Game Proccess Returning to Main Menu\n");
                system("pause");
                SYSTEM=MENU;
            }
            esc=1;
        }

        break;
    }
}

void menuLogic()
{

    switch (buffer)
    {
case (char)224:
    buffer=_getch();
    if(buffer==(char)72){
        if (CHOOSEN > 1)CHOOSEN--;
    }else if(buffer==(char)80){
        if (CHOOSEN < 5)CHOOSEN++;
    }
        break;
    case (char)27:
        SYSTEM = EXIT;
        esc = 1;
        break;
    }
}

void optionsLogic()
{
    switch (buffer)
    {
  case (char)224:
    buffer=_getch();
    if(buffer==(char)72){
        if (CHOOSEN > 0)CHOOSEN--;
  }else if(buffer==(char)80){
        if (CHOOSEN < 2)CHOOSEN++;
    }else  if(buffer==(char)75){
        switch (CHOOSEN)
        {
        case 0:
            if (width >5)width -=5;
            break;
        case 1:
            if (height >5)height -=5;
            break;
        default:
            break;
        }
     }else if(buffer==(char)77){
        switch (CHOOSEN)
        {
        case 0:
            if (width <150)width +=5;
            break;
        case 1:
            if (height <40)height +=5;
            break;
        default:
            break;
        }
     }
        break;
    case (char)13:
        if(CHOOSEN==2)
        {
            system("CLS");
            setColor(8);
            setColor(15);
            printf("Enter Your New Name:");
            setColor(12);
            emptyName(playerName,20);
            scanf("%s",playerName);
            esc=1;
        }
        break;
    case (char)27:
        SYSTEM = MENU;
        esc = 1;
        break;
    }
}

void leaderboardLogic()
{
    board_length=0;
    char Buffer[256];
    FILE *f;
    int k=0;
    f=fopen("names","r");
    if(f==NULL)
    {
        system("CLS");
        f=fopen("names","w");
        fprintf(f,"nameless player\n");
        fclose(f);
        f=fopen("scores","w");
        fprintf(f,"0\n");
        fclose(f);
        printf("WHOOPS COULDNT LOAD \"names\" And \"scores\" RE-RUN THE GAME \n");
        system("pause");
       exit(1);//EXITING THE PROGRAM
    }
    while(!feof(f))
    {
        fgets(Buffer,256,f);
        if(feof(f))break;
        if(!search_leaderboard_names(Buffer))continue;
        load_score(Buffer);
        leaderboard_scores[k]=final_score();
        strcpy(leaderboard_names[k],Buffer);
        board_length++;
        k++;

    }
    bubbleSort(leaderboard_scores,board_length);

    fclose(f);
}

void emptyName(char*str,int n)
{
    while(n--)
    {
        str[n]=' ';
    }
}
///GAME STUFF
unsigned int checkLevel(unsigned long long x)
{
    unsigned int lvl=0;
    while(x>LEVEL_EXP)
    {
        x-=LEVEL_EXP;
        lvl++;
    }
    return lvl;
}


unsigned long long final_score()
{
    unsigned long long tmp=0;
    //if its on the first line then the save loop will do fgets once and i can load from leaderboard
    char Buffer[256];
    int k=0;
    int tmpo=0;
    unsigned long long tempo;
    FILE *f;

    for(i=0; i<found_name[k]&&k<found_length; i++)
    {

        f=fopen("scores","r");
        tmpo=found_name[k];
        for(j=0; j<tmpo; j++) //KEEP SCANING TILL LINE
        {
            fgets(Buffer,256,f);
        }
        //from string to unsigned long long
        sscanf(Buffer,"%llu",&tempo);

        tmp+=tempo;
        k++;
        fclose(f);
    }


    return tmp;
}

void updateUI()
{
    gotoxy(2,0);
    setColor(11);
    printf("Not Revealed: %d   \t",unRevealed);
    printf("Mines: %d   ",nMines);
    gotoxy(2,1);
    printf("Moves: %d\t",nMoves);
    timeDif=time(NULL);
    if(timeDif-timeIdle<15)
    {
        printf("Time: %ldsec.            ",timeDif-timeInit);
    }
    else
    {
        printf("Time: %ldsec.(IDLE)",timeDif-timeInit);
    }
    gotoxy(2,height+4);
    printf("Flags: %d\t",flagCounter);
    printf("Ques.: %d",quesCounter);

}

///SEARCHING AND SORTING STUFF

int search_leaderboard_names(char* pname)
{
    for(i=0; i<board_length; i++)
    {
        if(!strcmp(leaderboard_names[i],pname))return 0;
    }
    return 1;
}

// sorting for leader board
void bubbleSort(unsigned long long arr[],size_t s)
{
    char tmpo[256];
    int pass,sorted=0;
    for(pass=0; pass<s; pass++)
    {
        if(sorted)break;
        sorted=1;
        for(j=0; j<s-1; j++)
        {
            if(arr[j]<arr[j+1])
            {

                swap(&arr[j],&arr[j+1]);

                strcpy(tmpo,leaderboard_names[j]);
                strcpy(leaderboard_names[j],leaderboard_names[j+1]);
                strcpy(leaderboard_names[j+1],tmpo);

                sorted=0;
            }

        }
    }
}

void swap(unsigned long long *pr1,unsigned long long* pr2)
{
    unsigned long long tmp;
    tmp=*pr2;
    *pr2=*pr1;
    *pr1=tmp;
}

///SAVING AND LOADING STUFF

void save_score()
{

    FILE *f;
    f=fopen("scores","a");
    fprintf(f,"%llu \n",score);
    fclose(f);
    f=fopen("names","a");
    fprintf(f,"%s\n",playerName);
    fclose(f);


}

void load_score(char *PlayerName)
{
    char Buffer[256];
    totalLines=0;//making it 0 will ignore the last \n in last line
    int k=0;
    found_length=0;
    FILE *f;
    f=fopen("names","r");
    if(f==NULL)
    {
        system("CLS");
        f=fopen("names","w");
        fprintf(f,"nameless player\n");
        fclose(f);
        f=fopen("scores","w");
        fprintf(f,"0\n");
        fclose(f);
        printf("WHOOPS COULDNT LOAD \"names\" And \"scores\" RE-RUN THE GAME \n");
        system("pause");
        exit(1);//EXITING THE PROGRAM
    }
    while(!feof(f))
    {
        totalLines++;
        fgets(Buffer,256,f);
        if(feof(f))break;//not to read the last line twice
        if(!strcmp(Buffer,PlayerName))
        {
            found_name[k++]=totalLines;
            found_length++;
        }
    }
    fclose(f);

}


