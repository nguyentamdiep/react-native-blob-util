#include "pch.h"

#include "ReactNativeBlobUtil.h"

namespace winrt::ReactNativeBlobUtil
{

// See https://microsoft.github.io/react-native-windows/docs/native-modules for details on writing native modules

void ReactNativeBlobUtil::Initialize(React::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
}

// Constants method
ReactNativeBlobUtilCodegen::BlobUtilsSpec_Constants ReactNativeBlobUtil::GetConstants() noexcept {
    return {};
}

// Stub implementations for all methods

void ReactNativeBlobUtil::fetchBlobForm(
    ::React::JSValue&&,
    std::string,
    std::string,
    std::string,
    ::React::JSValue&&,
    ::React::JSValueArray&&,
    std::function<void(::React::JSValueArray const&)> const&
) noexcept
{
    // Empty implementation
}

void ReactNativeBlobUtil::fetchBlob(
    ::React::JSValue&&,
    std::string,
    std::string,
    std::string,
    ::React::JSValue&&,
    std::string,
    std::function<void(::React::JSValueArray const&)> const&
) noexcept
{
    // Empty implementation
}

void ReactNativeBlobUtil::createFile(
    std::string,
    std::string,
    std::string,
    ::React::ReactPromise<void>&&
) noexcept
{
    // Empty implementation
}

void ReactNativeBlobUtil::createFileASCII(
    std::string path,
    ::React::JSValueArray&& data,
    ::React::ReactPromise<void>&& result) noexcept
{
    result.Resolve();
}

void ReactNativeBlobUtil::pathForAppGroup(
    std::string groupName,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    result.Resolve("");
}

std::string ReactNativeBlobUtil::syncPathAppGroup(
    std::string groupName) noexcept
{
    return "";
}

void ReactNativeBlobUtil::exists(
    std::string path,
    std::function<void(std::vector<bool> const&)> const& callback) noexcept
{
    callback({});
}

void ReactNativeBlobUtil::writeFile(
    std::string path,
    std::string encoding,
    std::string data,
    bool transformFile,
    bool append,
    ::React::ReactPromise<double>&& result) noexcept
{
    result.Resolve(0.0);
}

void ReactNativeBlobUtil::writeFileArray(
    std::string path,
    ::React::JSValueArray&& data,
    bool append,
    ::React::ReactPromise<double>&& result) noexcept
{
    result.Resolve(0.0);
}

void ReactNativeBlobUtil::writeStream(
    std::string path,
    std::string withEncoding,
    bool appendData,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::writeArrayChunk(
    std::string streamId,
    ::React::JSValueArray&& withArray,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::writeChunk(
    std::string streamId,
    std::string withData,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::closeStream(
    std::string streamId,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::unlink(
    std::string path,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::removeSession(
    ::React::JSValueArray&& paths,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::ls(
    std::string path,
    ::React::ReactPromise<::React::JSValueArray>&& result) noexcept
{
    result.Resolve(::React::JSValueArray{});
}

void ReactNativeBlobUtil::stat(
    std::string target,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::lstat(
    std::string path,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::cp(
    std::string src,
    std::string dest,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::mv(
    std::string path,
    std::string dest,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::mkdir(
    std::string path,
    ::React::ReactPromise<bool>&& result) noexcept
{
    result.Resolve(false);
}

void ReactNativeBlobUtil::readFile(
    std::string path,
    std::string encoding,
    bool transformFile,
    ::React::ReactPromise<::React::JSValueArray>&& result) noexcept
{
    result.Resolve(::React::JSValueArray{});
}

void ReactNativeBlobUtil::hash(
    std::string path,
    std::string algorithm,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    result.Resolve("");
}

void ReactNativeBlobUtil::readStream(
    std::string path,
    std::string encoding,
    double bufferSize,
    double tick,
    std::string streamId) noexcept
{
    // No-op
}

void ReactNativeBlobUtil::getEnvironmentDirs(
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::cancelRequest(
    std::string taskId,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::enableProgressReport(
    std::string taskId,
    double interval,
    double count) noexcept
{
    // No-op
}

void ReactNativeBlobUtil::enableUploadProgressReport(
    std::string taskId,
    double interval,
    double count) noexcept
{
    // No-op
}

void ReactNativeBlobUtil::slice(
    std::string src,
    std::string dest,
    double start,
    double end,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    result.Resolve("");
}

void ReactNativeBlobUtil::presentOptionsMenu(
    std::string uri,
    std::string scheme,
    ::React::ReactPromise<::React::JSValueArray>&& result) noexcept
{
    result.Resolve(::React::JSValueArray{});
}

void ReactNativeBlobUtil::presentOpenInMenu(
    std::string uri,
    std::string scheme,
    ::React::ReactPromise<::React::JSValueArray>&& result) noexcept
{
    result.Resolve(::React::JSValueArray{});
}

void ReactNativeBlobUtil::presentPreview(
    std::string uri,
    std::string scheme,
    ::React::ReactPromise<::React::JSValueArray>&& result) noexcept
{
    result.Resolve(::React::JSValueArray{});
}

void ReactNativeBlobUtil::excludeFromBackupKey(
    std::string url,
    ::React::ReactPromise<::React::JSValueArray>&& result) noexcept
{
    result.Resolve(::React::JSValueArray{});
}

void ReactNativeBlobUtil::df(
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::emitExpiredEvent(
    std::function<void(std::string)> const& callback) noexcept
{
    callback("");
}

void ReactNativeBlobUtil::actionViewIntent(
    std::string path,
    std::string mime,
    std::string chooserTitle,
    ::React::ReactPromise<void>&& result) noexcept
{
    result.Resolve();
}

void ReactNativeBlobUtil::addCompleteDownload(
    ::React::JSValue&& config,
    ::React::ReactPromise<void>&& result) noexcept
{
    result.Resolve();
}

void ReactNativeBlobUtil::copyToInternal(
    std::string contentUri,
    std::string destpath,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    result.Resolve("");
}

void ReactNativeBlobUtil::copyToMediaStore(
    ::React::JSValue&& filedata,
    std::string mt,
    std::string path,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    result.Resolve("");
}

void ReactNativeBlobUtil::createMediaFile(
    ::React::JSValue&& filedata,
    std::string mt,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    result.Resolve("");
}

void ReactNativeBlobUtil::getBlob(
    std::string contentUri,
    std::string encoding,
    ::React::ReactPromise<::React::JSValueArray>&& result) noexcept
{
    result.Resolve(::React::JSValueArray{});
}

void ReactNativeBlobUtil::getContentIntent(
    std::string mime,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    result.Resolve("");
}

void ReactNativeBlobUtil::getSDCardDir(
    ::React::ReactPromise<std::string>&& result) noexcept
{
    result.Resolve("");
}

void ReactNativeBlobUtil::getSDCardApplicationDir(
    ::React::ReactPromise<std::string>&& result) noexcept
{
    result.Resolve("");
}

void ReactNativeBlobUtil::scanFile(
    ::React::JSValueArray&& pairs,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::writeToMediaFile(
    std::string fileUri,
    std::string path,
    bool transformFile,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    result.Resolve("");
}

void ReactNativeBlobUtil::addListener(
    std::string eventName) noexcept
{
    // No-op
}

void ReactNativeBlobUtil::removeListeners(
    double count) noexcept
{
    // No-op
}
} // namespace winrt::ReactNativeBlobUtil