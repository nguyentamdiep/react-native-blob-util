#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen/NativeBlobUtilsDataTypes.g.h")
  #include "codegen/NativeBlobUtilsDataTypes.g.h"
#endif

#include "codegen/NativeBlobUtilsSpec.g.h"
#include "NativeModules.h"

namespace winrt::ReactNativeBlobUtil
{

REACT_MODULE(ReactNativeBlobUtil)
struct ReactNativeBlobUtil
{
  using ModuleSpec = ReactNativeBlobUtilCodegen::BlobUtilsSpec;

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const& reactContext) noexcept;

  REACT_METHOD(getConstants)
  ReactNativeBlobUtilCodegen::BlobUtilsSpec_Constants* getConstants();

  REACT_METHOD(fetchBlobForm)
  void fetchBlobForm(JSValue options, std::string const& taskId, std::string const& method, std::string const& url, JSValue headers, JSValue form, std::function<void(JSValue)> const& callback);

  REACT_METHOD(fetchBlob)
  void fetchBlob(JSValue options, std::string const& taskId, std::string const& method, std::string const& url, JSValue headers, std::string const& body, std::function<void(JSValue)> const& callback);

  REACT_METHOD(createFile)
  winrt::Windows::Foundation::IAsyncAction createFile(std::string const& path, std::string const& data, std::string const& encoding);

  REACT_METHOD(createFileASCII)
  winrt::Windows::Foundation::IAsyncAction createFileASCII(std::string const& path, JSValue data);

  REACT_METHOD(pathForAppGroup)
  winrt::Windows::Foundation::IAsyncOperation<std::string> pathForAppGroup(std::string const& groupName);

  REACT_METHOD(syncPathAppGroup)
  std::string syncPathAppGroup(std::string const& groupName);

  REACT_METHOD(exists)
  void exists(std::string const& path, std::function<void(JSValue)> const& callback);

  REACT_METHOD(writeFile)
  winrt::Windows::Foundation::IAsyncOperation<int> writeFile(std::string const& path, std::string const& encoding, std::string const& data, bool transformFile, bool append);

  REACT_METHOD(writeFileArray)
  winrt::Windows::Foundation::IAsyncOperation<int> writeFileArray(std::string const& path, JSValue data, bool append);

  REACT_METHOD(writeStream)
  void writeStream(std::string const& path, std::string const& withEncoding, bool appendData, std::function<void(JSValue)> const& callback);

  REACT_METHOD(writeArrayChunk)
  void writeArrayChunk(std::string const& streamId, JSValue withArray, std::function<void(JSValue)> const& callback);

  REACT_METHOD(writeChunk)
  void writeChunk(std::string const& streamId, std::string const& withData, std::function<void(JSValue)> const& callback);

  REACT_METHOD(closeStream)
  void closeStream(std::string const& streamId, std::function<void(JSValue)> const& callback);

  REACT_METHOD(unlink)
  void unlink(std::string const& path, std::function<void(JSValue)> const& callback);

  REACT_METHOD(removeSession)
  void removeSession(JSValue paths, std::function<void(JSValue)> const& callback);

  REACT_METHOD(ls)
  winrt::Windows::Foundation::IAsyncOperation<JSValue> ls(std::string const& path);

  REACT_METHOD(stat)
  void stat(std::string const& target, std::function<void(JSValue)> const& callback);

  REACT_METHOD(lstat)
  void lstat(std::string const& path, std::function<void(JSValue)> const& callback);

  REACT_METHOD(cp)
  void cp(std::string const& src, std::string const& dest, std::function<void(JSValue)> const& callback);

  REACT_METHOD(mv)
  void mv(std::string const& path, std::string const& dest, std::function<void(JSValue)> const& callback);

  REACT_METHOD(mkdir)
  winrt::Windows::Foundation::IAsyncOperation<bool> mkdir(std::string const& path);

  REACT_METHOD(readFile)
  winrt::Windows::Foundation::IAsyncOperation<JSValue> readFile(std::string const& path, std::string const& encoding, bool transformFile);

