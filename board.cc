#include "board.h"
#include <cmath>
#include "cellstate.h"
#include "heavy.h"
#include "generator.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;

Board::Board() {
    //this->theBoard=
    this->curr=nullptr;
    this->next=nullptr;
    this->hint=nullptr;
    this->hiScore=0;
    this->currScore=0;
    this->count=0;
    //this->newGame=true;
}

Board::~Board() {
    delete curr;
    delete next;
    delete hint;
}


//drop curr on the board but not yet change curr and next
void Board::dropBlock() {
    BlockState *bstate = dynamic_cast<BlockState *>(curr->getState());
    int len = bstate->states.size();
    for (int i = 0; i < len; i++) {
        int row = bstate->states[i].r;
        int col = bstate->states[i].c;
        BlockType b = bstate->states[i].blockt;
        int levelNum=curr->getLevelnum();
        theBoard[row][col].setBlockt(b);
        theBoard[row][col].setLevelnum(levelNum);
        theBoard[row][col].updateState();
        theBoard[row][col].notifyObservers();
        for (int j = 0; j < len; j++) {
            if (j != i) {
                int other_row = bstate->states[j].r;
                int other_col = bstate->states[j].c;
                theBoard[row][col].attach(&theBoard[other_row][other_col]);
            }
        }
        
    }
    clearLine();
    if (count!=0 && count%5==0 && level->getLevelNum()==4) {
        Block star=Block(BlockType::Star, level->getLevelNum());
        for (int i=0; i<HEIGHT; i++) {
            star.vertical_shift(1);
            Block *bptr=&star;
            if (!checkDrop(bptr)) {
                break;
            }
        }
        star.vertical_shift(-1);
        star.updateState();
        BlockState *starState = dynamic_cast<BlockState *>(star.getState());
        
        int rows = starState->states[0].r;
        int cols = starState->states[0].c;
        int levelNum1=star.getLevelnum();
        theBoard[rows][cols].setLevelnum(levelNum1);
        theBoard[rows][cols].setBlockt(BlockType::Star);
        theBoard[rows][cols].updateState();
        theBoard[rows][cols].notifyObservers();
        //assume count does not increase
    }
    updateState();
    notifyObservers();
}

//--finished
bool Board::checkDrop(Block *b) {
    BlockState *bstate = dynamic_cast<BlockState *>(b->getState());
    int len = bstate->states.size();
    for (int i = 0; i < len; i++) {
        int row = bstate->states[i].r;
        int col = bstate->states[i].c;
        if (!(row >= 0 && row <= 17 && col >= 0 && col <= 10)) {
            return false;
        }
        BlockType b1 = theBoard[row][col].getBlockt();
        if (b1 != BlockType::None) return false;
    }
    return true;
}

//--finished
int Board::getHiScore() {
    return this->hiScore;
}

//--finished
int Board::getWidth() {
    return this->WIDTH;
}

//--finished
int Board::getHeight() {
    return this->HEIGHT;
}

//--finished
//main everytime 
void Board::init(Level *l) {
    //delete original;
    delete curr;
    delete next;
    delete hint;
    curr = nullptr;
    next = nullptr;
    hint = nullptr;
    theBoard.clear();
    if (currScore > hiScore) {
        hiScore = currScore;
    }
    //set currScore and count to zero
    currScore = 0;
    count = 0;
    //init
    for (int i = 0; i < HEIGHT; i++) {
        vector<Cell> row;
        for (int j = 0; j < WIDTH; j++) {
            Cell c = Cell{i, j, BlockType::None};
            //every cell has a board ob
            for (int k = 0; k < this->getObservers().size(); k++) {
                Observer *currob = this->getObservers()[k];
                c.attach(currob);
            }
            row.emplace_back(c);
        }
        theBoard.emplace_back(row);
    }
    level = l;
}

//--finished
void Board::left() {
    Block *temp = curr->left();
    temp->updateState();
    if (checkDrop(temp)) {
        //drop the block on the board
        delete curr;
        curr = temp;
        curr->updateState();
    }
    curr->notifyObservers();
}

//--finished
void Board::right() {
    Block *temp = curr->right();
    if (checkDrop(temp)) {
        //drop the block on the board
        delete curr;
        curr = temp;
    }
    curr->updateState();
    curr->notifyObservers();
}

//--finished
void Board::down() {
    Block *temp = curr->down();
    if (checkDrop(temp)) {
        //drop the block on the board
        delete curr;
        curr = temp;
    }
    curr->updateState();
    curr->notifyObservers();
}

