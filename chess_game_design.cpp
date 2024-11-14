#include <iostream>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

class Piece {
    private:
        bool white;
        bool killed = false;

    public:
        virtual bool canMove(Board* board, Block* startBlock, Block* endBlock) = 0; // Pure virtual function
        Piece(bool white) : white(white) {}
        bool isWhite() { 
            return white; 
        }
        bool isKilled() { 
            return killed; 
        }
        void setKilled(bool killed) { 
            this->killed = killed;
        }
};


class King : public Piece {
    public:
        King(bool white) : Piece(white) {}
        bool canMove(Board* board, Block* startBlock, Block* endBlock) {
            return false;
        }
};


class Queen : public Piece {
    public:
        bool canMove(Board* board, Block* startBlock, Block* endBlock) {
            return false;
        }
        Queen(bool white) : Piece(white) {}
};


class Bishop : public Piece {
    public:
        bool canMove(Board* board, Block* startBlock, Block* endBlock) {
            return false;
        }
        Bishop(bool white) : Piece(white) {}
};


class Knight : public Piece {
    public:
        bool canMove(Board* board, Block* startBlock, Block* endBlock) {
            return false;
        }
        Knight(bool white) : Piece(white) {}
};


class Rook : public Piece {
    public:
        bool canMove(Board* board, Block* startBlock, Block* endBlock) {
            return false;
        }
        Rook(bool white) : Piece(white) {}
};


class Pawn : public Piece {
    public:
        bool canMove(Board* board, Block* startBlock, Block* endBlock) {
            return false;
        }
        Pawn(bool white) : Piece(white) {}
};

//one block of 8*8 board and optional piece
class Block {
    private:
        int x, y;
        Piece* piece;
    public:
        Block(int x, int y, Piece* piece) {
            this->x = x;
            this->y = y;
            this->piece = piece;
        }
        Piece* getPiece() {
            return piece;
        }
        void setPiece(Piece* piece) {
            this->piece = piece;
        }
};

//8*8 chess board
class Board {
    private:
        Block* blocks[8][8];
    public:
        Board() {
            initializeBoard();
        }
    private:
        void initializeBoard() {
            // Setting White Pieces
            blocks[0][0] = new Block(0, 0, new Rook(true));
            blocks[0][1] = new Block(0, 1, new Knight(true));
            blocks[0][2] = new Block(0, 2, new Bishop(true));
            blocks[0][3] = new Block(0, 3, new Queen(true));
            blocks[0][4] = new Block(0, 4, new King(true));
            blocks[0][5] = new Block(0, 5, new Bishop(true));
            blocks[0][6] = new Block(0, 6, new Knight(true));
            blocks[0][7] = new Block(0, 7, new Rook(true));
            for (int j = 0; j < 8; j++) {
                blocks[1][j] = new Block(1, j, new Pawn(true));
            }
            // Setting Black Pieces
            blocks[7][0] = new Block(7, 0, new Rook(false));
            blocks[7][1] = new Block(7, 1, new Knight(false));
            blocks[7][2] = new Block(7, 2, new Bishop(false));
            blocks[7][3] = new Block(7, 3, new Queen(false));
            blocks[7][4] = new Block(7, 4, new King(false));
            blocks[7][5] = new Block(7, 5, new Bishop(false));
            blocks[7][6] = new Block(7, 6, new Knight(false));
            blocks[7][7] = new Block(7, 7, new Rook(false));
            for (int j = 0; j < 8; j++) {
                blocks[6][j] = new Block(6, j, new Pawn(false));
            }
            // Defining rest of the blocks having no pieces
            for (int i = 2; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    blocks[i][j] = new Block(i, j, nullptr);
                }
            }
        }
};

//a participant playing game
class Player {
public:
    string playerName;

    Player(const string& name) : playerName(name) {}
    
    void join(Game& game) {
        // Implementation of join function (if needed)
    }
};

//game move 
class Move {
    private:
        Player* player;
        Block* startBlock;
        Block* endBlock;
        Piece* pieceMoved;
        Piece* pieceKilled;
    public:
        Move(Player* player, Block* startBlock, Block* endBlock) {
            this->player = player;
            this->endBlock = endBlock;
            this->startBlock = startBlock;
            this->pieceMoved = startBlock->getPiece();
        }
        bool isValid() {
            return !(startBlock->getPiece()->isWhite() == endBlock->getPiece()->isWhite());
        }
        Block* getStartBlock() {
            return startBlock;
        }
        Block* getEndBlock() {
            return endBlock;
        }
};

//game status
enum class Status {
    ACTIVE, SAVED, BLACK_WIN, WHITE_WIN, STALEMATE, FORFEIT, RESIGNATION
};

class Game {
    private:
        Board gameBoard;
        Player playerOne;
        Player playerTwo;
        bool isWhiteTurn;
        vector<Move> gameLog;
        Status gameStatus;

    public:
        Game(Player player1, Player player2) 
            : playerOne(player1), playerTwo(player2), isWhiteTurn(true), gameStatus(Status::ACTIVE) {
            gameLog.reserve(100); // Reserve space for game log
        }

        void start() {
            // Continue the game till the status is active
            while (gameStatus == Status::ACTIVE) {
                // player1 will make the move if it's white's turn
                // else player2 will make the move
                if (isWhiteTurn) {
                    // playerMove(Move(startBlock, endBlock), playerOne);
                } else {
                    // playerMove(Move(startBlock, endBlock), playerTwo);
                }
            }
        }

        bool isEnd() {
            return this->getStatus() != Status::ACTIVE;
        }

         Status getStatus() {
            return this->gameStatus;
        }

        void setStatus(Status status) {
            this->gameStatus = status;
        }

        void makeMove( Move& move, Player& player) {
            // Initial check for valid move
            if (move.isValid()) {
                Piece* sourcePiece = move.getStartBlock()->getPiece();

                // Check if source piece can be moved or not
                if (sourcePiece->canMove(&gameBoard, move.getStartBlock(), move.getEndBlock())) {
                    Piece* destinationPiece = move.getEndBlock()->getPiece();
                    // check if destination block contains some piece
                    if (destinationPiece != nullptr) {
                        // if destination block contains King and currently white is playing --> White wins
                        if (dynamic_cast<King*>(destinationPiece) && isWhiteTurn) {
                            gameStatus = Status::WHITE_WIN;
                            return;
                        }
                        // if destination block contains King and currently Black is playing --> Black wins
                        if (dynamic_cast<King*>(destinationPiece) && !isWhiteTurn) {
                            gameStatus = Status::BLACK_WIN;
                            return;
                        }
                        // Set the destination piece as killed
                        destinationPiece->setKilled(true);
                    }
                    // Adding the valid move to game logs
                    gameLog.push_back(move);
                    // Moving the source piece to the destination block
                    move.getEndBlock()->setPiece(sourcePiece);
                    // Setting the source block to null (means it doesn't have any piece)
                    move.getStartBlock()->setPiece(nullptr);
                    // Toggling the turn
                    isWhiteTurn = !isWhiteTurn;
                }
            }
        }
};
