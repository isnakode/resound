#include "text.h"
#include "widget.h"

struct Button : Widget {
  std::wstring text;
  Button(const std::wstring& str, function<void()> onClick = nullptr);

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, const Offset& o) override;

  Button setPadding(int all) &&;
  Button setPadding(int h, int v) &&;
  Button setPadding(int l, int t, int r, int b) &&;

  // lvalue-qualified (chaining dengan object biasa)
  Button& setPadding(int all) &;
  Button& setPadding(int h, int v) &;
  Button& setPadding(int l, int t, int r, int b) &;

 private:
  unique_ptr<Text> label;
  Padding padding{8, 4, 8, 4};
};