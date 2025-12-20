#include "input.h"

void Input::layout(D2Tool& dt, const Offset& o) {
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

void Input::draw(D2Tool& dt) {
  dt.brush->SetColor(D2::ColorF(D2::ColorF::Black));

  dt.rt->DrawLine(
      D2::Point2F(8, rect.y), D2::Point2F(8, rect.y + rect.h), dt.brush.Get()
  );
  dt.rt->DrawTextLayout(
      D2::Point2F(rect.x, rect.y), textLayout.Get(), dt.brush.Get()
  );
}

Input::Input(const std::wstring& str) : text(str) {}
