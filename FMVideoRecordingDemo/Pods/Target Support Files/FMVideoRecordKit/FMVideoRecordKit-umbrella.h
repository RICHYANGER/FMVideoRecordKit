#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "FMVideoConstant.h"
#import "FMVideoFileTool.h"
#import "FMVideoHelper.h"
#import "FMVideoRecordKit.h"
#import "FMVideoWriter.h"

FOUNDATION_EXPORT double FMVideoRecordKitVersionNumber;
FOUNDATION_EXPORT const unsigned char FMVideoRecordKitVersionString[];

