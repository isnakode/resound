#include <d2d1helper.h>
#include <dwrite.h>
#include <winuser.h>

#include "../widget.h"

void Button::layout(D2Tool& dt, const Offset& o) {
  rect.x = o.x;
  rect.y = o.y;
  Offset afterPadding = Offset{o.x + padding.l, o.y + padding.t};
  label->layout(dt, afterPadding);
  rect.h = label->rect.h + padding.t + padding.b;
  rect.w = label->rect.w + padding.l + padding.r;
}

void Button::draw(D2Tool& dt) {
  dt.brush->SetColor(D2::ColorF(D2::ColorF::White));
  auto rc = D2::RectF(rect.x, rect.y, rect.w + rect.x, rect.h + rect.y);
  dt.rt->FillRoundedRectangle(D2::RoundedRect(rc, 4, 4), dt.brush.Get());
  label->draw(dt);
}

Button::Button(const std::wstring& str, function<void()> onClick)
    : label(make_unique<Text>(str)) {
  onClickCallback = onClick;
};

Widget* Button::hitTest(const Offset& mOffset) {
  bool inX = mOffset.x >= rect.x && mOffset.x <= rect.w + rect.x;
  bool inY = mOffset.y >= rect.y && mOffset.y <= rect.h + rect.y;
  return inX && inY ? this : nullptr;
}
