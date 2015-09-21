#pragma once

#ifndef RGBIMAGE_HPP
#define RGBIMAGE_HPP

#include <stdint.h>

template<typename T>
T clamp(T value, T min, T max){
    if(value < min)
        return min;
    else if(value > max)
        return max;
    return value;
}
class Color {
public:
    float red;
    float green;
    float blue;
    
    uint32_t toInt(){
        int red = this->red*255.0;
        int green = this->green*255.0;
        int blue = this->blue*255.0;
        
        red = clamp<int>(red, 0, 0xFF);
        green = clamp<int>(green, 0, 0xFF);
        blue = clamp<int>(blue, 0, 0xFF);
        
        uint32_t color = (red) | (green << 8) | (blue << 16);
        return color;
    }
    
    Color(uint32_t color){
        red = color & 0xFF;
        green = (color >> 8) & 0xFF;
        blue = (color >> 16) & 0xFF;
        
        red /= 255.0f;
        green /= 255.0f;
        blue /= 255.0f;
    }
};

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
