#pragma once

#include "text.h"
#include "widget.h"

struct WgDialog : Widget {
  WgDialog(
    const std::wstring& title, const std::wstring& caption,
    unique_ptr<Widget> action
  );

  void draw(D2Tool& dt) override;
  Widget* hitTest(const Offset& mOffset) override;
  void layout(D2Tool& dt, Offset o, optional<Size> size) override;

 private:
  unique_ptr<Text> titleLabel;
  unique_ptr<Text> captionLabel;
  unique_ptr<Widget> action;
};

unique_ptr<WgDialog> Dialog(
  const std::wstring& title, const std::wstring& caption,
  unique_ptr<Widget> action
);