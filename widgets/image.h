#include "widget.h"

struct WgImage : Widget {
  WgImage(const std::wstring& filename);

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, Offset o, optional<Size> size) override;
  WgImage& setWidth(int value) &;
  WgImage setWidth(int value) &&;
  WgImage& setHeight(int value) &;
  WgImage setHeight(int value) &&;

 private:
  std::wstring filename;
  ComPtr<IWICBitmapDecoder> decoder;
  ComPtr<IWICBitmapFrameDecode> frame;
  ComPtr<ID2D1Bitmap> bitmap;
  bool userSetHeight = false;
};

unique_ptr<WgImage> Image(const std::wstring& filename);