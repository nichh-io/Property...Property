/*
    Description: A collection of UI flairs used in the game Property...Property
    Author: Aaron Nicholas Lizardo Gumapac
*/
#include "../libdefs/uiFX.h"
#include <string.h>
#define shortpause 600
#define longpause 1000
#define quickpause 200
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
/*
    This cross-platform function pauses the system for a given amount of time (milliseconds)
    @param milliseconds how long to pause the system for
*/
void sleep_ms(int milliseconds){ 
#ifdef WIN32 // if the current system is a windows system
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L // if the current system is posix compliant (linux/mac)
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else // if the current system is neither, use system directives
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

/*
    prints an image defined by a stack of strings
    @param img[] the image to be printed (2d array)
    @param img_height the height of the image, tells the method when to stop printing
*/
void print2d(char* img[], size_t img_height){
    int pace = img_height > 20 ? 20 : 100;
    for (size_t i = 0; i < img_height; i++)
    {
        sleep_ms(pace);
        printf("%s\n",img[i]);
        fflush(stdout);
    }
}

/*
    Creates a divider given a symbol and its length
    @param divSymbol the symbol or design of the divider
    @param divLength how long is the divider
    @returns a divider string
*/
char* createDivider(char divSymbol, int divLength){
    char* div = malloc(1 + sizeof div[0] * divLength);
    for (size_t i = 0; i < divLength; i++)
    {
        div[i] = divSymbol;
    }
    return div;
}

/*
    A simple method that helps with code readability. Asks the user to press enter in order to continue with game events
*/
void continuePrompt(){
    sleep_ms(500);
    fflush(stdout);
    printf("\nPress ENTER to continue: ");
    getchar();
}

/*
    Prints a string by printing each individual character sequentially within a randomized time interval 
    in order to mimic human typing
    @param str[] the string to be printed
    @param strLength the length of the string being passed
    @param paceFloor is the integer value that decides the 
*/
void print1d(char str[], int strLength, int paceFloor, int paceCeil)
{
    // if the string is long, speed up typing
    if(strLength > 20){
        paceFloor /= 2;
        paceCeil /= 2;
    }
    if(paceFloor == paceCeil) // don't randomize print intervals, makes printing smoother
    {
        for (size_t i = 0; i < strLength; i++)
        {
            sleep_ms(paceFloor);
            printf("%c",str[i]);
            fflush(stdout);
        }
        
    }
    else{
        for (size_t i = 0; i < strLength; i++)
        {
            fflush(stdout);
            printf("%c",str[i]);
            int randInterval = getRandNum(paceFloor,paceCeil);
            sleep_ms(randInterval);
            fflush(stdout); // flush stdout in order to begin the next output
        }
    }
    sleep_ms(1000);
}

/*
    Returns the name of the property given its index
    @params propIndex the property's position on the board
    @returns the name of the property (string)
*/
char* getPropertyName(int propIndex){
    switch(propIndex){
        case 1:
            return "Tree house";
            break;
        case 2:
            return "Electric Co.";
            break;
        case 3:
            return "Beach house";
            break;
        case 5:
            return "Castle";
            break;
        case 7:
            return "Railroad";
            break;
        case 8:
            return "Igloo";
            break;
        case 9:
            return "Farm house";
            break;
    }
    return " ";
}

/*
    Displays the changes in the player's balance as a UI flair
    @param currentBalance the player's balance before the change
    @param newBalance the player's balance after the change
*/
void showPersonalBalanceUpdate(float currentBalance, float newBalance)
{
    printf("\nYour pending balance: %.2f ➡️ %.2f\n", currentBalance, newBalance);
}

/*
    Displays the changes in the both players' balances in a with borders, dividers, and emojis
    @param p1CurrentBalance player1's balance before the change
    @param p1NewBalance player1's balance after the change
    @param p1Name player1's name, necessary for UI flair
    @param p2CurrentBalance player2's balance before the change
    @param p2NewBalance player2's balance after the change
    @param p2Name player2's name, necessary for UI flair
*/
void showBalanceUpdate(
                    float p1CurrentBalance,
                    float p1NewBalance,
                    char* p1Name,
                    float p2CurrentBalance,
                    float p2NewBalance,
                    char* p2Name
                    )
{
    char* DIVIDER = createDivider('-',24);
    char* DIVIDER2 = createDivider('-',13);
    char* p1Indicator = malloc(128);
    char* p2Indicator = malloc(128);


    setWhite
    printf("\n%s[ BALANCE  UPDATE 🏦 ]%s\n",DIVIDER,DIVIDER);
    resetColor
    if(p1CurrentBalance < p1NewBalance){
        p1Indicator = "🔺";
        setGreen;
    }
    else if(p1CurrentBalance > p1NewBalance){
        p1Indicator = "🔻";
        setRed
    }
    else{
        p1Indicator = " ✒ ";
        setYellow 
    } 
    sleep_ms(1000);
    printf("\n%s %s's balance: \n%.2f ➡️ %.2f\n\n",
                    p1Indicator,
                    p1Name,
                    p1CurrentBalance,
                    p1NewBalance
    );
    resetColor
    if(p2CurrentBalance < p2NewBalance){
        p2Indicator = "🔺";
        setGreen
    }
    else if(p2CurrentBalance > p2NewBalance){
        p2Indicator = "🔻";
        setRed
    }  
    else{
        p2Indicator = " ✒ ";
        setYellow
    }
    printf("\n%s %s's balance: \n%.2f ➡️ %.2f\n",
                    p2Indicator,
                    p2Name,
                    p2CurrentBalance,
                    p2NewBalance 
    );
    sleep_ms(700);
    setWhite
    printf("\n%s[ STATEMENT ISSUED BY: Wayland Corporation ]%s\n",DIVIDER2,DIVIDER2);
    resetColor
}


/*
    Dislays a message that congratulates or demeans the players
    @param context tells how the winningPlayer was decided and which win conditions were satisfied
    @param winningPlayer whether player1, player2, or both of the won
    @param p1Name player 1's name
    @param p2name player 2's name
*/
void displayContextFlair(enum winContext context, enum winner winningPlayer, char* p1Name, char* p2Name){
    char* strLoser = malloc (256);
    char* strWinner = malloc (256);
    strLoser = " both of you";
    strWinner = " both of you";
    if(winningPlayer == PLAYER2){
        strLoser = p1Name;
        strWinner = p2Name;
    }
    else if(winningPlayer == PLAYER1){
        strLoser = p2Name;
        strWinner = p1Name;
    }
    
    char* strArticle = winningPlayer == TIE ? " were" : " was";
    if(context == ENEMY_BANKRUPTY)
    {
        sleep_ms(1000);
        print1d(strLoser, strlen(strLoser),250,270); // animated print for loser name 
        sleep_ms(800);
        print1d(strArticle, strlen(strArticle),200,220);
        char strFlair1[] = " pushed to the annals of BANKRUPTCY!";
        print1d(strFlair1, strlen(strFlair1),200,220); // animated print for the bankruptcy flair
    }
    if(context == ENEMY_LOSING_BALANCE)
    {
        sleep_ms(1000);
        print1d(strLoser, strlen(strLoser),200,200); // animated print for loser name
        sleep_ms(800);
        print1d(strArticle, strlen(strArticle),200,200); // animated print for the article
        char strFlair1[] = " constricted by the forces of capitalism..."; // animated print for message flair
        print1d(strFlair1, strlen(strFlair1),200,200);
        sleep_ms(1000);
        char strFlair2[] = " so tightly that you could not maintain a balance above the losing balance"; // animated print for losing balance flair
        print1d(strFlair1, strlen(strFlair2),180,190); 
    }
    if(context == REACHED_WINNING_BALANCE){
        sleep_ms(1000);
        print1d(strWinner, strlen(strWinner),190,200); // animated print for winner name
        char strFlair1[] = " THRIVED IN THIS NEOCLASSICIST HELLSCAPE...";
        print1d(strFlair1, strlen(strFlair1),190,200); // animated print for winning balance flair
        sleep_ms(1000);
        char strFlair2[] = " and reached the winning balance!\n";
        print1d(strFlair2, strlen(strFlair2),190,200); // animated print for winning balance flair
        sleep_ms(1000);
        char strFlair3[] = " I could not find a better capitalist dog if I tried!";
        print1d(strFlair3, strlen(strFlair3),200,210); // animated print for winning balance flair
    }
    newL
}

/*
    UI flair for displaying player statistics. Includes how many times they were jailed/able to meet with the witch/paid rent
*/
void showEndingStats(Player player){
    char* DIVIDER = createDivider('=',18);
    printf("%s[ %s's Ending Stats ]%s",DIVIDER,player.name,DIVIDER);
    newL
    char* strJail = "Times you were caught by police for not paying taxes: ";
    print1d(strJail, strlen(strJail), 200, 210);
    setRed
    printf("%d",player.jailedCounter);
    resetColor
    newL
    char* strRent = "You ceded money over to your enemy on: ";
    print1d(strRent, strlen(strRent), 200, 210);
    setRed
    printf("%d",player.rentCounter);
    resetColor
    print1d(" occassions", strlen(" occassion"),200,210);
    newL
    char* strWitch = "You got lucky (or unlucky) and met the witch a grand total of: ";
    print1d(strWitch, strlen(strWitch), 200, 210);
    setRed
    printf("%d",player.luckyCounter);
    resetColor
    print1d(" times",strlen(" times"), 200, 210);
    newL
    char* strBalance = "How much money you had left: ";
    print1d(strBalance, strlen(strBalance), 200, 210);
    setRed
    printf("%.2f",player.balance);
    resetColor
    newL
    char* bonusMsg = "The thing you spent the most money on: ";
    print1d(bonusMsg, strlen(bonusMsg), 200,220);
    char* bonusRand[] = {
    "a replacement for Duterte",
    "your dog", "knowledge", "suspicious underwear",
    "some white powdered stuff", "your ego", "Donald Trump"
    };
    int size = sizeof bonusRand / sizeof bonusRand[0];
    char* randMsg = bonusRand[getRandNum(0,size-1)];
    setPurple
    print1d(randMsg, strlen(randMsg), 290, 300);
    resetColor
    newL
}

/* 
    Draws the monopoly moustache to add a ui flair for the ending screen
*/
void showPropertyMan(){
    char* hat[] = {

"                                oooo     oooo",
"                              o$$\"\"\"$oo$$\"\"\"\"\"$o",
"                             $\"      $$\"      $$$$",
"                            $\"      \"\"        $$$$$o",
"                            $                  $$$$$o",
"                           $                    $$$$$$",
"                          $\"                    \"$$$$$",
"                          $                      $$$$$$",
"                         $\"                      $$$$$$",
"                         $                        $$$$$",
"                         $                       o$$$$$",
"                         $                       $$$$$$",
"                         $                      o$$$$$$",
"                      ooo                      o$$$$$$$",
"              ooo$$$$\"\" $                   oo$$$$$\"\"\"\"\"\"oooo",
"           oo\"$$$$$$$ oo\"\" oooooooooooooooo$$\"\"\"           o$$\"oo",
"          o\"  $$$$$$$ \"$o           oo$$$$$\"               $$$$o\"$o",
"         $    $$$$$$$  \" \"\"oooooooooo$$$$\"         o$      $$$$$$o\"$",
"        o     $$\"\"               oo$$$\"           o$$     o$$$$$$$o$",
"        \"o    $$             oo$$$$\"\"            o$$$   o$$$$$$$$$$$",
"         \"$o  $$$oo                           $$$$$$$   ooo$$$$$\"\"",
"           \"$$oooo \"\"            ooo$$$$      $$$$$$$$$$$$$$\"\"",
"               \"\"\"\"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\"\"\"\"\"\"",
"                         \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\","
    };
    char* eyes[] ={
"              |========|----------/$/----------------|========|",
"              |PROPERTY|          $                 |PROPERTY|",
"              |========|         $$$$               |========|"
    };
    
    char* moustache[] = {
"                        ████████░░      ██████████                ██                ",
"    ██                ██████████████  ██████████████░░            ░░██              ",
"  ██▒▒            ▒▒██████████████████████████████████▒▒            ████            ",
"  ██            ████████████████████████████████████████▒▒          ████            ",
"░░██          ██████████████████████████████████████████████        ████            ",
"  ██▒▒    ▒▒██████████████████████████████████████████████████      ████            ",
"  ██████████████████████████████████████████████████████████████████████            ",
"  ██████████████████████████████████░░██████████████████████████████████            ",
"  ████████████████████████████████    ░░██████████████████████████████▒▒            ",
"  ░░████████████████████████████          ████████████████████████████              ",
"    ░░██████████████████████                ▒▒██████████████████████                ",
"        ████████████████                          ██████████████                    "
    };
    int rows = sizeof hat / sizeof hat[0];
    print2d(hat, rows);
    rows = sizeof eyes / sizeof eyes[0];
    setYellow
    print2d(eyes, rows);
    resetColor
    newL
    newL
    rows = sizeof moustache / sizeof moustache[0];
    setPurple
    print2d(moustache, rows);
    resetColor
}

/*
    contextual ending screen that cognratulates the winner(s) according to their win conditions
    @param win describes how the winner(s) won
    @param p1 player 1's values
    @param p2 player 2's values
*/
void displayEndingScreen(struct winstate win, Player p1, Player p2){
    showPropertyMan();
    char* winnerMsg = "\nA winner has been decided.\n";
    print1d(winnerMsg, strlen(winnerMsg), 300, 300);
    sleep_ms(2000);
    clear;
    if(win.winner == TIE){ // the players tie
    // show UI flair for tie
        char* tieMsg1 = "\nBy some freak accident";
        char* dots = "...";
        char* tieMsg2 = "both players won... or lost?\n";
        print1d(tieMsg1, strlen(tieMsg1), 250,270);
        print1d(dots, strlen(dots), 350,360);
        print1d(tieMsg2, strlen(tieMsg2), 250,270);
    }
        char* strMulti = (win.winRationale[0] != NOCONTEXT && win.winRationale[1] != NOCONTEXT) ? "\nfurthermore...\n" : " ";
        // additional UI prompt for when multiple winconditions are satisfied
        for (size_t i = 0; i < 2; i++)
        {
            if(win.winRationale[i] != NOCONTEXT)
            {
                displayContextFlair(win.winRationale[i], win.winner, p1.name, p2.name); // display ui flair for the specific wincondition
                sleep_ms(700);
                print1d(strMulti, strlen(strMulti), 200, 210);  // if multiple conditions are satisfied, print flair statement, otherwise print a space
            }
        }
    showEndingStats(p1);
    newL
    newL
    showEndingStats(p2);
}
/*
    Draws an image of where the player is given current position
    @param pos the player's current position
*/
void displayPos(int pos){
    if(pos == 4){
        char* display[] = {

"                                                                          ",
"                        ░░▓▓▒▒▒▒▒▒▓▓░░                                    ",
"                      ▒▒▓▓▒▒▒▒▒▒▓▓▓▓▓▓▒▒                                  ",
"                      ▒▒▓▓▓▓▒▒▓▓▓▓▓▓▓▓▒▒▒▒                                ",
"                      ▓▓▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒                                ",
"                    ░░▓▓▒▒▒▒▒▒▒▒▓▓▓▓▒▒▓▓▓▓░░                              ",
"                    ▒▒▓▓▒▒  ░░▓▓▓▓▓▓▓▓▒▒▓▓                                ",
"                    ░░▓▓▒▒    ▓▓▓▓▓▓▒▒▓▓▒▒                                ",
"                    ▒▒▓▓░░  ░░▓▓▓▓▒▒  ░░▓▓                                ",
"                    ▓▓▓▓    ░░▓▓▓▓░░  ░░▒▒                                ",
"                    ▓▓▒▒    ▒▒▓▓▓▓░░  ▒▒                                  ",
"                  ░░▓▓▓▓▒▒▒▒▓▓▓▓▓▓░░  ▒▒                                  ",
"                ░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░▒▒                                  ",
"                ░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓▓▒▒                                ",
"                ░░▒▒▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▓▓▒▒░░                            ",
"                ▒▒▓▓▓▓▒▒▒▒▓▓▓▓▒▒▒▒▒▒▓▓▓▓  ▓▓▓▓▒▒░░                        ",
"                ▒▒▓▓▒▒░░▓▓▓▓▓▓▓▓▒▒▒▒▒▒      ▓▓▓▓▒▒▒▒░░                    ",
"                ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒        ░░▓▓▓▓▒▒▒▒░░                ",
"                ░░████████▓▓▓▓▓▓▓▓▓▓▓▓            ▒▒▓▓▓▓▒▒▒▒░░            ",
"                    ▓▓██████████████▒▒                ▓▓▓▓▓▓▒▒▒▒          ",


        };
    int rows = sizeof(display) / sizeof(display[0]);
    print2d(display,rows);
    char* display2[] = {
"          ░░░░░░░░▒▒▒▒▒▒▒▒████████▓▓▒▒░░░░░░░░          ░░▓▓▓▓▓▓▒▒░░      ",
"      ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░          ▒▒▓▓▓▓▒▒▒▒    ",
"    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒            ▒▒▓▓▓▓▒▒░░",
"  ░░▒▒▒▒▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒                  ██▓▓",
"  ░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓  ▓▓▓▓░░░░▓▓░░░░░░░░▓▓▓▓▓▓▒▒▒▒▒▒▒▒                ░░▒▒▒▒",
"  ▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓░░▓▓▓▓░░░░▒▒▒▒░░▒▒░░▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒                    ",
"  ▒▒▒▒▓▓▓▓▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒                    ",
"  ░░▒▒▒▒▓▓████████████████████████████████▓▓▓▓▒▒▒▒░░░░                    "
    };
    char* theJail[] = {


" ─────────────────────────────────────────────────────────",
" ─────────██████─██████████████─██████████─██████─────────",
" ─────────██░░██─██░░░░░░░░░░██─██░░░░░░██─██░░██─────────",
" ─────────██░░██─██░░██████░░██─████░░████─██░░██─────────",
" ─────────██░░██─██░░██──██░░██───██░░██───██░░██─────────",
" ─────────██░░██─██░░██████░░██───██░░██───██░░██─────────",
" ─────────██░░██─██░░░░░░░░░░██───██░░██───██░░██─────────",
" ─██████──██░░██─██░░██████░░██───██░░██───██░░██─────────",
" ─██░░██──██░░██─██░░██──██░░██───██░░██───██░░██─────────",
" ─██░░██████░░██─██░░██──██░░██─████░░████─██░░██████████─",
" ─██░░░░░░░░░░██─██░░██──██░░██─██░░░░░░██─██░░░░░░░░░░██─",
" ─██████████████─██████──██████─██████████─██████████████─",
" ─────────────────────────────────────────────────────────"
    };
    rows = sizeof display2 / sizeof display2[0];
    setRed
    print2d(display2, rows);
    resetColor
    rows = sizeof theJail / sizeof display2[0];
    setRed
    newL
    print2d(theJail, rows);
    resetColor
    sleep_ms(500);
    char* jailMsg1 = "\nTHE JUDGE: You got caught by the police for TAX EVASION\nWhat do you have to say for yourself, criminal scum?\n\n";
    print1d(jailMsg1,strlen(jailMsg1), 180,180);
    char* jailMsg2 = "😏DIRTY INMATE: Don't drop the soap buddy\n\n";
    print1d(jailMsg2,strlen(jailMsg2), 200,200);
    char* jailMsg3 = "👤FORMER PRESIDENT RODRIGO ROA DUTERTE: Welcome";
    print1d(jailMsg3, strlen(jailMsg3), 200, 200);
    }
    else if(pos == 1){
        char* display[] = {

"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒    ██████████▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                  ██▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓██      ▒▒▒▒▒▒▒▒▒▒▒▒      ▓▓████▓▓▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓    ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒    ▓▓▓▓▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██    ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒        ██▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░  ██▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▓▓",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓░░  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▓▓",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒    ",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▓▓▒▒▒▒▒▒▒▒",
"░░▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒░░▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒██████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"

        };
        int rows = sizeof(display) / sizeof(display[0]);
        setGreen
        print2d(display,rows);
        resetColor
        char* treeMsg = "PARK RANGER: 🐒 WOAH THERE!\ndon't confuse the monkey for your reflection buddy.\n\nYou're not THAT ugly.\n\n You are in: The Tree House";
        print1d(treeMsg, strlen(treeMsg), 170, 180);
    }
    else if(pos == 2){
        char* display[] = {
"░░▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒░░",
"▓▓                                                                            ░░",
"▓▓                                                                            ░░",
"▓▓                                  ▒▒████                                      ",
"▓▓                                ▒▒██████▓▓                                  ▒▒",
"▓▓                                ████▓▓████                                  ▒▒",
"▓▓                              ▒▒████  ██████                                ▒▒",
"▓▓                              ████▒▒    ████░░                              ▒▒",
"▓▓                            ▓▓████      ▓▓████                              ▒▒",
"▓▓                            ████░░        ████                              ▒▒",
"▓▓                          ▒▒████          ▓▓██▓▓                            ▒▒",
"▓▓                          ████░░            ████                            ▒▒",
"▓▓                        ░░████              ▒▒██▓▓                          ▒▒",
"▓▓                        ████      ██████      ████▒▒                        ▒▒",
"▓▓                        ████    ▒▒██████      ▓▓████                        ▒▒",
"▓▓                      ████░░    ▓▓████▒▒      ░░████░░                      ▒▒",
"▓▓                    ░░████      ██████          ██████                      ▒▒",
"▓▓                    ████▒▒      ██████      ░░    ████▒▒                    ▒▒",
"▓▓                  ░░████        ████▒▒  ▓▓██      ░░████                    ▒▒",
"▓▓                  ████▓▓      ░░████▓▓██████        ████▒▒                  ▒▒",
"▓▓                ▒▒████        ▒▒██████████          ▒▒████                  ▒▒",
"▓▓                ████░░        ▓▓▒▒    ██▓▓            ██████                ▒▒",
"▓▓              ▓▓████                ░░██░░            ░░████▓▓              ▒▒",
"▓▓              ████░░                ▓▓██                ▓▓████░░            ▒▒",
"▓▓            ▓▓████                  ██▒▒                  ██████            ▒▒",
"▓▓          ▒▒████                    ██                    ▒▒██████          ▒▒",
"▓▓          ████▓▓                ▒▒▓▓██▒▒                    ▓▓████░░        ▒▒",
"▓▓        ██████                    ██                          ██████        ▒▒",
"▓▓      ▓▓████▒▒                                                  ██████      ▒▒",
"▓▓      ██████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██████      ▒▒",
"▓▓      ░░████████████████████████████████████████████████████████████▒▒      ▒▒",
"▓▓                                                                            ▒▒",
"▓▓                                                                            ▒▒",
"▓▓                                                                            ▒▒",
"▓▓                                                                            ▒▒",
"▓▓          ▓▓██░░▒▒░░  ██████░░████▓▓  ▓▓  ██  ████▓▓  ██    ██████          ▒▒",
"▓▓        ▓▓▓▓  ██░░▒▒░░▒▒██    ██  ▓▓  ▓▓  ██  ░░      ██░░  ██  ░░██        ▒▒",
"▓▓        ██    ▓▓  ██▒▒░░██▓▓  ██░░██  ██████  ██▓▓▒▒▒▒░░▓▓  ██    ██        ▒▒",
"▓▓        ██    ▓▓  ████  ██    ██░░██  ██  ██  ░░    ██▓▓██  ██    ██        ▒▒",
"▓▓        ░░██▓▓██  ▒▒██  ████░░██  ▓▓  ▓▓  ██  ████▓▓▓▓  ▓▓  ██████▓▓        ▒▒",
"▓▓            ░░                                                              ▒▒",
"▓▓                                                                            ▒▒",
"▓▓                                                                            ░░",
"▓▓  ██████  ░░████░░██  ██  ▓▓████████████░░██    ██  ██  ██  ██████░░▓▓▓▓██  ░░",
"▓▓  ██  ▓▓░░██    ██▒▒░░▓▓  ░░██░░░░▓▓  ░░▒▒██    ██  ▓▓▒▒██  ██░░▒▒  ██▒▒░░  ░░",
"▓▓  ██░░░░  ██    ██  ██░░▓▓  ██    ▓▓░░▒▒░░██    ██  ▒▒▓▓██  ██      ▒▒  ▒▒▓▓░░",
"▓▓  ██      ░░████░░  ██  ██  ██████▓▓  ░░▒▒████▒▒██  ▒▒  ██  ██████▒▒██████░░░░",
"▓▓  ░░        ░░░░    ░░  ░░  ░░░░░░░░    ░░░░░░░░░░  ░░  ░░  ░░░░░░░░  ▒▒░░  ▒▒",
"▓▓                                                                            ▒▒",
"░░                                                                              ",
"▒▒                                ░░░░░░░░░░                          ░░░░    ▒▒"

        };

        char* theElectric[] = {
"        ████████████████████████████████████████████████████████████████",
"        █▄─▄▄─█▄─▄███▄─▄▄─█─▄▄▄─█─▄─▄─█▄─▄▄▀█▄─▄█─▄▄▄─███─▄▄▄─█─▄▄─█████",
"        ██─▄█▀██─██▀██─▄█▀█─███▀███─████─▄─▄██─██─███▀███─███▀█─██─█░░██",
"        ▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▀▄▄▀▄▄▄▀▄▄▄▄▄▀▀▀▄▄▄▄▄▀▄▄▄▄▀▄▄▀▀"
        };
        int rows = sizeof display / sizeof display[0];
        setYellow
        print2d(display, rows);
        resetColor
        rows = sizeof theElectric / sizeof theElectric[0];
        setYellow
        print2d(theElectric, rows);
        resetColor
        char* electricMsg = "💡DAZZLING! You walk inside and sparks fly off left and right!\nYou wonder how humanity was ever able to contain the essence of the sun inside meager bottles\n\nThis place can not be cheap...\n\n You are in: The Electric Company";
        print1d(electricMsg, strlen(electricMsg), 150,150);
        sleep_ms(1000);
    }                                                                       
    else if(pos == 3){                                                                                
        char* display[] = {
                                                                                        
"                          ▓▓████                          ",
"                            ██▓▓██▓▓▓▓                    ",
"                              ████▓▓▓▓▓▓                  ",
"         -.-                    ▓▓██▓▓▓▓██                ",
"            --.--                 ████▓▓██                ",
"                      ████████████████▓▓██                ",
"                          ██████████▓▓██▓▓████            ",
"                    ████      ██████▓▓████████▓▓          ",
"                ██████      ████████████  ▓▓██▓▓██        ",
"              ██▓▓██      ████    ████    ████████        ",
"            ██████      ██      ████        ██████        ",
"            ████              ██████          ████        ",
"        ██████▓▓████        ██████            ██          ",
"      ▓▓▓▓▓▓████▓▓████      ████              ██          ",
"    ██████████████▓▓████  ██████                          ",
"    ████  ████  ████████  ████                            ",
"    ██    ██      ██████  ████                            ",
"    ██    ██      ██████▓▓████    /^\\                    ",
"          ██        ████▓▓████                            ",
"                    ██████▓▓██                            ",
"                      ████▓▓██                            ",
"                  ▓▓  ██████▓▓                            ",
"              ██  ▓▓██▓▓▓▓████                            ",
"        ████████▓▓████████████▓▓████████████              "
        };
        char* display2[] = {
"  ░░░░░░░░░░████░░░░████████░░░░████████░░░░░░░░░░░░░░░░░░",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░      ",
"      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░          "
        };
        int rows = sizeof display / sizeof display[0];
        setYellow
        print2d(display, rows);
        resetColor
        setCyan
        rows = sizeof display2 / sizeof display2[0];
        print2d(display2, rows);
        resetColor
        sleep_ms(600);
        char* beachMsg = "Seagulls swarm the sky, blocking out the radiance of the sun for a few seconds.\nYou take a whiff of the salt ridden air and think to yourself\nthat life could not get any better\n\n You are in: The Beach House";
        print1d(beachMsg, strlen(beachMsg), 150,150);
        sleep_ms(1000);
    }                                                                            
    else if(pos == 5){
        char* display[] = {



"        ░░░░░░      ░░  ░░░░░░      ░░  ░░██░░      ░░      ░░  ░░  ░░  ░░░░░░  ░░░░░░  ",
"░░░░    ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  ██████  ░░░░░░░░    ░░  ░░░░░░  ░░░░░░  ░░░░░░░░",
"            ░░░░░░░░                      ██  ░░░░░░░░                            ░░░░░░",
"          ░░  ░░                          ██░░  ░░░░                            ░░  ░░  ",
"          ░░░░░░                        ██  ██░░                                ░░░░░░  ",
"░░░░░░░░░░  ░░  ░░░░░░░░░░░░░░  ░░░░░░██      ██  ░░░░░░    ░░  ░░░░░░░░░░░░░░░░░░░░░░░░",
"      ░░░░░░  ░░      ░░      ░░      ██  ██  ██      ░░      ░░      ░░    ░░░░░░      ",
"░░░░░░░░░░                          ░░██  ██  ██                      ░░░░░░░░░░        ",
"░░░░░░░░                            ░░████  ████                      ░░░░  ░░          ",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██      ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
"      ░░      ░░      ░░      ░░    ██          ██    ░░      ░░      ░░      ░░        ",
"                                    ██    ██    ██                                      ",
"                                    ██  ██████  ██                                      ",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  ██  ██████  ██  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
"                                    ██  ██  ██  ██                                      ",
"                                    ████      ████                                      ",
"                                    ██          ██                                      ",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██              ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
"              ░░      ░░      ░░░░██              ██░░░░      ░░      ░░      ░░    ░░  ",
"            ░░░░          ░░░░██████              ██████░░░░                      ░░░░  ",
"            ░░░░░░    ░░░░██████████              ██████████░░░░                  ░░░░░░",
"  ░░      ░░░░░░  ░░░░██████████████    ██████    ██████████████░░░░    ░░░░    ░░░░░░  ",
"      ░░░░  ░░      ████████████████  ██      ██  ████████████████          ░░░░  ░░    ",
"    ░░░░░░░░        ██████  ██  ████  ██  ██  ██  ████  ██  ██████        ░░░░░░░░      ",
"  ░░░░░░░░          ████████████████  ██████████  ████████████████      ░░░░░░░░        ",
"░░░░░░░░  ░░░░░░░░░░██████  ██  ████  ██  ██  ██  ████  ██  ██████░░░░░░░░░░░░  ░░░░░░░░",
"  ░░░░        ░░    ██████  ██  ████  ██  ██  ██  ████  ██  ██████      ░░░░  ░░        ",
"                    ████████████████  ██      ██  ████████████████                      ",
"      ░░      ░░  ██████████████████████████████████████████████████                    "

        };
        char* theCastle[] = {
"         ▄████████    ▄████████    ▄████████     ███      ▄█          ▄████████ ",
"        ███    ███   ███    ███   ███    ███ ▀█████████▄ ███         ███    ███ ",
"        ███    █▀    ███    ███   ███    █▀     ▀███▀▀██ ███         ███    █▀  ",
"        ███          ███    ███   ███            ███   ▀ ███        ▄███▄▄▄     ",
"        ███        ▀███████████ ▀███████████     ███     ███       ▀▀███▀▀▀     ",
"        ███    █▄    ███    ███          ███     ███     ███         ███    █▄  ",
"        ███    ███   ███    ███    ▄█    ███     ███     ███▌    ▄   ███    ███ ",
"        ████████▀    ███    █▀   ▄████████▀     ▄████▀   █████▄▄██   ██████████ ",
"                                                         ▀                      "
        };
        int rows = sizeof display / sizeof display[0];
        setWhite
        print2d(display, rows);
        resetColor
        rows = sizeof theCastle / sizeof theCastle[0];
        setYellow
        newL
        print2d(theCastle, rows);
        resetColor
        char* castleMsg = "You walk in streets of ruin and decay\nYou have stumbled upon an ancient stronghold of an old Catholic cult!\n....";
        print1d(castleMsg, strlen(castleMsg), 180, 190);
        sleep_ms(700);
        char* dragonMsg1 = "\nIS THAT A ****ING DRAGON?!?\n";
        print1d(dragonMsg1, strlen(dragonMsg1), 300,300);
        char* dragon[] = {
                                                                                       
"                                                                                  ▒▒   ",
"                                                                ▒▒▒▒▒▒                 ",
"                                                            ▒▒▓▓▓▓▓▓▓▓▓▓               ",
"                                                          ▒▒▓▓▓▓▓▓▓▓▓▓▓▓░░             ",
"                                                        ▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░           ",
"                                                      ░░▓▓▓▓▓▓▓▓▓▓██████▓▓▒▒           ",
"                                                    ▒▒▓▓▓▓▓▓▓▓████▓▓▓▓▓▓▓▓▓▓           ",
"                                                  ▓▓▓▓▓▓▓▓▓▓████▓▓▓▓▓▓▓▓██▓▓          ▒",
"                                                ▒▒▓▓▓▓▓▓▓▓████▓▓▓▓▓▓▓▓██▓▓        ░░   ",
"                                              ▒▒▓▓▓▓▓▓▓▓████▓▓▓▓▓▓▓▓▓▓▓▓               ",
"                                            ▒▒▓▓▓▓▓▓▓▓▓▓████▓▓▒▒▓▓▒▒██                ░",
"                                          ▒▒▓▓▓▓▓▓▓▓▓▓████▓▓▒▒▒▒▒▒▓▓▓▓      ░░        ▒",
"                                        ▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▒▒▒▒▒▒▒▒▒▒██            ▒▒▒▒░",
"                                      ▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▓██▓▓▒▒▒▒▒▒▒▒██              ▒▒░░░",
"                                  ░░▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▓██▓▓▒▒▒▒▒▒▒▒▒▒▒▒            ▒▒░░",
"                          ░░░░░░░░░░▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓██▓▓▒▒░░░░░░▓▓██          ▒▒▒▒  ",
"                        ░░░░░░░░██▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓██▓▓░░░░  ░░██          ▒▒▒▒▒▒░░",
"                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░        ░░          ▒▒▒▒",
"                            ░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░        ░░          ▒▒░░",
"                        ░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░▓▓▓▓          ░░▓▓          ▒▒░░░░   ",
"                      ░░░░░░  ░░▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░██▓▓      ░░░░▓▓▓▓          ▒▒",
"                      ░░░░░░░░░░▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░  ██    ░░░░░░░░▒▒▓▓          ▒▒░░ ",
"                    ░░░░  ░░░░░░▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░██▓▓▒▒░░░░░░░░░░▓▓▓▓         ",
"                  ░░░░  ░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░  ████▓▓▒▒▒▒▒▒░░░░██▓▓       ",
"                ░░░░  ░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░  ██▒▒▓▓▓▓▒▒▒▒░░░░▓▓▓▓        ▒",
"              ░░░░  ░░░░  ▓▓▓▓▓▓▓▓░░░░▓▓▓▓▓▓▒▒░░░░░░░░░░░░  ████▓▓▓▓▓▓▒▒░░▓▓▓▓▓▓       ",
"            ░░░░  ░░    ▓▓▓▓▓▓▓▓▒▒░░▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░░  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓       ",
"          ░░░░  ░░      ▓▓▓▓▓▓▒▒░░▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░▒▒░░░░░░░░  ██████▓▓▓▓▓▓██▓▓       ",
"        ░░░░  ░░          ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░▒▒▒▒░░░░░░    ████████▓▓     ",    
"      ░░░░  ░░                ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░▒▒▒▒          ██████       ",    
"    ░░░░  ░░                ░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░▒▒▒▒▒▒░░░░▒▒           ",
"    ░░░░░░                  ░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░  ▒▒                   ",
"  ░░░░░░                  ░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░  ▒▒                   ",
"  ░░░░                    ░░  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░  ▒▒                   ",
"  ░░                      ░░    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░  ▒▒▒▒                 ",
"                              ░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░    ▒▒                 ",                                                                             
"                            ░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░    ▒▒               ",                                                                             
"                            ░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░    ▒▒             ",                                                                             
"                              ░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░    ░░           ",                                                                             
"                              ░░    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░  ▒▒░░         ",                                                                             
"                                  ░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░  ▒▒▒▒       ",                                                                              
"                                  ░░  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░    ▒▒▒▒     ",                                                                              
"                                  ░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░    ▒▒░░░░ ",
"                                  ░░░░  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░  ░░▒▒▒▒ ",
"                                    ░░  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░░░▒▒▒",
"                                          ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░    ▒",
"                                      ░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░   ",
"                                      ░░  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░ ",
"                                    ░░░░  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░ ",
"                                          ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░",
"                              ░░░░░░░░  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░",
"                      ░░░░        ░░  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░",
"                    ░░░░░░░░    ████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░",
"                        ░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░",
"              ░░░░░░    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░",
"            ░░░░░░  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░",
"                  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░ ",
"            ░░  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░ ",
"      ░░░░░░  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░░ ",
"    ░░░░░░  ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░ ",
"            ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░▒",
"      ░░░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░  ▒"
        };
        rows = sizeof dragon / sizeof dragon[0];
        setCyan
        print2d(dragon, rows);
        resetColor
        char* dragonMsg2 = "HURRY UP AND GET INSIDE!\n\n You are currently in: The Castle";
        print1d(dragonMsg2,strlen(dragonMsg2),160,160);
        sleep_ms(1000);
    }
    else if(pos == 8){
        char* display[] = {

"                                                                                  ░░▒▒▓▓▓▓▓▓▓▓██▓▓▒▒░░  ",
"  ██████████████████████▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░░░░░            ░░    ▒▒  ░░              ░░▒▒▓▓",
"▓▓                                                                                                      ",
"██                                                                                                ░░░░▒▒",
"██                                                                                              ░░░░░░██",
"░░▒▒                                    ░░░░░░░░░░░░░░░░░░░░                            ░░░░░░░░░░░░░░▒▒",
"  ▓▓░░                  ░░░░        ░░░░░░░░░░░░░░  ░░░░░░░░░░░░░░                  ░░░░░░░░░░░░░░░░░░  ",
"  ▓▓░░░░░░  ░░░░░░░░░░      ░░  ░░░░      ░░░░░░  ░░          ░░░░░░              ░░░░          ░░░░▒▒  ",
"  ░░▒▒    ░░██▒▒                                                      ░░                            ░░  ",
"    ▓▓        ▓▓          ░░░░                ░░▓▓                                    ██▒▒          ░░  ",
"    ██        ▒▒          ▓▓▓▓                ▒▒░░░░                      ▒▒▓▓      ▓▓  ▓▓              ",
"    ▓▓    ░░    ░░        ██▒▒                ░░  ▒▒        ▓▓▓▓          ████░░  ░░▒▒  ░░▒▒      ░░    ",
"    ▒▒░░  ░░    ░░      ░░██░░                    ▓▓        ████░░      ▓▓▒▒▓▓██  ██      ▓▓      ░░    ",
"    ▒▒▒▒  ░░    ▒▒      ▒▒██  ░░            ░░    ██      ░░▒▒██▓▓      ██  ░░██  ██      ██      ▒▒    ",
"      ██  ░░    ▓▓      ▓▓██░░▒▒            ▓▓    ▓▓      ▓▓  ▒▒██    ▒▒▓▓    ██▓▓▒▒      ██      ▒▒    ",
"      ██  ░░    ▓▓      ████  ██            ██    ▒▒      ██    ██▒▒  ██        ▒▒        ▒▒▒▒    ██    ",
"      ██  ░░    ▓▓      ██▒▒  ▓▓            ██    ░░░░    ██    ██▓▓  ██                  ░░▓▓    ██    ",
"      ██        ██    ░░██    ▓▓  ░░        ██    ░░▒▒    ██    ▒▒██░░▒▒                  ░░▓▓    ██    ",
"      ██        ▒▒    ▒▒██    ██▒▒██      ░░▓▓    ░░▓▓  ▒▒▓▓      ██▓▓░░                    ██    ██    ",
"      ██░░      ░░    ▓▓██    ██████      ▒▒██      ██  ██▒▒      ▓▓██                      ██    ██    ",
"      ██▒▒      ░░    ████    ▓▓▓▓██░░    ██▒▒      ██  ▓▓░░        ░░                      ██    ██    ",
"      ██▓▓        ▒▒  ████    ██▒▒▒▒▒▒    ██░░      ██  ██                                  ██  ░░██    ",
"      ▓▓██        ██  ██▒▒    ░░  ░░▓▓    ██░░      ██  ██                                  ██░░░░▒▒    ",
"      ░░██        ▓▓  ██░░          ██    ██        ██  ██                                  ██▒▒░░▒▒    ",
"        ░░        ██░░██            ██    ██        ██  ██                                  ▓▓▒▒▒▒      ",
"                  ▓▓████            ██  ░░██        ██░░██                                  ▒▒▓▓██      ",
"                  ██▓▓██            ██  ░░██        ██░░▓▓                                  ▒▒██▓▓      ",
"                  ████░░            ▒▒░░▒▒██        ██▒▒▒▒                                  ░░████      ",
"                  ████                ░░▓▓▓▓        ▓▓▓▓░░                                    ████      ",
"                  ████                ▒▒██▒▒        ░░██                                      ██▓▓      ",
"                  ▒▒██                ████▒▒          ▓▓                                      ██▒▒      ",
"                                      ▓▓██░░                                                  ██        ",
"                                      ████                                                    ██        ",
"                                      ████                                                    ░░        ",
"                                      ▒▒▓▓                                                              "

        };
        int rows = sizeof display / sizeof display[0];
        setWhite
        print2d(display, rows);
        resetColor
        char* iceMsg = "DAVID ATTENBOROUGH: BRRRR 😰 who turned all the ACs on?\n You have landed squarely in the arctic! Good luck surviving out here bruh.\n Oh look, an Igloo!\n\n You are currently in: The Igloo";
        print1d(iceMsg, strlen(iceMsg),170,180);
        sleep_ms(1000);
    }
    else if(pos == 9){
        char* display[] = {
                                                                                                
"                                                      ██                        ",
"                                        ████        ██░░██                      ",
"                                      ██  ▒▒▓▓    ██░░░░██          ██          ",
"    ████                              ░░██    ██  ██░░░░██        ██░░██        ",
"  ██    ██                              ██    ████████████▓▓██    ██░░██        ",
"██      ██                                ██████████████████  ██████░░██        ",
"░░██  ██                                  ██████████████████    ░░██▓▓██        ",
"  ░░██          ██████████████████████████░░████████████              ████████  ",
"    ██        ██████████████████████████▒▒████████████                ░░░░░░░░██",
"    ██      ██████████████████████████░░  ██      ██                  ████    ██",
"    ██    ████████████████████████████  ██      ████                  ████  ██░░",
"      ████  ██████████████████████████  ██      ████          ██    ██░░░░██    ",
"        ██  ████████████░░████████████  ██      ░░░░        ████    ██          ",
"        ██  ░░████████    ░░████████    ██  ██████          ████  ██            ",
"        ██      ░░██          ████      ████░░▒▒░░██████          ██            ",
"        ██                              ██░░░░░░░░░░░░░░████      ██            ",
"        ██                              ██░░██▓▓░░░░░░░░░░░░▓▓  ▓▓░░            ",
"        ██      ██░░                    ░░▓▓▒▒▒▒░░░░░░░░░░░░▒▒████              ",
"        ██    ██████        ██              ██░░░░░░░░░░████░░██                ",
"        ██    ██████    ██    ████            ██████▒▒▒▒░░░░██                  ",
"        ░░▓▓  ▒▒░░░░    ██    ████        ▓▓  ░░░░░░▒▒▒▒▓▓▓▓░░                  ",
"          ██            ████████████      ████▓▓    ▒▒▒▒░░░░                    ",
"          ██          ██▒▒  ██    ██      ██░░██    ██▒▒▒▒                      ",
"            ██        ██    ██      ██    ██    ██  ██                          ",
"            ██        ██    ██      ██    ██    ██  ██                          ",
"            ██      ████    ██      ██    ██    ██  ██                          ",
"            ██▓▓  ▓▓████▓▓▒▒██      ██  ▓▓██▓▓  ████████                        ",
"              ██▓▓██▒▒▓▓██████      ░░░░██████  ░░██████                        "

        };
        int rows = sizeof display / sizeof display[0];
        setWhite
        print2d(display, rows);
        resetColor
        sleep_ms(600);
        char* farmMsg = "\n🐄You smell the fresh air and get a distinct stench of cow manure\nYou're in the country side! The corn gleans with fresh morning dew\n\n You are currently in: The Farm house";
        newL
        print1d(farmMsg, strlen(farmMsg), 200,200);
    }
    else if(pos == 0){
        char* display[] = {
                                                              
"                                ▒▒                            ",
"                              ▓▓░░░░                          ",
"                              ▒▒░░▓▓                          ",
"                            ░░▒▒░░▓▓                          ",
"                            ▒▒░░░░░░▒▒                        ",
"                            ▓▓░░░░░░▓▓                        ",
"                            ██░░░░░░▓▓                        ",
"                          ██░░░░░░░░▒▒░░                      ",
"                          ▓▓░░░░░░░░░░░░                      ",
"                          ▓▓░░░░░░░░░░░░                      ",
"                          ▓▓░░░░░░░░▒▒░░                      "
        };
        char* body[] = {
"                        ░░██████████████                      ",
"                        ░░██░░░░▓▓▓▓░░██                      ",
"                        ░░██░░░░▓▓▓▓░░██                      ",
"                        ░░██░░░░▓▓▓▓░░██                      ",
"                        ░░██░░░░▓▓▓▓░░██                      ",
"                        ░░██▓▓▓▓████▓▓██                      ",
"                        ░░░░░░░░░░░░░░██                      ",
"                        ░░░░░░░░▒▒░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░▒▒░░░░▓▓                      ",
"                        ░░░░░░░░▒▒░░░░▓▓                      ",
"                        ░░░░░░░░▒▒░░░░▓▓                      ",
"                        ░░██████████████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓▓▓▓▓▓▓██                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ▓▓░░░░░░▒▒░░░░▓▓▒▒                    ",
"                        ██░░░░░░▓▓░░░░▓▓▒▒                    ",
"                      ▓▓▒▒░░░░░░▓▓░░░░▓▓▒▒░░                  ",
"                      ▒▒▒▒░░░░░░▓▓░░░░▓▓░░▒▒                  ",
"                    ▒▒░░▒▒░░░░░░▓▓░░░░▓▓░░▒▒                  ",
"                    ▓▓░░▒▒▒▒░░░░▓▓░░░░▒▒░░░░▓▓                ",
"                    ▒▒▒▒▒▒██▒▒▒▒██▒▒▒▒▓▓▒▒░░                  ",
"                            ░░▓▓▓▓██                          ",
"                            ██▓▓▓▓▓▓▓▓                        ",
"                          ▒▒▓▓▓▓▓▓▓▓▓▓                        ",
"                          ▓▓▓▓▓▓▓▓▓▓▓▓░░                      ",
"                            ██████████                        "
        };
        char* thrust[] = {
"                          ▒▒░░░░  ░░▒▒░░                      ",
"                          ▒▒░░░░  ░░░░▒▒                      ",
"                        ░░▒▒░░      ░░▓▓                      ",
"                        ░░▒▒░░    ░░░░▓▓                      ",
"                        ░░░░░░    ░░░░▒▒                      ",
"                        ▓▓░░░░░░  ░░░░░░▓▓                    ",
"                        ▓▓░░░░░░░░░░░░░░▓▓                    ",
"                        ▓▓░░░░░░░░░░░░░░▓▓                    ",
"                        ▓▓░░░░░░░░░░░░░░▓▓                    ",
"                        ░░░░░░░░░░░░░░▒▒                      ",
"                          ▒▒░░░░░░░░░░▒▒                      ",
"                            ░░░░░░░░░░                        ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" ",
" "
        };
        int rows = sizeof display / sizeof display[0];
        setRed
        print2d(display, rows);
        setWhite
        rows = sizeof body / sizeof body[0];
        print2d(body, rows);
        setYellow
        rows = sizeof thrust / sizeof thrust[0];
        print2d(thrust, rows);
        resetColor
        sleep_ms(600);
        char* goMsg = "\nHOUSTON: 🏁Go Go Go!' The bank handed you a STIMULUS CHECK!\n\n You are currently at: Go!";
        sleep_ms(1000);
        print1d(goMsg, strlen(goMsg), 200,200);
        sleep_ms(1000);
    }
    else if(pos == 6){
        char* display[] = {

"                                ██▓▓██                                      ",
"                            ▓▓▓▓▓▓██                                        ",
"                          ██▓▓▓▓██                                          ",
"                        ▓▓▓▓▓▓▓▓██                                          ",
"                        ██▓▓▓▓▓▓██                                          ",
"                      ██▓▓▓▓▓▓▓▓▓▓██                                        ",
"                      ██▓▓▓▓▓▓▓▓▓▓▓▓████          ██████                    ",
"                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██░░▓▓▓▓▓▓██                    ",
"                    ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██                      ",
"                    ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████                        ",
"                ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████░░                          ",
"      ████▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████                                ",
"      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██████░░░░██                              ",
"        ██████▓▓▓▓▓▓▓▓▓▓▓▓████████░░░░░░░░░░██                              ",
"              ████████████░░▓▓░░██░░░░░░░░░░░░██                            ",
"                      ██░░░░░░░░██░░░░░░░░░░░░░░████████      ██████        ",
"                    ██  ░░░░░░░░░░██░░░░░░░░░░░░░░░░░░░░██████░░██          ",
"  ██████████        ██████░░▓▓░░░░██░░░░░░░░░░████░░░░░░░░░░░░██            ",
"██░░░░░░░░░░██          ██▓▓░░░░██░░██░░░░░░██▓▓▓▓██░░░░░░░░██              ",
"██░░▓▓░░░░░░██▓▓        ████████░░████░░░░██▓▓▓▓▓▓▒▒██░░░░██████            ",
"██░░░░▓▓░░░░██  ▒▒            ████▓▓██░░██▓▓▓▓▒▒▓▓▓▓▓▓▓▓░░░░░░░░▓▓▓▓        ",
"██▓▓░░░░████    ▓▓            ██▓▓▓▓██░░██▓▓▓▓██▓▓▓▓▓▓▓▓██░░░░░░░░░░██      ",
"██░░░░░░██    ▓▓              ██▓▓▓▓██░░██▓▓▓▓▒▒██▓▓▓▓▓▓▒▒██░░██████████    ",
"██▒▒▒▒░░██  ▓▓██████▓▓██    ▓▓▓▓██▓▓▓▓▓▓██▓▓▓▓▓▓▓▓██▓▓▓▓▓▓██░░██░░          ",
"████████    ██░░░░██▓▓▓▓████▓▓▓▓██▓▓▓▓▓▓██▓▓▓▓▓▓██▓▓▓▓▓▓▓▓██░░░░██          ",
"            ██░░░░██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▓▓▓▓▓▓▓▓▓▓██▓▓▓▓▓▓▓▓▓▓██░░░░░░██        ",
"              ▓▓████▓▓▓▓▓▓▓▓▓▓▓▓████▓▓▓▓▓▓▓▓████▓▓▓▓▓▓▒▒██▓▓██▓▓░░░░▓▓      ",
"              ▓▓  ██▓▓▓▓▓▓▓▓▓▓██  ██▓▓▓▓▓▓██░░░░██▓▓▓▓▓▓██▓▓██  ██████▓▓    ",
"              ▒▒  ██▓▓▓▓▓▓▓▓██      ██▓▓▓▓██░░░░██▓▓▓▓██▓▓▓▓██              ",
"              ▒▒    ██▓▓▓▓██        ██▓▓▓▓▓▓████▓▓▓▓██▒▒▓▓▓▓██              ",
"              ▓▓      ████          ██▓▓▓▓▓▓▓▓██████▓▓▓▓▓▓▓▓▓▓██            ",
"              ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"              ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"              ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"            ▒▒░░                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"            ▒▒                        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"            ▒▒                        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"            ▓▓                          ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██          ",
"            ░░▒▒                        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██          ",
"              ▒▒                        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██          ",
"                ▒▒                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██        ",
"                ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██        ",
"                ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      ",
"                ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██    ",
"              ▓▓                        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██  ",
"              ▒▒                      ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
"              ▓▓                      ██████████████████████████████████████",

        };

        char* theWitch[] = {
"        ▄▄▄█████▓ ██░ ██ ▓█████     █     █░ ██▓▄▄▄█████▓ ▄████▄   ██░ ██ ",
"        ▓  ██▒ ▓▒▓██░ ██▒▓█   ▀    ▓█░ █ ░█░▓██▒▓  ██▒ ▓▒▒██▀ ▀█  ▓██░ ██▒",
"        ▒ ▓██░ ▒░▒██▀▀██░▒███      ▒█░ █ ░█ ▒██▒▒ ▓██░ ▒░▒▓█    ▄ ▒██▀▀██░",
"        ░ ▓██▓ ░ ░▓█ ░██ ▒▓█  ▄    ░█░ █ ░█ ░██░░ ▓██▓ ░ ▒▓▓▄ ▄██▒░▓█ ░██ ",
"          ▒██▒ ░ ░▓█▒░██▓░▒████▒   ░░██▒██▓ ░██░  ▒██▒ ░ ▒ ▓███▀ ░░▓█▒░██▓",
"          ▒ ░░    ▒ ░░▒░▒░░ ▒░ ░   ░ ▓░▒ ▒  ░▓    ▒ ░░   ░ ░▒ ▒  ░ ▒ ░░▒░▒",
"            ░     ▒ ░▒░ ░ ░ ░  ░     ▒ ░ ░   ▒ ░    ░      ░  ▒    ▒ ░▒░ ░",
"          ░       ░  ░░ ░   ░        ░   ░   ▒ ░  ░      ░         ░  ░░ ░",
"                  ░  ░  ░   ░  ░       ░     ░           ░ ░       ░  ░  ░",
"                                                         ░                "
        };
        int rows = sizeof display / sizeof display[0];
        setPurple
        print2d(display, rows);
        resetColor
        rows = sizeof theWitch / sizeof theWitch[0];
        setRed
        newL
        print2d(theWitch, rows);
        resetColor
        sleep_ms(700);
        char* luckMsg = "\nWITCH: You feelin' lucky, Child? 🦹";
        newL
        print1d(luckMsg,strlen(luckMsg), 230,240);
        sleep_ms(1000);
    }
if(pos == 7){
    char* display[] = {
"                                                                              ▓▓▓▓              ",
"                  ████████                                                ████                  ",
"                ▓▓░░░░░░░░██                    ▓▓▓▓▒▒▓▓▓▓▒▒          ▓▓▒▒████▓▓██▓▓██▓▓██▓▓▓▓  ",
"                  ████████                      ██▒▒▒▒▒▒▒▒██        ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██",
"                  ██░░░░██                      ██▒▒▒▒▒▒▒▒██    ▓▓  ████████▓▓▓▓██▓▓▓▓██████████",
"          ██████  ██░░░░██  ████████            ██▒▒▒▒▒▒▒▒██  ██▒▒██  ██▒▒▒▒▒▒██    ██          ",
"          ██▒▒██  ██░░░░██  ██▒▒▒▒██    ▓▓      ██▒▒▒▒▒▒▒▒██  ██▒▒██  ██▒▒░░▒▒██    ██          ",
"          ██▒▒██  ██░░░░██  ██▒▒▒▒██  ▓▓▒▒▓▓  ████▒▒▒▒▒▒▒▒██░░██████▓▓██▒▒  ▒▒██    ██          ",
"          ██████████░░░░██████▒▒▒▒██▓▓██████▓▓██▒▒████████▒▒██▒▒▒▒▒▒▒▒██▒▒▒▒▒▒██    ██          ",
"        ██▒▒░░▒▒░░░░▓▓██░░██▒▒▓▓▓▓▒▒▓▓▓▓▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒██████▓▓████████          ",
"      ▓▓░░░░░░░░░░░░░░░░░░██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██          ",
"      ██░░░░░░░░░░░░░░░░░░██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██          ",
"      ██░░░░░░░░░░░░░░░░░░██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██▒▒▒▒▒▒▒▒▒▒▒▒██          ",
"        ██░░░░░░░░░░░░░░░░██▓▓▓▓▓▓▓▓▓▓██████▓▓▓▓▓▓▓▓▓▓██████▓▓▓▓▓▓▓▓▓▓██████▒▒▒▒▒▒▒▒██          ",
"          ████▓▓██▓▓██▓▓████▓▓▓▓▓▓▓▓██▒▒▒▒▒▒██▓▓▓▓▓▓██▒▒▒▒▒▒██▓▓▓▓▓▓██▒▒▒▒▒▒██████████▓▓▓▓      ",
"    ██████▒▒▒▒▒▒▒▒██▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒██▓▓██▒▒▒▒▒▒▒▒▒▒██▓▓██▒▒▒▒▒▒▒▒▒▒██▓▓▓▓██▒▒██      ",
"  ▓▓▒▒▒▒▒▒██▓▓████████████████  ░░██▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒██▓▓▓▓████        ",
"██▒▒▒▒▒▒▒▒██  ██▒▒▒▒██▓▓██▒▒▒▒██  ██▒▒▒▒▒▒▒▒▒▒██  ██▒▒▒▒▒▒▒▒▒▒██  ██▒▒▒▒▒▒▒▒▒▒██████  ████      ",
"████████████  ██▒▒▒▒██████▒▒▒▒██    ██▒▒▒▒▒▒██      ██▒▒▒▒▒▒██      ██▒▒▒▒▒▒██                  ",
"                ████      ████        ██████          ██████          ██████                    ",
"                                                                        ░░                      "
        };
        int rows = sizeof display / sizeof display[0];
        print2d(display, rows);                                                                                         
        char* theRail[] = {
"                ██████╗  █████╗ ██╗██╗     ██████╗  ██████╗  █████╗ ██████╗ ",
"                ██╔══██╗██╔══██╗██║██║     ██╔══██╗██╔═══██╗██╔══██╗██╔══██╗",
"                ██████╔╝███████║██║██║     ██████╔╝██║   ██║███████║██║  ██║",
"                ██╔══██╗██╔══██║██║██║     ██╔══██╗██║   ██║██╔══██║██║  ██║",
"                ██║  ██║██║  ██║██║███████╗██║  ██║╚██████╔╝██║  ██║██████╔╝",
"                ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ "
        };
        rows = sizeof theRail / sizeof theRail[0];
        print2d(theRail, rows);
        sleep_ms(700);
        char* railMsg = "\nTHOMAS THE dank ENGINE: You hear the sound of trains and the complex machinations of the industrial era!\n\n You are currently at: The Railroad station";
        newL
        print1d(railMsg, strlen(railMsg),170,180);
        sleep_ms(1000);
    }                                                                                                

}                                                                                               

void showMonopolyTitle(){
    char* monopoly[] = {
"         ▄▄   ▄▄ ▄▄▄▄▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄     ▄▄   ▄▄",
"        █  █▄█  █       █  █  █ █       █       █       █   █   █  █ █  █",
"        █       █   ▄   █   █▄█ █   ▄   █    ▄  █   ▄   █   █   █  █▄█  █",
"        █       █  █ █  █       █  █ █  █   █▄█ █  █ █  █   █   █       █",
"        █       █  █▄█  █  ▄    █  █▄█  █    ▄▄▄█  █▄█  █   █▄▄▄█▄     ▄█",
"        █ ██▄██ █       █ █ █   █       █   █   █       █       █ █   █",
"        █▄█   █▄█▄▄▄▄▄▄▄█▄█  █▄▄█▄▄▄▄▄▄▄█▄▄▄█   █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█ █▄▄▄█"
    };
    int rows = sizeof monopoly / sizeof monopoly[0];
    print2d(monopoly, rows);
}
void showWelcome(){
    char* welcome[] = {
"                ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
"                ██░███░█░▄▄█░██▀▄▀█▀▄▄▀█░▄▀▄░█░▄▄███▄░▄█▀▄▄▀",
"                ██░█░█░█░▄▄█░██░█▀█░██░█░█▄█░█░▄▄████░██░██░",
"                ██▄▀▄▀▄█▄▄▄█▄▄██▄███▄▄██▄███▄█▄▄▄████▄███▄▄█",
"                ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"
    };
    int rows = sizeof welcome / sizeof welcome[0];
    print2d(welcome, rows);
}
void showPropertyTitle(){




    char* property[] = {
"                  ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
"                  ██░▄▄░█░▄▄▀█▀▄▄▀█▀▄▄▀█░▄▄█░▄▄▀█▄░▄█░██░██",
"                  ██░▀▀░█░▀▀▄█░██░█░▀▀░█░▄▄█░▀▀▄██░██░▀▀░██",
"                  ██░████▄█▄▄██▄▄██░████▄▄▄█▄█▄▄██▄██▀▀▀▄██",
"                  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"
    };
    int rows = sizeof property / sizeof property[0];
    print2d(property, rows);
    char* property2[] = {
"      ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄▄ ▄▄   ▄▄ ",
"     █       █   ▄  █ █       █       █       █   ▄  █ █       █  █ █  █",
"     █    ▄  █  █ █ █ █   ▄   █    ▄  █    ▄▄▄█  █ █ █ █▄     ▄█  █▄█  █",
"     █   █▄█ █   █▄▄█▄█  █ █  █   █▄█ █   █▄▄▄█   █▄▄█▄  █   █ █       █",
"     █    ▄▄▄█    ▄▄  █  █▄█  █    ▄▄▄█    ▄▄▄█    ▄▄  █ █   █ █▄     ▄█",
"     █   █   █   █  █ █       █   █   █   █▄▄▄█   █  █ █ █   █   █   █  ",
"     █▄▄▄█   █▄▄▄█  █▄█▄▄▄▄▄▄▄█▄▄▄█   █▄▄▄▄▄▄▄█▄▄▄█  █▄█ █▄▄▄█   █▄▄▄█  "
    };
    rows = sizeof property2 / sizeof property2[0];
    print2d(property2, rows);
}

void introScene(int scene){
    // scene can either be 1 or 2, representing a 50/50 chance to show the easter egg
    showWelcome();
    switch(scene){
        case 1:
            showPropertyTitle();
        break;
        case 2:
            showMonopolyTitle();
            char* flair = "oh wait...";
            newL
            print1d(flair, strlen(flair), 250, 250);
            clear
            return introScene(1);
        default:
            break;    
    }
}