#include <d2d1.h>
#include <windows.h>
#include <wrl/client.h>

#pragma comment(lib, "d2d1.lib")

namespace D2 = D2D1;
using Microsoft::WRL::ComPtr;

struct D2Tool {
  ComPtr<ID2D1Factory> d2dFactory;
  ComPtr<ID2D1HwndRenderTarget> rt;
  ComPtr<ID2D1SolidColorBrush> brush;
};

void initTool(HWND hwnd) {
  RECT rc;
  GetClientRect(hwnd, &rc);

  D2Tool* dt = new D2Tool{};

  HRESULT hr = D2D1CreateFactory(
      D2D1_FACTORY_TYPE_SINGLE_THREADED, dt->d2dFactory.GetAddressOf()
  );

  if (FAILED(hr)) PostQuitMessage(hr);

  hr = dt->d2dFactory->CreateHwndRenderTarget(
      D2::RenderTargetProperties(),
      D2::HwndRenderTargetProperties(
          hwnd, D2::SizeU(rc.right - rc.left, rc.bottom - rc.top)
      ),
      dt->rt.GetAddressOf()
  );
  if (FAILED(hr)) PostQuitMessage(hr);

  hr = dt->rt->CreateSolidColorBrush(
      D2::ColorF(D2::ColorF::Green), dt->brush.GetAddressOf()
  );

  if (FAILED(hr)) PostQuitMessage(hr);

  SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)dt);
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_CREATE: {
      initTool(hwnd);
      return 0;
    }
    case WM_PAINT: {
      RECT rc;
      GetClientRect(hwnd, &rc);
      auto* dt = (D2Tool*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
      dt->rt->BeginDraw();

      dt->rt->FillRectangle(
          D2::RectF(rc.left, rc.top, rc.right, rc.bottom), dt->brush.Get()
      );

      dt->rt->EndDraw();
      return 0;
    }
    case WM_DESTROY:
      auto* dt = (D2Tool*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
      delete dt;
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
  const wchar_t WIN_CLASS[] = L"WIN_CLASS";

  WNDCLASSEXW wc{};
  wc.lpszClassName = WIN_CLASS;
  wc.cbSize = sizeof(wc);
  wc.hInstance = hInst;
  wc.lpfnWndProc = WinProc;
  wc.hCursor = LoadCursorW(hInst, MAKEINTRESOURCEW(IDC_ARROW));

  RegisterClassExW(&wc);

  HWND hwnd = CreateWindowExW(
      0, WIN_CLASS, L"Resound", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInst,
      nullptr
  );

  if (!hwnd) {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  MSG msg;
  while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  return 0;
}