  REACT_METHOD(hash)
  winrt::Windows::Foundation::IAsyncOperation<std::string> hash(std::string const& path, std::string const& algorithm);

  REACT_METHOD(readStream)
  void readStream(std::string const& path, std::string const& encoding, int bufferSize, int tick, std::string const& streamId);

  REACT_METHOD(getEnvironmentDirs)
  void getEnvironmentDirs(std::function<void(JSValue)> const& callback);

  REACT_METHOD(cancelRequest)
  void cancelRequest(std::string const& taskId, std::function<void(JSValue)> const& callback);

  REACT_METHOD(enableProgressReport)
  void enableProgressReport(std::string const& taskId, int interval, int count);

  REACT_METHOD(enableUploadProgressReport)
  void enableUploadProgressReport(std::string const& taskId, int interval, int count);

  REACT_METHOD(slice)
  winrt::Windows::Foundation::IAsyncOperation<std::string> slice(std::string const& src, std::string const& dest, int64_t start, int64_t end);

  REACT_METHOD(presentOptionsMenu)
  winrt::Windows::Foundation::IAsyncOperation<JSValue> presentOptionsMenu(std::string const& uri, std::string const& scheme);

  REACT_METHOD(presentOpenInMenu)
  winrt::Windows::Foundation::IAsyncOperation<JSValue> presentOpenInMenu(std::string const& uri, std::string const& scheme);

  REACT_METHOD(presentPreview)
  winrt::Windows::Foundation::IAsyncOperation<JSValue> presentPreview(std::string const& uri, std::string const& scheme);

  REACT_METHOD(excludeFromBackupKey)
  winrt::Windows::Foundation::IAsyncOperation<JSValue> excludeFromBackupKey(std::string const& url);

  REACT_METHOD(df)
  void df(std::function<void(JSValue)> const& callback);

  REACT_METHOD(emitExpiredEvent)
  void emitExpiredEvent(std::function<void(std::string)> const& callback);

  REACT_METHOD(actionViewIntent)
  winrt::Windows::Foundation::IAsyncAction actionViewIntent(std::string const& path, std::string const& mime, std::string const& chooserTitle);

  REACT_METHOD(addCompleteDownload)
  winrt::Windows::Foundation::IAsyncAction addCompleteDownload(JSValue config);

  REACT_METHOD(copyToInternal)
  winrt::Windows::Foundation::IAsyncOperation<std::string> copyToInternal(std::string const& contentUri, std::string const& destPath);

  REACT_METHOD(copyToMediaStore)
  winrt::Windows::Foundation::IAsyncOperation<std::string> copyToMediaStore(JSValue filedata, std::string const& mt, std::string const& path);

  REACT_METHOD(createMediaFile)
  winrt::Windows::Foundation::IAsyncOperation<std::string> createMediaFile(JSValue filedata, std::string const& mt);

  REACT_METHOD(getBlob)
  winrt::Windows::Foundation::IAsyncOperation<JSValue> getBlob(std::string const& contentUri, std::string const& encoding);

  REACT_METHOD(getContentIntent)
  winrt::Windows::Foundation::IAsyncOperation<std::string> getContentIntent(std::string const& mime);

  REACT_METHOD(getSDCardDir)
  winrt::Windows::Foundation::IAsyncOperation<std::string> getSDCardDir();

  REACT_METHOD(getSDCardApplicationDir)
  winrt::Windows::Foundation::IAsyncOperation<std::string> getSDCardApplicationDir();

  REACT_METHOD(scanFile)
  void scanFile(JSValue pairs, std::function<void(JSValue)> const& callback);

  REACT_METHOD(writeToMediaFile)
  winrt::Windows::Foundation::IAsyncOperation<std::string> writeToMediaFile(std::string const& fileUri, std::string const& path, bool transformFile);

  REACT_METHOD(addListener)
  void addListener(std::string const& eventName);

  REACT_METHOD(removeListeners)
  void removeListeners(int count);

private:
  React::ReactContext m_context;
};

} // namespace winrt::ReactNativeBlobUtil