
#include "app.h"

#include "../header/pch.h"
#include "../widgets/button.h"
#include "../widgets/checkbox.h"
#include "../widgets/dialog.h"
#include "../widgets/image.h"
#include "../widgets/linear.h"
#include "../widgets/progress.h"
#include "../widgets/radio.h"
#include "../widgets/slider.h"
#include "../widgets/text.h"
#include "../widgets/widget.h"

unique_ptr<Widget> Home() {
  return Row(children(Image(L"cpp.jpeg", {80, 80})));
}

void main() { runApp(Home()); }