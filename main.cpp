/*  Name:  Tyler Cobb                         */
/*  Date:  10/16/2023                             */
/*  Assignment:  APP W08B-1                       */
/*  Seat:  21       Instructor:  Paul Cligan        Time:  3:00 */


#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHLCD.h"
#include "LCDColors.h"
#include "FEHRandom.h"
#include "FEHSD.h"
#include "FEHUtility.h"


void PvP();
void stats();
void credits();
void instructions();
void menu();


/*Initializing variables for user stats globally*/
int totalDeaths=0, totalWins=0, totalPlayed=0;


class Grid
{
public:
    void AI();
};


void Grid::AI()
{


    /*Clears background*/
    LCD.Clear(WHITE);
    LCD.Update();

/*Creates campain background*/
    FEHImage Battle2;
    Battle2.Open("Battle2FEH.pic");
    Battle2.Draw(320, 240);
    Battle2.Close();
    LCD.Update();

    /*Draws your board*/

    /*Sets your board as a 5 by 5 array*/
    FEHIcon::Icon YourBoard[5][5];


    /*Creates the actual board through a loop*/
    for (int X = 0; X < 5; X++)
    {
        for (int Y = 0; Y < 5; Y++)
        {


            YourBoard[X][Y].SetProperties("", 20 + 20 * X, 20 + 20 * Y, 20, 20, BLACK, BLACK);
            YourBoard[X][Y].Draw();
        }
    }


    /*Draws opponent's board*/


    /*Sets opponent's board as a 5 by 5 array*/
    FEHIcon::Icon AIBoard[5][5];


    /*Creates the actual board through a loop*/
    for (int OX = 0; OX < 5; OX++)
    {
        for (int OY = 0; OY < 5; OY++)
        {


            AIBoard[OX][OY].SetProperties("", 200 + 20 * OX, 20 + 20 * OY, 20, 20, BLACK, BLACK);
            AIBoard[OX][OY].Draw();
        }
    }


    /*User picks squares and it stores the picked squares*/

    /*Initilizes variables used to pick squares*/
    int YourBoardX[5];
    int YourBoardY[5];
    float x, y, xTrash, yTrash;

    /*Throws away the campain touch*/
    while (LCD.Touch(&xTrash, &yTrash))
    {
    };
    /*Starts loop which allows player to choose 5 squares*/
    for (int n = 0; n < 5; n++)
    {
        /*Waits for user touch*/
        while (!LCD.Touch(&x, &y))
        {
        };
        while (LCD.Touch(&xTrash, &yTrash))
        {
        };
        /*Evaulates what icon was touch and saves the cordinates of the top left of the square*/
        for (int X = 0; X < 5; X++)
        {
            for (int Y = 0; Y < 5; Y++)
            {
                if (YourBoard[X][Y].Pressed(x, y, 0))
                {
                    LCD.SetFontColor(GREEN);
                    LCD.FillRectangle(20 + 20 * X, 20 + 20 * Y, 20, 20);
                    LCD.SetFontColor(BLACK);
                    LCD.DrawRectangle(20 + 20 * X, 20 + 20 * Y, 20, 20);
                    YourBoardX[n] = 20 + 20 * X;
                    YourBoardY[n] = 20 + 20 * Y;
                    LCD.Update();
                }
            }
        }
    }


    /*AI picks squares and it stores the picked squares*/

    /*Initilizes variables used to pick squares*/
    int AIBoardX[5];
    int AIBoardY[5];
    int AIX[5];
    int AIY[5];
    int n = 0;
    int f;
       
    /*Creates a loop that goes on until the AI has picked 5 unique squares*/
    while (n < 5)
    {


        f = 0;

        /*Picks a random integer between 0 and 4*/
        AIX[n] = rand() % 5;
        AIY[n] = rand() % 5;

        /*Checks if the square has already been picked*/
        for ( int z = 0; z < n; z++) {


            if (AIX[n] == AIX[z] && AIY[n] == AIY[z] )
            {
                /*If it has been picked it will change f to 1 to keep n from indexing*/
                f = 1;
            }


        }

        /*If the square has not been picked it will add 1 to n*/
        if (f == 0){
            n += 1;
        }

        /*If the square has been picked it will add 1 to the square and check again*/
        if (n == 0)
        {
            n += 1;
        }


    }

    /*Converts the random integers into cordinates*/
    for (int n = 0; n < 5; n++){
        AIBoardX[n] = 200 + (20 * AIX[n]);
        AIBoardY[n] = 20 + 20 * AIY[n];
    }


    /*Plays out game*/


    /*Initilizes variables used to play out game*/
    int playgame = true;
    int AIshipslost = 0;
    int Yourshipslost = 0;
    int hit = 0;
    int numguess = 0;
    int ShipHitGenerator = 0;
    int YourBoardX2[5][5];
    int YourBoardY2[5][5];


    /*Creates a loop that goes on until someone destroys the others ships or the time limit runs out*/
    float t_now;
    t_now = TimeNow();
    while(playgame && (TimeNow()-t_now<300)) {
   


        /*Player takes their turn*/
        hit = 0;
        LCD.ClearBuffer( );


        /*Waits for player touch*/
        while (!LCD.Touch(&x, &y))
        {
        };
        while (LCD.Touch(&xTrash, &yTrash))
        {
        };

        /*Starts loop to check if any of the 5 AI squares where hit*/
        for (int n = 0; n < 5; n++)
        {
            /*If it is a hit it will execute the below code*/
            if( AIBoardX[n] < x && x < (AIBoardX[n]+20) && AIBoardY[n] < y && y < (AIBoardY[n]+20)){

                /*Collision: Runs an animation that grows from center of hit square unitl edge*/
                int GrowX = AIBoardX[n] + 10;
                int GrowY = AIBoardY[n] + 10;
                int GX = 1;
                int GY = 1;

                /*Draws the animation*/
                while ( GrowX > AIBoardX[n] && GrowY > AIBoardY[n] ){
                    LCD.SetFontColor(RED);
                    LCD.FillRectangle(GrowX, GrowY, GX, GY);
                    LCD.Update();
                    Sleep(100);
                    GrowX -= 1;
                    GrowY -= 1;
                    GX += 2;    
                    GY += 2;
                }

                /*Draws border around final square*/
                LCD.SetFontColor(BLACK);
                LCD.DrawRectangle(AIBoardX[n], AIBoardY[n], 20, 20);
                LCD.Update();

                /*Changes hit to 10 so it won't enter the other if*/
                hit = 10;

                /*Adds to ships lost*/
                AIshipslost++;

                /*If ships lost for the AI is 5 the game will end*/
                if (AIshipslost == 5)
                {
                    totalWins++;
                    LCD.WriteAt("YOU WIN!",80,180);
                    /*If all the AI ships are destroyed the game will end*/
                    playgame = false;
                }
            }
        }
            /*If it is not a hit it will execute the below code*/
            if (hit == 0)
            {
                /*Runds through loop finding which square was clicked and changes it to black*/
                for (int X = 0; X < 5; X++)
                {
                    for (int Y = 0; Y < 5; Y++)
                    {
                        if (AIBoard[X][Y].Pressed(x, y, 0))
                        {
                            LCD.SetFontColor(BLACK);
                            LCD.FillRectangle(200 + 20 * X, 20 + 20 * Y, 20, 20);
                            LCD.SetFontColor(BLACK);
                            LCD.DrawRectangle(200 + 20 * X, 20 + 20 * Y, 20, 20);
                            LCD.Update();
                        }
                    }
                }
            }
       
        /*AI takes their turn*/


        int YourX[25];
        int YourY[25];


        /*Random Generation: AI picks square to attack checking against previous attempts*/
        // Uses same basic logic as choosing AI ships
        n = 0;


        if (ShipHitGenerator != 1){
            while (n < 25) {
                int xrep = rand() % 5;
                int yrep = rand() % 5;


                int duplicate = 0;
                for (int z = 0; z < n; z++) {
                    if (xrep == YourX[z] && yrep == YourY[z]) {
                        duplicate = 1;
                        break; // Duplicate found
                    }
                }


                if (duplicate == 0) {
                    YourX[n] = xrep;
                    YourY[n] = yrep;
                    n += 1;
                }
            }
            for (n=0; n<25; n++){
                YourX[n] = 20 + (20 * YourX[n]);
                YourY[n] = 20 + 20 * YourY[n];
            }

            /*Generates a 5 by 5 array of options for the ai to potentially hit*/
            for (int n = 0; n < 25; n++)
            {
                for (int X = 0; X < 5; X++)
                {
                    for (int Y = 0; Y < 5; Y++)
                    {
                            YourBoardX2[X][Y] = 20 + 20 * X;
                            YourBoardY2[X][Y] = 20 + 20 * Y;
                    }
                }
            }

            /*Changes ShipHitGenrator to 1 so it won't enter this f statment again*/
            ShipHitGenerator = 1;
        }


        /*Resets hit to 0*/
        hit = 0;


        /*Finds if AI had a hit*/
        for (int n = 0; n < 5; n++)
        {
            /*If it is a hit it will execute the below code*/
            if( YourBoardX[n] == YourX[numguess] && YourBoardY[n] == YourY[numguess]){



                /*Collision: Runs an animation that grows from center of hit square unitl edge*/
                int GrowX = YourBoardX[n] + 10;
                int GrowY = YourBoardY[n] + 10;
                int GX = 1;
                int GY = 1;

                /*Draws the animation*/
                while ( GrowX > YourBoardX[n] && GrowY > YourBoardY[n] ){
                    LCD.SetFontColor(RED);
                    LCD.FillRectangle(GrowX, GrowY, GX, GY);
                    LCD.Update();
                    Sleep(100);
                    GrowX -= 1;
                    GrowY -= 1;
                    GX += 2;    
                    GY += 2;
                }

                /*Draws border around final square*/
                LCD.SetFontColor(BLACK);
                LCD.DrawRectangle(AIBoardX[n], AIBoardY[n], 20, 20);
                LCD.Update();

                /*Changes hit to 10 so it won't enter the other if*/
                hit = 10;

                /*Adds to ships lost*/
                Yourshipslost++;
               
                /*If ships lost for the player is 5 the game will end*/
                if (Yourshipslost == 5)
                {
                    totalDeaths++;
                    LCD.WriteAt("YOU LOST!",80,180);


                    /*If all the AI ships are destroyed the game will end*/
                    playgame = false;
                }
            }


        }


        /*If it is not a hit it will execute the below code*/
        if (hit == 0)
        {
                LCD.SetFontColor(BLACK);
                LCD.FillRectangle(YourX[numguess], YourY[numguess], 20, 20);
                LCD.SetFontColor(BLACK);
                LCD.DrawRectangle(YourX[numguess], YourY[numguess], 20, 20);
                LCD.Update();
        }

        /*Adds 1 to numguess so that way the AI will move to its next guess*/
        numguess += 1;
    }


    /*Exit Button*/

    /*Creates icon for exit button*/
    FEHIcon::Icon exit_button;
    exit_button.SetProperties("Exit", 200, 190, 100, 25, BLACK, BLACK);
    exit_button.Draw();

    /*Waits until touch to execute*/
    while (true)
    {
        while (!LCD.Touch(&x, &y))
        {
        };


        LCD.Touch(&x, &y);

        /*Returns to menu*/
        if (exit_button.Pressed(x, y, 0))
        {
            menu();
        }
    }
}


