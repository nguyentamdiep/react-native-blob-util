# react-native-blob-util

[![release](https://img.shields.io/github/release/RonRadtke/react-native-blob-util.svg?style=flat-square)](https://github.com/RonRadtke/react-native-blob-util/releases) [![npm](https://img.shields.io/npm/v/react-native-blob-util.svg?style=flat-square)](https://www.npmjs.com/package/react-native-blob-util) ![](https://img.shields.io/badge/PR-Welcome-brightgreen.svg?style=flat-square) [![](https://img.shields.io/badge/Wiki-Public-brightgreen.svg?style=flat-square)](https://github.com/RonRadtke/react-native-blob-util/wiki) [![npm](https://img.shields.io/npm/l/react-native-blob-util.svg?maxAge=2592000&style=flat-square)]()

A project committed to making file access and data transfer easier and more efficient for React Native developers.

# I forked this project to continue working on it.

This project is a fork of https://www.npmjs.com/package/rn-fetch-blob which on the other hand is a fork of https://github.com/wkh237/react-native-fetch-blob. Both the original repository and its first fork are not maintained anymore.

The project will be continued in this repository. React-Native-Blob-Util is fully compatible with RN-Fetch-Blob and React-Native-Fetch-Blob. If you want to support the project feel free to contact me or create a pull request with your feature.

# Version Compatibility Warning

react-native-blob-util version **0.22.0** and up is only compatible with react native **0.76** and up.
"0.22.0" -> 0.76 RN
"0.22.1" -> 0.77 RN
"0.22.2" -> 0.78 RN

react-native-blob-util version **0.17.0** and up is only compatible with react native **0.65** and up.

react-native-blob-util version **0.10.16** and up is only compatible with react native **0.60** and up.

## Features

- Access and write data to Android Media Store (e.g. Downloads folder on devices > Android 9)
- Transfer data directly from/to storage without BASE64 bridging
- File API supports regular files, Asset files, and CameraRoll files
- Native-to-native file manipulation API, reduce JS bridging performance loss
- File stream support for dealing with large file
- Blob, File, XMLHttpRequest polyfills that make browser-based library available in RN (experimental)
- JSON stream supported base on [Oboe.js](https://github.com/jimhigson/oboe.js/) @jimhigson

## React Native New Architecture
With React Native 0.68.0 the switch to enable the new aritechture was introduced.
Starting with version 0.17.0 this library introduces support for the new architecture as well. Of course the old architecture will still be supported.
Further information about it and how to use it you can find here: https://reactnative.dev/docs/next/the-new-architecture/landing-page

## Android 10 & 11

Android 10 introduced scoped storage for apps. Apps no longer can create own directories directly on the external storage or access files outside the apps own directories. With version 0.14.0 support for the media storage is implemented. For more information please see the chapter about the mediastore API.
[test](###android-media-storage)
For more information see: https://developer.android.com/training/data-storage

## TOC (visit [Wiki](https://github.com/RonRadtke/react-native-blob-util/wiki) to get the complete documentation)

* [About](#user-content-about)
* [Installation](#user-content-installation)
* [HTTP Data Transfer](#user-content-http-data-transfer)
* [Regular Request](#user-content-regular-request)
* [Download file](#download-example-fetch-files-that-need-authorization-token)
* [Upload file](#user-content-upload-example--dropbox-files-upload-api)
* [Multipart/form upload](#user-content-multipartform-data-example--post-form-data-with-file-and-data)
* [Upload/Download progress](#user-content-uploaddownload-progress)
* [Cancel HTTP request](#user-content-cancel-request)
* [Android Media Scanner, and Download Manager Support](#user-content-android-media-scanner-and-download-manager-support)
* [Self-Signed SSL Server](#user-content-self-signed-ssl-server)
* [Transfer Encoding](#user-content-transfer-encoding)
* [Drop-in Fetch Replacement](#user-content-drop-in-fetch-replacement)
* [File System](#user-content-file-system)
* [File access](#user-content-file-access)
* [File stream](#user-content-file-stream)
* [Manage cached files](#user-content-cache-file-management)
* [Web API Polyfills](#user-content-web-api-polyfills)
* [Performance Tips](#user-content-performance-tips)
* [API References](https://github.com/RonRadtke/react-native-blob-util/wiki/Fetch-API)
* [Caveats](#user-content-caveats)
* [Development](#user-content-development)

## About

This project was started in the cause of solving issue [facebook/react-native#854](https://github.com/facebook/react-native/issues/854), React Native's lacks of `Blob` implementation which results into problems when transferring binary data.

It is committed to making file access and transfer easier and more efficient for React Native developers. We've implemented highly customizable filesystem and network module which plays well together. For example, developers can upload and download data directly from/to storage, which is more efficient, especially for large files. The file system supports file stream, so you don't have to worry about OOM problem when accessing large files.

In `0.8.0` we introduced experimental Web API polyfills that make it possible to use browser-based libraries in React Native, such as, [FireBase JS SDK](https://github.com/joltup/rn-firebase-storage-upload-sample)

## Installation

Install package from npm

```sh
npm install --save react-native-blob-util
```

Or if using CocoaPods, add the pod to your `Podfile`

```
pod 'react-native-blob-util',
    :path => '../node_modules/react-native-blob-util'
```

After `0.10.3` you can install this package directly from Github

```sh
# replace <branch_name> with any one of the branches
npm install --save github:RonRadtke/react-native-blob-util#<branch_name>
```

**iOS**

When using the package from npm, run `pod install` from the `ios` directory:

```sh
cd ios; pod install; cd ..
```

**Okhttp**

For using the library okhttp3 is required. It's in general included in react-native. The library uses the okhttp version shipped with react-native or used by your app. For very old devices android devices okhttp 3.12 can be used.

**Manually Link Native Modules**

If you're using RN 0.60 or higher, manual linking should not be required anymore.

If automatically linking doesn't work for you, see instructions on [manually linking](https://github.com/RonRadtke/react-native-blob-util/wiki/Manually-Link-Package#index).

**Automatically Link Native Modules**

For 0.29.2+ projects, simply link native packages via the following command (note: rnpm has been merged into react-native)

```
react-native link react-native-blob-util
```

As for projects < 0.29 you need `rnpm` to link native packages

```sh
rnpm link
```

Optionally, use the following command to add Android permissions to `AndroidManifest.xml` automatically

```sh
RNFB_ANDROID_PERMISSIONS=true react-native react-native-blob-util
```

pre 0.29 projects

```sh
RNFB_ANDROID_PERMISSIONS=true rnpm link
```

The link script might not take effect if you have non-default project structure, please visit [the wiki](https://github.com/RonRadtke/react-native-blob-util/wiki/Manually-Link-Package) to link the package manually.

**Grant Permission to External storage for Android 5.0 or lower**

The mechanism for granting Android permissions has slightly different since Android 6.0 released, please refer to [Official Document](https://developer.android.com/training/permissions/requesting.html).

If you're going to access external storage (say, SD card storage) for `Android 5.0` (or lower) devices, you might have to add the following line to `AndroidManifest.xml`.

```diff
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.ReactNativeBlobUtiltest"
    android:versionCode="1"
    android:versionName="1.0">

    <uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>
+   <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
+   <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
+   <uses-permission android:name="android.permission.DOWNLOAD_WITHOUT_NOTIFICATION" />
    ...

```

Also, if you're going to use `Android Download Manager` you have to add this to `AndroidManifest.xml`

```diff
    <intent-filter>
            <action android:name="android.intent.action.MAIN" />
            <category android:name="android.intent.category.LAUNCHER" />
+           <action android:name="android.intent.action.DOWNLOAD_COMPLETE"/>
    </intent-filter>
```

If you are going to use the `wifiOnly` flag, you need to add this to `AndroidManifest.xml`

```diff
+   <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
    ...

```

**Grant Access Permission for Android 6.0**

Beginning in Android 6.0 (API level 23), users grant permissions to apps while the app is running, not when they install the app. So adding permissions in `AndroidManifest.xml` won't work for Android 6.0+ devices. To grant permissions in runtime, you might use [PermissionAndroid API](https://facebook.github.io/react-native/docs/permissionsandroid).

## Usage

ES6

The module uses ES6 style export statement, simply use `import` to load the module.

```js
import ReactNativeBlobUtil from 'react-native-blob-util'
```

ES5

If you're using ES5 require statement to load the module, please add `default`. See [here](https://github.com/RonRadtke/react-native-blob-util/wiki/Trouble-Shooting#ReactNativeBlobUtilfetch-is-not-a-function) for more detail.

```
var ReactNativeBlobUtil = require('react-native-blob-util').default
```

## HTTP Data Transfer

### Regular Request

After `0.8.0` react-native-blob-util automatically decides how to send the body by checking its type and `Content-Type` in the header. The rule is described in the following diagram

<img src="img/RNFB-Flow-hd.png" style="width : 90%" />

To sum up:

- To send a form data, the `Content-Type` header does not matter. When the body is an `Array` we will set proper content type for you.
- To send binary data, you have two choices, use BASE64 encoded string or path points to a file contains the body.
- If the `Content-Type` containing substring`;BASE64` or `application/octet` the given body will be considered as a BASE64 encoded data which will be decoded to binary data as the request body.
- Otherwise, if a string starts with `ReactNativeBlobUtil-file://` (which can simply be done by `ReactNativeBlobUtil.wrap(PATH_TO_THE_FILE)`), it will try to find the data from the URI string after `ReactNativeBlobUtil-file://` and use it as the request body.
- To send the body as-is, simply use a `Content-Type` header not containing `;BASE64` or `application/octet`.

> It is Worth to mentioning that the HTTP request uses cache by default, if you're going to disable it simply add a Cache-Control header `'Cache-Control' : 'no-store'`

> After 0.9.4, we disabled `Chunked` transfer encoding by default, if you're going to use it, you should explicitly set header `Transfer-Encoding` to `Chunked`.

### Download example: Fetch files that need authorization token

Most simple way is download to memory and stored as BASE64 encoded string, this is handy when the response data is small. Note that when it comes to authorization, not only can you use an authorization token, but this package will automatically pass the cookies created by normal js requests such as axios and fetch. Therefore, if you are using traditional cookie-based ways to authorize your user, you don't need to do anything before this package works.

```js

// send http request in a new thread (using native code)
ReactNativeBlobUtil.fetch('GET', 'http://www.example.com/images/img1.png', {
    Authorization: 'Bearer access-token...',
    // more headers  ..
})
        .then((res) => {
            let status = res.info().status;

            if (status == 200) {
                // the conversion is done in native code
                let base64Str = res.base64()
                // the following conversions are done in js, it's SYNC
                let text = res.text()
                let json = res.json()
            }
            else {
                // handle other status codes
            }
        })
        // Something went wrong:
        .catch((errorMessage, statusCode) => {
            // error handling
        })
```

### Download to storage directly

If the response data is large, that would be a bad idea to convert it into BASE64 string. A better solution is streaming the response directly into a file, simply add a `fileCache` option to config, and set it to `true`. This will make incoming response data stored in a temporary path **without** any file extension.

**These files won't be removed automatically, please refer to [Cache File Management](#user-content-cache-file-management)**

```js
ReactNativeBlobUtil
        .config({
            // add this option that makes response data to be stored as a file,
            // this is much more performant.
            fileCache: true,
        })
        .fetch('GET', 'http://www.example.com/file/example.zip', {
            //some headers ..
        })
        .then((res) => {
            // the temp file path
            console.log('The file saved to ', res.path())
        })
```

**Set Temp File Extension**

Sometimes you might need a file extension for some reason. For example, when using file path as the source of `Image` component, the path should end with something like .png or .jpg, you can do this by add `appendExt` option to `config`.

```js
ReactNativeBlobUtil
        .config({
            fileCache: true,
            // by adding this option, the temp files will have a file extension
            appendExt: 'png'
        })
        .fetch('GET', 'http://www.example.com/file/example.zip', {
            //some headers ..
        })
        .then((res) => {
            // the temp file path with file extension `png`
            console.log('The file saved to ', res.path())
            // Beware that when using a file path as Image source on Android,
            // you must prepend "file://"" before the file path
            imageView = <Image source={{uri: Platform.OS === 'android' ? 'file://' + res.path() : '' + res.path()}}/>
        })
```

**Use Specific File Path**

If you prefer a particular file path rather than randomly generated one, you can use `path` option. We've added [several  constants](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#dirs) in v0.5.0 which represents commonly used directories.

```js
let dirs = ReactNativeBlobUtil.fs.dirs
ReactNativeBlobUtil
        .config({
            // response data will be saved to this path if it has access right.
            path: dirs.DocumentDir + '/path-to-file.anything'
        })
        .fetch('GET', 'http://www.example.com/file/example.zip', {
            //some headers ..
        })
        .then((res) => {
            // the path should be dirs.DocumentDir + 'path-to-file.anything'
            console.log('The file saved to ', res.path())
        })
```

**These files won't be removed automatically, please refer to [Cache File Management](#user-content-cache-file-management)**

**Use File Transformer**

If you need to perform any processing on the bytes prior to it being written into storage (e.g. if you want it to be encrypted) then you can use `transform` option.  NOTE: you will need to set a transformer on the libray (see [Setting a File Transformer](#Setting-A-File-Transformer))

```js
ReactNativeBlobUtil
        .config({
            // response data will be saved to this path if it has access right.
            path: dirs.DocumentDir + '/path-to-file.anything',
            transform: true
        })
        .fetch('GET', 'http://www.example.com/file/example.zip', {
            //some headers ..
        })
        .then((res) => {
            // the path should be dirs.DocumentDir + 'path-to-file.anything'
            console.log('The file saved to ', res.path())
        })
```

#### Upload example : Dropbox [files-upload](https://www.dropbox.com/developers/documentation/http/documentation#files-upload) API

`react-native-blob-util` will convert the base64 string in `body` to binary format using native API, this process is done in a separated thread so that it won't block your GUI.

```js

ReactNativeBlobUtil.fetch('POST', 'https://content.dropboxapi.com/2/files/upload', {
    Authorization: "Bearer access-token...",
    'Dropbox-API-Arg': JSON.stringify({
        path: '/img-from-react-native.png',
        mode: 'add',
        autorename: true,
        mute: false
    }),
    'Content-Type': 'application/octet-stream',
    // here's the body you're going to send, should be a BASE64 encoded string
    // (you can use "base64"(refer to the library 'mathiasbynens/base64') APIs to make one).
    // The data will be converted to "byte array"(say, blob) before request sent.
}, base64ImageString)
        .then((res) => {
            console.log(res.text())
        })
        .catch((err) => {
            // error handling ..
        })
```

### Upload a file from storage

If you're going to use a `file` as request body, just wrap the path with `wrap` API.

```js
ReactNativeBlobUtil.fetch('POST', 'https://content.dropboxapi.com/2/files/upload', {
    // dropbox upload headers
    Authorization: "Bearer access-token...",
    'Dropbox-API-Arg': JSON.stringify({
        path: '/img-from-react-native.png',
        mode: 'add',
        autorename: true,
        mute: false
    }),
    'Content-Type': 'application/octet-stream',
    // Change BASE64 encoded data to a file path with prefix `ReactNativeBlobUtil-file://`.
    // Or simply wrap the file path with ReactNativeBlobUtil.wrap().
}, ReactNativeBlobUtil.wrap(PATH_TO_THE_FILE))
        .then((res) => {
            console.log(res.text())
        })
        .catch((err) => {
            // error handling ..
        })
```

### Multipart/form-data example: Post form data with file and data

In `version >= 0.3.0` you can also post files with form data, just put an array in `body`, with elements have property `name`, `data`, and `filename`(optional).

Elements have property `filename` will be transformed into binary format, otherwise, it turns into utf8 string.

```js

ReactNativeBlobUtil.fetch('POST', 'http://www.example.com/upload-form', {
    Authorization: "Bearer access-token",
    otherHeader: "foo",
    'Content-Type': 'multipart/form-data',
}, [
    // element with property `filename` will be transformed into `file` in form data
    {name: 'avatar', filename: 'avatar.png', data: binaryDataInBase64},
    // custom content type
    {name: 'avatar-png', filename: 'avatar-png.png', type: 'image/png', data: binaryDataInBase64},
    // part file from storage
    {name: 'avatar-foo', filename: 'avatar-foo.png', type: 'image/foo', data: ReactNativeBlobUtil.wrap(path_to_a_file)},
    // elements without property `filename` will be sent as plain text
    {name: 'name', data: 'user'},
    {
        name: 'info', data: JSON.stringify({
            mail: 'example@example.com',
            tel: '12345678'
        })
    },
]).then((resp) => {
    // ...
}).catch((err) => {
    // ...
})
```

What if you want to append a file to form data? Just like [upload a file from storage](#user-content-upload-a-file-from-storage) example, wrap `data` by `wrap` API (this feature is only available for `version >= v0.5.0`). On version >= `0.6.2`, it is possible to set custom MIME type when appending a file to form data. But keep in mind when the file is large it's likely to crash your app. Please consider use other strategy (see [#94](https://github.com/joltup/react-native-blob-util/issues/94)).

```js

ReactNativeBlobUtil.fetch('POST', 'http://www.example.com/upload-form', {
    Authorization: "Bearer access-token",
    otherHeader: "foo",
    // this is required, otherwise it won't be process as a multipart/form-data request
    'Content-Type': 'multipart/form-data',
}, [
    // append field data from file path
    {
        name: 'avatar',
        filename: 'avatar.png',
        // Change BASE64 encoded data to a file path with prefix `ReactNativeBlobUtil-file://`.
        // Or simply wrap the file path with ReactNativeBlobUtil.wrap().
        data: ReactNativeBlobUtil.wrap(PATH_TO_THE_FILE)
    },
    {
        name: 'ringtone',
        filename: 'ring.mp3',
        // use custom MIME type
        type: 'application/mp3',
        // upload a file from asset is also possible in version >= 0.6.2
        data: ReactNativeBlobUtil.wrap(ReactNativeBlobUtil.fs.asset('default-ringtone.mp3'))
    },
    // elements without property `filename` will be sent as plain text
    {name: 'name', data: 'user'},
    {
        name: 'info', data: JSON.stringify({
            mail: 'example@example.com',
            tel: '12345678'
        })
    },
]).then((resp) => {
    // ...
}).catch((err) => {
    // ...
})
```

### Upload/Download progress

In `version >= 0.4.2` it is possible to know the upload/download progress. After `0.7.0` IOS and Android upload progress are also supported.

```js
  ReactNativeBlobUtil.fetch('POST', 'http://www.example.com/upload', {
    //... some headers,
    'Content-Type': 'octet-stream'
}, base64DataString)
        // listen to upload progress event
        .uploadProgress((written, total) => {
            console.log('uploaded', written / total)
        })
        // listen to download progress event
        .progress((received, total) => {
            console.log('progress', received / total)
        })
        .then((resp) => {
            // ...
        })
        .catch((err) => {
            // ...
        })
```

In `0.9.6`, you can specify an object as the first argument which contains `count` and `interval`, to the frequency of progress event (this will be done in the native context a reduce RCT bridge overhead). Notice that `count` argument will not work if the server does not provide response content length.

```js
  ReactNativeBlobUtil.fetch('POST', 'http://www.example.com/upload', {
    //... some headers,
    'Content-Type': 'octet-stream'
}, base64DataString)
        // listen to upload progress event, emit every 250ms
        .uploadProgress({interval: 250}, (written, total) => {
            console.log('uploaded', written / total)
        })
        // listen to download progress event, every 10%
        .progress({count: 10}, (received, total) => {
            console.log('progress', received / total)
        })
        .then((resp) => {
            // ...
        })
        .catch((err) => {
            // ...
        })
```

### Cancel Request

After `0.7.0` it is possible to cancel an HTTP request. Upon cancellation, it throws a promise rejection, be sure to catch it.

```js
let task = ReactNativeBlobUtil.fetch('GET', 'http://example.com/file/1')

task.then(() => { ...
})
        // handle request cancelled rejection
        .catch((err) => {
            console.log(err)
        })
// cancel the request, the callback function is optional
task.cancel((err) => { ...
})

```

### Drop-in Fetch Replacement

0.9.0

If you have existing code that uses `whatwg-fetch`(the official **fetch**), it's not necessary to replace them with `ReactNativeBlobUtil.fetch`, you can simply use our **Fetch Replacement**. The difference between Official them is official fetch uses [whatwg-fetch](https://github.com/github/fetch) which wraps XMLHttpRequest polyfill under the hood. It's a great library for web developers, but does not play very well with RN. Our implementation is simply a wrapper of our `fetch` and `fs` APIs, so you can access all the features we provided.

[See document and examples](https://github.com/RonRadtke/react-native-blob-util/wiki/Fetch-API#fetch-replacement)

### Android Media Scanner, and Download Manager Support

If you want to make a file in `External Storage` becomes visible in Picture, Downloads, or other built-in apps, you will have to use `Media Scanner` or `Download Manager` or the `Media Storage`.

**Media Scanner**

Media scanner scans the file and categorizes by given MIME type, if MIME type not specified, it will try to resolve the file using its file extension.

```js

ReactNativeBlobUtil
        .config({
            // DCIMDir is in external storage
            path: dirs.DCIMDir + '/music.mp3'
        })
        .fetch('GET', 'http://example.com/music.mp3')
        .then((res) => ReactNativeBlobUtil.fs.scanFile([{path: res.path(), mime: 'audio/mpeg'}]))
        .then(() => {
            // scan file success
        })
        .catch((err) => {
            // scan file error
        })
```

**Download Manager**

When downloading large files on Android it is recommended to use `Download Manager`, it supports a lot of native features like the progress bar, and notification, also the download task will be handled by OS, and more efficient.

<img src="img/download-manager.png" width="256">

When using DownloadManager, `fileCache` and `path` properties in `config` will not take effect, because Android DownloadManager can only store files to external storage, also notice that Download Manager can only support `GET` method, which means the request body will be ignored.

When download complete, DownloadManager will generate a file path so that you can deal with it.

```js
ReactNativeBlobUtil
        .config({
            addAndroidDownloads: {
                useDownloadManager: true, // <-- this is the only thing required
                // Optional, override notification setting (default to true)
                notification: false,
                // Optional, but recommended since android DownloadManager will fail when
                // the url does not contains a file extension, by default the mime type will be text/plain
                mime: 'text/plain',
                description: 'File downloaded by download manager.'
            }
        })
        .fetch('GET', 'http://example.com/file/somefile')
        .then((resp) => {
            // the path of downloaded file
            resp.path()
        })
```

Your app might not have right to remove/change the file created by Download Manager, therefore you might need to [set custom location to the download task](https://github.com/wkh237/react-native-fetch-blob/issues/236).

**Download Notification and Visibility in Download App (Android Only)**

<img src="img/android-notification1.png" width="256">
<img src="img/android-notification2.png" width="256">


If you need to display a notification upon the file is downloaded to storage (as the above) or make the downloaded file visible in "Downloads" app. You have to add some options to `config`.

```js
ReactNativeBlobUtil.config({
    fileCache: true,
    // android only options, these options be a no-op on IOS
    addAndroidDownloads: {
        // Show notification when response data transmitted
        notification: true,
        // Title of download notification
        title: 'Great ! Download Success ! :O ',
        // File description (not notification description)
        description: 'An image file.',
        mime: 'image/png',
        // Make the file scannable  by media scanner
        mediaScannable: true,
    }
})
        .fetch('GET', 'http://example.com/image1.png')
        .then(...)
```

**Open Downloaded File with Intent**

This is a new feature added in `0.9.0` if you're going to open a file path using official [Linking](https://facebook.github.io/react-native/docs/linking.html) API that might not work as expected, also, if you're going to install an APK in `Downloads` app, that will not function too. As an alternative, you can try `actionViewIntent` API, which will send an ACTION_VIEW intent for you which uses the given `MIME` type.

Download and install an APK programmatically

Note:
be sure to specify the path, do not use the default path, because the permission problem causes the installation to fail, parsing the package fails

default path: `/data/data/com.android.providers.downloads/cache/xxx.apk`   // Will cause parsing of the package to fail，Unable to install APK

```js

const android = ReactNativeBlobUtil.android
const dirs = ReactNativeBlobUtil.fs.dirs;
const apkUrl = "http://www.example.com/awesome.apk";    
const fileName = url.substring(url.lastIndexOf('/') + 1);

ReactNativeBlobUtil.config({
    addAndroidDownloads: {
        useDownloadManager: true,
        path: `${dirs.DownloadDir}/${fileName}`,    // <-- Must specify
        title: 'awesome.apk',
        description: 'An APK that will be installed',
        mime: 'application/vnd.android.package-archive',
        mediaScannable: true,
        notification: true,
    }
})
        .fetch('GET', `http://www.example.com/awesome.apk`)
        .then((res) => {
            android.actionViewIntent(res.path(), 'application/vnd.android.package-archive')
        })
```

Or show an image in image viewer

```js
      android.actionViewIntent(PATH_OF_IMG, 'image/png')
```

## File System

### Android Media Storage

Android 10 introduced scoped storage and thus new APIs to store files to Documents, Downloads, Music and other collections. Version 0.14.0 introduced an API to access files in the Media Store but also to create and write to new files in the Media Store. In general you only can access files in the Media Store created by your app, or selected by a picker.

#### CopyToMediaStore

Copies an existing file from the internal Storage to the Media Store. <br> An example for downloading a file and storing it to the `downloads` collection

```js
ReactNativeBlobUtil
        .config({
            fileCache: true
        })
        .fetch('GET', 'https://example.de/image.png')
        .then(async (res) => {
            let result = await ReactNativeBlobUtil.MediaCollection.copyToMediaStore({
                        name: filename, // name of the file
                        parentFolder: '', // subdirectory in the Media Store, e.g. HawkIntech/Files to create a folder HawkIntech with a subfolder Files and save the image within this folder
                        mimeType: 'image/png' // MIME type of the file
                    },
                    'Download', // Media Collection to store the file in ("Audio" | "Image" | "Video" | "Download")
                    res.path() // Path to the file being copied in the apps own storage
            );
        });
```

This example is taking advantage of the fileCache option to directly store the downloaded file and get a path for. <br>
Currently it's not possible to write data directly from a string recevied by fetch, but only to copy it from a file.

#### createMediaFile

Creates a new file in the specified collection without writing any data

````js
let path = await ReactNativeBlobUtil.MediaCollection.createMediafile({
            name: filename, // name of the file
            parentFolder: '', // subdirectory in the Media Store, e.g. HawkIntech/Files to create a folder HawkIntech with a subfolder Files and save the image within this folder
            mimeType: 'image/png' // MIME type of the file
        }, 'Download'// Media Collection to store the file in ("Audio" | "Image" | "Video" | "Download")
);
````

#### writeMediaFile

Writes data from a file in the apps storage to an existing entry of the Media Store
````js
await ReactNativeBlobUtil.MediaCollection.writeToMediafile('content://....', // content uri of the entry in the media storage
        localpath // path to the file that should be copied
);
````

Copies and tranforms data from a file in the apps storage to an existing entry of the Media Store. NOTE: you must set a transformer on the file in order for the transformation to happen (see [Setting a File Transformer](#Setting-A-File-Transformer)).

````js
await ReactNativeBlobUtil.MediaCollection.writeToMediafileWithTransform('content://....', // content uri of the entry in the media storage
        localpath // path to the file that should be copied
);
````

#### copyToInternal
Copies an entry form the media storage to the apps internal storage.
````js
let destpath = ReactNativeBlobUtil.dirs.CacheDir + '/image.png';
await ReactNativeBlobUtil.MediaCollection.copyToInternal('content://....', // content uri of the entry in the media storage
        destpath // path to destination the entry should be copied to
);
````

### File Access

File access APIs were made when developing `v0.5.0`, which helping us write tests, and was not planned to be a part of this module. However, we realized that it's hard to find a great solution to manage cached files, everyone who uses this module may need these APIs for their cases.

Before start using file APIs, we recommend read [Differences between File Source](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#differences-between-file-source) first.

File Access APIs

- [asset (0.6.2)](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#assetfilenamestringstring)
- [dirs](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#dirs)
- [createFile](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#createfilepath-data-encodingpromise)
- [writeFile (0.6.0)](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#writefilepathstring-contentstring--array-encodingstring-appendbooleanpromise)
- writeFileWithTransform
- [appendFile (0.6.0) ](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#appendfilepathstring-contentstring--arraynumber-encodingstring-promisenumber)
- [readFile (0.6.0)](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#readfilepath-encodingpromise)
- readFileWithTransform
- [readStream](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#readstreampath-encoding-buffersize-interval-promisernfbreadstream)
- [hash (0.10.9)](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#hashpath-algorithm-promise)
- [writeStream](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#writestreampathstring-encodingstringpromise)
- [hash](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#hashpath-algorithmpromise)
- [unlink](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#unlinkpathstringpromise)
- [mkdir](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#mkdirpathstringpromise)
- [ls](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#lspathstringpromise)
- [mv](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#mvfromstring-tostringpromise)
- [cp](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#cpsrcstring-deststringpromise)
- [exists](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#existspathstringpromise)
- [isDir](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#isdirpathstringpromise)
- [stat](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#statpathstringpromise)
- [lstat](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#lstatpathstringpromise)
- [scanFile (Android only)](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API#scanfilepathstringpromise-androi-only)

See [File API](https://github.com/RonRadtke/react-native-blob-util/wiki/File-System-Access-API) for more information

### File Stream

In `v0.5.0` we've added  `writeStream` and `readStream`, which allows your app read/write data from the file path. This API creates a file stream, rather than convert entire data into BASE64 encoded string. It's handy when processing **large files**.

When calling `readStream` method, you have to `open` the stream, and start to read data. When the file is large, consider using an appropriate `bufferSize` and `interval` to reduce the native event dispatching overhead (see [Performance Tips](#user-content-performance-tips))

> The file stream event has a default throttle(10ms) and buffer size which preventing it cause too much overhead to main thread, you can also [tweak these values](#user-content-performance-tips).

```js
let data = ''
ReactNativeBlobUtil.fs.readStream(
        // file path
        PATH_TO_THE_FILE,
        // encoding, should be one of `base64`, `utf8`, `ascii`
        'base64',
        // (optional) buffer size, default to 4096 (4095 for BASE64 encoded data)
        // when reading file in BASE64 encoding, buffer size must be multiples of 3.
        4095)
        .then((ifstream) => {
            ifstream.open()
            ifstream.onData((chunk) => {
                // when encoding is `ascii`, chunk will be an array contains numbers
                // otherwise it will be a string
                data += chunk
            })
            ifstream.onError((err) => {
                console.log('oops', err)
            })
            ifstream.onEnd(() => {
                <Image source={{uri: 'data:image/png,base64' + data}}
    })
            })
```

When using `writeStream`, the stream object becomes writable, and you can then perform operations like `write` and `close`.

Since version 0.10.9 `write()` resolves with the `ReactNativeBlobUtil` instance so you can promise-chain write calls:

```js
ReactNativeBlobUtil.fs.writeStream(
        PATH_TO_FILE,
        // encoding, should be one of `base64`, `utf8`, `ascii`
        'utf8',
        // should data append to existing content ?
        true
)
        .then(ofstream => ofstream.write('foo'))
        .then(ofstream => ofstream.write('bar'))
        .then(ofstream => ofstream.write('foobar'))
        .then(ofstream => ofstream.close())
        .catch(console.error)
```

or

```js
ReactNativeBlobUtil.fs.writeStream(
        PATH_TO_FILE,
        // encoding, should be one of `base64`, `utf8`, `ascii`
        'utf8',
        // should data append to existing content ?
        true
)
        .then(stream => Promise.all([
            stream.write('foo'),
            stream.write('bar'),
            stream.write('foobar')
        ]))
        // Use array destructuring to get the stream object from the first item of the array we get from Promise.all()
        .then(([stream]) => stream.close())
        .catch(console.error)
```

You should **NOT** do something like this:

```js
ReactNativeBlobUtil.fs.writeStream(
        PATH_TO_FILE,
        // encoding, should be one of `base64`, `utf8`, `ascii`
        'utf8',
        // should data append to existing content ?
        true)
        .then((ofstream) => {
            // BAD IDEA - Don't do this, those writes are unchecked:
            ofstream.write('foo')
            ofstream.write('bar')
            ofstream.close()
        })
        .catch(console.error)  // Cannot catch any write() errors!
```

The problem with the above code is that the promises from the `ofstream.write()` calls are detached and "Lost". That means the entire promise chain A) resolves without waiting for the writes to finish and B) any errors caused by them are lost. That code may _seem_ to work if there are no errors, but those writes are of the type "fire and forget": You start them and then turn away and never know if they really succeeded.

### Cache File Management

When using `fileCache` or `path` options along with `fetch` API, response data will automatically store into the file system. The files will **NOT** removed unless you `unlink` it. There're several ways to remove the files

```js

// remove file using ReactNativeBlobUtilResponse.flush() object method
ReactNativeBlobUtil.config({
    fileCache: true
})
        .fetch('GET', 'http://example.com/download/file')
        .then((res) => {
            // remove cached file from storage
            res.flush()
        })

// remove file by specifying a path
ReactNativeBlobUtil.fs.unlink('some-file-path').then(() => {
    // ...
})

```

You can also group requests by using `session` API and use `dispose` to remove them all when needed.

```js

ReactNativeBlobUtil.config({
    fileCache: true
})
        .fetch('GET', 'http://example.com/download/file')
        .then((res) => {
            // set session of a response
            res.session('foo')
        })

ReactNativeBlobUtil.config({
    // you can also set session beforehand
    session: 'foo'
    fileCache: true
})
        .fetch('GET', 'http://example.com/download/file')
        .then((res) => {
            // ...
        })

// or put an existing file path to the session
ReactNativeBlobUtil.session('foo').add('some-file-path')
// remove a file path from the session
ReactNativeBlobUtil.session('foo').remove('some-file-path')
// list paths of a session
ReactNativeBlobUtil.session('foo').list()
// remove all files in a session
ReactNativeBlobUtil.session('foo').dispose().then(() => { ...
})

```

### Transfer Encoding

After `0.9.4`, the `Chunked` transfer encoding is disabled by default due to some service provider may not support chunked transfer. To enable it, set `Transfer-Encoding` header to `Chunked`.

```js
ReactNativeBlobUtil.fetch('POST', 'http://example.com/upload', {'Transfer-Encoding': 'Chunked'}, bodyData)
```

### Self-Signed SSL Server

By default, react-native-blob-util does NOT allow connection to unknown certification provider since it's dangerous. To connect a server with self-signed certification, you need to add `trusty` to `config` explicitly. This function is available for version >= `0.5.3`
In addition since ``0.16.0`` you'll have to define your own trust manager for android.
````java
....
import com.ReactNativeBlobUtil.ReactNativeBlobUtilUtils;
...

public class MainApplication extends Application implements ReactApplication {
    ...
    @Override
    public void onCreate() {
       ...
        ReactNativeBlobUtilUtils.sharedTrustManager = x509TrustManager = new X509TrustManager() {
                @Override
                public void checkClientTrusted(java.security.cert.X509Certificate[] chain, String authType) throws CertificateException {
                }

                @Override
                public void checkServerTrusted(java.security.cert.X509Certificate[] chain, String authType) throws CertificateException {
                }

                @Override
                public java.security.cert.X509Certificate[] getAcceptedIssuers() {
                    return new java.security.cert.X509Certificate[]{};
                }
        };
        ...
    }
````

#### Kotlin
````kotlin
....
import com.ReactNativeBlobUtil.ReactNativeBlobUtilUtils;
import javax.net.ssl.X509TrustManager
...

public class MainApplication extends Application implements ReactApplication {
    ...
    public void onCreate() {
       ...
        ReactNativeBlobUtilUtils.sharedTrustManager = object : X509TrustManager {
          override fun checkClientTrusted(chain: Array<java.security.cert.X509Certificate>, authType: String) {}

          override fun checkServerTrusted(chain: Array<java.security.cert.X509Certificate>, authType: String) {}

          override fun getAcceptedIssuers(): Array<java.security.cert.X509Certificate> {
            return arrayOf()
          }
        };
        ...
    }
````

```js
ReactNativeBlobUtil.config({
    trusty: true
})
        .fetch('GET', 'https://mysite.com')
        .then((resp) => {
            // ...
        })
```

### WiFi only requests

If you wish to only route requests through the Wifi interface, set the below configuration. Note: On Android, the `ACCESS_NETWORK_STATE` permission must be set, and this flag will only work on API version 21 (Lollipop, Android 5.0) or above. APIs below 21 will ignore this flag.

```js
ReactNativeBlobUtil.config({
    wifiOnly: true
})
        .fetch('GET', 'https://mysite.com')
        .then((resp) => {
            // ...
        })
```

### Transform Files

Sometimes you may need the files to be transformed after reading from storage or before writing into storage (eg encryption/decyrption). In order to perform the transformations, use `readFileWithTransform` and `writeFileWithTransform`. NOTE: you must set a transformer on the file in order for the transformation to happen (see [Setting a File Transformer](#Setting-A-File-Transformer)).

## Web API Polyfills

After `0.8.0` we've made some [Web API polyfills](https://github.com/RonRadtke/react-native-blob-util/wiki/Web-API-Polyfills-(experimental)) that makes some browser-based library available in RN.

- Blob
- XMLHttpRequest (Use our implementation if you're going to use it with Blob)


## Setting A File Transformer

Setting a file transformer will allow you to specify how data should be transformed whenever the library is writing into storage or reading from storage. A use case for this is if you want the files handled by this library to be encrypted.

If you want to use a file transformer, you must implement an interface defined in:

[ReactNativeBlobUtilFileTransformer.h (iOS)](/ios/ReactNativeBlobUtilFileTransformer.h)

[ReactNativeBlobUtilFileTransformer.java (Android)](/android/src/main/java/com/ReactNativeBlobUtil/ReactNativeBlobUtilFileTransformer.java)

Then you set the File Transformer during app startup

Android:
```java
public class MainApplication extends Application implements ReactApplication {
    ...
    @Override
    public void onCreate() {
       ...
       ReactNativeBlobUtilFileTransformer.sharedFileTransformer = new MyCustomEncryptor();
       ...
    }
```

iOS:
```m
@implementation AppDelegate
...
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    ...
    [ReactNativeBlobUtilFileTransformer setFileTransformer: MyCustomEncryptor.new];
    ...
}
```

Here are the places where the transformer would apply
- Reading a file from the file system
- Writing a file into the file system
- Http response is downloaded to storage directly

## Performance Tips

**Read Stream and Progress Event Overhead**

If the process seems to block JS thread when file is large when reading data via `fs.readStream`. It might because the default buffer size is quite small (4kb) which result in a lot of events triggered from JS thread. Try to increase the buffer size (for example 100kb = 102400) and set a larger interval (available for 0.9.4+, the default value is 10ms) to limit the frequency.

**Reduce RCT Bridge and BASE64 Overhead**

React Native connects JS and Native context by passing JSON around React Native bridge, and there will be an overhead to convert data before they sent to each side. When data is large, this will be quite a performance impact to your app. It's recommended to use file storage instead of BASE64 if possible.The following chart shows how much faster when loading data from storage than BASE64 encoded string on iPhone 6.

<img src="img/performance_1.png" style="width : 100%"/>

**ASCII Encoding has /terrible Performance**

Due to the [lack of typed array implementation in JavascriptCore, and limitation of React Native structure](https://github.com/facebook/react-native/issues/1424), to convert data to JS byte array spends lot of time. Use it only when needed, the following chart shows how much time it takes when reading a file with different encoding.

<img src="img/performance_encoding.png" style="width : 100%"/>

**Concat and Replacing Files**

If you're going to concatenate files, you don't have to read the data to JS context anymore! In `0.8.0` we introduced new encoding `uri` for writeFile and appendFile API, which make it possible to handle the whole process in native.

<img src="img/performance_f2f.png" style="width : 100%"/>

## Caveats

* This library does not urlencode unicode characters in URL automatically, see [#146](https://github.com/wkh237/react-native-fetch-blob/issues/146).
* When you create a `Blob` , from an existing file, the file **WILL BE REMOVED** if you `close` the blob.
* If you replaced `window.XMLHttpRequest` for some reason (e.g. make Firebase SDK work), it will also affect how official `fetch` works (basically it should work just fine).
* When file stream and upload/download progress event slow down your app, consider an upgrade to `0.9.6+`, use [additional arguments](https://github.com/RonRadtke/react-native-blob-util/wiki/Fetch-API#fetchprogressconfig-eventlistenerpromiseReactNativeBlobUtilresponse) to limit its frequency.
* When passing a file path to the library, remove `file://` prefix.

when you got a problem, have a look at [Trouble Shooting](https://github.com/RonRadtke/react-native-blob-util/wiki/Trouble-Shooting).

## Changes

See [release notes](https://github.com/RonRadtke/react-native-blob-util/releases)

### Development

If you're interested in hacking this module, check our [development guide](https://github.com/RonRadtke/react-native-blob-util/wiki/Home), there might be some helpful information. Please feel free to make a PR or file an issue.
