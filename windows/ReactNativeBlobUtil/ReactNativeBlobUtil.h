#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen/NativeBlobUtilsDataTypes.g.h")
  #include "codegen/NativeBlobUtilsDataTypes.g.h"
#endif

#include "codegen/NativeBlobUtilsSpec.g.h"
#include "NativeModules.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Windows.Web.Http.Filters.h>
#include <mutex>

namespace Cryptography = winrt::Windows::Security::Cryptography;
namespace CryptographyCore = winrt::Windows::Security::Cryptography::Core;

enum struct EncodingOptions { UTF8, BASE64, ASCII, URI };

struct CancellationDisposable
{
	CancellationDisposable() = default;
	CancellationDisposable(winrt::Windows::Foundation::IAsyncInfo const& async, std::function<void()>&& onCancel) noexcept;

	CancellationDisposable(CancellationDisposable&& other) noexcept;
	CancellationDisposable& operator=(CancellationDisposable&& other) noexcept;

	CancellationDisposable(CancellationDisposable const&) = delete;
	CancellationDisposable& operator=(CancellationDisposable const&) = delete;

	~CancellationDisposable() noexcept;

	void Cancel() noexcept;
private:
	winrt::Windows::Foundation::IAsyncInfo m_async{ nullptr };
	std::function<void()> m_onCancel;
};

struct TaskCancellationManager
{
	using TaskId = std::string;

	TaskCancellationManager() = default;
	~TaskCancellationManager() noexcept;

	TaskCancellationManager(TaskCancellationManager const&) = delete;
	TaskCancellationManager& operator=(TaskCancellationManager const&) = delete;

	winrt::Windows::Foundation::IAsyncAction Add(TaskId taskId, winrt::Windows::Foundation::IAsyncAction const& asyncAction) noexcept;
	void Cancel(TaskId taskId) noexcept;

private:
	std::mutex m_mutex; // to protect m_pendingTasks
	std::map<TaskId, CancellationDisposable> m_pendingTasks;
};

struct ReactNativeBlobUtilState
{
	/*
		
		@"state": @"2", // store
		@"headers": headers, // store
		@"redirects": redirects, //check how to track, store
		@"respType" : respType, // store
		@"status": [NSNumber numberWithInteger : statusCode] // store
	*/
	std::string state;
	winrt::Microsoft::ReactNative::JSValueObject headers;
	winrt::Microsoft::ReactNative::JSValueArray redirects;
	std::string respType;
	int status = 0;

	/*
	taskId: string;
    state: string;
    headers: any;
    redirects: string[];
    status: number;
    respType: "text" | "blob" | "" | "json";
    rnfbEncode: "path" | "base64" | "ascii" | "utf8";
    timeout: boolean;
	*/
};


struct ReactNativeBlobUtilStream
{
public:
	ReactNativeBlobUtilStream(winrt::Windows::Storage::Streams::IRandomAccessStream& _streamInstance, EncodingOptions _encoding) noexcept;
	winrt::Windows::Storage::Streams::IRandomAccessStream streamInstance;
	const EncodingOptions encoding;
};

struct ReactNativeBlobUtilConfig
{
public:
	ReactNativeBlobUtilConfig(::React::JSValue& options);

	bool overwrite;
	std::chrono::seconds timeout;
	bool trusty;
	bool fileCache;
	std::string key;
	std::string appendExt;
	std::string path;
	bool followRedirect;
};


struct ReactNativeBlobUtilProgressConfig {
public:
	ReactNativeBlobUtilProgressConfig() = default;
	ReactNativeBlobUtilProgressConfig(double count_, double interval_);
	
	double count{ -1.0 };
	double interval{ -1.0 };
};

namespace winrt::ReactNativeBlobUtil
{

REACT_MODULE(ReactNativeBlobUtil)
struct ReactNativeBlobUtil
{
    using ModuleSpec = ReactNativeBlobUtilCodegen::BlobUtilsSpec;
    using StreamId = std::string;

    REACT_INIT(Initialize)
        void Initialize(React::ReactContext const& reactContext) noexcept;

