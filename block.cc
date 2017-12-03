#include "block.h"
#include "cellstate.h"
#include <iostream>

using namespace std;

Block &Block::operator=(const Block &other){
	Subject::operator=(other);
	blockWid = other.blockWid;
    blockHei = other.blockHei;
    blockt = other.blockt;
    levelnum = other.levelnum;
    cells.clear();
    for (int i = 0; i < other.blockHei; i++){
        std::vector<Cell> row;
    	for(int j = 0; j < other.blockWid; j++) {
    		Cell newcell{other.cells[i][j]};
    		row.emplace_back(newcell);
    	}
    	cells.emplace_back(row);
    }
    updateState();
    return *this;
}

Block::Block(const Block &other): blockWid{other.blockWid}, blockHei{other.blockHei},
blockt{other.blockt}, levelnum{other.levelnum}{
    
	Subject::operator=(other);
	cells.clear();
    for (int i = 0; i < other.blockHei; i++){
        std::vector<Cell> row;
    	for(int j = 0; j < other.blockWid; j++) {
    		Cell newcell{other.cells[i][j]};
    		row.emplace_back(newcell);
    	}
    	cells.emplace_back(row);
    }
    updateState();

}

//all notify are set in board
//everytime mutate block, set new state to each cell, delete old one
void Block::updateState() {
    std::vector<CellState> states;
    for(int i = 0; i < blockHei; i++) {
        for (int j = 0; j < blockWid; j++) {
            cells[i][j].updateState();
            BlockType curr_bt = cells[i][j].getBlockt();
            if (curr_bt != BlockType::None) {
                CellState *curr_state = dynamic_cast<CellState*>(cells[i][j].getState());
                CellState copy_state{*curr_state};
                states.emplace_back(copy_state);
            }
        }
    }
    State *block_state = new BlockState{states};
    setState(block_state);
}

