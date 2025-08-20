#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Represent a chess piece
enum Piece { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

// Represent a color
enum Color { NONE, WHITE, BLACK };

// Struct for each square
struct Square {
    Piece piece;
    Color color;
};

// Chessboard 8x8
Square board[8][8];

// Initialize the board with pawns only for simplicity
void initBoard() {
    for (int i = 0; i < 8; i++) {
        board[1][i] = {PAWN, WHITE};
        board[6][i] = {PAWN, BLACK};
        for (int j = 2; j < 6; j++)
            board[j][i] = {EMPTY, NONE};
    }
}

// Print the board
void printBoard() {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].piece == PAWN)
                cout << (board[i][j].color == WHITE ? "P " : "p ");
            else
                cout << ". ";
        }
        cout << endl;
    }
}

// Generate all possible moves for pawns (very simplified)
vector<pair<int,int>> getPawnMoves(int x, int y) {
    vector<pair<int,int>> moves;
    if (board[x][y].color == WHITE && x+1 < 8 && board[x+1][y].piece == EMPTY)
        moves.push_back({x+1, y});
    if (board[x][y].color == BLACK && x-1 >= 0 && board[x-1][y].piece == EMPTY)
        moves.push_back({x-1, y});
    return moves;
}

// Simple random bot move
void makeRandomMove(Color turn) {
    vector<pair<int,int>> allPieces;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j].color == turn)
                allPieces.push_back({i,j});
    
    srand(time(0));
    while (!allPieces.empty()) {
        int idx = rand() % allPieces.size();
        int x = allPieces[idx].first;
        int y = allPieces[idx].second;
        auto moves = getPawnMoves(x, y);
        if (!moves.empty()) {
            int m = rand() % moves.size();
            int nx = moves[m].first;
            int ny = moves[m].second;
            board[nx][ny] = board[x][y];
            board[x][y] = {EMPTY, NONE};
            break;
        } else {
            allPieces.erase(allPieces.begin() + idx);
        }
    }
}

int main() {
    initBoard();
    printBoard();

    cout << "\nWhite moves:\n";
    makeRandomMove(WHITE);
    printBoard();

    cout << "\nBlack moves:\n";
    makeRandomMove(BLACK);
    printBoard();

    return 0;
}
