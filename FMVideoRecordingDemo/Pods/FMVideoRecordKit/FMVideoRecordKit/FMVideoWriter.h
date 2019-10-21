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
/**  是否正在写入数据 */
@property (nonatomic, assign, readonly) BOOL isWriting;
/** 是否录制扬声器音频 ,默认YES, iOS11以后有效 */
@property (nonatomic, assign) BOOL recordAudioMic;
/** 是否录制视频音频 ,默认YES,  iOS11以后有效 */
@property (nonatomic, assign) BOOL recordVideoSound;

// 初始化方法
// @param dispatchQueue 串行队列
// @param videoSettings 视频参数
// @param audioSettings 音频参数
// @param orientation 录制视频方向
- (id)initWithDispatchQueue:(dispatch_queue_t)dispatchQueue
              VideoSettings:(NSDictionary *)videoSettings
              audioSettings:(NSDictionary *)audioSettings
     RecordVideoOrientation:(FMVideoRecordOrientation)orientation
                 OutputPath:(NSString *)outputPath;

// 初始化方法
// @param dispatchQueue 串行队列
// @param defition 视频清晰度
// @param orientation 录制视频方向
// @param outputPath 视频输出路径
- (id)initWithDispatchQueue:(dispatch_queue_t)dispatchQueue
              VideoDefition:(FMVideoRecordDefinition)defition
     RecordVideoOrientation:(FMVideoRecordOrientation)orientation
                 OutputPath:(NSString *)outputPath;;

// 开启录屏数据写入
- (void)startWritingWithError:(NSError **)error;

// 停止录屏数据写入
- (void)stopWritingWithError:(NSError **)error;

// 将录屏数据写入文件
// @param sampleBuffer 录屏buffer
- (void)writeVideoBuffer:(CMSampleBufferRef)sampleBuffer bufferType:(RPSampleBufferType)bufferType error:(NSError **)error API_AVAILABLE(ios(10.0)) API_AVAILABLE(ios(10.0));;

@end
