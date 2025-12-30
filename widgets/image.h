#include "widget.h"

struct ImageConfig {
  Size size{-1, -1};
};

struct WgImage : Widget {
  WgImage(const std::wstring& filename, const ImageConfig& cfg = {});

  void draw(D2Tool& dt) override;
  void layout(D2Tool& dt, Offset o, optional<Size> size) override;

 private:
  std::wstring filename;
  std::wstring oldFileName;
  ComPtr<IWICBitmapDecoder> decoder;
  ComPtr<IWICBitmapFrameDecode> frame;
  ComPtr<ID2D1Bitmap> bitmap;
  bool userSetHeight = false;
};

unique_ptr<WgImage> Image(
  const std::wstring& filename, const ImageConfig& cfg = {}
);