void stats()
{
    /*Clearing previous background*/
    LCD.Clear(WHITE);
    LCD.Update();
    /*Creates menu background*/
    FEHImage menuB;
    menuB.Open("MenuFEH.pic");
    menuB.Draw(320, 240);
    menuB.Close();

    /*Adding wins and losses to find total games played*/
    totalPlayed=totalDeaths+totalWins;


    /*Shows written stats*/
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Total deaths: ",1,40);
    LCD.WriteAt(totalDeaths, 180, 40);
    LCD.WriteAt("Total wins: ",1,60);
    LCD.WriteAt(totalWins, 150, 60);
    LCD.WriteAt("Total games played: ",1,80);
    LCD.WriteAt(totalPlayed, 250, 80);
   
    /*Exit Button*/

    int n=0;
    float x, y;
   
    /*Creates icon for exit button*/
    FEHIcon::Icon exit_button;
    exit_button.SetProperties("Exit", 200, 190, 100, 25, BLACK, BLACK);
    exit_button.Draw();

    /*Waits until touch to execute*/
    while (true)
    {
        while (!LCD.Touch(&x, &y))
        {
        };


        LCD.Touch(&x, &y);

        /*Returns to menu*/
        if (exit_button.Pressed(x, y, 0))
        {
            menu();
        }
    }
}


