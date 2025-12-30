#pragma once
#include "widget.h"
// linear
enum class LinearType { Col, Row, Stack };
enum class CrossAxis { STRETCH, CENTER, START, END };
enum class MainAxis { SPACE_BETWEEN };

struct LinearConfig {
  MainAxis mainAxis = MainAxis::SPACE_BETWEEN;
  CrossAxis crossAxis = CrossAxis::CENTER;
  LinearType direction;

  LinearConfig(
    MainAxis mainAxis = MainAxis::SPACE_BETWEEN,
    CrossAxis crossAxis = CrossAxis::START, LinearType dir = LinearType::Row
  )
      : mainAxis(mainAxis), crossAxis(crossAxis), direction(dir) {}
};

template <typename... T>
deque<unique_ptr<Widget>> children(T&&... args) {
  deque<unique_ptr<Widget>> dec;
  (dec.push_back(std::move(args)), ...);
  return dec;
}

struct Linear : Widget {
  LinearConfig config;
  std::deque<unique_ptr<Widget>> children;
  bool isDirty = true;

  void addChild(std::unique_ptr<Widget> child) {
    child->parent = this;
    children.push_back(std::move(child));
  }

  Linear(deque<unique_ptr<Widget>> childList, const LinearConfig& cfg = {})
      : config(cfg), children(std::move(childList)) {
    for (auto& c : children) {
      c->parent = this;  // set parent
    }
  }

  Widget* hitTest(const Offset& mOffset) override;
  void draw(D2Tool& dt) override;
  void layout(
    D2Tool& dt, Offset o, optional<Size> size = std::nullopt
  ) override;

 private:
  int gap = 0;
};

inline unique_ptr<Widget> Row(
  deque<unique_ptr<Widget>> children, LinearConfig cfg = {}
) {
  cfg.direction = LinearType::Row;
  return make_unique<Linear>(std::move(children), cfg);
}

inline unique_ptr<Widget> Col(
  deque<unique_ptr<Widget>> children, LinearConfig cfg = {}
) {
  cfg.direction = LinearType::Col;
  return make_unique<Linear>(std::move(children), cfg);
}

inline unique_ptr<Widget> Stack(
  deque<unique_ptr<Widget>> children, LinearConfig cfg = {}
) {
  cfg.direction = LinearType::Stack;
  return make_unique<Linear>(std::move(children), cfg);
}
