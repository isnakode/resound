#pragma once

struct Point {
  int x, y;
};

struct Rect {
  int x, y, w, h;
};

struct Renderer {
  virtual void drawText() = 0;
  virtual void drawRect(Rect r) = 0;
  virtual void drawRRect() = 0;
  virtual void drawLine(const Point& p1, const Point& p2) = 0;
};