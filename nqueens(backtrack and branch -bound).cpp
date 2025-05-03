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
bool issafe_forbacktrack(vector<vector<char>>& board, int row, int col, int n) {
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
void queensplace_backtrack(vector<vector<char>>& board, int row, int n) {
    if (row == n) {
        printboard(board, n);
        return;
    }
    for (int j = 0; j < n; j++) {
        if (issafe_forbacktrack(board, row, j, n)) {
            board[row][j] = 'Q';
            queensplace_backtrack(board, row + 1, n);
            board[row][j] = '.';
        }
    }
}

// Branch and Bound version of N-Queens
void queensplace_branch_bound(vector<vector<char>>& board, int row, int n,
                               vector<bool>& column,
                               vector<bool>& diag1,
                               vector<bool>& diag2) {
    if (row == n) {
        printboard(board, n);
        return;
    }

    for (int j = 0; j < n; j++) {
        if (!column[j] && !diag1[row + j] && !diag2[row - j + n - 1]) {
            // Place queen
            board[row][j] = 'Q';
            column[j] = diag1[row + j] = diag2[row - j + n - 1] = true;

            // Recurse to next row
            queensplace_branch_bound(board, row + 1, n, column, diag1, diag2);

            // Backtrack
            board[row][j] = '.';
            column[j] = diag1[row + j] = diag2[row - j + n - 1] = false;
        }
    }
}
int main() {
    
    cout << "n: ";
    int n;
    cin >> n;
    cout<<"-----------------------Backtracking"<<endl;
   
    
    vector<vector<char>> board(n, vector<char>(n, '.'));
    queensplace_backtrack(board, 0, n);
    
    
    
    cout<<"--------------------branch and bound"<<endl;
    vector<vector<char>> board2(n, vector<char>(n, '.'));

    //Branch and bound helpers
    
    vector<bool> column(n, false);
    vector<bool> diag1(2 * n - 1, false);
    vector<bool> diag2(2 * n - 1, false);

    // Start placing queens
    queensplace_branch_bound(board2, 0, n, column, diag1, diag2);
    return 0;
}