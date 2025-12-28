#include "button.h"

void WgButton::layout(D2Tool& dt, Offset o, optional<Size> size) {
  rect.x = o.x;
  rect.y = o.y;
  Offset afterPadding = Offset{o.x + padding.l, o.y + padding.t};
  label->layout(dt, afterPadding);
  // if (size.has_value()) {
  //   if (size.value().h > 0) rect.h = size.value().h;
  //   if (size.value().w > 0) rect.w = size.value().w;
  // } else {
  rect.h = label->rect.h + padding.t + padding.b;
  rect.w = label->rect.w + padding.l + padding.r;
  // }
}

void WgButton::draw(D2Tool& dt) {
  dt.brush->SetColor(D2::ColorF(D2::ColorF::Black));
  auto rc = D2::RectF(rect.x, rect.y, rect.w + rect.x, rect.h + rect.y);
  dt.rt->FillRoundedRectangle(D2::RoundedRect(rc, 4, 4), dt.brush.Get());
  label->draw(dt);
}

WgButton::WgButton(const std::wstring& str, const ButtonConfig config)
    : label(make_unique<Text>(str)) {
  onClickCallback = config.onClick;
  if (config.padding.has_value()) padding = config.padding.value();
};

unique_ptr<Widget> Button(const std::wstring& str, const ButtonConfig config) {
  return make_unique<WgButton>(str, config);
}
