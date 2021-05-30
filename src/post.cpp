// T01_G07

#include "post.h"

Post::Post(unsigned int column, unsigned int line)
    : column(column), line(line) {}

unsigned int Post::getColumn() const { return column; }

unsigned int Post::getLine() const { return line; }
