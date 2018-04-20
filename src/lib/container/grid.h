/*
 *
 * Created by shacking on 23/08/17.
 */
#ifndef __SOKOBAN_GRID_H
#define __SOKOBAN_GRID_H

#include <vector>

template<typename T>
class Grid {
public:
    /**
     * Allocate a Grid<T> with width x height dimensions. Initialized to
     * the zero value for T.
     * @param width
     * @param height
     */
    explicit Grid<T> (const size_t width, const size_t height)
          : mWidth{width}, mHeight{height} { mGrid.resize(width * height); }

    explicit Grid<T> (const size_t width, const size_t height, T init)
          : mWidth{width}, mHeight{height} { mGrid.resize(width * height, init); }

    int width () const { return mWidth; }

    int height () const { return mHeight; }

    /**
     * Get item which is a T at Grid coordinate [x, y]
     */
    T get (int x, int y) const {
        return mGrid[y * mWidth + x];
    }

    /**
     * Set item which is a T at Grid coordinate [x, y]
     */
    void set (int x, int y, T val) {
        mGrid[y * mWidth + x] = val;
    }

private:
    size_t mWidth;
    size_t mHeight;
    std::vector<T> mGrid;
};

#endif /* __SOKOBAN_GRID_H */
