#include "dialog.h"

WgDialog::WgDialog(const std::wstring& title, const std::wstring& caption)
    : titleLabel(make_unique<Text>(title)),
      captionLabel(make_unique<Text>(caption)) {
  rect = {0, 0, 200, 100};
}

void WgDialog::layout(D2Tool& dt, Offset o, optional<Size> size) {
  rect.x = o.x;
  rect.y = o.y;
  titleLabel->layout(dt, o);
  o.y += titleLabel->getSize().h;
  captionLabel->layout(dt, o);
}

void WgDialog::draw(D2Tool& dt) {
  dt.brush->SetColor(D2::ColorF(D2::ColorF::Black));
  auto rc = D2::RectF(rect.x, rect.y, rect.w + rect.x, rect.h + rect.y);
  dt.rt->FillRoundedRectangle(D2::RoundedRect(rc, 4, 4), dt.brush.Get());
  titleLabel->draw(dt);
  captionLabel->draw(dt);
}

unique_ptr<WgDialog> Dialog(
  const std::wstring& title, const std::wstring& caption
) {
  return make_unique<WgDialog>(title, caption);
}
