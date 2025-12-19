#include "widget.h"

struct Radio : Widget {
  bool value;
  Radio(bool value = false);

  void draw(D2Tool& dt) override;
  void onClick() override;
  void layout(D2Tool& dt, const Offset& o) override;
};