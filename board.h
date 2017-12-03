#ifndef board_h
#define board_h
#include <vector>
#include "block.h"
#include "level.h"
#include "gamestate.h"
#include "levelvisitor.h"


class Board : public Subject{
    std::vector<std::vector<Cell>> theBoard;
    //notify all not none blocktype
    Block *curr;
    Block *next;
    Block *hint;
    Level *level;
    const int WIDTH=11;
    const int HEIGHT=18;
    int hiScore;
    int currScore;
    int count; //mutate count
    //bool newGame;
    
    //drop curr onto the board
    void dropBlock();
    //return and clear row number which need to be cleared
    void clearLine();
    
public:
    Board();
    ~Board();
    void updateState();
    int getHeight();
    int getWidth();
    int getHiScore();
    //check if mutate is possible
    bool checkDrop(Block *);
    //initialize the board, delete td, cell and block gd???
    void init(Level *);
    //mutate curr block, have a copy of curr pass to level and
    void left();
    void right();
    void down();
    void clock();
    void coclock();
    
    int calcScoreLine();
    int calcScoreBlock(int LineNum);
    
    //if return false, tell main game over, cell->notify, set friends
    bool drop();
    
    //pass level * and curr to level
    void heavy();
    

    void giveHint();
    void clearHint();
    
    //regular generate
    bool generate();
    //generate given a blocktype
    bool generate(BlockType, int);
    bool generateBlock(BlockType, int);
    void setLevel(Level *lev);
    
    friend std::ostream &operator <<(std::ostream &out, const Board &b);
    
};

#endif
