#pragma once

#ifndef RGBIMAGE_HPP
#define RGBIMAGE_HPP

#include <stdint.h>


class RGBImage
{
public:
    /** Allocates an RGB image of width & height */
    RGBImage(int width, int height);
    ~RGBImage();
    
    /** Allocates an RGB image of width & height */
    void allocate(int width, int height);
    void release();
    
    /** once called this class will not release */
    void releaseOwnership();
    /** gives address of the pixel at x, y */
    uint8_t *at(int x, int y);
    inline uint8_t *data(){
        return m_data;
    }
    /** sets pixel at x, y to color */
    void setPixel(int x, int y, uint32_t color);
    
    /** @return width of image in pixels */
    inline int width(){
        return m_width;
    }
    
    /** @return height of image in pixels */
    inline int height(){
        return m_height;
    }
private:
    uint8_t *m_data;
    int m_width;
    int m_height;
    bool m_ownsData;
};

#endif // RGBIMAGE_HPP
