//
//  FMVideoConstant.h
//  BroadcastUploadNew
//
//  Created by RICH on 2019/10/16.
//  Copyright © 2019 Anirban. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

// Error domain
UIKIT_EXTERN NSString *const FMVideoRecoderErrorDomain;
// Album name
UIKIT_EXTERN NSString *const FMALBUM;
// APPGroup identity
UIKIT_EXTERN NSString * const FMGroupIdentifier;
// Custom folders under shared directories
UIKIT_EXTERN NSString * const FMGroupDirName;
// File names in shared directories
UIKIT_EXTERN NSString * const FMRepKitFileName;



// Error code
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

// Video clarity
typedef NS_ENUM(NSInteger, FMVideoRecordDefinition) {
    
    FMVideoRecordStandardDefinition       = 1,    // Standard definition
    FMVideoRecordHighDefinition           = 2,    // HD
    FMVideoRecordSuperDefinition          = 3     // Super clear
};

// Video recording direction
typedef NS_ENUM(NSInteger, FMVideoRecordOrientation) {
    
    FMVideoRecordPortraitOrientation    = 1, // Vertical screen
    FMVideoRecordLandscapeOrientation   = 2, // Landscape screen
};

NS_INLINE NSError* FMVideoRecoderError(NSString *description,FMVideoRecoderErrorCode code)
{
    NSDictionary *userInfo = @{NSLocalizedDescriptionKey : description};
    NSError *error = [NSError errorWithDomain:FMVideoRecoderErrorDomain code:code userInfo:userInfo];
    return error;
}
