
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
  return Row({}, Image(L"C:\\Users\\isnaini\\Downloads\\circle_glow.png"));
}

void main() { runApp(Home()); }