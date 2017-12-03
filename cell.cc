#include "cell.h"
#include "observer.h"
#include "cellstate.h"
#include <iostream>

using namespace std;

Cell::Cell(int r, int c, BlockType blockt): r{r}, c{c}, blockt{blockt} {
    remained = 3;
    levelnum = -1;
    updateState();
}

Cell::Cell(const Cell &other): r{other.r}, c{other.c}, blockt{other.blockt}, 
remained{other.remained}, levelnum{other.levelnum} {
    Subject::operator=(other);
    updateState();
}

Cell &Cell::operator=(const Cell &other) {
    Subject::operator=(other);
    r = other.r;
    c = other.c;
    blockt = other.blockt;
    remained = other.remained;
    levelnum = other.levelnum;
    updateState();
    return *this;
}

void Cell::updateState() {
    shared_ptr<State> cell_state = make_share<CellState> {r, c, blockt};
    setState(cell_state);
}

void Cell::notify(Subject &whoFrom) {
    shared_ptr<State> state = whoFrom.getState();
    CellState *cstate = dynamic_cast<CellState *>(state);
    remained--;
    int whof_r = cstate->r;
    int whof_c = cstate->c;
    for (int i = 0; i < getObservers().size(); i++) {
        Observer *curr = getObservers()[i];
        Cell *cell_curr = dynamic_cast<Cell*>(curr);
        if (cell_curr) {
            int curr_r = cell_curr->r;
            int curr_c = cell_curr->c;
            if (whof_r == curr_r && whof_c == curr_c) {
                detach(cell_curr);
            }
        }
    }
}

void Cell::setBlockt(BlockType b) {
    blockt = b;
}

BlockType Cell::getBlockt() {
    return blockt;
}

void Cell::setIndex(int r, int c) {
    this->r = r;
    this->c = c;
    updateState();
}

pair<int, int> Cell::getIndex() {
    pair<int, int> result(r, c);
    return result;
}

int Cell::getRem() {
    return remained;
}

void Cell::setRem(int r) {
    remained = r;
}

int Cell::getLevelnum(){
    return levelnum;
}

void Cell::setLevelnum(int i){
    levelnum = i;
}
