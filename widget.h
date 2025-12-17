#pragma once
#include <functional>
#include <memory>
#include <utility>

#include "header/pch.h"

struct Widget {
  Rect rect;
  function<void()> onClickCallback;

  Widget() : rect{0, 0, 0, 0} {};

  virtual Size getSize() { return Size{rect.w, rect.h}; }
  virtual Offset getPos() { return Offset{rect.x, rect.y}; }
  virtual void onClick() {
    if (onClickCallback) onClickCallback();
  }

  virtual void draw(D2Tool& dt) = 0;
  virtual void layout(D2Tool& dt, const Offset& o) = 0;
  virtual Widget* hitTest(const Offset& mOffset) = 0;
};

// text
struct Text : Widget {
  std::wstring text;
  Text(const std::wstring& str);

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, const Offset& o) override;
  Widget* hitTest(const Offset& mOffset) override;

 private:
  ComPtr<IDWriteTextLayout> textLayout;
};

// button
struct Button : Widget {
  std::wstring text;
  Button(const std::wstring& str, function<void()> onClick = nullptr);

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, const Offset& o) override;
  Widget* hitTest(const Offset& mOffset) override;

  Button&& setPadding(int all) {
    this->padding = Padding{all, all, all, all};
    return std::move(*this);
  }
  Button&& setPadding(int h, int v) {
    this->padding = Padding{h, v, h, v};
    return std::move(*this);
  }
  Button&& setPadding(int l, int t, int r, int b) {
    this->padding = Padding{l, t, r, b};
    return std::move(*this);
  }

 private:
  unique_ptr<Text> label;
  Padding padding{8, 4, 8, 4};
};

// linear
enum class LDirection { VERT, HORIZ };

struct Linear : Widget {
  LDirection direction;

  template <typename... T>
  Linear(LDirection dir = LDirection::HORIZ, T&&... children);

  Widget* hitTest(const Offset& mOffset) override;
  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, const Offset& o) override;

 private:
  vector<unique_ptr<Widget>> children;
};

template <typename... T>
Linear::Linear(LDirection dir, T&&... args) : direction(dir) {
  using expander = int[];
  (void)expander{0,
      (children.push_back(
           std::make_unique<std::decay_t<T>>(std::forward<T>(args))),
          0)...};
};
