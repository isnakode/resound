
#include "app.h"

#include "../header/pch.h"
#include "../widgets/button.h"
#include "../widgets/checkbox.h"
#include "../widgets/image.h"
#include "../widgets/linear.h"
#include "../widgets/progress.h"
#include "../widgets/radio.h"
#include "../widgets/slider.h"
#include "../widgets/text.h"
#include "../widgets/widget.h"

unique_ptr<Widget> Img() { return make_unique<Image>(L"cpp.jpeg"); }
unique_ptr<Widget> Home() {
  return make_unique<Row>(
      make_unique<Button>(L"halo"),
      Img(),
      make_unique<Button>(L"Click me", []() {
        MessageBoxW(nullptr, L"caption", L"judul", MB_OKCANCEL);
      })
  );
}

void main() { runApp(Home()); }