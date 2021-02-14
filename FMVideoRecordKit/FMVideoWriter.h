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
/**  Whether data is being written */
@property (nonatomic, assign, readonly) BOOL isWriting;
/** Whether to record speaker audio, default YES, valid after iOS11 */
@property (nonatomic, assign) BOOL recordAudioMic;
/** Whether to record video and audio, default YES, iOS11 is valid after */
@property (nonatomic, assign) BOOL recordVideoSound;

// Initialization method
// @param dispatchQueue serial queue
// @param videoSettings video parameters
// @param audioSettings audio parameters
// @param orientation record video orientation
- (id)initWithDispatchQueue:(dispatch_queue_t)dispatchQueue
              VideoSettings:(NSDictionary *)videoSettings
              audioSettings:(NSDictionary *)audioSettings
     RecordVideoOrientation:(FMVideoRecordOrientation)orientation
                 OutputPath:(NSString *)outputPath;

// Initialization method
// @param dispatchQueue serial queue
// @param defition video clarity
// @param orientation record video orientation
// @param outputPath video output path
- (id)initWithDispatchQueue:(dispatch_queue_t)dispatchQueue
              VideoDefition:(FMVideoRecordDefinition)defition
     RecordVideoOrientation:(FMVideoRecordOrientation)orientation
                 OutputPath:(NSString *)outputPath;;

// Turn on screen recording data writing
- (void)startWritingWithError:(NSError **)error;

// Stop recording data writing
- (void)stopWritingWithError:(NSError **)error;

// Write screen recording data to a file
//  @param sampleBuffer recording screen buffer
- (void)writeVideoBuffer:(CMSampleBufferRef)sampleBuffer bufferType:(RPSampleBufferType)bufferType error:(NSError **)error API_AVAILABLE(ios(10.0)) API_AVAILABLE(ios(10.0));;

@end
