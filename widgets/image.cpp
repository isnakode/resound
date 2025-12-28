#include "image.h"

Image::Image(const std::wstring& filename) : filename(filename) {
  rect = {0, 0, 80, 80};
}

void Image::draw(D2Tool& dt) {
  auto rc = D2::RectF(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
  dt.rt->DrawBitmap(bitmap.Get(), rc);
}

void Image::layout(D2Tool& dt, Offset o, optional<Size> size) {
  rect.x = o.x;
  rect.y = o.y;
  HRESULT hr = dt.wicFactory->CreateDecoderFromFilename(
    filename.c_str(),
    nullptr,
    GENERIC_READ,
    WICDecodeMetadataCacheOnDemand,
    decoder.GetAddressOf()
  );
  if (FAILED(hr)) {
    MessageBoxW(
      nullptr, (std::to_wstring(hr)).c_str(), L"Error decoder", MB_OKCANCEL
    );
  }
  hr = decoder->GetFrame(0, &frame);

  if (FAILED(hr)) {
    MessageBoxW(
      nullptr, (std::to_wstring(hr)).c_str(), L"Error decoder", MB_OKCANCEL
    );
  }
  IWICFormatConverter* converter;
  hr = dt.wicFactory->CreateFormatConverter(&converter);

  if (FAILED(hr)) {
    MessageBoxW(
      nullptr, (std::to_wstring(hr)).c_str(), L"Error convert", MB_OKCANCEL
    );
  }
  hr = converter->Initialize(
    frame.Get(),
    GUID_WICPixelFormat32bppPBGRA,
    WICBitmapDitherTypeNone,
    nullptr,
    0.f,
    WICBitmapPaletteTypeCustom
  );
  if (FAILED(hr)) {
    MessageBoxW(
      nullptr,
      (std::to_wstring(hr)).c_str(),
      L"Error convert initialize",
      MB_OKCANCEL
    );
  }
  dt.rt->CreateBitmapFromWicBitmap(converter, nullptr, bitmap.GetAddressOf());
  if (!userSetHeight) {
    rect.h = (bitmap->GetSize().height / bitmap->GetSize().width) * rect.w;
  }
}

Image& Image::setWidth(int value) & {
  rect.w = value;
  return *this;
}

Image Image::setWidth(int value) && {
  rect.w = value;
  return std::move(*this);
}
Image& Image::setHeight(int value) & {
  userSetHeight = true;
  rect.h = value;
  return *this;
}

Image Image::setHeight(int value) && {
  userSetHeight = true;
  rect.h = value;
  return std::move(*this);
}