//assume when generate it is on the top left of the board
//if it blocktype is None, it not considered in the actual block -> rem=0
//row start at 3
Block::Block(BlockType b, int levnum) {
    if (b==BlockType::Star) {
        Cell c=Cell(3,5,b);
        std::vector<Cell> newRow;
        newRow.emplace_back(c);
        this->cells.emplace_back(newRow);
        this->blockWid=1;
        this->blockHei=1;
        this->blockt=b;
    }
    if (b==BlockType::I) {
        std::vector<std::vector<Cell>> newCell;
        std::vector<Cell> row;
        for (int i=0; i<4; i++) {
            Cell c=Cell(3,i,b);
            row.emplace_back(c);
        }
        newCell.emplace_back(row);
        this->cells=newCell;
        this->blockWid=4;
        this->blockHei=1;
        this->blockt=b;
    }
    
    if (b==BlockType::J) {
        std::vector<Cell> row1;
        for (int i=0; i<3; i++) {
            if (i==0) {
               Cell c=Cell(3,i,b);
                 row1.emplace_back(c);
            }
            else {
                Cell c=Cell(3,i,BlockType::None);
                 row1.emplace_back(c);
            }
           
        }
        this->cells.emplace_back(row1);
        std::vector<Cell> row2;
        for (int j=0; j<3; j++) {
            Cell c=Cell(4,j,b);
            row2.emplace_back(c);
        }
        this->cells.emplace_back(row2);
        this->blockWid=3;
        this->blockHei=2;
        this->blockt=b;
    }
    
    if (b==BlockType::L) {
        std::vector<Cell> row1;
        for (int i=0; i<3; i++) {
            
            if (i==2) {
                Cell c=Cell(3,i,b);
                 row1.emplace_back(c);
            }
            else {
                Cell c=Cell(3,i,BlockType::None);
                 row1.emplace_back(c);
            }
        }
        this->cells.emplace_back(row1);
        std::vector<Cell> row2;
        for (int j=0; j<3; j++) {
            Cell c=Cell(4,j, b);
            row2.emplace_back(c);
        }
        this->cells.emplace_back(row2);
        this->blockWid=3;
        this->blockHei=2;
        this->blockt=b;
    }
    
    //note for BlockType O  it is a 2*2 block!!
    if (b==BlockType::O) {
        std::vector<Cell> row1;
        for (int i=0; i<2; i++) {
            Cell c=Cell(3,i,b);
            row1.emplace_back(c);
        }
        this->cells.emplace_back(row1);
        std::vector<Cell> row2;
        for (int j=0; j<2; j++) {
            Cell c=Cell(4,j,b);
            row2.emplace_back(c);
        }
        this->cells.emplace_back(row2);
        this->blockWid=2;
        this->blockHei=2;
        this->blockt=b;
    }
    if (b==BlockType::S) {
        std::vector<Cell> row1;
        for (int i=0; i<3; i++) {

            if (i==0) {
                Cell c=Cell(3,i,BlockType::None);
                 row1.emplace_back(c);
            }
            else {
                Cell c=Cell(3,i,b);
                 row1.emplace_back(c);
            }
        }
        this->cells.emplace_back(row1);
        std::vector<Cell> row2;
        for (int j=0; j<3; j++) {
            if (j==2) {
                Cell c=Cell(4,j,BlockType::None);
                row2.emplace_back(c);
            }
            else {
//                c.setBlockt(b);
                Cell c=Cell(4,j,b);
                row2.emplace_back(c);
            }
            
        }
        this->cells.emplace_back(row2);
        this->blockWid=3;
        this->blockHei=2;
        this->blockt=b;
    }
        
    if (b==BlockType::Z) {
        std::vector<Cell> row1;
        for (int i=0; i<3; i++) {
            if (i==2) {
                Cell c=Cell(3,i,BlockType::None);
                row1.emplace_back(c);
            }
            else {
                Cell c=Cell(3,i,b);
                row1.emplace_back(c);
            }
            
        }
        this->cells.emplace_back(row1);
        std::vector<Cell> row2;
        for (int j=0; j<3; j++) {
            if (j==0) {
                Cell c=Cell(4,j,BlockType::None);
                 row2.emplace_back(c);
            }
            else {
                Cell c=Cell(4,j, b);
                 row2.emplace_back(c);
            }
           
        }
        this->cells.emplace_back(row2);
        this->blockWid=3;
        this->blockHei=2;
        this->blockt=b;
    }
    
    if (b==BlockType::T) {
        std::vector<Cell> row1;
        for (int i=0; i<3; i++) {
            Cell c=Cell(3,i,b);
            row1.emplace_back(c);
        }
        this->cells.emplace_back(row1);
        std::vector<Cell> row2;
        for (int j=0; j<3; j++) {

            if (j==1) {
                Cell c=Cell(4,j,b);
                row2.emplace_back(c);
            }
            else {
                Cell c=Cell(4,j, BlockType::None);
                row2.emplace_back(c);
            }
            
        }
        this->cells.emplace_back(row2);
        this->blockWid=3;
        this->blockHei=2;
        this->blockt=b;
    }
    updateState();
    setLevelnum(levnum);
}


//create a copy of this and mutate the copy
Block *Block::left() {
    Block *copy=new Block{*this};
    for (int i=0; i<blockHei; i++) {
        for (int j=0; j<blockWid; j++) {
            std::pair<int, int> in=copy->cells[i][j].getIndex();
            copy->cells[i][j].setIndex(in.first, in.second-1);
        }
    }
    copy->updateState();
    return copy;
}

Block *Block::right() {
    Block *copy=new Block{*this};
    for (int i=0; i<blockHei; i++) {
        for (int j=0; j<blockWid; j++) {
            std::pair<int, int> in=copy->cells[i][j].getIndex();
            copy->cells[i][j].setIndex(in.first, in.second+1);
        }
    }
    copy->updateState();
    return copy;
}


