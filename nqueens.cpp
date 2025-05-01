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