//--finished
void Board::clock() {
    Block *temp=curr->clock();
    if (checkDrop(temp)) {
        //drop the block on the board
        delete curr;
        curr = temp;
    }
    curr->updateState();
    curr->notifyObservers();
}

//--finished
void Board::coclock() {
    Block *temp=curr->coclock();
    if (checkDrop(temp)) {
        //drop the block on the board
        delete curr;
        curr = temp;
    }
    curr->updateState();
    curr->notifyObservers();
}

//calculate increased score by clearing lines
int Board::calcScoreLine() {
    int lineNum=0;
    for (int i=0; i<HEIGHT; i++) {
        int completeNum=0;
        for (int j=0; j<WIDTH; j++) {
            if (theBoard[i][j].getBlockt()!=BlockType::None) {
                completeNum++;
            }
        }
        if (completeNum==WIDTH) {
            lineNum++;
        }
    }
    int levelNum=level->getLevelNum();
    int incScore;
    if (lineNum==0) {
        incScore=0;
    } 
    else {
        incScore=pow(levelNum+lineNum,2);
    }
    return incScore;
}

//calculate increaed score by clearing blocks
int Board::calcScoreBlock(int lineNum) {
    int incScore=0;
    for (int i=0; i<WIDTH; i++) {
        if (theBoard[lineNum][i].getRem()==0) {
            int levelNum=theBoard[lineNum][i].getLevelnum();
            incScore+=pow(levelNum+1,2);
        }
    }
    return incScore;
}

void Board::clearLine() {
    currScore+=calcScoreLine();
    for (int i=0; i<HEIGHT; i++) {
        int completeNum=0;
        for (int j=0; j<WIDTH; j++) {
            if (theBoard[i][j].getBlockt()!=BlockType::None) {
                completeNum++;
            }
        }
        if (completeNum==WIDTH) {
            //score clear block
            //clear line
            for (int s=0; s<WIDTH; s++) {
                if (theBoard[i][s].getBlockt()==BlockType::Star) {
                    currScore+=pow(theBoard[i][s].getLevelnum()+1,2);
                }
                theBoard[i][s].setBlockt(BlockType::None);
                
                theBoard[i][s].notifyObservers();
            }
            currScore+=calcScoreBlock(i);
            theBoard.erase(theBoard.begin()+i);
            

            std::vector<Cell> newRow;
            for (int m=0; m<WIDTH; m++) {
                Cell c=Cell(0,m, BlockType::None);
                for (int x=0; x<this->getObservers().size(); x++) {
                    c.attach(this->getObservers()[x]);
                }
                newRow.emplace_back(c);
            }
            theBoard.insert(theBoard.begin(), newRow);
            for (int n=i; n>2; n--){
                for (int k=0; k<WIDTH; k++) {
                    theBoard[n][k].setIndex(n,k);
                    theBoard[n][k].updateState();
                    vector<Observer *>ob_copy = theBoard[n][k].getObservers();
                    vector<Observer *>ob_display;
                    for (int q = 0; q < getObservers().size(); q++) {
                        ob_display.emplace_back(getObservers()[q]);
                    }
                    theBoard[n][k].setObservers(ob_display);
                    theBoard[n][k].notifyObservers();
                    theBoard[n][k].setObservers(ob_copy);
                }
            }
        }
    }
    // for (int i = HEIGHT - 1; i >= 0; i--) {
    //     for (int j = 0; j < WIDTH; j++) {
    //         theBoard[i][j].notifyObservers();
    //     }
    // }
    if (currScore > hiScore) hiScore = currScore;
    notifyObservers();
    updateState();
}


bool Board::drop() {
    if (!checkDrop(curr)) return false;
    while (checkDrop(curr)) {
        curr->vertical_shift(1);
        curr->updateState();
    }
    curr->vertical_shift(-1);
    updateState();
    notifyObservers();
    dropBlock();
    return true;
}


//--finished
void Board::heavy() {
    Heavy *h = new Heavy{};
    Block *temp = nullptr;
    Block **double_temp = &temp;
    level->accept(h, curr, double_temp);
    if (temp && checkDrop(temp)) {
        delete curr;
    	curr = temp;
    	curr->notifyObservers();
    }
}


//--finished
//if command = IJL etc. mutate next into new block with blockType b
bool Board::generateBlock(BlockType b, int levelNum) {
    Block *temp = new Block{b, levelNum};
    for(int i = 0; i < this->getObservers().size(); i++) {
        temp->attach(this->getObservers()[i]);
    }
    if (!checkDrop(temp)) {
        delete temp;
        return false;
    }
    delete next;
    temp->normal_to_next();
    next = temp;
    next->notifyObservers();
    return true;
}

