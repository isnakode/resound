#include "progress.h"

Progress::Progress(float start, float end) : start(start), end(end) {
  rect = Rect{0, 0, 100, 10};
}

void Progress::layout(D2Tool& dt, Offset o, optional<Size> size) {
  rect.x = o.x;
  rect.y = o.y;
}

void Progress::draw(D2Tool& dt) {
  dt.brush->SetColor(D2::ColorF(D2::ColorF::White, .5f));
  auto rc = D2::RectF(rect.x, rect.y, rect.w + rect.x, rect.h + rect.y);
  dt.rt->FillRoundedRectangle(D2::RoundedRect(rc, 4, 4), dt.brush.Get());
  dt.brush->SetColor(D2::ColorF(D2::ColorF::White));
  auto foregroundRc = D2::RectF(
    rect.x + rect.w * start, rect.y, rect.w * end + rect.x, rect.h + rect.y
  );
  dt.rt->FillRoundedRectangle(
    D2::RoundedRect(foregroundRc, 4, 4), dt.brush.Get()
  );
}
