#pragma once

namespace sip {
#if defined   __MOFLIB
#include "Mof.h"
using Vector3 = Mof::Vector3;
using Vector4 = Mof::Vector4;
#elif defined __GLLIB
#include "../../Framework/Math/Vector3.h"
#include "../../Framework/Math/Vector4.h"
using Vector3 = Sample::Vector3F;
using Vector4 = Sample::Vector4F;
#endif
}