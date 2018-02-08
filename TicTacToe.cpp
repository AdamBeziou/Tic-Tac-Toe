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


int AdjacentCheck(int i, int j, int tempDecisionValue) {
    continue;
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
                        catch (const out_of_range& e) {
                                continue;
                        }
                    }
                }
            }

            if (tempDecisionValue > decisionValue) {
                decisionValue = tempDecisionValue;
                maxI = i;
                maxJ = j;
            }
        }
    }

    gameBoard[maxI][maxJ] = 2;
    return tieCheck;
}

bool UpdateScreen(vector<vector<int> > & gameBoard, int numPlayer) {
    int counter = 1;
    int gameChoice = 0;
    int i = 0;
    int j = 0;
    
    vector<int> jVals;
    vector<int> iVals;

    bool tieCheck = true;
    
    cout << string(50, '\n');
    cout << "Player " << numPlayer << endl
        << "--------" << endl << endl;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (gameBoard[i][j] == 0) {
                cout << counter;
                counter++;
                tieCheck = false;

                iVals.push_back(i);
                jVals.push_back(j);
            }
            else if (gameBoard[i][j] == 1) {
                cout << "X";
            }
            else {
                cout << "O";
            }

            if (j != 2) {
                cout << "|";
            }
        }
        if (i != 2) {
            cout << endl << "-|-|-" << endl;
        }
    }
        
    if (tieCheck == true) {
        return tieCheck;
    }

    else {

        cout << endl << endl << "Valid Spaces: ";
            
        for (i = 1; i < counter; i++) {
            if (i < counter - 1) {
                cout << i << ", ";
            }
            else {
                cout << i << ".";
            }
        }
            
        cout << endl << "Selection: ";

        do {
            cin >> gameChoice;
        } while (!(gameChoice >= 1 && gameChoice <= counter - 1));


        if (numPlayer == 1) {
            gameBoard[iVals.at(gameChoice - 1)][jVals.at(gameChoice - 1)] = 1;
        }
        else {
            gameBoard[iVals.at(gameChoice - 1)][jVals.at(gameChoice - 1)] = 2;
        }

        return tieCheck;
    }
}


void PvPGame() {
    vector< vector<int> > gameBoard(3, vector<int>(3));
    int tieCheck;
    int numPlayer = 1;
    bool human = true;
    bool win = false;

    while (win == false) {
        tieCheck = UpdateScreen(gameBoard, numPlayer);

        if (tieCheck == true) {
            cout << endl << endl << "It's a tie!" << endl << endl;
            break;
        }

        win = CheckWin(gameBoard);

        if (win == false) {
            numPlayer = (numPlayer % 2) + 1;
        }
        else {
            cout << endl << endl << "Player " << numPlayer << " has won!" << endl << endl;
        }
    }

    return;
}


void PvCPUGame() {
    vector< vector<int> > gameBoard(3, vector<int>(3));
    int tieCheck;
    int numPlayer = 1;
    bool win = false;

    do {
        tieCheck = UpdateScreen(gameBoard, numPlayer);

        win = CheckWin(gameBoard);

        if (win == true) {
            cout << endl << endl << "You've won!" << endl << endl;
            return;
        }

        else if (tieCheck == true) {
            cout << endl << endl << "It's a tie!" << endl << endl;
            return;
        }

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

int main() {
    char gameChoice = '0';
    char continueChoice = 'y';

    do {
        cout << string(50, '\n');

        cout << "Tic-Tac-Toe" << endl
             << "-----------" << endl
             << "Select a game:" << endl
             << "1) Player vs Player" << endl
             << "2) Player vs CPU" << endl
             << "3) Quit" << endl
             << "Selection: ";

        do {
            cin.get(gameChoice);
        } while (gameChoice != '1' && gameChoice != '2' && gameChoice != '3');

    
        switch(gameChoice) {
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

        cout << "Do you want to play again? (y/n)" << endl;
        cout << "Selection: ";
        
        do {
            cin.get(continueChoice);
        } while(continueChoice != 'n' && continueChoice != 'y');

    } while (continueChoice == 'y');

    return 0;
}