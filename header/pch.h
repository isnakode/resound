#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "shcore.lib")
#pragma comment(lib, "windowscodecs.lib")

#include <ShellScalingApi.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#define NOMINMAX
#include <windows.h>
#include <wrl/client.h>

#include <algorithm>
#include <deque>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace D2 = D2D1;

using Microsoft::WRL::ComPtr;
using std::deque;
using std::function;
using std::make_unique;
using std::optional;
using std::string;
using std::unique_ptr;
using std::vector;

struct D2Tool {
  ComPtr<ID2D1HwndRenderTarget> rt;
  ComPtr<ID2D1SolidColorBrush> brush;
  ComPtr<ID2D1Factory> d2dFactory;
  ComPtr<IDWriteFactory> dwFactory;
  ComPtr<IDWriteTextFormat> dwFormat;
  ComPtr<IWICImagingFactory> wicFactory;
};

struct Point {
  float x, y;

  // static Point zero() { return Point{0, 0}; };
};

using Offset = Point;

struct Rect {
  float x, y, w, h;

  Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

  float bottom() { return y + h; }
  float right() { return x + w; }

  Offset center() { return Offset{x + w / 2, y + h / 2}; }
};

struct Padding {
  int l, t, r, b;

  Padding(int all) : l(all), t(all), r(all), b(all) {}
  Padding(int horizontal, int vertical)
      : l(horizontal), t(vertical), r(horizontal), b(vertical) {}
  Padding(int l, int t, int r, int b) : l(l), t(t), r(r), b(b) {}
};

using Margin = Padding;

struct Size {
  float w, h;
};

struct Window {
  float width;
  float height;
  HWND hwnd;
  std::wstring filename;
};

inline Window window{};