void credits()
{
    /*Clearing previous background*/
    LCD.Clear(WHITE);
    LCD.Update();
    /*Creates menu background*/
    FEHImage menuB;
    menuB.Open("MenuFEH.pic");
    menuB.Draw(320, 240);
    menuB.Close();


    /*Written Credits*/
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Created By:",50,50);
    LCD.WriteAt("Tyler and Charishma",50,70);
    LCD.Update();


    /*Exit Button*/

    int n=0;
    float x, y;
   
    /*Creates icon for exit button*/
    FEHIcon::Icon exit_button;
    exit_button.SetProperties("Exit", 200, 190, 100, 25, BLACK, BLACK);
    exit_button.Draw();

    /*Waits until touch to execute*/
    while (true)
    {
        while (!LCD.Touch(&x, &y))
        {
        };


        LCD.Touch(&x, &y);

        /*Returns to menu*/
        if (exit_button.Pressed(x, y, 0))
        {
            menu();
        }
    }
   
}


void instructions()
{
    /*Clearing previous background*/
    LCD.Clear(WHITE);
    LCD.Update();


    /*Creates menu background*/
    FEHImage menuB;
    menuB.Open("MenuFEH.pic");
    menuB.Draw(320, 240);
    menuB.Close();


    /*Written Instructions on how to play the game*/
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("1.Left board:Yours.",1,1);
    LCD.WriteAt("2.Right board:Opponent's.",1,20);
    LCD.WriteAt("3.Press spots on left to",1,40);
    LCD.WriteAt("place 5 ships (green).",1,60);
    LCD.WriteAt("4.Fire shots on right.",1,80);
    LCD.WriteAt("5.Hit=red, miss=black.",1,100);
    LCD.WriteAt("6.Opponent takes shots",1,120);
    LCD.WriteAt("on left.",1,140);
    LCD.WriteAt("7.Alternate firing and",1,160);
    LCD.WriteAt("getting shot at.",1,180);
    LCD.WriteAt("8.First to hit",1,200);
    LCD.WriteAt("all ships wins.",1,220);


    LCD.Update();


    /*Exit Button*/

    int n=0;
    float x, y;
   
    /*Creates icon for exit button*/
    FEHIcon::Icon exit_button;
    exit_button.SetProperties("Exit", 200, 190, 100, 25, BLACK, BLACK);
    exit_button.Draw();

    /*Waits until touch to execute*/
    while (true)
    {
        while (!LCD.Touch(&x, &y))
        {
        };


        LCD.Touch(&x, &y);

        /*Returns to menu*/
        if (exit_button.Pressed(x, y, 0))
        {
            menu();
        }
    }
}


