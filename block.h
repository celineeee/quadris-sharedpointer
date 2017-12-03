#ifndef block_h
#define block_h
#include <vector>
#include "cell.h"
#include "blockstate.h"
#include "blocktype.h"

class Subject;
class Block: public Subject {
    int blockWid;
    int blockHei;
    std::vector<std::vector<Cell>> cells;
    BlockType blockt;
    int levelnum;

    
public:
    Block(BlockType,int);
    Block(const Block &other);
    Block &operator=(const Block &other);
    Block *left();
    Block *right();
    Block *down();
    Block *clock();
    Block *coclock();
    void updateState();
    void vertical_shift(int n);
    void normal_to_next();
    void next_to_curr();
    int getLevelnum();
    void setLevelnum(int);
    BlockType getBlockt();
};


#endif
