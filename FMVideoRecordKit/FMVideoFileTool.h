//
//  FMVideoFileTool.h
//  BroadcastUploadNew
//
//  Created by RICH on 2019/10/17.
//  Copyright © 2019 Anirban. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface FMVideoFileTool : NSObject

/**
Save pictures to fixed albums

@param image target image
@param completionHandler result returned
 */
+ (void)saveImage:(UIImage *)image toMyAlbumCompletionHandler:(void(^)(BOOL success))completionHandler;
+ (void)saveImages:(NSArray<UIImage *>*)images toAlbum:(nullable NSString *)albumName completionHandler:(void(^)(BOOL success))completionHandler;

/**
Save pictures to the specified album folder

@param image Image object to be stored
@param albumName the name of the album to be stored,nil means stored in the system Gallery
@param completionHandler saves the result callback
 */
+ (void)saveImage:(UIImage *)image toAlbum:(nullable NSString *)albumName completionHandler:(void(^)(BOOL success))completionHandler;

/**
Save pictures to the specified album folder

@param path image path
@param albumName album name
@param completionHandler saves the result callback
 */
+ (void)saveImageWithPath:(NSString *)path albumName:(nullable NSString *)albumName completionHandler:(void(^)(BOOL success))completionHandler;

/**
Save the video to the specified album file
@param videoUrl video URL address
@param completionHandler result returned
*/
+ (void)saveVideo:(NSURL *)videoUrl toMyAlbumcompletionHandler:(void(^)(BOOL success))completionHandler;
+ (void)saveVideo:(NSURL *)videoUrl toAlbumName:(nullable NSString *)albumName completionHandler:(void(^)(BOOL success))completionHandler;

/**
Request album access

@param block result returned
 */
+ (void)requestPhotoAuthorizationBlock:(void(^)(BOOL hasAuthorize))block;

@end

NS_ASSUME_NONNULL_END
