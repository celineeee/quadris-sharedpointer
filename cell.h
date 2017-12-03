#ifndef cell_h
#define cell_h
#include <utility>
#include "subject.h"
#include "observer.h"
#include "blocktype.h"

class Cell:public Subject, public Observer {
    int r;
    int c;
    BlockType blockt=BlockType::None;
    int remained;
    int levelnum;

public:
    Cell(int r, int c, BlockType blockt);
    Cell(const Cell &other);
    Cell &operator=(const Cell &other);
    void updateState();
    void notify(Subject &) override;
    void setBlockt(BlockType);
    BlockType getBlockt();
    void setIndex(int, int);
    std::pair <int, int> getIndex();
    int getRem();
    void setRem(int);
    int getLevelnum();
    void setLevelnum(int i);
};

#endif
