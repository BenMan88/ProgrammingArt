#include "RGBImage.hpp"
#include <cstdlib>
#include <cassert>

RGBImage::RGBImage(int width, int height)
{
    m_data = nullptr;
    m_ownsData = false;
    allocate(width, height);
}

void RGBImage::allocate(int width, int height){
    release();
    
    m_data = (uint8_t*) malloc(width*height*3);
    m_width = width;
    m_height = height;
    m_ownsData = true;
}



void RGBImage::release(){
    if(m_data != nullptr && m_ownsData){
        free(m_data);
    }
    m_data = nullptr;
    m_width = 0;
    m_height = 0;
}

void RGBImage::releaseOwnership(){
    m_ownsData = false;
}

uint8_t *RGBImage::at(int x, int y){
    assert(x >= 0);
    assert(y >= 0);
    assert(x < m_width);
    assert(y < m_height);

    return m_data + x*3 + y*m_width*3;
}

void RGBImage::setPixel(int x, int y, uint32_t color) {
    uint8_t *where = at(x, y);
    
    where[0] = color & 0xFF;
    where[1] = (color >> 8) & 0xFF;
    where[2] = (color >> 16) & 0xFF;
}

RGBImage::~RGBImage()
{
    release();
}