//--finished
bool Board::generate(BlockType b, int levelNum) {
    Block *temp = new Block{b, levelNum};
    for(int i = 0; i < this->getObservers().size(); i++) {
        temp->attach(this->getObservers()[i]);
    }
    if (!checkDrop(temp)) {
        delete temp;
        return false;
    }
    Block *temp_curr = curr;
    if (next) next->next_to_curr();
    curr = next;
    temp->normal_to_next();
    next = temp;
    delete temp_curr;
    if (curr) curr->notifyObservers();
    if (next) next->notifyObservers();
    count++;
    return true;
}

//--finished
bool Board::generate(){
    Generator *g = new Generator{};
    Block *temp = nullptr;
    Block **double_temp = &temp;
    level->accept(g, double_temp);
    for(int i = 0; i < this->getObservers().size(); i++) {
        temp->attach(this->getObservers()[i]);
    }
    if (!checkDrop(temp)) {
        delete temp;
        return false;
    }
    delete curr;
    if (next!=nullptr) {
        next->next_to_curr();
        curr = next;
    }
    temp->normal_to_next();
    next = temp;
    if (curr !=nullptr) curr->notifyObservers();
    next->notifyObservers();
    count++;
    delete g;
    return true;
}

//--finished
void Board::updateState() {
	State *gamestate = new GameState{level->getLevelNum(), currScore, hiScore};
	setState(gamestate);
}

//--finished
ostream &operator <<(ostream &out, const Board &b) {
    TextDisplay *td = nullptr;
    for (int i = 0; i < b.getObservers().size(); i++) {
        TextDisplay *curr_ob = dynamic_cast<TextDisplay *>(b.getObservers()[i]);
        if (curr_ob) td = curr_ob;
    }
    out << *td;
    return out;
}

void Board::setLevel(Level *lev) {
    level = lev;
}

void Board::giveHint() {
    int currline=0;
    int maxline=0;
    Block *currhint=nullptr;
    int i=0;
    Block *temp=new Block{*curr};
    BlockType b=curr->getBlockt();
    int rotateTimes=0;
    if (b==BlockType::O) {
        rotateTimes=1;
    }
    else if (b==BlockType::I || b==BlockType::S || b==BlockType::Z){
        rotateTimes=2;
    } else {
        rotateTimes=3;
    }
    for (int k=0; k<rotateTimes; k++) {
        
        while(i<WIDTH) {
            
            while (checkDrop(temp)) {
                temp->vertical_shift(1);
            }
            temp->vertical_shift(-1);
            temp->updateState();
            BlockState *bstate = dynamic_cast<BlockState *>(curr->getState());
            int len = bstate->states.size();
            //change board
            for (int j = 0; j < len; j++) {
                int row = bstate->states[i].r;
                int col = bstate->states[i].c;
                BlockType b = bstate->states[i].blockt;
                int levelNum=curr->getLevelnum();
                theBoard[row][col].setBlockt(b);
                theBoard[row][col].setLevelnum(levelNum);
            }
            int lineNum=0;
            for (int r=0; r<HEIGHT; r++) {
                int completeNum=0;
                for (int j=0; j<WIDTH; j++) {
                    if (theBoard[r][j].getBlockt()!=BlockType::None) {
                        completeNum++;
                    }
                }
                if (completeNum==WIDTH) {
                    lineNum++;
                }
            }
            if (currline==maxline) {
                BlockState *tstate = dynamic_cast<BlockState *>(temp->getState());
                BlockState *cstate = dynamic_cast<BlockState *>(currhint->getState());
                if (tstate->states[len-1].r<cstate->states[len-1].r) {
                    currhint=temp;
                    currhint->updateState();
                }
            }
            if (currline>maxline) {
                maxline=currline;
                currhint=temp;
                currhint->updateState();
            }
            delete bstate;
            i++;
        }
        delete temp;
        temp=curr->clock();
    }
    hint=currhint;
    BlockState *hstate = dynamic_cast<BlockState *>(hint->getState());
    int len=hstate->states.size();
    for (int i=0;i<len; i++) {
        hstate->states[i].blockt=BlockType::Hint;
    }
    hint->updateState();
    notifyObservers();
    delete currhint;
}

void Board::clearHint() {
    BlockState *hstate = dynamic_cast<BlockState *>(hint->getState());
    int len=hstate->states.size();
    
    for (int i=0; i<len; i++) {
        hstate->states[i].blockt=BlockType::None;
    }
    hint->updateState();
    notifyObservers();
    delete hint;
    hint=nullptr;
}

