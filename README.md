# FMVideoRecordKit

[![CI Status](https://img.shields.io/travis/907689522@qq.com/FMVideoRecordKit.svg?style=flat)](https://travis-ci.org/907689522@qq.com/FMVideoRecordKit)
[![Version](https://img.shields.io/cocoapods/v/FMVideoRecordKit.svg?style=flat)](https://cocoapods.org/pods/FMVideoRecordKit)
[![License](https://img.shields.io/cocoapods/l/FMVideoRecordKit.svg?style=flat)](https://cocoapods.org/pods/FMVideoRecordKit)
[![Platform](https://img.shields.io/cocoapods/p/FMVideoRecordKit.svg?style=flat)](https://cocoapods.org/pods/FMVideoRecordKit)

iOS视频录制工具类

## Example

To run the example project, clone the repo, and run `pod install` from the Example directory first.

## 使用方法
* #import "FMVideoRecordKit.h" 即可使用

```objc
- (void)broadcastStartedWithSetupInfo:(NSDictionary<NSString *,NSObject *> *)setupInfo {
    // User has requested to start the broadcast. Setup info from the UI extension can be supplied but optional.
    NSLog(@"%s", __func__);
    NSLog(@"开始录制 :%@", setupInfo);
    
    NSError *error = nil;
    [self.assetVideoWriter startWritingWithError:&error];
}


- (void)broadcastPaused {
    // User has requested to pause the broadcast. Samples will stop being delivered.
    NSLog(@"%s", __func__);
}

- (void)broadcastResumed {
    // User has requested to resume the broadcast. Samples delivery will resume.
    NSLog(@"%s", __func__);
}

- (void)broadcastFinished {
    NSLog(@"%s", __func__);
    
    // User has requested to finish the broadcast.
    NSLog(@"结束录制");
    NSError *error = nil;
    [self.assetVideoWriter stopWritingWithError:&error];
}

- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType {
    NSError *error = nil;
    [self.assetVideoWriter writeVideoBuffer:sampleBuffer bufferType:sampleBufferType error:&error];
        switch (sampleBufferType) {
            case RPSampleBufferTypeVideo:
                // Handle video sample buffer
    //            [encoder encode:sampleBuffer];
                break;
            case RPSampleBufferTypeAudioApp:
                // Handle audio sample buffer for app audio
                break;
            case RPSampleBufferTypeAudioMic:
                // Handle audio sample buffer for mic audio
                break;
                
            default:
                break;
        }
}

- (void)finishBroadcastWithError:(NSError *)error {
    NSLog(@"%s", __func__);
    NSLog(@"结束录制 error:%@", error);
}

-  (FMVideoWriter *)assetVideoWriter {
    if (!_assetVideoWriter) {
        _assetVideoWriter = [[FMVideoWriter alloc] initWithDispatchQueue:dispatch_queue_create("com.feimo.ReplayKit.VideoWriteQueue", DISPATCH_QUEUE_SERIAL)
                                                           VideoDefition:FMVideoRecordSuperDefinition RecordVideoOrientation:FMVideoRecordPortraitOrientation
                                                              OutputPath:[FMVideoHelper getAppGroupFilePath]];
    }
    return _assetVideoWriter;
}
```

## Installation
FMVideoRecordKit is available through [CocoaPods](https://cocoapods.org). To install
it, simply add the following line to your Podfile:

```ruby
pod 'FMVideoRecordKit'
```

## Author

rich,  richyounger@163.com

## License

FMVideoRecordKit is available under the MIT license. See the LICENSE file for more info.
