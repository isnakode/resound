#pragma once
#include "../header/pch.h"

struct Widget {
  Rect rect;
  int flexWidth = 0;
  Widget* parent = nullptr;

  function<void()> onClickCallback;

  Widget() : rect{0, 0, 0, 0} {};
  virtual ~Widget() = default;

  virtual Size getSize() { return Size{rect.w, rect.h}; }
  virtual Offset getPos() { return Offset{rect.x, rect.y}; }
  virtual void onClick() {
    if (onClickCallback) onClickCallback();
  }

  virtual void draw(D2Tool& dt) = 0;
  virtual void layout(
    D2Tool& dt, Offset o, optional<Size> size = std::nullopt
  ) = 0;
  virtual Widget* hitTest(const Offset& mOffset) {
    bool inX = mOffset.x >= rect.x && mOffset.x <= rect.w + rect.x;
    bool inY = mOffset.y >= rect.y && mOffset.y <= rect.h + rect.y;
    return inX && inY ? this : nullptr;
  }
};
