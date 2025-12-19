#include "widget.h"

struct Progress : Widget {
  float start;
  float end;
  Progress(float value = .0f) : Progress(.0f, value) {}
  Progress(float start, float end);

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, const Offset& o) override;
};