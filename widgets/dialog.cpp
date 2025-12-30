#include "dialog.h"

WgDialog::WgDialog(
  const std::wstring& title, const std::wstring& caption,
  unique_ptr<Widget> action
)
    : titleLabel(make_unique<Text>(title)),
      action(std::move(action)),
      captionLabel(make_unique<Text>(caption)) {
  rect = {0, 0, 200, 100};
}

void WgDialog::layout(D2Tool& dt, Offset, optional<Size>) {
  rect.x = (window.width - rect.w) / 2;
  rect.y = (window.height - rect.h) / 2;

  Offset cur{rect.x, rect.y};

  titleLabel->layout(dt, cur);
  cur.y += titleLabel->getSize().h;

  captionLabel->layout(dt, cur);
  cur.y += captionLabel->getSize().h;

  if (action) {
    action->layout(dt, cur);
  }
}

void WgDialog::draw(D2Tool& dt) {
  dt.brush->SetColor(D2::ColorF(D2::ColorF::CornflowerBlue));
  auto rc = D2::RectF(rect.x, rect.y, rect.right(), rect.bottom());
  dt.rt->FillRoundedRectangle(D2::RoundedRect(rc, 4, 4), dt.brush.Get());
  titleLabel->draw(dt);
  captionLabel->draw(dt);
  action->draw(dt);
}

unique_ptr<WgDialog> Dialog(
  const std::wstring& title, const std::wstring& caption,
  unique_ptr<Widget> action
) {
  return make_unique<WgDialog>(title, caption, std::move(action));
}

Widget* WgDialog::hitTest(const Offset& mOffset) {
  if (action) {
    return action->hitTest(mOffset);
  }
  return Widget::hitTest(mOffset);
};
