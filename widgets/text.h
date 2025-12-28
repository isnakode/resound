#pragma once
#include "widget.h"

struct Text : Widget {
  std::wstring text;
  Text(const std::wstring& str);

  void draw(D2Tool& dt) override;
  void layout(
    D2Tool& dt, Offset o, optional<Size> size = std::nullopt
  ) override;

 private:
  ComPtr<IDWriteTextLayout> textLayout;
};