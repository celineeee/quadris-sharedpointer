Block &Block::operator=(const Block &other){
	Subject::operator=(other);
	blockWid = other.blockWid;
    blockHei = other.blockHei;
    blockt = other.blockt;
    cells.clear();
    for (int i = 0; i < other.blockHei; i++){
    	vector<Cell> row;
    	for(int j = 0; j < other.blockWid; j++) {
    		Cell newcell{other.cells[i][j]};
    		row.emplace_back(newcell);
    	}
    	cells.emplace_back(row);
    }
    updateState();
}

Block::Block(const Block &other): blockWid{other.blockWid}, blockHei{other.blockHei},
blockt{other.blockt} {
	Subject::operator=(other);
	cells.clear();
    for (int i = 0; i < other.blockHei; i++){
    	vector<Cell> row;
    	for(int j = 0; j < other.blockWid; j++) {
    		Cell newcell{other.cells[i][j]};
    		row.emplace_back(newcell);
    	}
    	cells.emplace_back(row);
    }
    updateState();
}

Block::updateState() {
	vector<CellState> states;
	for(int i = 0; i < blockHei; i++) {
		for (int j = 0; j < blockWid; j++) {
			BlockType curr_bt = cells[i][j].getBlockt();
			if (curr_bt != BlockType::None) {
				CellState *curr_state = dynamic_cast<CellState*>(cell[i][j].getState());
				CellState copy_state{*curr_state};
				states.emplace_back(copy_state);
			}
		}
	}
	State *block_state = new BlockState{states};
	setState(block_state);
}