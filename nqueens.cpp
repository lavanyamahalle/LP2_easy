#include<bits/stdc++.h>
using namespace std;
void printboard(vector<vector<char>>& board, int n) {
    cout << "board" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
        }
}

bool issafe(vector<vector<char>>& board, int row, int col, int n) {
    // vertical
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }
    // upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }
    // upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }
    return true;
}

void queensplace(vector<vector<char>>& board, int row, int n) {
    if (row == n) {
        printboard(board, n);
        return;
    }
    for (int j = 0; j < n; j++) {
        if (issafe(board, row, j, n)) {
            board[row][j] = 'Q';
            queensplace(board, row + 1, n);
            board[row][j] = '.';
        }
    }
}
int main() {
    cout << "n: ";
    int n;
    cin >> n;
    vector<vector<char>> board(n, vector<char>(n, '.'));
    queensplace(board, 0, n);
    return 0;
}


//Time Complexity
/*    O(N * N!)

   O(N):For each queen placement, the issafe function checks the column and two diagonals. This takes O(N) time for each call.

   O(N!): backtracking explores all possible placements of queens.
   For the first row, there are N possible positions to place a queen.
   For the second row, there are at most N-1 valid positions (since one column is already occupied, and some diagonals may also be blocked).
   For the third row, there are at most N-2 valid positions, and so on.
    

*/

//space complexity
/*    O(N^2): The space complexity is O(N^2) because we are using a 2D board of size N x N to store the positions of the queens.
   Additionally, the recursion stack can go up to O(N) in depth, but the dominant factor is the board size.
*/



//Code explaination
/*
Here is the flow of function execution in your N-Queens program:

1. main()
The program starts in the main() function.
It takes input n (size of the chessboard).
Initializes a 2D board of size n x n with '.' (empty cells).
Calls the recursive function queensplace(board, 0, n) to start placing queens from row 0.

2. queensplace()
Base Case:
If row == n, all queens are placed successfully:
Calls printboard() to display the current board configuration.
Returns to explore other solutions (backtracking).
Recursive Case:
For the current row:

Iterates over all columns (j = 0 to n-1).
Calls issafe(board, row, j, n) to check if placing a queen at (row, j) is valid.
If safe:
Places the queen (board[row][j] = 'Q').
Recursively calls queensplace(board, row + 1, n) to place queens in the next row.
Backtracks by removing the queen (board[row][j] = '.') after exploring all possibilities.

3. issafe()
Checks if placing a queen at (row, col) is safe:
Column Check: Ensures no queen exists in the same column above the current row.
Upper-Left Diagonal Check: Ensures no queen exists in the upper-left diagonal.
Upper-Right Diagonal Check: Ensures no queen exists in the upper-right diagonal.
Returns true if the position is safe, otherwise false.

4. printboard()
Prints the current state of the board when a valid configuration is found.
Iterates through the 2D board and displays 'Q' for queens and '.' for empty cells.


Flow Example for N = 4:
main() initializes the board and calls queensplace(board, 0, 4).
queensplace() tries placing a queen in row 0, column 0, and calls issafe().
If safe, places the queen and recursively calls queensplace(board, 1, 4).
Repeats the process for subsequent rows.
If a conflict arises, backtracks to the previous row and tries the next column.
When all queens are placed, calls printboard() to display the solution.
Continues exploring other solutions until all possibilities are exhausted.






/*Viva*/

/*1. What is the N-Queens problem?
Answer:
The N-Queens problem is a classic combinatorial problem where the goal is to place N queens on an N x N chessboard such that no two queens threaten each other. This means no two queens can be in the same row, column, or diagonal.

2. How does your program solve the N-Queens problem?
Answer:
The program uses a backtracking approach. It places queens row by row, checking if the position is safe using the issafe function. If a position is safe, the queen is placed, and the program recursively tries to place queens in the next row. If no valid position is found, it backtracks by removing the queen and trying the next position.

3. What is the role of the issafe function?
Answer:
The issafe function checks if placing a queen at a specific position (row, col) is valid. It ensures that no other queen exists in the same column, upper-left diagonal, or upper-right diagonal.

4. What is backtracking, and why is it used here?
Answer:
Backtracking is a recursive algorithmic technique used to solve problems by exploring all possible solutions and abandoning paths that fail to satisfy the constraints. It is used here to systematically explore all possible queen placements and backtrack when a conflict arises.

5. How does the printboard function work?
Answer:
The printboard function prints the current state of the chessboard. It iterates through the board matrix and displays each cell, showing where the queens ('Q') are placed and empty cells ('.').

6. What is the time complexity of your solution?
Answer:
The time complexity of the N-Queens problem using backtracking is approximately O(N!). This is because there are N choices for the first row, N-1 for the second row, and so on.

7. How do you ensure that no two queens are on the same diagonal?
Answer:
To check for diagonal conflicts:

For the upper-left diagonal, the program iterates with i-- and j--.
For the upper-right diagonal, it iterates with i-- and j++.
If a queen is found in either diagonal, the position is deemed unsafe.

8. What happens if no solution exists for a given N?
Answer:
If no solution exists, the program will backtrack through all possible placements and eventually terminate without printing any board configurations.

9. Can this program handle all values of N?
Answer:
The program can handle all values of N greater than or equal to 1. However, for N = 2 and N = 3, no solutions exist, so the program will not print any boards.

10. How can this program be optimized further?
Answer:
The program can be optimized by:

Using bitwise operations to represent columns and diagonals instead of a 2D board.
Reducing redundant checks in the issafe function.
Let me know if you need more questions or explanations!*/