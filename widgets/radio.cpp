#include "radio.h"

Radio::Radio(bool value) : value(value) { rect = Rect{0, 0, 20, 20}; }

void Radio::layout(D2Tool& dt, Offset o, optional<Size> size) {
  rect.x = o.x;
  rect.y = o.y;
}
void Radio::onClick() { value = !value; }

void Radio::draw(D2Tool& dt) {
  dt.brush->SetColor(D2::ColorF(D2::ColorF::Black));
  auto rc = D2::RectF(rect.x, rect.y, rect.w + rect.x, rect.h + rect.y);
  auto p = D2::Point2F(rect.x + rect.w / 2, rect.y + rect.h / 2);
  dt.rt->DrawEllipse(D2::Ellipse(p, rect.w / 2, rect.h / 2), dt.brush.Get());
  if (value) {
    dt.rt->FillEllipse(
      D2::Ellipse(p, rect.w / 2 - 3, rect.h / 2 - 3), dt.brush.Get()
    );
  }
}
