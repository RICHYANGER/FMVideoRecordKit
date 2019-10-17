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
 将图片存入固定相册
 
 @param image 目标图片
 @param completionHandler 结果返回
 */
+ (void)saveImage:(UIImage *)image toMyAlbumCompletionHandler:(void(^)(BOOL success))completionHandler;
+ (void)saveImages:(NSArray<UIImage *>*)images toAlbum:(nullable NSString *)albumName completionHandler:(void(^)(BOOL success))completionHandler;

/**
 将图片存入指定的相册文件夹
 
 @param image 要存入的图片对象
 @param albumName 要存入的相册名称,nil表示存入系统图库
 @param completionHandler 存入结果回调
 */
+ (void)saveImage:(UIImage *)image toAlbum:(nullable NSString *)albumName completionHandler:(void(^)(BOOL success))completionHandler;

/**
 将图片存入指定相册文件夹
 
 @param path 图片路径
 @param albumName 相册名称
 @param completionHandler 存入结果回调
 */
+ (void)saveImageWithPath:(NSString *)path albumName:(nullable NSString *)albumName completionHandler:(void(^)(BOOL success))completionHandler;

/**
将视频存入指定相册文件
 @param videoUrl 视频URL地址
 @param completionHandler 结果返回
*/
+ (void)saveVideo:(NSURL *)videoUrl toMyAlbumcompletionHandler:(void(^)(BOOL success))completionHandler;
+ (void)saveVideo:(NSURL *)videoUrl toAlbumName:(nullable NSString *)albumName completionHandler:(void(^)(BOOL success))completionHandler;

/**
 请求相册访问权限
 
 @param block 结果返回
 */
+ (void)requestPhotoAuthorizationBlock:(void(^)(BOOL hasAuthorize))block;

@end

NS_ASSUME_NONNULL_END
