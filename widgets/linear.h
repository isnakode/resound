#include "widget.h"
// linear
enum class LDirection { VERT, HORIZ, STACK };

struct Linear : Widget {
  LDirection direction;

  template <typename... T>
  Linear(LDirection dir = LDirection::HORIZ, T&&... children);

  Widget* hitTest(const Offset& mOffset) override;
  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, Offset o, optional<Size> size) override;
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

template <typename... T>
unique_ptr<Widget> Row(T&&... children) {
  return make_unique<Linear>(LDirection::HORIZ, std::forward<T>(children)...);
}

template <typename... T>
unique_ptr<Widget> Column(T&&... children) {
  return make_unique<Linear>(LDirection::VERT, std::forward<T>(children)...);
}

template <typename... T>
unique_ptr<Widget> Stack(T&&... children) {
  return make_unique<Linear>(LDirection::STACK, std::forward<T>(children)...);
}
