#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "shcore.lib")

#include <ShellScalingApi.h>
#include <d2d1.h>
#include <dwrite.h>
#include <windows.h>
#include <wrl/client.h>

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace D2 = D2D1;

using Microsoft::WRL::ComPtr;
using std::function;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

struct D2Tool {
  ComPtr<ID2D1HwndRenderTarget> rt;
  ComPtr<ID2D1SolidColorBrush> brush;
  ComPtr<ID2D1Factory> d2dFactory;
  ComPtr<IDWriteFactory> dwFactory;
  ComPtr<IDWriteTextFormat> dwFormat;
};

struct Point {
  int x, y;

  // static Point zero() { return Point{0, 0}; };
};

struct Rect {
  int x, y, w, h;
};
struct Padding {
  int l, t, r, b;
};

using Offset = Point;
using Margin = Padding;

struct Size {
  int w, h;
};
