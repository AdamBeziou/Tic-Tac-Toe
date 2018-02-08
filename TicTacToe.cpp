#include <iostream> // For cin, cout, etc.
#include <string> // For spacing using '\n'
#include <vector> // For the game board
using namespace std;


int CheckWin(vector< vector<int> > gameBoard) { // Checks for win conditions
    /* Sets up variables for loops, checking, and win state */
    int i = 0; 
    int j = 0;
    int checkValue = 0;
    bool win = false;

    /* Checks for 3 across of the same type */
    if (win == false) { // Checks if the game is already won
        for (i = 0; i < 3; i++) { // Starts at the top and goes to the bottom of the board
            checkValue = gameBoard[i][0]; // Sets a value at the leftmost position of a row to be checked against
    
            if (checkValue != 0 && win == false) { // Checks if the check value is not an open space (which will always win because the board is all blank) and that the game is not already won
                win = true; // Sets the win condition to a default position of true

                for (j = 1; j < 3; j++) { // Goes down the row, checking every value against the check; if there is a mismatch, the loop is broken
                    if (gameBoard[i][j] != checkValue) {
                        win = false;
                        break;
                    }
                    else {
                        continue;
                    }
                }
            }
        }
    }

    /* Checks for 3 down of the same type */
    if (win == false) {
        for (j = 0; j < 3; j++) {
            checkValue = gameBoard[0][j];

            if (checkValue != 0 && win != true) {
                win = true;
                
                for (i = 1; i < 3; i++) {
                    if (gameBoard[i][j] != checkValue) {
                        win = false;
                        break;
                    }
                    else {
                        continue;
                    }
                }
            }
        }
    }

    /* Checks for diagonal win conditions */
    if (win == false) {
        
        checkValue = gameBoard[0][2];

        if (checkValue != 0 && win != true) {
            win = true;

            for (i = 0; i < 3; i++) {
                if (gameBoard[i][2 - i] == checkValue) {
                    continue;
                }
                else {
                    win = false;
                    break;
                }
            }
        }

        checkValue = gameBoard[0][0];

        if (checkValue != 0 && win != true) {
            win = true;

            for (i = 0; i < 3; i++) {
                if (gameBoard[i][0 + i] == checkValue) {
                    continue;
                }
                else {
                    win = false;
                    break;
                }
            }
        }
    }

    return win; // Returns win state
}

/* Below is all of the CPU process garbage */
int AdjacentCheck(int i, int j, int tempDecisionValue, vector<vector<int> > & gameBoard) { // Checks for adjacent squares of the same type, modifying the CPU's decision value

    /* Declares/initializes variables for the for-loops and check values */
    int x = 0;
    int y = 0;
    int checkValue = 0;

    /* For-loops to check adjacent squares */
    for (x = -1; x < 2; x++) {
        for (y = -1; y < 2; y++) {
            if (y != 0 && x != 0) { // Prevents a square from checking itself
                try {
                    checkValue = gameBoard.at(i + x).at(j + y); // Checks every adjacent square

                    if (checkValue == 0) {
                        tempDecisionValue += 1;
                    }
                    else if (checkValue == 1) {
                        tempDecisionValue += 2;
                    }
                    else if (checkValue == 2) {
                        tempDecisionValue += 2;
                    }
                }
                catch (const out_of_range& e) { // Catches out of range errors
                    continue;
                }
            }
        }
    }

    return tempDecisionValue; // Returns the decision value
}

bool CPUMove(vector<vector<int> > & gameBoard){

    /* Declares a number of variables for looping, decision-making, etc. */
    int i = 0;
    int j = 0;

    int decisionValue = 0;
    int maxI = 0;
    int maxJ = 0;

    int x = 0;
    int y = 0;

    int tempDecisionValue = 0;
    int positionValue = 0;
    int checkValue = 0;

    bool tieCheck = true;

    /* Checks for the first open position; if there are none, tells the game function that there is a tie */
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (gameBoard.at(i).at(j) == 0) {
                maxI = i;
                maxJ = j;
                tieCheck = false;
            }
        }
    }

    if (tieCheck == true) {
        return tieCheck;
    }

    /* Main decision loop */
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            positionValue = gameBoard[i][j]; // Checks every position to see if it is 0
            tempDecisionValue = 0; // Sets the "decision" value to 0
                
            if (positionValue == 0) { // If the position is blank, continues
                
                for (x = -1; x < 2; x++) {
                    for (y = -1; y < 2; y++) {
                        if (y != 0 && x != 0) {
                            try {
                                checkValue = gameBoard.at(i + x).at(j + y); // Checks every adjacent square

                                if (checkValue == 0) {
                                    tempDecisionValue += 1;
                                }
                                else if (checkValue == 1) {
                                    tempDecisionValue += 2;
                                    tempDecisionValue += AdjacentCheck(i + x, j + y, tempDecisionValue, gameBoard);
                                }
                                else if (checkValue == 2) {
                                    tempDecisionValue += 2;
                                    tempDecisionValue += AdjacentCheck(i + x, j + y, tempDecisionValue, gameBoard);
                                }
                            }
                            catch (const out_of_range& e) { // Catches out of range errors
                                    continue;
                            }
                        }
                    }
                }
            }

            if (tempDecisionValue > decisionValue) { // If the current square's decision value is larger than the previous largest squares, replaces the previous position with the current
                decisionValue = tempDecisionValue;
                maxI = i;
                maxJ = j;
            }
        }
    }

    gameBoard[maxI][maxJ] = 2; // Changes the square with the largest decision value
    return tieCheck;
}

