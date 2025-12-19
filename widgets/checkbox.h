#include "widget.h"

struct Checkbox : Widget {
  bool value;
  Checkbox(bool value = false);

  void draw(D2Tool& dt) override;
  void onClick() override;
  void layout(D2Tool& dt, const Offset& o) override;

 private:
  ComPtr<ID2D1PathGeometry> path;
};