Block *Block::down() {
    Block *copy = new Block{*this};
    for (int i=0; i<blockHei; i++) {
        for (int j=0; j<blockWid; j++) {
            std::pair<int, int> in=copy->cells[i][j].getIndex();
            copy->cells[i][j].setIndex(in.first+1, in.second);
        }
    }
    copy->updateState();
    return copy;
}

//mutate each cell separately
//assume hint, None, star won't be passed in this function
Block *Block::clock() {
    Block *copy=new Block{*this};
    //for 1*4 block, 2 possible rotates
    BlockType b=this->blockt;
    if (b==BlockType::I) {
        if (this->blockWid==4) {
            std::vector<std::vector<Cell>> newCells;
            for (int i=0; i<blockWid; i++) {
                std::vector<Cell> newRow;
                if (i==0) {
                    for (int j=0; j<blockHei; j++) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first-3,in.second,b);
                        newRow.emplace_back(c);
                    }
                    
                }
                else if (i==1) {
                    for (int j=0; j<blockHei; j++) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first-2,in.second-1,b);
                        newRow.emplace_back(c);
                    }
                }
                else if (i==2) {
                    for (int j=0; j<blockHei; j++) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first-1,in.second-2,b);
                        newRow.emplace_back(c);
                    }
                }
                else {
                    for (int j=0; j<blockHei; j++) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first,in.second-3,b);
                        newRow.emplace_back(c);
                    }
                }
                newCells.emplace_back(newRow);
            }
            //delete copy->cells;
            copy->cells=newCells;
            copy->blockWid=1;
            copy->blockHei=4;
            copy->updateState();
            return copy;
        }
        else {
            std::vector<std::vector<Cell>> newCells;
            for (int i=0; i<blockWid; i++) {
                std::vector<Cell> newRow;
                for (int j=0; j<blockHei; j++) {
                    if (j==0) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first+3,in.second,b);
                        newRow.emplace_back(c);
                        
                    }
                    else if (j==1) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first+2,in.second+1,b);
                        newRow.emplace_back(c);
                    }
                    else if (j==2) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first+1,in.second+2,b);
                        newRow.emplace_back(c);
                    }
                    else {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first,in.second+3,b);
                        newRow.emplace_back(c);
                    }
                }
                newCells.emplace_back(newRow);
            }
            //delete copy->cells;
            copy->cells=newCells;
            copy->blockWid=4;
            copy->blockHei=1;
            copy->updateState();
            return copy;
        }
        
    }
    //for 2*3 block
    else if (this->blockt!=BlockType::O) {
        if (copy->blockWid==3) {
            std::vector<std::vector<Cell>> newCells;
            for (int i=0; i<blockWid; i++) {
                std::vector<Cell> newRow;
                if (i==0){
                    for (int j=blockHei-1; j>-1; j--) {
                        if (j==1) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first-2, in.second, bt);
                            newRow.emplace_back(c);
                        }
                        else {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first-1, in.second+1, bt);
                            newRow.emplace_back(c);
                        }
                    }
                    newCells.emplace_back(newRow);
                }
                else if (i==1) {
                    for (int j=blockHei-1; j>-1; j--) {
                        if (j==1) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first-1, in.second-1, bt);
                            newRow.emplace_back(c);
                        }
                        else {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first, in.second, bt);
                            newRow.emplace_back(c);
                        }
                    }
                    newCells.emplace_back(newRow);
                }
                else {
                    for (int j=blockHei-1; j>-1; j--) {
                        if (j==1) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first, in.second-2, bt);
                            newRow.emplace_back(c);
                        }
                        else {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first+1, in.second-1, bt);
                            newRow.emplace_back(c);
                        }
                    }
                    newCells.emplace_back(newRow);
                }
            }
            //delete copy->cells;
            copy->cells=newCells;
            copy->blockWid=2;
            copy->blockHei=3;
            for (int i = 0; i < copy->blockHei; i++) {
                for (int j = 0; j < copy->blockWid; j++) {
                    int index_r = (copy->cells)[i][j].getIndex().first;
                    int index_c = (copy->cells)[i][j].getIndex().second;
                }
            }
            copy->updateState();
            return copy;
        }
        else {
            //rotate from 3*2
            std::vector<std::vector<Cell>> newCells;
            for (int i=0; i<blockWid; i++) {
                std::vector<Cell> newRow;
                if (i==0){
                    for (int j=blockHei-1; j>-1; j--) {
                        if (j==2) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first-1, in.second, bt);
                            newRow.emplace_back(c);
                        } else if (j==1) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first, in.second+1, bt);
                            newRow.emplace_back(c);
                        } else {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first+1, in.second+2, bt);
                            newRow.emplace_back(c);
                        }
                    }
                    newCells.emplace_back(newRow);
                }
                else  {
                    for (int j=blockHei-1; j>-1; j--) {
                        if (j==2) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first, in.second-1, bt);
                            newRow.emplace_back(c);
                        } else if (j==1) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first+1, in.second, bt);
                            newRow.emplace_back(c);
                        } else {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first+2, in.second+1, bt);
                            newRow.emplace_back(c);
                        }
                    }
                    newCells.emplace_back(newRow);
                }
            }
            //delete copy->cells;
            copy->cells=newCells;
            copy->blockWid=3;
            copy->blockHei=2;
            copy->updateState();
            return copy;
        }
    }
    //2*2
    else {
        return copy;
    }
}

