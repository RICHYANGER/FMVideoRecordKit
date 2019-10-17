//
//  FMVideoConstant.h
//  BroadcastUploadNew
//
//  Created by RICH on 2019/10/16.
//  Copyright © 2019 Anirban. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

// 错误域
UIKIT_EXTERN NSString * const FMVideoRecoderErrorDomain;
// 相册名
UIKIT_EXTERN NSString * const FMALBUM;
// APPGroup标识
UIKIT_EXTERN NSString * const FMGroupIdentifier;
// 共享目录下自定义文件夹
UIKIT_EXTERN NSString * const FMGroupDirName;
// 共享目录下的文件名
UIKIT_EXTERN NSString * const FMRepKitFileName;


// 错误码
typedef NS_ENUM(NSInteger, FMVideoRecoderErrorCode) {
    
    FMVideoRecoderErrorFailedToAddVideoInput  = 1000,
    FMVideoRecoderErrorFailedToAddAudioInput  = 1001,
    
    FMVideoRecoderErrorFailedToAddVideoOutput = 2000,
    FMVideoRecoderErrorFailedToAddAudioOutput = 2000,
    
    FMVideoRecoderErrorFailedToSwitchCameras      = 3000,
    FMVideoRecoderErrorFailedToFocusAndExposure = 3001,
    
    FMVideoRecoderErrorFailedToCreatWriter      = 4000,
    FMVideoRecoderErrorFailedToStartwriting   = 4001,
    FMVideoRecoderErrorFailedToCreatePixelBuffer = 4002,
    FMVideoRecoderErrorFailedToAppendVideoBuffer = 4003,
    FMVideoRecoderErrorFailedToAppendAudioBuffer = 4004,
    
    FMVideoRecoderErrorFailedToAddVideoInputWriter = 5000,
    FMVideoRecoderErrorFailedToAddAudioInputWriter = 5001,
    
};

// 视频清晰度
typedef NS_ENUM(NSInteger, FMVideoRecordDefinition) {
    
    FMVideoRecordStandardDefinition       = 1,    // 标清
    FMVideoRecordHighDefinition           = 2,    // 高清
    FMVideoRecordSuperDefinition          = 3     // 超清
};

// 视频录屏方向
typedef NS_ENUM(NSInteger, FMVideoRecordOrientation) {
    
    FMVideoRecordPortraitOrientation    = 1, // 竖屏
    FMVideoRecordLandscapeOrientation   = 2, // 横屏
};

NS_INLINE NSError* FMVideoRecoderError(NSString *description,FMVideoRecoderErrorCode code)
{
    NSDictionary *userInfo = @{NSLocalizedDescriptionKey : description};
    NSError *error = [NSError errorWithDomain:FMVideoRecoderErrorDomain code:code userInfo:userInfo];
    return error;
}
