#ifndef POST_H
#define POST_H

class Post
{
public:
    Post(size_t column, size_t line);

    size_t getColumn() const;
    size_t getLine() const;

private:
    size_t column;
    size_t line;
};

#endif