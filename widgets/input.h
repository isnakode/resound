#pragma once
#include "widget.h"

struct Input : Widget {
  std::wstring text;
  Input(const std::wstring& str);

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, Offset o, optional<Size> size) override;

 private:
  ComPtr<IDWriteTextLayout> textLayout;
};