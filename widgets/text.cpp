#include <d2d1helper.h>
#include <dwrite.h>
#include <winuser.h>

#include <cwchar>

#include "../widget.h"

void Text::layout(D2Tool& dt, const Offset& o) {
  rect.x = o.x;
  rect.y = o.y;
  DWRITE_TEXT_METRICS metrics;
  dt.dwFactory->CreateTextLayout(text.c_str(),
      text.length(),
      dt.dwFormat.Get(),
      500.0f,
      500.0f,
      textLayout.GetAddressOf());
  textLayout->GetMetrics(&metrics);
  rect.w = metrics.width;
  rect.h = metrics.height;
}

void Text::draw(D2Tool& dt) {
  dt.brush->SetColor(D2::ColorF(D2::ColorF::Black));
  dt.rt->DrawTextLayout(
      D2::Point2F(rect.x, rect.y), textLayout.Get(), dt.brush.Get());
}

Text::Text(const std::wstring& str) : text(str) {}

Widget* Text::hitTest(const Offset& mOffset) {
  bool inX = mOffset.x >= rect.x && mOffset.x <= rect.w + rect.x;
  bool inY = mOffset.y >= rect.y && mOffset.y <= rect.h + rect.y;
  return inX && inY ? this : nullptr;
}
