#include "text.h"
#include "widget.h"

struct ButtonConfig {
  optional<Padding> padding;
  function<void()> onClick;
};

struct WgButton : Widget {
  std::wstring text;
  WgButton(const std::wstring& str, const ButtonConfig config = {});

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, Offset o, optional<Size> size) override;

 private:
  unique_ptr<Text> label;
  Padding padding{8, 4, 8, 4};
};

unique_ptr<Widget> Button(
  const std::wstring& str, const ButtonConfig config = {}
);