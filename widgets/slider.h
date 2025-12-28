#include "widget.h"

struct Slider : Widget {
  float start;
  float end;
  bool showStartHandle = false;
  Slider(float value = .0f);
  Slider(float start, float end);

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, Offset o, optional<Size> size) override;
};