/* Below is the player decision garbage */
bool UpdateScreen(vector<vector<int> > & gameBoard, int numPlayer) {

    /* Declares/initializes varables for for-loops, choices, etc. */
    int counter = 1;
    int gameChoice = 0;
    int i = 0;
    int j = 0;
    
    vector<int> jVals;
    vector<int> iVals;

    bool tieCheck = true;
    
    cout << string(50, '\n'); // Creates a large space to separate different actions
    cout << "Player " << numPlayer << endl // Displays the urrent player's number
        << "--------" << endl << endl;

    for (i = 0; i < 3; i++) { // Checks if each square is empty/available
        for (j = 0; j < 3; j++) {
            if (gameBoard[i][j] == 0) { // IF a square is available, increments the counter (used for diaplayying choices), changes the tie checker to false, and appends the i/j value vectors with its position
                counter++;
                tieCheck = false;

                iVals.push_back(i);
                jVals.push_back(j);
            }
            else if (gameBoard[i][j] == 1) { // IF the square is owned/claimed by player 1, displays an X
                cout << "X";
            }
            else { // If the square is owned/claimed by player 2/CPU, displays a O
                cout << "O";
            }

            if (j != 2) { // Separates adjacent symbols
                cout << "|";
            }
        }
        if (i != 2) { // Separates adjacent rows
            cout << endl << "-|-|-" << endl;
        }
    }
        
    if (tieCheck == true) { // Tells the game function if there is a tie before prompting for a chooice
        return tieCheck;
    }

    else {

        cout << endl << endl << "Valid Spaces: "; // Lists the valid spaces
            
        for (i = 1; i < counter; i++) {
            if (i < counter - 1) {
                cout << i << ", ";
            }
            else {
                cout << i << ".";
            }
        }
            
        cout << endl << "Selection: "; // Prompts the user for a selection

        do {
            cin >> gameChoice;
        } while (!(gameChoice >= 1 && gameChoice <= counter - 1)); // Checks for a valid input


        if (numPlayer == 1) { // IF player == 1, replaces choice with an X, else replaces with an O
            gameBoard[iVals.at(gameChoice - 1)][jVals.at(gameChoice - 1)] = 1;
        }
        else {
            gameBoard[iVals.at(gameChoice - 1)][jVals.at(gameChoice - 1)] = 2;
        }

        return tieCheck;
    }
}


/* Below is the function for a PVP game */
void PvPGame() {

    /* Declares variables for the game board, tie checking, win state, etc. */
    vector< vector<int> > gameBoard(3, vector<int>(3));

    int tieCheck;
    int numPlayer = 1;

    bool win = false;

    while (win == false) { // While nobody has won...
        tieCheck = UpdateScreen(gameBoard, numPlayer); // Prompts the current playyer for a choice, checks if there is a tie

        if (tieCheck == true) { // Breaks if there is a tie
            cout << endl << endl << "It's a tie!" << endl << endl;
            break;
        }

        win = CheckWin(gameBoard); // Checks if anyone won if not

        if (win == false) { // If nobody won, changes the player number and repeats
            numPlayer = (numPlayer % 2) + 1;
        }
        else { // IF somebody won, break and display who won
            cout << endl << endl << "Player " << numPlayer << " has won!" << endl << endl;
        }
    }

    return;
}


/* Below is the function for PVCPU games */
void PvCPUGame() {

    /* Declares variabes for the game board, tie checking, win state, etc. */
    vector< vector<int> > gameBoard(3, vector<int>(3));

    int tieCheck;
    int numPlayer = 1;

    bool win = false;

    do { // While true...
        tieCheck = UpdateScreen(gameBoard, numPlayer); // Prompts the user for a decision and checks if there is a tie

        win = CheckWin(gameBoard); // Checks if anyone won

        if (win == true) { // IF the player has won, break and tell them
            cout << endl << endl << "You've won!" << endl << endl;
            return;
        }

        else if (tieCheck == true) { // IF there is a tie, break and tell the player
            cout << endl << endl << "It's a tie!" << endl << endl;
            return;
        }

        // Else, repeat the process for the CPU
        tieCheck = CPUMove(gameBoard);

        win = CheckWin(gameBoard);

        if (win == true) {
            cout << endl << endl << "You've lost!" << endl << endl;
            return;
        }

        else if (tieCheck == true) {
            cout << endl << endl << "It's a tie!" << endl << endl;
            return;
        }
    } while (true);
}


/* Below is the main function */
int main() {

    /* Declares the variables for the game choice and repeating choice */
    char gameChoice = '0';
    char continueChoice = 'y';

    do { // While the player wants to repeat/when the game starts...
        cout << string(50, '\n'); // Create some spacing

        cout << "Tic-Tac-Toe" << endl // List choices for games
             << "-----------" << endl
             << "Select a game:" << endl
             << "1) Player vs Player" << endl
             << "2) Player vs CPU" << endl
             << "3) Quit" << endl
             << "Selection: ";

        do {
            cin.get(gameChoice); // Get game choice and check for invalid inputs
        } while (gameChoice != '1' && gameChoice != '2' && gameChoice != '3');

    
        switch(gameChoice) { // Checks what game the player wants to play
            case '1':
                PvPGame();
                break;
            case '2':
                PvCPUGame();
                break;
            case '3':
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Something broke. Goodbye!" << endl;
                break;
        }

        cout << "Do you want to play again? (y/n)" << endl; // Once a game is over, asks the player is they want to play again
        cout << "Selection: ";
        
        do {
            cin.get(continueChoice);
        } while(continueChoice != 'n' && continueChoice != 'y');

    } while (continueChoice == 'y');

    return 0;
}
