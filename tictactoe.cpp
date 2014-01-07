#include <vector>
#include <iostream>

using namespace std;

const bool CLEAR_SCREEN = true;

/// @brief Utilizes an escape character sequence to clear the screen
void clearScreen()
{
    cout << endl;

    if (CLEAR_SCREEN)
    {
        cout << "\033c";
    }

    cout << endl;
}


/// @brief Draws the provided tic-tac-toe board to the screen
//  @param board is the tic-tac-toe board that should be drawn
void drawBoard(const vector <char> &board)
{
    clearScreen();
    for (int i = 0; i < 9; i += 3)
    {
        cout << "  " << board.at(i) << "  |  " << board.at(i + 1) << "  |  "
            << board.at(i + 2) << "  " << endl;
        if (i < 6)
            cout << "-----|-----|-----" << endl;
    }
    cout << endl;
}



/// @brief Fills vector with characters starting at lower case a.
///
///     The amount of the alphabet placed into the vector depends on its size.
///     When the vector is size 1 then it will have only character a.
///     When the vector is size 5 then it will have characters a to e.
///     When the vector is size 26 then it will have characters a to z.
///
/// @param v the vector to initialize
/// @pre-condition the vector size will never be over 26
void initVector(vector <char> &v)
{
    //not sure why we needed the entire alphabet, but whatever.
    if (v.size() <= 26)
    {
        for (int i = 0; i < v.size(); i++)
        {
            v.at(i) = 'a' + i;
        }
    }
    
    return;
}


/// @brief Converts a character representing a cell to associated vector index
/// @param the position to be converted to a vector index
/// @return the integer index in the vector, should be 0 to (vector size - 1)
int convertPosition(char position)
{
    //using the function above, name a new vector to compare the inputted
    //character position.
    vector <char> v1(9);
    
    initVector(v1);

    for (int i = 0; i < v1.size(); i++)
    {
        if (position == v1.at(i))
            return i;
    }
    
    return 10;
}


/// @brief Predicate function to determine if a spot in board is available.
/// @param board the current tic-tac-toe board 
/// @param position is an index into vector to check if available
/// @return true if position's state is available (not marked) AND is in bounds
bool validPlacement(const vector <char> &board, int position)
{
    //if there is an empty statement then this function becomes true.
    if (position < board.size())
    {
        if ((board.at(position) != 'x' && board.at(position) != 'o'))
            return true;
    }
    else
        return false;
}

/// @brief Acquires a play from the user as to where to put her mark
///
///     Utilizes convertPosition and validPlacement functions to convert the
///     user input and then determine if the converted input is a valid play.
///
/// @param board the current tic-tac-toe board 
/// @return an integer index in board vector of a chosen available board spot
int getPlay(const vector <char> &board)
{
    //the position inputted by user.
    char position;
    int index;
    
    do
    {
        cout << "Please choose a position: ";
        cin >> position;
        cout << endl;
        
        index = convertPosition (position);
    } while ((!validPlacement(board, index)));
    return index;
}


/// @brief Predicate function to determine if the game has been won
///
///     Winning conditions in tic-tac-toe require three marks from same 
///     player in a single row, column or diagonal.
///
/// @param board the current tic-tac-toe board 
/// @return true if the game has been won, false otherwise
bool gameWon(const vector <char> &board)
{
    //code to determine if we have 3 in a row horizontally, then vertically
    for (int i = 0; i < 3; i++)
    {
        if (board.at(3*i) == board.at(3*i+1) 
            && board.at(3*i+1) == board.at(3*i+2))
            return true;
        else if (board.at(i) == board.at(i+3) && board.at(i+3) == board.at(i+6))
            return true;
    }
    
    //code to determine if we have 3 in a row diagonally.
    if (board.at(0) == board.at(4) && board.at(4) == board.at(8))
        return true;
    else if (board.at(2) == board.at(4) && board.at(4) == board.at(6))
        return true;
        
    return false;
}


/// @brief Predicate function to determine if the board is full
/// @param board the current tic-tac-toe board 
/// @return true iff the board is full (no cell is available)
bool boardFull(const vector <char> &board)
{
    //game is a draw when 9 turns have gone by with no winner.
    int j = 0;
    for (int i = 0; i < board.size(); i++)
    {
        if (board.at(i) == 'x' || board.at(i) == 'o')
            j++;
    }
    
    if(j == 9)
        return true;
    else
        return false;
}


// Global constants for player representation
const int PLAYER1 = 0;
const int PLAYER2 = 1;

int main()
{
    // Variables that you may find useful to utilize
    vector <char> board(9);
    int curPlay;
    int turn = PLAYER1; // Player 1 always goes first and is 'x'

    /// TODO: Initialize board to empty state
    initVector(board);

    /// TODO: Display empty board
    drawBoard(board);


    /// TODO: Play until game is over
    while (!boardFull(board) && !gameWon(board))
    {
        curPlay = getPlay(board);
        
        board.at(curPlay) = (turn == PLAYER1) ? 'x' : 'o';
        
        // Turn switches only when board is not full or game is not won
        if (!boardFull(board) && !gameWon(board))
        {
            if (turn == PLAYER1)
                turn = PLAYER2;
            else if (turn == PLAYER2)
                turn = PLAYER1;
        }
        
        drawBoard(board);
    }

    if (turn == PLAYER1 && gameWon(board))
        cout << "Player 1 (x's) wins!" << endl << endl;
    else if (turn == PLAYER2 && gameWon(board))
        cout << "Player 2 (o's) wins!" << endl << endl;
    else
        cout << "No one wins" << endl << endl;
    /// TODO: Determine winner 

    return 0;
}
