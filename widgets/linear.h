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
vector<unique_ptr<Widget>> children(T&&... args) {
  vector<unique_ptr<Widget>> vec;
  vec.reserve(sizeof...(args));
  (vec.push_back(std::move(args)), ...);
  return vec;
}

struct Linear : Widget {
  LinearConfig config;
  std::deque<unique_ptr<Widget>> children;
  bool isDirty = true;

  void addChild(std::unique_ptr<Widget> child) {
    child->parent = this;
    children.push_back(std::move(child));
  }

  template <typename... T>
  Linear(const LinearConfig& cfg = {}, T&&... args) : config(cfg) {
    (addChild(std::forward<T>(args)), ...);
  };

  Widget* hitTest(const Offset& mOffset) override;
  void draw(D2Tool& dt) override;
  void layout(
    D2Tool& dt, Offset o, optional<Size> size = std::nullopt
  ) override;

 private:
  int gap = 0;
};

template <typename... T>
unique_ptr<Widget> Row(LinearConfig cfg, T&&... children) {
  cfg.direction = LinearType::Row;
  return make_unique<Linear>(cfg, std::forward<T>(children)...);
}

template <typename... T>
unique_ptr<Widget> Column(LinearConfig cfg, T&&... children) {
  cfg.direction = LinearType::Col;
  return make_unique<Linear>(cfg, std::forward<T>(children)...);
}

template <typename... T>
unique_ptr<Widget> Stack(LinearConfig cfg, T&&... children) {
  cfg.direction = LinearType::Stack;
  return make_unique<Linear>(cfg, std::forward<T>(children)...);
}
