/**************************************************************************************************

An interactive SUDOKU game which makes use of the standard template library and recursive algorithm

***************************************************************************************************/
#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int num) 
{
    // Check if 'num' already exists in the row
    for (int i = 0; i < 9; i++)  //O(N) time complexity where N is 9
    {
        if (board[row][i] == num) 
        {
            return false;
        }
    }
    
    // Check if 'num' already exists in the column
    for (int i = 0; i < 9; i++)   //O(N) time complexity where N is 9
    {
        if (board[i][col] == num) 
        {
            return false;
        }
    }
    
    // Check if 'num' already exists in the 3x3 box
    int boxRow = 3 * (row / 3);
    int boxCol = 3 * (col / 3);
    for (int i = 0; i < 3; i++)   //O(N^2) time complexity where N is 3
    {
        for (int j = 0; j < 3; j++) 
        {
            if (board[boxRow + i][boxCol + j] == num) 
            {
                return false;
            }
        }
    }
    
    return true;
}

bool solveSudoku(vector<vector<int>>& board) 
{
    for (int row = 0; row < 9; row++)  //O(N^3) time complexity where N is 9
    {
        for (int col = 0; col < 9; col++) 
        {
            if (board[row][col] == 0) 
            {
                // Find an empty cell
                
                // Create a map of possible values for the current cell
                map<int, bool> possibleValues;
                for (int num = 1; num <= 9; num++) 
                {
                    possibleValues[num] = true;
                }
                
                // Update the map based on horizontal, vertical, and box constraints
                for (int i = 0; i < 9; i++) 
                {
                    // Check row constraint
                    if (board[row][i] != 0) 
                    {
                        possibleValues[board[row][i]] = false;
                    }
                    
                    // Check column constraint
                    if (board[i][col] != 0) 
                    {
                        possibleValues[board[i][col]] = false;
                    }
                    
                    // Check box constraint
                    int boxRow = 3 * (row / 3);
                    int boxCol = 3 * (col / 3);
                    if (board[boxRow + i / 3][boxCol + i % 3] != 0) 
                    {
                        possibleValues[board[boxRow + i / 3][boxCol + i % 3]] = false;
                    }
                }
                
                // Try each possible value and solve recursively
                for (auto it = possibleValues.begin(); it != possibleValues.end(); it++) 
                {
                    int num = it->first;
                    if (it->second && isSafe(board, row, col, num)) 
                    {
                        board[row][col] = num;
                        
                        if (solveSudoku(board)) 
                        {
                            return true;
                        }
                        
                        board[row][col] = 0;
                    }
                }
                
                // If no solution found, backtrack
                return false;
            }
        }
    }
    
    return true;  // All cells filled, solution found
}

void printBoard(vector<vector<int>>& board) 
{
    for (int row = 0; row < 9; row++)  //  O(N^2) time complexity where N is 9
    {
        if(row % 3 == 0)
        {
            for(int i = 0; i < 13; i++)
            {
                cout << "-" << " ";
            }
            cout << "\n";
        }
        
        for (int col = 0; col < 9; col++) 
        {
            if(col % 3 == 0)
            {
                cout << "|" << " ";
            }
            cout << board[row][col] << " ";
        }
        cout << "|";
        cout << "\n";
    }
    for(int i = 0; i < 13; i++)
    {
        cout << "-" << " ";
    }
    cout << "\n";
}

int main() 
{
    vector<vector<int>> board(9, vector<int>(9)); 
    cout<<"ENTER A VALID SUDOKU BOARD AND REPLACE THE BLANKS WITH ZERO"<<"\n";
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cin >> board[i][j] ;
        }
    }
    if (solveSudoku(board)) 
    {
        cout << "Solution found; SUDOKU BOARD:" << "\n";
        printBoard(board);
    } 
    else 
    {
        cout << "No solution exists . Enter a valid board(Note each valid board definitely has a UNIQUE solution" << "\n";
    }
    
    return 0;
}
