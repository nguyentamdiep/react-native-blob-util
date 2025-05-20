#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen/NativeReactNativeBlobUtilDataTypes.g.h")
  #include "codegen/NativeReactNativeBlobUtilDataTypes.g.h"
#endif
#include "codegen/NativeReactNativeBlobUtilSpec.g.h"

#include "NativeModules.h"

namespace winrt::ReactNativeBlobUtil
{

REACT_MODULE(ReactNativeBlobUtil)
struct ReactNativeBlobUtil
{
  using ModuleSpec = ReactNativeBlobUtilCodegen::ReactNativeBlobUtilSpec;

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  REACT_SYNC_METHOD(multiply)
  double multiply(double a, double b) noexcept;

private:
  React::ReactContext m_context;
};

} // namespace winrt::ReactNativeBlobUtil