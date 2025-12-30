#include "image.h"

WgImage::WgImage(const std::wstring& filename, const ImageConfig& cfg)
    : filename(filename) {
  rect = {0, 0, cfg.size.w, cfg.size.h};
}

void WgImage::draw(D2Tool& dt) {
  auto rc = D2::RectF(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
  dt.rt->DrawBitmap(bitmap.Get(), rc);
}

void WgImage::layout(D2Tool& dt, Offset o, optional<Size> size) {
  rect.x = o.x;
  rect.y = o.y;
  if (oldFileName != filename) {
    HRESULT hr = dt.wicFactory->CreateDecoderFromFilename(
      filename.c_str(),
      nullptr,
      GENERIC_READ,
      WICDecodeMetadataCacheOnDemand,
      decoder.ReleaseAndGetAddressOf()
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
    ComPtr<IWICFormatConverter> converter;
    hr =
      dt.wicFactory->CreateFormatConverter(converter.ReleaseAndGetAddressOf());

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
    dt.rt->CreateBitmapFromWicBitmap(
      converter.Get(), nullptr, bitmap.ReleaseAndGetAddressOf()
    );
    MessageBoxW(
      nullptr, std::to_wstring(parent->rect.w).c_str(), L"Debug", MB_OK
    );

    auto bmpSize = bitmap->GetSize();
    if (rect.w >= 0 && rect.h < 0) {
      rect.h = (bmpSize.height / bmpSize.width) * rect.w;
    } else if (rect.h >= 0 && rect.w < 0) {
      rect.w = (bmpSize.width / bmpSize.height) * rect.h;
    } else if (rect.w < 0 && rect.h < 0) {
      float scaleW = parent->rect.w / bmpSize.width;
      float scaleH = parent->rect.h / bmpSize.height;
      float scale = (std::min)(scaleW, scaleH);
      rect.w = bmpSize.width * scale;
      rect.h = bmpSize.height * scale;
    }
    oldFileName = filename;
  }
}

unique_ptr<WgImage> Image(
  const std::wstring& filename, const ImageConfig& cfg
) {
  return make_unique<WgImage>(filename, cfg);
}