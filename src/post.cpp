#include <cstddef>

#include "post.h"

Post::Post(size_t x, size_t y)
{
    this->x = x;
    this->y = y;
}

size_t Post::getColumn() const
{
    return x;
}

size_t Post::getLine() const
{
    return y;
}
