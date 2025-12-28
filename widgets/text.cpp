#include "text.h"

void Text::layout(D2Tool& dt, Offset o, optional<Size> size) {
  rect.x = o.x;
  rect.y = o.y;
  DWRITE_TEXT_METRICS metrics;
  dt.dwFactory->CreateTextLayout(
    text.c_str(),
    text.length(),
    dt.dwFormat.Get(),
    500.0f,
    500.0f,
    textLayout.GetAddressOf()
  );
  textLayout->GetMetrics(&metrics);
  rect.w = metrics.width;
  rect.h = metrics.height;
}

void Text::draw(D2Tool& dt) {
  dt.brush->SetColor(D2::ColorF(D2::ColorF::White));
  dt.rt->DrawTextLayout(
    D2::Point2F(rect.x, rect.y), textLayout.Get(), dt.brush.Get()
  );
}

Text::Text(const std::wstring& str) : text(str) {}
