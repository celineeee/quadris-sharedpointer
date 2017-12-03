#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <string>
enum class BlockType { I, J, L, O, S, Z, T, Star, Hint, None };

char transform_char(BlockType blockt);
int transform_colour(BlockType blockt);
BlockType str_transform(std::string s);

#endif
