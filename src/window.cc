#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

#include <map>
#include <vector>

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[5][10]={"white", "black", "red", "green", "blue"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 5; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);

  letters['A'] = {
        "  1  ",
        " 1 1 ",
        "11111",
        "1   1",
        "1   1"
    };

    letters['B'] = {
        "1111 ",
        "1   1",
        "1111 ",
        "1   1",
        "1111 "
    };

    letters['C'] = {
        " 111 ",
        "1   1",
        "1    ",
        "1    ",
        " 111 "
    };

    letters['D'] = {
        "111  ",
        "1  1 ",
        "1   1",
        "1  1 ",
        "111  "
    };

    letters['E'] = {
        "11111",
        "1    ",
        "1111 ",
        "1    ",
        "11111"
    };

    letters['F'] = {
        "11111",
        "1    ",
        "1111 ",
        "1    ",
        "1    "
    };

    letters['G'] = {
        " 111 ",
        "1   1",
        "1    ",
        "1 111",
        " 111 "
    };

    letters['H'] = {
        "1   1",
        "1   1",
        "11111",
        "1   1",
        "1   1"
    };

    letters['I'] = {
        " 111 ",
        "  1  ",
        "  1  ",
        "  1  ",
        " 111 "
    };

    letters['J'] = {
        "   1",
        "   1",
        "   1",
        "1  1",
        " 11"
    };

    letters['K'] = {
        "1   1",
        "1  1 ",
        "111  ",
        "1  1 ",
        "1   1"
    };

    letters['L'] = {
        "1    ",
        "1    ",
        "1    ",
        "1    ",
        "11111"
    };

    letters['M'] = {
        "1   1",
        "11 11",
        "1 1 1",
        "1   1",
        "1   1"
    };

    letters['N'] = {
        "1   1",
        "11  1",
        "1 1 1",
        "1  11",
        "1   1"
    };

    letters['O'] = {
        " 111 ",
        "1   1",
        "1   1",
        "1   1",
        " 111 "
    };

    letters['P'] = {
        "1111 ",
        "1   1",
        "1111 ",
        "1    ",
        "1    "
    };

    letters['Q'] = {
        " 111 ",
        "1   1",
        "1   1",
        "1 1 1",
        " 1111"
    };

    letters['R'] = {
        "1111 ",
        "1   1",
        "1111 ",
        "1  1 ",
        "1   1"
    };

    letters['S'] = {
        " 1111",
        "1    ",
        " 111 ",
        "    1",
        "1111 "
    };

    letters['T'] = {
        "11111",
        "  1  ",
        "  1  ",
        "  1  ",
        "  1  "
    };

    letters['U'] = {
        "1   1",
        "1   1",
        "1   1",
        "1   1",
        " 111 "
    };

    letters['V'] = {
        "1   1",
        "1   1",
        "1   1",
        " 1 1 ",
        "  1  "
    };

    letters['W'] = {
        "1   1",
        "1   1",
        "1 1 1",
        "11 11",
        "1   1"
    };

    letters['X'] = {
        "1   1",
        " 1 1 ",
        "  1  ",
        " 1 1 ",
        "1   1"
    };

    letters['Y'] = {
        "1   1",
        " 1 1 ",
        "  1  ",
        "  1  ",
        "  1  "
    };

    letters['Z'] = {
        "11111",
        "   1 ",
        "  1  ",
        " 1   ",
        "11111"
    };

    letters['a'] = {
        "     ",
        "     ",
        " 111 ",
        "1  11",
        " 11 1"
    };

    letters['b'] = {
        "1    ",
        "1    ",
        "11   ",
        "1 1  ",
        "11   "
    };

    letters['c'] = {
        "     ",
        "     ",
        " 11  ",
        "1    ",
        " 11  "
    };

    letters['d'] = {
        "   1 ",
        "   1 ",
        "  11 ",
        " 1 1 ",
        "  11 "
    };

    letters['e'] = {
        " 111 ",
        "1   1",
        "1111 ",
        "1    ",
        " 1111"
    };

    letters['f'] = {
        "  111",
        " 1   ",
        "1111 ",
        " 1   ",
        " 1   "
    };

    letters['g'] = {
        "  11 ",
        " 1  1",
        "  111",
        "    1",
        " 111 "
    };

    letters['h'] = {
        "1    ",
        "1    ",
        "111  ",
        "1  1 ",
        "1  1 "
    };

    letters['i'] = {
        "  1  ",
        "     ",
        "  1  ",
        "  1  ",
        "  1  "
    };

    letters['j'] = {
        "     1",
        "     1",
        "     1",
        "1    1",
        " 111  "
    };

    letters['k'] = {
        "1  1 ",
        "1  1 ",
        "111  ",
        "1  1 ",
        "1  1 "
    };

    letters['l'] = {
        "1    ",
        "1    ",
        "1    ",
        "1    ",
        " 111 "
    };

    letters['m'] = {
        "     ",
        "     ",
        "1 1 1",
        "1 1 1",
        "1   1"
    };

    letters['n'] = {
        "     ",
        "     ",
        "111  ",
        "1 1  ",
        "1 1  "
    };

    letters['o'] = {
        "     ",
        "     ",
        " 11  ",
        "1  1 ",
        " 11  "
    };

    letters['p'] = {
        "     ",
        "     ",
        "111  ",
        "1 1  ",
        "1    "
    };

    letters['q'] = {
        "     ",
        "     ",
        " 11  ",
        "1  1 ",
        " 1111"
    };

    letters['r'] = {
        "     ",
        "     ",
        "111  ",
        "1    ",
        "1    "
    };

    letters['s'] = {
        " 111 ",
        "1    ",
        " 11  ",
        "   1 ",
        "111  "
    };

    letters['t'] = {
        "  1  ",
        "  1  ",
        "11111",
        "  1  ",
        "  1  "
    };

    letters['u'] = {
        "     ",
        "     ",
        "1  1 ",
        "1  1 ",
        " 11  "
    };

    letters['v'] = {
        "     ",
        "     ",
        "1   1",
        " 1 1 ",
        "  1  "
    };

    letters['w'] = {
        "     ",
        "     ",
        "1   1",
        "1 1 1",
        " 1 1 "
    };

    letters['x'] = {
        "     ",
        "     ",
        "1   1",
        " 1 1 ",
        "1   1"
    };

    letters['y'] = {
        "     ",
        "1 1  ",
        "1 1  ",
        " 1   ",
        " 1   "
    };

    letters['z'] = {
        "     ",
        "     ",
        "1111 ",
        "   1 ",
        "1111 "
    };

    letters[' '] = {
        "     ",
        "     ",
        "     ",
        "     ",
        "     "
    };

    letters[':'] = {
        "     ",
        " 1   ",
        "     ",
        " 1   ",
        "     "
    };

    letters['0'] = {
        "11111",
        "1   1",
        "1   1",
        "1   1",
        "11111"
    };

    letters['1'] = {
        "  11 ",
        "   1 ",
        "   1 ",
        "   1 ",
        " 1111"
    };

    letters['2'] = {
        "1111 ",
        "    1",
        " 111 ",
        "1    ",
        "1111 "
    };

    letters['3'] = {
        "1111 ",
        "    1",
        " 111 ",
        "    1",
        "1111 "
    };

    letters['4'] = {
        "1   1",
        "1   1",
        "11111",
        "    1",
        "    1"
    };

    letters['5'] = {
        "11111",
        "1    ",
        "1111 ",
        "    1",
        "1111 "
    };

    letters['6'] = {
        " 111 ",
        "1    ",
        "1111 ",
        "1   1",
        " 111 "
    };

    letters['7'] = {
        "11111",
        "    1",
        "   1 ",
        "  1  ",
        " 1   "
    };

    letters['8'] = {
        " 111 ",
        "1   1",
        " 111 ",
        "1   1",
        " 111 "
    };

    letters['9'] = {
        " 111 ",
        "1   1",
        " 1111",
        "    1",
        " 111 "
    };

    letters['?'] = {
        " 111 ",
        "    1",
        "  11 ",
        "     ",
        "  1  "
    };
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawRectangle(int x, int y, int width, int height, int girth, int colour) {
  fillRectangle(x, y, width, height, Xwindow::Black);
  fillRectangle(x+girth, y+girth, width-girth*2, height-girth*2, colour);
}

void Xwindow::drawRectCenter(int x, int y, int width, int height, int girth, int colour){
  fillRectangle(x+girth, y+girth, width-girth*2, height-girth*2, colour);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawPiece(int x, int y, char a) {
  int z = 15;
  string s;
  s += a;
  drawString(x+z, y+z, s);
}

void Xwindow::drawChar(int x, int y, char c, int sz, int colour) {
    int cellSz = sz/5;
    for (int i=0; i<5;i++) {
      for (int j=0;j<5;j++) {
        if (letters[c][i][j] == '1'){
          // cerr << "DEBUG: hello???" << '\n';
          fillRectangle(x+j*cellSz, y+i*cellSz, cellSz, cellSz, colour);
        }
      }
    }
}

void Xwindow::drawText(int x, int y, string s, int sz) {
  for (char c : s) {
    drawChar(x, y, c, sz, Xwindow::Black);
    x += sz + 1;
    if (c == ' ') { // spaces are too wide
        x -= sz/2;
    }
  }
}