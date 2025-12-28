
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

unique_ptr<Widget> Home() {
  return Button(
    L"Click me",
    {
      .padding = Padding{8, 90},
      .onClick =
        []() { MessageBoxW(nullptr, L"caption", L"judul", MB_OKCANCEL); },
    }
  );
}

void main() { runApp(Home()); }