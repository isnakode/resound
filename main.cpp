#include <d2d1helper.h>
#include <dwrite.h>
#include <minwindef.h>
#include <unknwnbase.h>
#include <windef.h>
#include <winuser.h>

#include <memory>
#include <string>

#include "header/pch.h"
#include "widget.h"

D2Tool dt = D2Tool{};
unique_ptr<Widget> widget;

void initTool(HWND hwnd) {
  RECT rc;
  GetClientRect(hwnd, &rc);

  HRESULT hr = D2D1CreateFactory(
      D2D1_FACTORY_TYPE_SINGLE_THREADED, dt.d2dFactory.GetAddressOf());

  if (FAILED(hr)) PostQuitMessage(hr);

  hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
      __uuidof(IDWriteFactory),
      reinterpret_cast<IUnknown**>(dt.dwFactory.GetAddressOf()));

  if (FAILED(hr)) PostQuitMessage(hr);
  hr = dt.dwFactory->CreateTextFormat(L"Arial",
      nullptr,
      DWRITE_FONT_WEIGHT_REGULAR,
      DWRITE_FONT_STYLE_NORMAL,
      DWRITE_FONT_STRETCH_NORMAL,
      16,
      L"id",
      dt.dwFormat.GetAddressOf());

  if (FAILED(hr)) PostQuitMessage(hr);

  hr = dt.d2dFactory->CreateHwndRenderTarget(D2::RenderTargetProperties(),
      D2::HwndRenderTargetProperties(
          hwnd, D2::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
      dt.rt.GetAddressOf());
  if (FAILED(hr)) PostQuitMessage(hr);

  hr = dt.rt->CreateSolidColorBrush(
      D2::ColorF(D2::ColorF::Green), dt.brush.GetAddressOf());

  if (FAILED(hr)) PostQuitMessage(hr);
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
  SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
  const wchar_t WIN_CLASS[] = L"WIN_CLASS";

  WNDCLASSEXW wc{};
  wc.lpszClassName = WIN_CLASS;
  wc.cbSize = sizeof(wc);
  wc.hInstance = hInst;
  wc.lpfnWndProc = WinProc;
  wc.hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(IDC_ARROW));

  RegisterClassExW(&wc);

  HWND hwnd = CreateWindowExW(0,
      WIN_CLASS,
      L"Resound",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      nullptr,
      nullptr,
      hInst,
      nullptr);

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

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_CREATE: {
      initTool(hwnd);
      widget = make_unique<Linear>(LDirection::HORIZ,
          Linear{
              LDirection::VERT,
              Button{L"Halo"},
              Button{
                  L"ini contoh",
                  []() {
                    MessageBoxW(
                        nullptr, L"contoh button", L"title", MB_OKCANCEL);
                  },
              },
              Linear{
                  LDirection::HORIZ,
                  Button{L"Halo 1"},
                  Button{L"Halo 2"},
                  Text{L"Contoh teks"},
                  Linear{
                      LDirection::VERT,
                      Button{L"Halo vert 1"},
                      Button{L"Halo vert 1"},
                  },
              },
              Button{L"Halo"},
              Button{L"Halo"},
          },
          Button{L"Oi isnaini"});
      widget->layout(dt, Offset{0, 0});
      return 0;
    }
    case WM_LBUTTONDOWN: {
      int x = LOWORD(lParam);
      int y = HIWORD(lParam);
      float g_DPIScale = 1.0f;
      float dpi = GetDpiForWindow(hwnd);
      g_DPIScale = dpi / USER_DEFAULT_SCREEN_DPI;

      auto w =
          widget->hitTest(Offset{int(x / g_DPIScale), int(y / g_DPIScale)});
      if (w) {
        w->onClick();
      }
    }
    case WM_PAINT: {
      RECT rc;
      GetClientRect(hwnd, &rc);
      PAINTSTRUCT ps;
      BeginPaint(hwnd, &ps);
      dt.rt->BeginDraw();

      dt.rt->Clear(D2::ColorF(D2::ColorF::Green));

      widget->draw(dt);

      dt.rt->EndDraw();
      EndPaint(hwnd, &ps);
      return 0;
    }
    case WM_SIZE: {
      RECT rc;
      GetClientRect(hwnd, &rc);
      dt.rt->Resize(D2::SizeU(rc.right - rc.left, rc.bottom - rc.top));
      return 0;
    }
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProcW(hwnd, msg, wParam, lParam);
}
