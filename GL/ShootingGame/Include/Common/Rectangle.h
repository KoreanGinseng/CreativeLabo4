#pragma once

namespace sip {
#if defined   __MOFLIB
#include "Rectangle.h"
using Rectangle = Mof::CRectangle;
#elif defined __GLLIB
#include "../../Framework/Math/Rectangle.h"
using Rectangle = Sample::RectangleF;
#endif
}