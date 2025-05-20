#include "pch.h"

#include "ReactNativeBlobUtil.h"

namespace winrt::ReactNativeBlobUtil
{

// See https://microsoft.github.io/react-native-windows/docs/native-modules for details on writing native modules

void ReactNativeBlobUtil::Initialize(React::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
}

// Constants method
ReactNativeBlobUtilCodegen::Constants ReactNativeBlobUtil::getConstants() noexcept {
    return {
      .CacheDir = L"",
      .DocumentDir = L"",
      .DownloadDir = L"",
      .LibraryDir = L"",
      .MainBundleDir = L"",
      .MovieDir = L"",
      .MusicDir = L"",
      .PictureDir = L"",
      .ApplicationSupportDir = L"",
      .RingtoneDir = L"",
      .SDCardDir = L"",
      .SDCardApplicationDir = L"",
      .DCIMDir = L"",
      .LegacyDCIMDir = L"",
      .LegacyPictureDir = L"",
      .LegacyMusicDir = L"",
      .LegacyDownloadDir = L"",
      .LegacyMovieDir = L"",
      .LegacyRingtoneDir = L"",
      .LegacySDCardDir = L""
    };
}

// Stub implementations for all methods

void ReactNativeBlobUtil::fetchBlobForm(JSValue const&, std::string const&, std::string const&, std::string const&, JSValue const&, JSValue const&, React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::fetchBlob(JSValue const&, std::string const&, std::string const&, std::string const&, JSValue const&, std::string const&, React::ReactCallback<const JSValue&> const&) noexcept {}
fire_and_forget ReactNativeBlobUtil::createFile(std::string const&, std::string const&, std::string const&) noexcept { co_return; }
fire_and_forget ReactNativeBlobUtil::createFileASCII(std::string const&, JSValue const&) noexcept { co_return; }
fire_and_forget ReactNativeBlobUtil::pathForAppGroup(std::string const&, React::ReactPromise<std::string> const& result) noexcept { result.Reject("Not implemented"); co_return; }
std::string ReactNativeBlobUtil::syncPathAppGroup(std::string const&) noexcept { return ""; }
void ReactNativeBlobUtil::exists(std::string const&, React::ReactCallback<const JSValue&> const&) noexcept {}
fire_and_forget ReactNativeBlobUtil::writeFile(std::string const&, std::string const&, std::string const&, bool, bool, React::ReactPromise<int32_t> const& result) noexcept { result.Resolve(0); co_return; }
fire_and_forget ReactNativeBlobUtil::writeFileArray(std::string const&, JSValue const&, bool, React::ReactPromise<int32_t> const& result) noexcept { result.Resolve(0); co_return; }
void ReactNativeBlobUtil::writeStream(std::string const&, std::string const&, bool, React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::writeArrayChunk(std::string const&, JSValue const&, React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::writeChunk(std::string const&, std::string const&, React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::closeStream(std::string const&, React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::unlink(std::string const&, React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::removeSession(JSValue const&, React::ReactCallback<const JSValue&> const&) noexcept {}
fire_and_forget ReactNativeBlobUtil::ls(std::string const&, React::ReactPromise<JSValue> const& result) noexcept { result.Resolve(JSValueArray{}); co_return; }
void ReactNativeBlobUtil::stat(std::string const&, React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::lstat(std::string const&, React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::cp(std::string const&, std::string const&, React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::mv(std::string const&, std::string const&, React::ReactCallback<const JSValue&> const&) noexcept {}
fire_and_forget ReactNativeBlobUtil::mkdir(std::string const&, React::ReactPromise<bool> const& result) noexcept { result.Resolve(true); co_return; }
fire_and_forget ReactNativeBlobUtil::readFile(std::string const&, std::string const&, bool, React::ReactPromise<JSValue> const& result) noexcept { result.Resolve(JSValueArray{}); co_return; }
fire_and_forget ReactNativeBlobUtil::hash(std::string const&, std::string const&, React::ReactPromise<std::string> const& result) noexcept { result.Resolve(""); co_return; }
void ReactNativeBlobUtil::readStream(std::string const&, std::string const&, int32_t, int32_t, std::string const&) noexcept {}
void ReactNativeBlobUtil::getEnvironmentDirs(React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::cancelRequest(std::string const&, React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::enableProgressReport(std::string const&, int32_t, int32_t) noexcept {}
void ReactNativeBlobUtil::enableUploadProgressReport(std::string const&, int32_t, int32_t) noexcept {}
fire_and_forget ReactNativeBlobUtil::slice(std::string const&, std::string const&, int64_t, int64_t, React::ReactPromise<std::string> const& result) noexcept { result.Resolve(""); co_return; }
fire_and_forget ReactNativeBlobUtil::presentOptionsMenu(std::string const&, std::string const&, React::ReactPromise<JSValue> const& result) noexcept { result.Resolve(JSValueArray{}); co_return; }
fire_and_forget ReactNativeBlobUtil::presentOpenInMenu(std::string const&, std::string const&, React::ReactPromise<JSValue> const& result) noexcept { result.Resolve(JSValueArray{}); co_return; }
fire_and_forget ReactNativeBlobUtil::presentPreview(std::string const&, std::string const&, React::ReactPromise<JSValue> const& result) noexcept { result.Resolve(JSValueArray{}); co_return; }
fire_and_forget ReactNativeBlobUtil::excludeFromBackupKey(std::string const&, React::ReactPromise<JSValue> const& result) noexcept { result.Resolve(JSValueArray{}); co_return; }
void ReactNativeBlobUtil::df(React::ReactCallback<const JSValue&> const&) noexcept {}
void ReactNativeBlobUtil::emitExpiredEvent(React::ReactCallback<std::string const&> const&) noexcept {}
fire_and_forget ReactNativeBlobUtil::actionViewIntent(std::string const&, std::string const&, std::string const&) noexcept { co_return; }
fire_and_forget ReactNativeBlobUtil::addCompleteDownload(JSValue const&) noexcept { co_return; }
fire_and_forget ReactNativeBlobUtil::copyToInternal(std::string const&, std::string const&, React::ReactPromise<std::string> const& result) noexcept { result.Resolve(""); co_return; }
fire_and_forget ReactNativeBlobUtil::copyToMediaStore(JSValue const&, std::string const&, std::string const&, React::ReactPromise<std::string> const& result) noexcept { result.Resolve(""); co_return; }
fire_and_forget ReactNativeBlobUtil::createMediaFile(JSValue const&, std::string const&, React::ReactPromise<std::string> const& result) noexcept { result.Resolve(""); co_return; }
fire_and_forget ReactNativeBlobUtil::getBlob(std::string const&, std::string const&, React::ReactPromise<JSValue> const& result) noexcept { result.Resolve(JSValueArray{}); co_return; }
fire_and_forget ReactNativeBlobUtil::getContentIntent(std::string const&, React::ReactPromise<std::string> const& result) noexcept { result.Resolve(""); co_return; }
fire_and_forget ReactNativeBlobUtil::getSDCardDir(React::ReactPromise<std::string> const& result) noexcept { result.Resolve(""); co_return; }
fire_and_forget ReactNativeBlobUtil::getSDCardApplicationDir(React::ReactPromise<std::string> const& result) noexcept { result.Resolve(""); co_return; }
void ReactNativeBlobUtil::scanFile(JSValue const&, React::ReactCallback<const JSValue&> const&) noexcept {}
fire_and_forget ReactNativeBlobUtil::writeToMediaFile(std::string const&, std::string const&, bool, React::ReactPromise<std::string> const& result) noexcept { result.Resolve(""); co_return; }

void ReactNativeBlobUtil::addListener(std::string const&) noexcept {}
void ReactNativeBlobUtil::removeListeners(int32_t) noexcept {}

} // namespace winrt::ReactNativeBlobUtil