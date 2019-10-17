//
//  FMVideoHelper.h
//  BroadcastUploadNew
//
//  Created by RICH on 2019/10/17.
//  Copyright © 2019 Anirban. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMVideoConstant.h"
NS_ASSUME_NONNULL_BEGIN

@interface FMVideoHelper : NSObject

+ (NSDictionary *)getVideoOutputSettingsWithVideoDefinition:(FMVideoRecordDefinition)definition;
+ (NSDictionary *)getAudioOutputSettings;

@end

NS_ASSUME_NONNULL_END
