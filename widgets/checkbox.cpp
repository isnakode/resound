#include "../header/widget.h"

Checkbox::Checkbox(bool value) : value(value) { rect = Rect{0, 0, 20, 20}; }

void Checkbox::layout(D2Tool& dt, const Offset& o) {
  rect.x = o.x;
  rect.y = o.y;
  dt.d2dFactory->CreatePathGeometry(&path);
  ComPtr<ID2D1GeometrySink> sink;
  path->Open(&sink);
  sink->BeginFigure(D2D1::Point2F(rect.x + rect.w * .2, rect.y + rect.h * .55),
      D2D1_FIGURE_BEGIN_FILLED);
  sink->AddLine(D2D1::Point2F(rect.x + rect.w * .4, rect.y + rect.h * .7));
  sink->AddLine(D2D1::Point2F(rect.x + rect.w * .8, rect.y + rect.h * .35));
  sink->EndFigure(D2D1_FIGURE_END_OPEN);
  sink->Close();
}
void Checkbox::onClick() { value = !value; }

void Checkbox::draw(D2Tool& dt) {
  dt.brush->SetColor(D2::ColorF(D2::ColorF::Black));
  auto rc = D2::RectF(rect.x, rect.y, rect.w + rect.x, rect.h + rect.y);
  if (value) {
    dt.rt->FillRoundedRectangle(D2::RoundedRect(rc, 4, 4), dt.brush.Get());
    dt.brush->SetColor(D2::ColorF(D2::ColorF::White));
  } else {
    dt.rt->DrawRoundedRectangle(D2::RoundedRect(rc, 4, 4), dt.brush.Get());
    dt.brush->SetColor(D2::ColorF(D2::ColorF::White, 0));
  }

  dt.rt->DrawGeometry(path.Get(), dt.brush.Get(), 2.0f);  // outline
}
