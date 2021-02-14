//
//  FMVideoHelper.m
//  BroadcastUploadNew
//
//  Created by RICH on 2019/10/17.
//  Copyright © 2019 Anirban. All rights reserved.
//

#import "FMVideoHelper.h"

@implementation FMVideoHelper
//              SD                        HD                         Ultra HD
//         Bit rate：   12 * 100 * 1000   20 * 100 * 1000 * 1.5      25 * 100 * 1000 * 1.5
//       Resolution：     432*768           720*1280                   720*1280
//       Frame rate:         15                25                           25
//   ProfileLevelKey ：  Main Level 3         Main Level 3.1             Main Level 4.1
+ (NSDictionary *)getVideoOutputSettingsWithVideoDefinition:(FMVideoRecordDefinition)definition {
    
    CGSize size = [UIScreen mainScreen].bounds.size;
    size = CGSizeMake(size.width * 2, size.height * 2);
    
    NSDictionary *compressionProperties;
    if (definition == FMVideoRecordStandardDefinition) {
        // Standard definition
        compressionProperties = @{ AVVideoAverageBitRateKey : @(12 * 100 * 1000),
                                                 AVVideoExpectedSourceFrameRateKey : @(15),
                                                 AVVideoMaxKeyFrameIntervalKey : @(15),
                                                 AVVideoProfileLevelKey : AVVideoProfileLevelH264Main30
                                                 };


    }else if (definition == FMVideoRecordHighDefinition) {
        // HD
        compressionProperties = @{ AVVideoAverageBitRateKey : @(20 * 100 * 1000 * 1.5),
                                                 AVVideoExpectedSourceFrameRateKey : @(25),
                                                 AVVideoMaxKeyFrameIntervalKey : @(25),
                                                 AVVideoProfileLevelKey : AVVideoProfileLevelH264Main31
                                                 };
    }else {
        // Super clear
        compressionProperties = @{ AVVideoAverageBitRateKey : @(25 * 100 * 1000 * 1.5),
                                                 AVVideoExpectedSourceFrameRateKey : @(25),
                                                 AVVideoMaxKeyFrameIntervalKey : @(25),
                                                 AVVideoProfileLevelKey : AVVideoProfileLevelH264High41
                                                 };

    }
    if (@available(iOS 11.0, *)) {
        return @{AVVideoCodecKey : AVVideoCodecTypeH264,
                 AVVideoScalingModeKey : AVVideoScalingModeResizeAspectFill,
                 AVVideoWidthKey : @(size.width),
                 AVVideoHeightKey : @(size.height),
                 AVVideoCompressionPropertiesKey : compressionProperties};
    } else {
        // Fallback on earlier versions
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wdeprecated-declarations"
        return @{AVVideoCodecKey : AVVideoCodecH264,
                 AVVideoScalingModeKey : AVVideoScalingModeResizeAspectFill,
                 AVVideoWidthKey : @(size.width),
                 AVVideoHeightKey : @(size.height),
                 AVVideoCompressionPropertiesKey : compressionProperties
                 
                };
        #pragma clang diagnostic pop
    }
}

+ (NSDictionary *)getAudioOutputSettings {
   return @{
            AVSampleRateKey : @(44100),
            AVFormatIDKey : @(kAudioFormatMPEG4AAC_HE),
            AVNumberOfChannelsKey : @(1)
            };
}

// AppGroup shared directory file path
+ (NSString *)getAppGroupFilePath {

    NSString *path = [[NSFileManager defaultManager] containerURLForSecurityApplicationGroupIdentifier:FMGroupIdentifier].path;
    NSString *fullPathWrite  = [path stringByAppendingPathComponent:FMGroupDirName];

    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:fullPathWrite]) {
       [fileManager createDirectoryAtPath:fullPathWrite withIntermediateDirectories:NO attributes:nil error:nil];
    }
    NSString *appGroupFilePath = [fullPathWrite stringByAppendingPathComponent:FMRepKitFileName];
    if ([[NSFileManager defaultManager] fileExistsAtPath:appGroupFilePath]) {
        [[NSFileManager defaultManager] removeItemAtPath:appGroupFilePath error:nil];
    }
    return appGroupFilePath;
}

@end
