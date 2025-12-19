#include "widget.h"

struct Image : Widget {
  float start;
  float end;
  bool showStartHandle = false;
  Image(float value = .0f);
  Image(float start, float end);

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, const Offset& o) override;
};