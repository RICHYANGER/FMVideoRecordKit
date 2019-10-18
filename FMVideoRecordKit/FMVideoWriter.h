//
//  FMVideoWriter.h
//  BroadcastUploadNew
//
//  Created by RICH on 2019/10/16.
//  Copyright © 2019 Anirban. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ReplayKit/ReplayKit.h>
#import "FMVideoConstant.h"

@class FMVideoWriter;

@protocol videoWriterDelegate <NSObject>

- (void)videoWriter:(FMVideoWriter *)videoWriter didOutputVideoAtPath:(NSURL *)url;

@end

@interface FMVideoWriter : NSObject

@property (weak, nonatomic) id<videoWriterDelegate> delegate;
@property (nonatomic, assign) BOOL isWriting;


// 初始化方法
// @param videoSettings 视频参数
// @param audioSettings 音频参数
// @param dispatchQueue 异步队列
// @param orientation 设备方向
- (id)initWithDispatchQueue:(dispatch_queue_t)dispatchQueue VideoSettings:(NSDictionary *)videoSettings audioSettings:(NSDictionary *)audioSettings  RecordVideoOrientation:(FMVideoRecordOrientation)orientation;

- (id)initWithDispatchQueue:(dispatch_queue_t)dispatchQueue VideoDefition:(FMVideoRecordDefinition)defition  RecordVideoOrientation:(FMVideoRecordOrientation)orientation;

// 开启录屏数据写入
// @param error <#error description#>
- (void)startWritingWithError:(NSError **)error;

// 停止录屏数据写入
// @param error <#error description#>
- (void)stopWritingWithError:(NSError **)error;

// 将录屏数据写入文件
// @param sampleBuffer 录屏buffer
// @param bufferType <#bufferType description#>
// @param error <#error description#>
- (void)writeVideoBuffer:(CMSampleBufferRef)sampleBuffer bufferType:(RPSampleBufferType)bufferType error:(NSError **)error API_AVAILABLE(ios(10.0)) API_AVAILABLE(ios(10.0));;

@end
