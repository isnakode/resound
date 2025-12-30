#include "linear.h"

void Linear::layout(D2Tool& dt, Offset o, optional<Size> size) {
  Offset currentOffset = o;
  rect.x = o.x;
  rect.y = o.y;
  for (auto& c : children) {
    c->layout(dt, currentOffset);
    if (config.direction == LinearType::Row) {
      currentOffset.x += c->getSize().w + gap;
      if (rect.h < c->getSize().h) rect.h = c->getSize().h;
      rect.w += c->rect.w;
    } else if (config.direction == LinearType::Col) {
      currentOffset.y += c->getSize().h + gap;
      if (rect.w < c->getSize().w) rect.w = c->getSize().w;
      rect.h += c->rect.h;
    }
  }
}
void Linear::draw(D2Tool& dt) {
  for (auto& c : children) {
    c->draw(dt);
  }
}

Widget* Linear::hitTest(const Offset& mOffset) {
  for (auto& c : children) {
    auto hit = c->hitTest(mOffset);
    if (hit) return hit;
  }
  return nullptr;
};
