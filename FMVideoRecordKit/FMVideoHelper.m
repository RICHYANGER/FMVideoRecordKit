//
//  FMVideoHelper.m
//  BroadcastUploadNew
//
//  Created by RICH on 2019/10/17.
//  Copyright © 2019 Anirban. All rights reserved.
//

#import "FMVideoHelper.h"

@implementation FMVideoHelper

//              标清                      高清                        超高清
//              比特率：12 * 100 * 1000    20 * 100 * 1000 * 1.5      25 * 100 * 1000 * 1.5
//              分辨率：     432*768             720*1280                   720*1280
//              帧率  ：      15                    25                         25
//   ProfileLevelKey ：  Main Level 3         Main Level 3.1             Main Level 4.1
+ (NSDictionary *)getVideoOutputSettingsWithVideoDefinition:(FMVideoRecordDefinition)definition {
    
    CGSize size = [UIScreen mainScreen].bounds.size;
    size = CGSizeMake(size.width * 2, size.height * 2);
    
    NSDictionary *compressionProperties;
    if (definition == FMVideoRecordStandardDefinition) {
        // 标清
        compressionProperties = @{ AVVideoAverageBitRateKey : @(12 * 100 * 1000),
                                                 AVVideoExpectedSourceFrameRateKey : @(15),
                                                 AVVideoMaxKeyFrameIntervalKey : @(15),
                                                 AVVideoProfileLevelKey : AVVideoProfileLevelH264Main30
                                                 };


    }else if (definition == FMVideoRecordHighDefinition) {
        // 高清
        compressionProperties = @{ AVVideoAverageBitRateKey : @(20 * 100 * 1000 * 1.5),
                                                 AVVideoExpectedSourceFrameRateKey : @(25),
                                                 AVVideoMaxKeyFrameIntervalKey : @(25),
                                                 AVVideoProfileLevelKey : AVVideoProfileLevelH264Main31
                                                 };
    }else {
        // 超清
        compressionProperties = @{ AVVideoAverageBitRateKey : @(25 * 100 * 1000 * 1.5),
                                                 AVVideoExpectedSourceFrameRateKey : @(25),
                                                 AVVideoMaxKeyFrameIntervalKey : @(25),
                                                 AVVideoProfileLevelKey : AVVideoProfileLevelH264High41
                                                 };

    }
    return @{AVVideoCodecKey : AVVideoCodecTypeH264,
             AVVideoScalingModeKey : AVVideoScalingModeResizeAspectFill,
             AVVideoWidthKey : @(size.width),
             AVVideoHeightKey : @(size.height),
             AVVideoCompressionPropertiesKey : compressionProperties};
}

+ (NSDictionary *)getAudioOutputSettings{
   return @{
            AVSampleRateKey : @(44100),
            AVFormatIDKey : @(kAudioFormatMPEG4AAC_HE),
            AVNumberOfChannelsKey : @(1)
            };
}

@end
