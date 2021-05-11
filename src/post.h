#ifndef POST_H
#define POST_H

class Post
{
public:
    Post(size_t x, size_t y);

    size_t getColumn() const;
    size_t getLine() const;

private:
    size_t x;
    size_t y;
};

#endif