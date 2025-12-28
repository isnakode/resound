#pragma once

#include "widget.h"

unique_ptr<Widget> Expanded(unique_ptr<Widget> w, int flex = 1) {
  w->flexWidth = flex;
  return std::move(w);
}