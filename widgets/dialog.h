#pragma once

#include "text.h"
#include "widget.h"

struct WgDialog : Widget {
  WgDialog(const std::wstring& title, const std::wstring& caption);

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, Offset o, optional<Size> size) override;

 private:
  unique_ptr<Text> titleLabel;
  unique_ptr<Text> captionLabel;
};

unique_ptr<WgDialog> Dialog(
  const std::wstring& title, const std::wstring& caption
);