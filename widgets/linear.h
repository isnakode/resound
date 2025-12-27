#include "widget.h"
// linear
enum class LDirection { VERT, HORIZ };

struct Linear : Widget {
  LDirection direction;

  template <typename... T>
  Linear(LDirection dir = LDirection::HORIZ, T&&... children);

  Widget* hitTest(const Offset& mOffset) override;
  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, const Offset& o) override;

  Linear&& setGap(int gap) &&;
  Linear& setGap(int gap) &;

 private:
  vector<unique_ptr<Widget>> children;
  int gap = 0;
};

template <typename... T>
Linear::Linear(LDirection dir, T&&... args) : direction(dir) {
  (children.push_back(std::forward<T>(args)), ...);
};

struct Row : Linear {
  template <typename... T>
  Row(T&&... children)
      : Linear(LDirection::HORIZ, std::forward<T>(children)...) {}
};

struct Column : Linear {
  template <typename... T>
  Column(T&&... children)
      : Linear(LDirection::VERT, std::forward<T>(children)...) {}
};