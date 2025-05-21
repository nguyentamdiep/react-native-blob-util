#include "pch.h"

#include "ReactNativeBlobUtil.h"
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Web.Http.Headers.h>
#include <winrt/windows.web.http.filters.h>
#include <filesystem>
#include <sstream> 

using namespace winrt;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Security::Cryptography;
using namespace winrt::Windows::Security::Cryptography::Core;
using namespace std::chrono_literals;

CancellationDisposable::CancellationDisposable(IAsyncInfo const& async, std::function<void()>&& onCancel) noexcept
	: m_async{ async }
	, m_onCancel{ std::move(onCancel) }
{
}

CancellationDisposable::CancellationDisposable(CancellationDisposable&& other) noexcept
	: m_async{ std::move(other.m_async) }
	, m_onCancel{ std::move(other.m_onCancel) }
{
}

CancellationDisposable& CancellationDisposable::operator=(CancellationDisposable&& other) noexcept
{
	if (this != &other)
	{
		CancellationDisposable temp{ std::move(*this) };
		m_async = std::move(other.m_async);
		m_onCancel = std::move(other.m_onCancel);
	}
	return *this;
}

CancellationDisposable::~CancellationDisposable() noexcept
{
	Cancel();
}

void CancellationDisposable::Cancel() noexcept
{
	if (m_async)
	{
		if (m_async.Status() == AsyncStatus::Started)
		{
			m_async.Cancel();
		}

		if (m_onCancel)
		{
			m_onCancel();
		}
	}
}

TaskCancellationManager::~TaskCancellationManager() noexcept
{
	// Do the explicit cleaning to make sure that CancellationDisposable
	// destructors run while this instance still has valid fields because
	// they are used by the onCancel callback.
	// We also want to clear the m_pendingTasks before running the
	// CancellationDisposable destructors since they touch the m_pendingTasks.
	std::map<TaskId, CancellationDisposable> pendingTasks;
	{
		std::scoped_lock lock{ m_mutex };
		pendingTasks = std::move(m_pendingTasks);
	}
}


IAsyncAction TaskCancellationManager::Add(TaskId taskId, IAsyncAction const& asyncAction) noexcept
{
	std::scoped_lock lock{ m_mutex };
	m_pendingTasks.try_emplace(taskId, asyncAction, [this, taskId]()
		{
			Cancel(taskId);
		});
	return asyncAction;
}

void TaskCancellationManager::Cancel(TaskId taskId) noexcept
{
	// The destructor of the token does the cancellation. We must do it outside of lock.
	CancellationDisposable token;

	{
		std::scoped_lock lock{ m_mutex };
		if (!m_pendingTasks.empty())
		{
			if (auto it = m_pendingTasks.find(taskId); it != m_pendingTasks.end())
			{
				token = std::move(it->second);
				m_pendingTasks.erase(it);
			}
		}
	}
}

ReactNativeBlobUtilConfig::ReactNativeBlobUtilConfig(winrt::Microsoft::ReactNative::JSValueObject& options) {
	if (options["appendExt"].IsNull() == true)
	{
		appendExt = "";
	}
	else
	{
		appendExt = options["appendExt"].AsString();
	}
	fileCache = options["fileCache"].AsBoolean();
	followRedirect = options["followRedirect"].AsBoolean();
	overwrite = options["overwrite"].AsBoolean();
	if (options["path"].IsNull() == true)
	{
		path = "";
	}
	else
	{
		auto filepath{ options["path"].AsString() };
		auto fileLength{ filepath.length() };
		bool hasTrailingSlash{ filepath[fileLength - 1] == '\\' || filepath[fileLength - 1] == '/' };
		std::filesystem::path pathToParse{ hasTrailingSlash ? filepath.substr(0, fileLength - 1) : filepath };
		pathToParse.make_preferred();
		path = pathToParse.string();
	}
	trusty = options["trusty"].AsBoolean();

	int64_t potentialTimeout{ options["timeout"].AsInt64() };
	timeout = std::chrono::seconds{ potentialTimeout > 0 ? potentialTimeout : 60000 };

}

ReactNativeBlobUtilProgressConfig::ReactNativeBlobUtilProgressConfig(int32_t count_, int32_t interval_) : count(count_), interval(interval_) {
}

ReactNativeBlobUtilStream::ReactNativeBlobUtilStream(Streams::IRandomAccessStream& _streamInstance, EncodingOptions _encoding) noexcept
	: streamInstance{ std::move(_streamInstance) }
	, encoding{ _encoding }
{
}

