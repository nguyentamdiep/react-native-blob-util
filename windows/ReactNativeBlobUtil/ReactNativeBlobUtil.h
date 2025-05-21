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

  REACT_GET_CONSTANTS(GetConstants, L"GetConstants")
  ReactNativeBlobUtilCodegen::BlobUtilsSpec_Constants GetConstants() noexcept;

  REACT_METHOD(fetchBlobForm, L"fetchBlobForm")
  void fetchBlobForm(::React::JSValue&& options, std::string taskId, std::string method, std::string url, ::React::JSValue&& headers, ::React::JSValueArray&& form, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(fetchBlob, L"fetchBlob")
  void fetchBlob(::React::JSValue&& options, std::string taskId, std::string method, std::string url, ::React::JSValue&& headers, std::string body, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;
  
  REACT_METHOD(createFile, L"createFile")
  void createFile(std::string path, std::string data, std::string encoding, ::React::ReactPromise<void>&& result) noexcept;
  
  REACT_METHOD(createFileASCII, L"createFileASCII")
  void createFileASCII(std::string path, ::React::JSValueArray&& data, ::React::ReactPromise<void>&& result) noexcept;

  REACT_METHOD(pathForAppGroup, L"pathForAppGroup")
  void pathForAppGroup(std::string groupName, ::React::ReactPromise<std::string>&& result) noexcept;

  REACT_SYNC_METHOD(syncPathAppGroup, L"syncPathAppGroup")
  std::string syncPathAppGroup(std::string groupName) noexcept;

  REACT_METHOD(exists, L"exists")
  void exists(std::string path, std::function<void(std::vector<bool> const&)> const& callback) noexcept;

  REACT_METHOD(writeFile, L"writeFile")
  void writeFile(std::string path, std::string encoding, std::string data, bool transformFile, bool append, ::React::ReactPromise<double>&& result) noexcept;

  REACT_METHOD(writeFileArray, L"writeFileArray")
  void writeFileArray(std::string path, ::React::JSValueArray&& data, bool append, ::React::ReactPromise<double>&& result) noexcept;

  REACT_METHOD(writeStream, L"writeStream")
  void writeStream(std::string path, std::string withEncoding, bool appendData, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(writeArrayChunk, L"writeArrayChunk")
  void writeArrayChunk(std::string streamId, ::React::JSValueArray&& withArray, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(writeChunk, L"writeChunk")
  void writeChunk(std::string streamId, std::string withData, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(closeStream, L"closeStream")
  void closeStream(std::string streamId, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(unlink, L"unlink")
  void unlink(std::string path, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(removeSession, L"removeSession")
  void removeSession(::React::JSValueArray&& paths, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(ls, L"ls")
  void ls(std::string path, ::React::ReactPromise<::React::JSValueArray>&& result) noexcept;

  REACT_METHOD(stat, L"stat")
  void stat(std::string target, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(lstat, L"lstat")
  void lstat(std::string path, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(cp, L"cp")
  void cp(std::string src, std::string dest, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(mv, L"mv")
  void mv(std::string path, std::string dest, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(mkdir, L"mkdir")
  void mkdir(std::string path, ::React::ReactPromise<bool>&& result) noexcept;

  REACT_METHOD(readFile, L"readFile")
  void readFile(std::string path, std::string encoding, bool transformFile, ::React::ReactPromise<::React::JSValueArray>&& result) noexcept;

  REACT_METHOD(hash, L"hash")
  void hash(std::string path, std::string algorithm, ::React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(readStream, L"readStream")
  void readStream(std::string path, std::string encoding, double bufferSize, double tick, std::string streamId) noexcept;

  REACT_METHOD(getEnvironmentDirs, L"getEnvironmentDirs")
  void getEnvironmentDirs(std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(cancelRequest, L"cancelRequest")
  void cancelRequest(std::string taskId, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(enableProgressReport, L"enableProgressReport")
  void enableProgressReport(std::string taskId, double interval, double count) noexcept;

  REACT_METHOD(enableUploadProgressReport, L"enableUploadProgressReport")
  void enableUploadProgressReport(std::string taskId, double interval, double count) noexcept;

  REACT_METHOD(slice, L"slice")
  void slice(std::string src, std::string dest, double start, double end, ::React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(presentOptionsMenu, L"presentOptionsMenu")
  void presentOptionsMenu(std::string uri, std::string scheme, ::React::ReactPromise<::React::JSValueArray>&& result) noexcept;

  REACT_METHOD(presentOpenInMenu, L"presentOpenInMenu")
  void presentOpenInMenu(std::string uri, std::string scheme, ::React::ReactPromise<::React::JSValueArray>&& result) noexcept;

  REACT_METHOD(presentPreview, L"presentPreview")
  void presentPreview(std::string uri, std::string scheme, ::React::ReactPromise<::React::JSValueArray>&& result) noexcept;

  REACT_METHOD(excludeFromBackupKey, L"excludeFromBackupKey")
  void excludeFromBackupKey(std::string url, ::React::ReactPromise<::React::JSValueArray>&& result) noexcept;

  REACT_METHOD(df, L"df")
  void df(std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(emitExpiredEvent, L"emitExpiredEvent")
  void emitExpiredEvent(std::function<void(std::string)> const& callback) noexcept;

  REACT_METHOD(actionViewIntent, L"actionViewIntent")
  void actionViewIntent(std::string path, std::string mime, std::string chooserTitle, ::React::ReactPromise<void>&& result) noexcept;

  REACT_METHOD(addCompleteDownload, L"addCompleteDownload")
  void addCompleteDownload(::React::JSValue&& config, ::React::ReactPromise<void>&& result) noexcept;

  REACT_METHOD(copyToInternal, L"copyToInternal")
  void copyToInternal(std::string contentUri, std::string destpath, ::React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(copyToMediaStore, L"copyToMediaStore")
  void copyToMediaStore(::React::JSValue&& filedata, std::string mt, std::string path, ::React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(createMediaFile, L"createMediaFile")
  void createMediaFile(::React::JSValue&& filedata, std::string mt, ::React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(getBlob, L"getBlob")
  void getBlob(std::string contentUri, std::string encoding, ::React::ReactPromise<::React::JSValueArray>&& result) noexcept;

  REACT_METHOD(getContentIntent, L"getContentIntent")
  void getContentIntent(std::string mime, ::React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(getSDCardDir, L"getSDCardDir")
  void getSDCardDir(::React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(getSDCardApplicationDir, L"getSDCardApplicationDir")
  void getSDCardApplicationDir(::React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(scanFile, L"scanFile")
  void scanFile(::React::JSValueArray&& pairs, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

  REACT_METHOD(writeToMediaFile, L"writeToMediaFile")
  void writeToMediaFile(std::string fileUri, std::string path, bool transformFile, ::React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(addListener, L"addListener")
  void addListener(std::string eventName) noexcept;

  REACT_METHOD(removeListeners, L"removeListeners")
  void removeListeners(double count) noexcept;

private:
  React::ReactContext m_context;
};

} // namespace winrt::ReactNativeBlobUtil