#include "blocktype.h"

using namespace std;
char transform_char(BlockType blockt) {
	if (blockt == BlockType::None) return ' ';
	if (blockt == BlockType::I) return 'I';
	if (blockt == BlockType::J) return 'J';
	if (blockt == BlockType::L) return 'L';
	if (blockt == BlockType::O) return 'O';
	if (blockt == BlockType::S) return 'S';
	if (blockt == BlockType::Z) return 'Z';
	if (blockt == BlockType::T) return 'T';
	if (blockt == BlockType::Star) return '*';
	if (blockt == BlockType::Hint) return '?';
}

int transform_colour(BlockType blockt) {
	if (blockt == BlockType::None) return 0;
	if (blockt == BlockType::I) return 2;
	if (blockt == BlockType::J) return 3;
	if (blockt == BlockType::L) return 4;
	if (blockt == BlockType::O) return 5;
	if (blockt == BlockType::S) return 6;
	if (blockt == BlockType::Z) return 7;
	if (blockt == BlockType::T) return 8;
	if (blockt == BlockType::Star) return 9;
	if (blockt == BlockType::Hint) return 1;
}

BlockType str_transform(string s) {
	if (s == " ") return BlockType::None;
	if (s == "I") return BlockType::I;
	if (s == "J") return BlockType::J;
	if (s == "L") return BlockType::L;
	if (s == "O") return BlockType::O;
	if (s == "S") return BlockType::S;
	if (s == "Z") return BlockType::Z;
	if (s == "T") return BlockType::T;
	if (s == "*") return BlockType::Star;
	if (s == "?") return BlockType::Hint;
}