namespace winrt::ReactNativeBlobUtil
{

// See https://microsoft.github.io/react-native-windows/docs/native-modules for details on writing native modules

void ReactNativeBlobUtil::Initialize(React::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
}

// Constants method
ReactNativeBlobUtilCodegen::BlobUtilsSpec_Constants ReactNativeBlobUtil::GetConstants() noexcept {
    ReactNativeBlobUtilCodegen::BlobUtilsSpec_Constants constants;
    constants.DocumentDir = to_string(ApplicationData::Current().LocalFolder().Path());
    constants.CacheDir = to_string(ApplicationData::Current().LocalCacheFolder().Path());
    constants.PictureDir = to_string(UserDataPaths::GetDefault().Pictures());
    constants.MusicDir = to_string(UserDataPaths::GetDefault().Music());
    constants.MovieDir = to_string(UserDataPaths::GetDefault().Videos());
    constants.DownloadDir = to_string(UserDataPaths::GetDefault().Downloads());
    constants.MainBundleDir = to_string(Package::Current().InstalledLocation().Path());
    return constants;
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
    std::string path,
    std::wstring content,
    std::string encoding,
    winrt::Microsoft::ReactNative::ReactPromise<void> promise
) noexcept {
    try
    {
        bool shouldExit{ false };
        winrt::Windows::Storage::Streams::IBuffer buffer{ nullptr };
        if (encoding == "uri")
        {
            try
            {
                winrt::hstring srcDirectoryPath, srcFileName;
                splitPath(content, srcDirectoryPath, srcFileName);
                auto srcFolder = winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(srcDirectoryPath).get();
                auto srcFile = srcFolder.GetFileAsync(srcFileName).get();
                buffer = winrt::Windows::Storage::FileIO::ReadBufferAsync(srcFile).get();
            }
            catch (...)
            {
                shouldExit = true;
            }
        }
        else if (encoding == "utf8")
        {
            buffer = winrt::Windows::Security::Cryptography::CryptographicBuffer::ConvertStringToBinary(
                content, winrt::Windows::Security::Cryptography::BinaryStringEncoding::Utf8);
        }
        else if (encoding == "base64")
        {
            buffer = winrt::Windows::Security::Cryptography::CryptographicBuffer::DecodeFromBase64String(content);
        }
        else
        {
            promise.Reject("Invalid encoding");
            shouldExit = true;
        }

        if (!shouldExit)
        {
            winrt::hstring destDirectoryPath, destFileName;
            splitPath(path, destDirectoryPath, destFileName);

            auto folder = winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(destDirectoryPath).get();

            try
            {
                auto file = folder.CreateFileAsync(destFileName, winrt::Windows::Storage::CreationCollisionOption::FailIfExists).get();
                auto stream = file.OpenAsync(winrt::Windows::Storage::FileAccessMode::ReadWrite).get();
                stream.WriteAsync(buffer).get();
            }
            catch (...)
            {
                promise.Reject(winrt::Microsoft::ReactNative::ReactError{ "EEXIST", "EEXIST: File already exists; " + path });
                shouldExit = true;
            }
        }
        if (!shouldExit)
        {
            promise.Resolve();
        }
    }
    catch (const winrt::hresult_error& ex)
    {
        winrt::hresult result{ ex.code() };
        if (result == 0x80070002) // FileNotFoundException
        {
            promise.Reject(winrt::Microsoft::ReactNative::ReactError{ "ENOENT", "ENOENT: File does not exist and could not be created; " + path });
        }
        else
        {
            promise.Reject(winrt::Microsoft::ReactNative::ReactError{ "EUNSPECIFIED", "EUNSPECIFIED: " + winrt::to_string(ex.message()) + "; " + path });
        }
    }
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
    // No-op: Android API
    result.Resolve();
}

void ReactNativeBlobUtil::addCompleteDownload(
    ::React::JSValue&& config,
    ::React::ReactPromise<void>&& result) noexcept
{
    // No-op: Android API
    result.Resolve();
}

void ReactNativeBlobUtil::copyToInternal(
    std::string contentUri,
    std::string destpath,
    ::React::ReactPromise<std::string>&& result) noexcept
{    
    // No-op: Android API
    result.Resolve("");
}

void ReactNativeBlobUtil::copyToMediaStore(
    ::React::JSValue&& filedata,
    std::string mt,
    std::string path,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    // No-op: Android API
    result.Resolve("");
}

void ReactNativeBlobUtil::createMediaFile(
    ::React::JSValue&& filedata,
    std::string mt,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    // No-op: Android API
    result.Resolve("");
}

void ReactNativeBlobUtil::getBlob(
    std::string contentUri,
    std::string encoding,
    ::React::ReactPromise<::React::JSValueArray>&& result) noexcept
{
    // No-op: Android API
    result.Resolve(::React::JSValueArray{});
}

void ReactNativeBlobUtil::getContentIntent(
    std::string mime,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    // No-op: Android API
    result.Resolve("");
}

void ReactNativeBlobUtil::getSDCardDir(
    ::React::ReactPromise<std::string>&& result) noexcept
{
    // No-op: Android API
    result.Resolve("");
}

void ReactNativeBlobUtil::getSDCardApplicationDir(
    ::React::ReactPromise<std::string>&& result) noexcept
{
    // No-op: Android API
    result.Resolve("");
}

void ReactNativeBlobUtil::scanFile(
    ::React::JSValueArray&& pairs,
    std::function<void(::React::JSValueArray const&)> const& callback) noexcept
{
    // No-op: Android API
    callback(::React::JSValueArray{});
}

void ReactNativeBlobUtil::writeToMediaFile(
    std::string fileUri,
    std::string path,
    bool transformFile,
    ::React::ReactPromise<std::string>&& result) noexcept
{
    // No-op: Android API
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

void ReactNativeBlobUtil::splitPath(const std::string& fullPath, winrt::hstring& directoryPath, winrt::hstring& fileName) noexcept
{
	std::filesystem::path path{ fullPath };
	path.make_preferred();

	directoryPath = path.has_parent_path() ? winrt::to_hstring(path.parent_path().c_str()) : L"";
	fileName = path.has_filename() ? winrt::to_hstring(path.filename().c_str()) : L"";
}

void ReactNativeBlobUtil::splitPath(const std::wstring& fullPath, winrt::hstring& directoryPath, winrt::hstring& fileName) noexcept
{
	std::filesystem::path path{ fullPath };
	path.make_preferred();

	directoryPath = path.has_parent_path() ? winrt::to_hstring(path.parent_path().c_str()) : L"";
	fileName = path.has_filename() ? winrt::to_hstring(path.filename().c_str()) : L"";
}

winrt::Windows::Foundation::IAsyncAction ReactNativeBlobUtil::ProcessRequestAsync(
	const std::string& taskId,
	const winrt::Windows::Web::Http::Filters::HttpBaseProtocolFilter& filter,
	winrt::Windows::Web::Http::HttpRequestMessage& httpRequestMessage,
	ReactNativeBlobUtilConfig& config,
	std::function<void(std::string, std::string, std::string)> callback,
	std::string& error) noexcept
try
{
	winrt::Windows::Web::Http::HttpClient httpClient{filter};

	winrt::Windows::Web::Http::HttpResponseMessage response{ co_await httpClient.SendRequestAsync(httpRequestMessage, winrt::Windows::Web::Http::HttpCompletionOption::ResponseHeadersRead) };
	
	ReactNativeBlobUtilState eventState;

	auto status{ static_cast<int>(response.StatusCode()) };
	if (config.followRedirect) {
		while (status >= 300 && status < 400) {
			auto redirect{ response.Headers().Location().ToString() };
			eventState.redirects.push_back(Microsoft::ReactNative::JSValue(winrt::to_string(redirect)));
			httpRequestMessage.RequestUri(Uri{ redirect });
			response = co_await httpClient.SendRequestAsync(httpRequestMessage, winrt::Windows::Web::Http::HttpCompletionOption::ResponseHeadersRead);
			status = static_cast<int>(response.StatusCode());
		}
	}
	
	eventState.status = static_cast<int>(response.StatusCode());

	for (const auto header : response.Content().Headers().GetView()) {
		eventState.headers[winrt::to_string(header.Key())] = winrt::to_string(header.Value());
	}

	if (response.Content().Headers().ContentType() != nullptr) {
		eventState.respType = winrt::to_string(response.Content().Headers().ContentType().ToString());
	}

	eventState.state = winrt::to_string(response.ReasonPhrase());

	m_reactContext.CallJSFunction(L"RCTDeviceEventEmitter", L"emit", L"ReactNativeBlobUtilState",
		Microsoft::ReactNative::JSValueObject{
			{ "taskId", taskId },
			{ "state", eventState.state },
			{ "headers", std::move(eventState.headers) },
			{ "redirects", std::move(eventState.redirects) },
			{ "respType", eventState.respType },
			{ "status", eventState.status },
			{ "timeout", false },
		});

	IReference<uint64_t> contentLength{ response.Content().Headers().ContentLength() };

	IOutputStream outputStream;
	bool writeToFile{ config.fileCache || !config.path.empty() };

	if (writeToFile)
	{
		if (config.path.empty())
		{
			config.path = winrt::to_string(ApplicationData::Current().TemporaryFolder().Path()) + "\\ReactNativeBlobUtilTmp_" + taskId;
			if (config.appendExt.length() > 0)
			{
				config.path += "." + config.appendExt;
			}
		}
		std::filesystem::path path{ config.path };
		StorageFolder storageFolder{ co_await StorageFolder::GetFolderFromPathAsync( path.parent_path().wstring()) };
		StorageFile storageFile{ co_await storageFolder.CreateFileAsync(path.filename().wstring(), CreationCollisionOption::FailIfExists) };
		IRandomAccessStream stream{ co_await storageFile.OpenAsync(FileAccessMode::ReadWrite) };
		outputStream = stream.GetOutputStreamAt(0) ;
	}

	auto contentStream{ co_await response.Content().ReadAsInputStreamAsync() };
	Buffer buffer{ 10 * 1024 };
	uint64_t read{ 0 };
	uint64_t totalRead{ 0 };

	ReactNativeBlobUtilProgressConfig progressInfo;
	uint64_t progressInterval{ 0 };

	std::stringstream chunkStream;
	std::stringstream resultOutput;

	std::string readContents{""};

	auto exists{ downloadProgressMap.find(taskId) };
	if (exists != downloadProgressMap.end() && contentLength.Type() == PropertyType::UInt64) {
		progressInfo = downloadProgressMap[taskId];

		if (progressInfo.count > -1) {
			progressInterval = contentLength.Value() / 100 * progressInfo.count;
		}
	}

	int64_t initialProgressTime{ winrt::clock::now().time_since_epoch().count() / 10000 };
	int64_t currentProgressTime;

	for (;;)
	{
		buffer.Length(0);
		auto readBuffer{ co_await contentStream.ReadAsync(buffer, buffer.Capacity(), InputStreamOptions::None) };

		read += readBuffer.Length();
		totalRead += read;

		if (readBuffer.Length() == 0)
		{
			break;
		}
		
		readContents = winrt::to_string(CryptographicBuffer::EncodeToBase64String(readBuffer));

		if (writeToFile) {
			co_await outputStream.WriteAsync(readBuffer);
		}
		else {
			resultOutput << readContents;
		}

		if (progressInfo.count > -1 || progressInfo.interval > -1) {
			chunkStream << readContents;

			currentProgressTime = winrt::clock::now().time_since_epoch().count() / 10000;
			if ((currentProgressTime - initialProgressTime >= progressInfo.interval && progressInfo.interval > -1) ||
				(totalRead >= progressInterval && progressInfo.count > -1)) {
				m_reactContext.CallJSFunction(L"RCTDeviceEventEmitter", L"emit", L"ReactNativeBlobUtilProgress",
					Microsoft::ReactNative::JSValueObject{
						{ "taskId", taskId },
						{ "written", int64_t(totalRead) },
						{ "total", contentLength.Type() == PropertyType::UInt64 ?
									Microsoft::ReactNative::JSValue(contentLength.Value()) :
									Microsoft::ReactNative::JSValue{nullptr} },
						{ "chunk", chunkStream.str() },
					});
				chunkStream.clear();
				initialProgressTime = winrt::clock::now().time_since_epoch().count() / 10000;
				if (progressInfo.count > -1) {
					read = 0;
				}
			}
		}
	}

	if (writeToFile) {
		callback("", "path", config.path);
	}
	else {
		callback("", "result", resultOutput.str());
	}
}
catch (const hresult_error& ex)
{
	error = winrt::to_string(ex.message().c_str());
	//callback(winrt::to_string(ex.message().c_str()), "error", "");
}
catch (...) {
	co_return;
}

} // namespace winrt::ReactNativeBlobUtil