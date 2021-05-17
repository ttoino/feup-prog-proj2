#include <cstddef>

#include "post.h"

Post::Post(size_t column, size_t line)
    : column(column), line(line)
{
}

size_t Post::getColumn() const
{
    return column;
}

size_t Post::getLine() const
{
    return line;
}