Block *Block::coclock() {
    Block *copy=new Block{*this};
    //for 1*4 block, assume it is the same with clock()
    BlockType b=this->blockt;
    if (b==BlockType::I) {
        if (this->blockWid==4) {
            std::vector<std::vector<Cell>> newCells;
            for (int i=0; i<blockWid; i++) {
                std::vector<Cell> newRow;
                if (i==0) {
                    for (int j=0; j<blockHei; j++) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first-3,in.second,b);
                        newRow.emplace_back(c);
                    }
                    
                }
                else if (i==1) {
                    for (int j=0; j<blockHei; j++) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first-2,in.second-1,b);
                        newRow.emplace_back(c);
                    }
                }
                else if (i==2) {
                    for (int j=0; j<blockHei; j++) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first-1,in.second-2,b);
                        newRow.emplace_back(c);
                    }
                }
                else {
                    for (int j=0; j<blockHei; j++) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first,in.second-3,b);
                        newRow.emplace_back(c);
                    }
                }
                newCells.emplace_back(newRow);
            }
            //delete copy->cells;
            copy->cells=newCells;
            copy->blockWid=1;
            copy->blockHei=4;
            copy->updateState();
            return copy;
        }
        else {
            std::vector<std::vector<Cell>> newCells;
            for (int i=0; i<blockWid; i++) {
                std::vector<Cell> newRow;
                for (int j=0; j<blockHei; j++) {
                    if (j==0) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first+3,in.second,b);
                        newRow.emplace_back(c);
                        
                    }
                    else if (j==1) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first+2,in.second+1,b);
                        newRow.emplace_back(c);
                    }
                    else if (j==2) {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first+1,in.second+2,b);
                        newRow.emplace_back(c);
                    }
                    else {
                        std::pair<int, int> in=copy->cells[j][i].getIndex();
                        Cell c=Cell(in.first,in.second+3,b);
                        newRow.emplace_back(c);
                    }
                }
                newCells.emplace_back(newRow);
            }
            //delete copy->cells;
            copy->cells=newCells;
            copy->blockWid=4;
            copy->blockHei=1;
            copy->updateState();
            return copy;
        }
        
    }
    //for 2*3 block
    else if (this->blockt!=BlockType::O) {
        if (copy->blockWid==3) {
            std::vector<std::vector<Cell>> newCells;
            for (int i=blockWid-1; i>-1; i--) {
                std::vector<Cell> newRow;
                if (i==2){
                    for (int j=0; j<blockHei; j++) {
                        if (j==0) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first-1, in.second-2, bt);
                            newRow.emplace_back(c);
                        }
                        else {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first-2, in.second-1, bt);
                            newRow.emplace_back(c);
                        }
                    }
                    newCells.emplace_back(newRow);
                }
                else if (i==1) {
                    for (int j=0; j<blockHei; j++) {
                        if (j==0) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first, in.second-1, bt);
                            newRow.emplace_back(c);
                        }
                        else {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first-1, in.second, bt);
                            newRow.emplace_back(c);
                        }
                    }
                    newCells.emplace_back(newRow);
                }
                else {
                    for (int j=0; j<blockHei; j++) {
                        if (j==0) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first+1, in.second, bt);
                            newRow.emplace_back(c);
                        }
                        else {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first, in.second+1, bt);
                            newRow.emplace_back(c);
                        }
                    }
                    newCells.emplace_back(newRow);
                }
            }
            //delete copy->cells;
            copy->cells=newCells;
            copy->blockWid=2;
            copy->blockHei=3;
            copy->updateState();
            return copy;
        }
        else {
            //rotate from 3*2
            std::vector<std::vector<Cell>> newCells;
            for (int i=blockWid-1; i>-1; i--) {
                std::vector<Cell> newRow;
                if (i==1){
                    for (int j=0; j<blockHei; j++) {
                        if (j==0) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first+1, in.second-1, bt);
                            newRow.emplace_back(c);
                        }
                        else if (j==1) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first, in.second, bt);
                            newRow.emplace_back(c);
                        }
                        else {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first-1, in.second+1, bt);
                            newRow.emplace_back(c);
                        }
                    }
                    newCells.emplace_back(newRow);
                }
                else  {
                    for (int j=0; j<blockHei; j++) {
                        if (j==0) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first+2, in.second, bt);
                            newRow.emplace_back(c);
                        }
                        else if (j==1) {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first+1, in.second+1, bt);
                            newRow.emplace_back(c);
                        }
                        else {
                            std::pair<int, int> in=copy->cells[j][i].getIndex();
                            BlockType bt=copy->cells[j][i].getBlockt();
                            Cell c=Cell(in.first, in.second+2, bt);
                            newRow.emplace_back(c);
                        }
                    }

                    newCells.emplace_back(newRow);
                }
            }
            //delete copy->cells;
            copy->cells=newCells;
            copy->blockWid=3;
            copy->blockHei=2;
            copy->updateState();
            return copy;
        }
    }
    //2*2
    else {
        return copy;
    }
}