    REACT_GET_CONSTANTS(GetConstants, L"GetConstants")
        ReactNativeBlobUtilCodegen::BlobUtilsSpec_Constants GetConstants() noexcept;

    REACT_METHOD(fetchBlobForm, L"fetchBlobForm")
        void fetchBlobForm(::React::JSValue&& options, std::string taskId, std::string method, std::string url, ::React::JSValue&& headers, ::React::JSValueArray&& form, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

    REACT_METHOD(fetchBlob, L"fetchBlob")
        void fetchBlob(::React::JSValue&& options, std::string taskId, std::string method, std::string url, ::React::JSValue&& headers, std::string body, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

    REACT_METHOD(createFile, L"createFile")
        winrt::fire_and_forget createFile(
                std::string path,
                std::wstring content,
                std::string encoding,
                winrt::Microsoft::ReactNative::ReactPromise<void> promise
            ) noexcept;

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
        void writeFileArray(std::string path, ::React::JSValueArray&& dataArray, bool append, ::React::ReactPromise<double>&& promise) noexcept;

    REACT_METHOD(writeStream, L"writeStream")
        void writeStream(std::string path, std::string encoding, bool appendData, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

    REACT_METHOD(writeArrayChunk, L"writeArrayChunk")
        void writeArrayChunk(std::string streamId, ::React::JSValueArray&& dataArray, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

    REACT_METHOD(writeChunk, L"writeChunk")
        void writeChunk(std::string streamId, std::string data, std::function<void(::React::JSValueArray const&)> const& callback) noexcept;

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

    constexpr static int64_t UNIX_EPOCH_IN_WINRT_SECONDS = 11644473600;

    std::map<StreamId, ReactNativeBlobUtilStream> m_streamMap;
    //winrt::Windows::Web::Http::HttpClient m_httpClient;
    winrt::Microsoft::ReactNative::ReactContext m_reactContext;
    TaskCancellationManager m_tasks;

    winrt::Windows::Foundation::IAsyncAction ProcessRequestAsync(
        const std::string& taskId,
        const winrt::Windows::Web::Http::Filters::HttpBaseProtocolFilter& filter,
        winrt::Windows::Web::Http::HttpRequestMessage& httpRequestMessage,
        ReactNativeBlobUtilConfig& config,
        std::function<void(std::string, std::string, std::string)> callback,
        std::string& error) noexcept;

    const std::map<std::string, std::function<CryptographyCore::HashAlgorithmProvider()>> availableHashes{
        {"md5", []() { return CryptographyCore::HashAlgorithmProvider::OpenAlgorithm(CryptographyCore::HashAlgorithmNames::Md5()); } },
        {"sha1", []() { return CryptographyCore::HashAlgorithmProvider::OpenAlgorithm(CryptographyCore::HashAlgorithmNames::Sha1()); } },
        {"sha256", []() { return CryptographyCore::HashAlgorithmProvider::OpenAlgorithm(CryptographyCore::HashAlgorithmNames::Sha256()); } },
        {"sha384", []() { return CryptographyCore::HashAlgorithmProvider::OpenAlgorithm(CryptographyCore::HashAlgorithmNames::Sha384()); } },
        {"sha512", []() { return CryptographyCore::HashAlgorithmProvider::OpenAlgorithm(CryptographyCore::HashAlgorithmNames::Sha512()); } }
    };

    void splitPath(const std::string& fullPath,
        winrt::hstring& directoryPath,
        winrt::hstring& fileName) noexcept;

    void splitPath(const std::wstring& fullPath,
        winrt::hstring& directoryPath,
        winrt::hstring& fileName) noexcept;

    const std::string prefix{ "ReactNativeBlobUtil-file://" };

    std::mutex m_mutex;
    std::map<std::string, ReactNativeBlobUtilProgressConfig> downloadProgressMap;
    std::map<std::string, ReactNativeBlobUtilProgressConfig> uploadProgressMap;
};

} // namespace winrt::ReactNativeBlobUtil