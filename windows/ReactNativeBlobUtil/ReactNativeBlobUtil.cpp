#include "pch.h"

#include "ReactNativeBlobUtil.h"

namespace winrt::ReactNativeBlobUtil
{

// See https://microsoft.github.io/react-native-windows/docs/native-modules for details on writing native modules

void ReactNativeBlobUtil::Initialize(React::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
}

double ReactNativeBlobUtil::multiply(double a, double b) noexcept {
  return a * b;
}

} // namespace winrt::ReactNativeBlobUtil