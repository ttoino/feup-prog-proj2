#ifndef POST_H
#define POST_H

/**
 * This class represents a post (electrified, non-electrified or an exit)
 */
class Post
{
public:
    /** 
     * Creates a post at the specified position
     * 
     * @param column The position on the x-axis
     * @param line The position on the y-axis
     */
    Post(size_t column, size_t line);

    /** @returns The position on the x-axis */
    size_t getColumn() const;

    /** @returns The position on the y-axis */
    size_t getLine() const;

private:
    /** Position on the x-axis */
    size_t column;

    /** Position on the y-axis */
    size_t line;
};

#endif