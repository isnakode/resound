#include "widget.h"

struct Image : Widget {
  Image(const std::wstring& filename);

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, const Offset& o) override;

  Image& setWidth(int value) &;
  Image setWidth(int value) &&;
  Image& setHeight(int value) &;
  Image setHeight(int value) &&;

 private:
  std::wstring filename;
  ComPtr<IWICBitmapDecoder> decoder;
  ComPtr<IWICBitmapFrameDecode> frame;
  ComPtr<ID2D1Bitmap> bitmap;
  bool userSetHeight = false;
};