/*Menu function*/
void menu()
{
    LCD.Clear(WHITE);
    LCD.Update(); // Never quit
    /*Creates menu background*/
    FEHImage menu;
    menu.Open("MenuFEH.pic");
    menu.Draw(320, 240);
    menu.Close();

    /*Draws Menu Buttons*/

    LCD.SetFontColor(WHITE);
    LCD.FillRectangle(95, 220, 133, 5);
    LCD.FillCircle(95, 222, 2);
    LCD.FillCircle(228, 222, 2);
    LCD.FillRectangle(115, 217, 93, 11);
    LCD.FillCircle(115, 222, 5);
    LCD.FillCircle(208, 222, 5);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Battle Ship",95,200);

    FEHIcon::Icon ai_button;
    ai_button.SetProperties("Campaign", 110, 25, 100, 25, BLACK, BLACK);
    ai_button.Draw();

    FEHIcon::Icon stats_button;
    stats_button.SetProperties("Stats", 110, 55, 100, 25, BLACK, BLACK);
    stats_button.Draw();

    FEHIcon::Icon credits_button;
    credits_button.SetProperties("Credits", 110, 85, 100, 25, BLACK, BLACK);
    credits_button.Draw();

    FEHIcon::Icon instructions_button;
    instructions_button.SetProperties("Guide", 110, 115, 100, 25, BLACK, BLACK);
    instructions_button.Draw();

    /*Checks for pressed buttons*/
    float x, y;

    while (true)
    {
        while (!LCD.Touch(&x, &y))
        {
        };
        LCD.Touch(&x, &y);
        if (ai_button.Pressed(x, y, 0))
        {
            Grid grid;
            grid.AI();
        }
        else if (stats_button.Pressed(x, y, 0))
        {
            stats();
        }
        else if (credits_button.Pressed(x, y, 0))
        {
            credits();
        }
        else if (instructions_button.Pressed(x, y, 0))
        {
            instructions();
        }
    }

    while (1)
        LCD.Update(); // Never quit
}


int main()
{
    menu();
}
