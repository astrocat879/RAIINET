#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=900, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws an outline of a rectangle
  void drawRectangle(int x, int y, int width, int height, int girth = 5, int colour=White);

  // Draw center of an outline
  void drawRectCenter(int x, int y, int width, int height, int girth = 5, int colour=Blue);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  // Draw a character with some offset
  void drawPiece(int x, int y, char a);
};

#endif
