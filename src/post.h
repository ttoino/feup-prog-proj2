#ifndef POST_H
#define POST_H

class Post
{
public:

    /** Constructer, initializes de post with its position
    * @param Column The column is the position on the x-axis
    * @param line The line is the position on the y-axis
    */
    Post(size_t column, size_t line);

    /** @return returns the column of the post position*/
    size_t getColumn() const;

    /** @return returns the line of the post position*/
    size_t getLine() const;

private:

    /** Position on the x-axis */
    size_t column;

    /** Position on the y-axis */
    size_t line;
};

#endif