void Block::vertical_shift(int n) {
    for (int i = 0; i < blockHei; i++) {
        for (int j = 0; j < blockWid; j++) {
            int cell_row = cells[i][j].getIndex().first + n;
            int cell_col = cells[i][j].getIndex().second;
            cells[i][j].setIndex(cell_row, cell_col);
        }
    }
    updateState();
}

void Block::normal_to_next() {
    for (int i = 0; i < blockHei; i++) {
        for (int j = 0; j < blockWid; j++) {
            int cell_row = - (cells[i][j].getIndex().first - 2);
            int cell_col = cells[i][j].getIndex().second;
            cells[i][j].setIndex(cell_row, cell_col);
        }
    }
    updateState();
}

void Block::next_to_curr() {
    for (int i = 0; i < blockHei; i++) {
        for (int j = 0; j < blockWid; j++) {
            int cell_row = - cells[i][j].getIndex().first + 2;
            int cell_col = cells[i][j].getIndex().second;
            cells[i][j].setIndex(cell_row, cell_col);
        }
    }
    updateState();
}

void Block::setLevelnum(int levnum){
    levelnum = levnum;
    for(int i = 0; i < blockHei; i++) {
        for(int j = 0; j < blockWid; j++) {
            cells[i][j].setLevelnum(levnum);
        }
    }
}

int Block::getLevelnum(){
    return levelnum;
}

BlockType Block::getBlockt() {
    return this->blockt;
}
