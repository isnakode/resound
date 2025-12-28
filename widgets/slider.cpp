#include "slider.h"

Slider::Slider(float value) : start(.0f), end(value) {
  rect = Rect{0, 0, 100, 20};
}

Slider::Slider(float start, float end)
    : start(start), end(end), showStartHandle(true) {
  rect = Rect{0, 0, 100, 20};
}

void Slider::layout(D2Tool& dt, Offset o, optional<Size> size) {
  rect.x = o.x;
  rect.y = o.y;
}

void Slider::draw(D2Tool& dt) {
  float knobStartX = rect.x + rect.w * start;
  float knobEndX = rect.x + rect.w * end;
  int barHeight = 10;
  float barTop = (rect.y + rect.h / 2) - barHeight / 2;
  float barBottom = (rect.y + rect.h / 2) + barHeight / 2;

  dt.brush->SetColor(D2::ColorF(D2::ColorF::White, .5f));
  auto rc = D2::RectF(rect.x, barTop, rect.w + rect.x, barBottom);
  dt.rt->FillRoundedRectangle(D2::RoundedRect(rc, 4, 4), dt.brush.Get());
  dt.brush->SetColor(D2::ColorF(D2::ColorF::White));

  rc.left = knobStartX;
  rc.right = knobEndX;
  dt.rt->FillRoundedRectangle(D2::RoundedRect(rc, 4, 4), dt.brush.Get());

  // knob
  auto startPoint = D2::Point2F(knobStartX, rect.center().y);
  auto endPoint = D2::Point2F(knobEndX, rect.center().y);
  dt.brush->SetColor(D2::ColorF(D2::ColorF::White));
  dt.rt->DrawEllipse(D2::Ellipse(endPoint, 10, 10), dt.brush.Get());
  dt.brush->SetColor(D2::ColorF(D2::ColorF::DarkGreen));
  dt.rt->FillEllipse(D2::Ellipse(endPoint, 10, 10), dt.brush.Get());
  if (showStartHandle) {
    dt.brush->SetColor(D2::ColorF(D2::ColorF::White));
    dt.rt->DrawEllipse(D2::Ellipse(startPoint, 10, 10), dt.brush.Get());
    dt.brush->SetColor(D2::ColorF(D2::ColorF::DarkGreen));
    dt.rt->FillEllipse(D2::Ellipse(startPoint, 10, 10), dt.brush.Get());
  }
}
