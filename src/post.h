// T01_G07

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
    Post(unsigned int column, unsigned int line);

    /** @returns The position on the x-axis */
    unsigned int getColumn() const;

    /** @returns The position on the y-axis */
    unsigned int getLine() const;

private:
    /** Position on the x-axis */
    unsigned int column;

    /** Position on the y-axis */
    unsigned int line;
};

#endif