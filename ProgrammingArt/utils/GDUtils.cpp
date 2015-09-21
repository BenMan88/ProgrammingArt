#include "GDUtils.hpp"
#include <cstdio>
#include <cassert>
#include <memory>

gdImagePtr loadPng(char *filename)
{
  FILE *in;
  gdImagePtr im;
  in = fopen(filename, "rb");
  assert(in != nullptr);
  
  if (!in) {
    /* Error */
  }
  
  fseek(in, 0, SEEK_END);
  int fileSize = ftell(in);
  fseek(in, 0, SEEK_SET);
  
  /* Read the entire thing into a buffer
    that we allocate */
  std::shared_ptr<char> buffer(new char[fileSize], [] (char *array){
      delete [] array;
  });
  
  if (!buffer) {
    /* Error */
  }
  if (fread(buffer.get(), 1, fileSize, in) != fileSize)
  {
    /* Error */
    assert(false);
  }
  im = gdImageCreateFromPngPtr(fileSize, buffer.get());
  /* WE allocated the memory, WE free
    it with our normal free function */
  fclose(in);
  return im;
}