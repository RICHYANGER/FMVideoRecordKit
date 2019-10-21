//
//  FMVideoFileTool.m
//  BroadcastUploadNew
//
//  Created by RICH on 2019/10/17.
//  Copyright © 2019 Anirban. All rights reserved.
//

#import "FMVideoFileTool.h"
#import "FMVideoConstant.h"
#import <Photos/Photos.h>


@implementation FMVideoFileTool
 // 将图片存入固定相册
+ (void)saveImage:(UIImage *)image toMyAlbumCompletionHandler:(void (^)(BOOL))completionHandler
{
    [self saveImage:image toAlbum:FMALBUM completionHandler:completionHandler];
}


//  将图片存入指定的相册文件夹
+ (void)saveImage:(UIImage *)image toAlbum:(NSString *)albumName completionHandler:(void (^)(BOOL))completionHandler
{
    [self requestPhotoAuthorizationBlock:^(BOOL hasAuthorize) {
       
        if (hasAuthorize) {
            [self photoSaveImages:@[image] toAlbum:albumName completionHandler:completionHandler];
        }else {
            NSLog(@"用户拒绝访问相册");
        }
    }];
}

// 将图片数组写入固定相册
+ (void)saveImages:(NSArray<UIImage *> *)images toAlbum:(NSString *)albumName completionHandler:(void (^)(BOOL))completionHandler {
    [self requestPhotoAuthorizationBlock:^(BOOL hasAuthorize) {
       
        if (hasAuthorize) {
            [self photoSaveImages:images toAlbum:albumName completionHandler:completionHandler];
        }else {
            NSLog(@"用户拒绝访问相册");
        }
    }];
}


// 请求相册访问权限
+ (void)requestPhotoAuthorizationBlock:(void (^)(BOOL))block
{
    // 判断授权状态
    PHAuthorizationStatus status = [PHPhotoLibrary authorizationStatus];
    if (status == PHAuthorizationStatusAuthorized) {
        // 已授权
        if (block) {
//            [self createPhotoWithAlbumName:FMALBUM];
            block(YES);
        }
    }else if(status == PHAuthorizationStatusNotDetermined) {
        // 弹窗请求用户授权
        [PHPhotoLibrary requestAuthorization:^(PHAuthorizationStatus status) {
            if (status == PHAuthorizationStatusAuthorized) {
                if (block) {
//                    [self createPhotoWithAlbumName:FMALBUM];
                    block(YES);
                }
            }
        }];
    }else {
        if (block) {
            block(NO);
        }
    }
}

//  将图片存入指定相册文件夹
+ (void)saveImageWithPath:(NSString *)path albumName:(NSString *)albumName completionHandler:(void (^)(BOOL))completionHandler
{
    [self requestPhotoAuthorizationBlock:^(BOOL hasAuthorize) {
        if (hasAuthorize) {
            UIImage *image = [UIImage imageWithContentsOfFile:path];
            if (image) {
                [self saveImage:image toAlbum:albumName completionHandler:completionHandler];
            }else {
                completionHandler(NO);
            }
        }else {
            NSLog(@"用户拒绝访问相册");
        }
    }];
}

// 将视频存入固定相册文件夹
+ (void)saveVideo:(NSURL *)videoUrl toMyAlbumcompletionHandler:(void (^)(BOOL))completionHandler {
    [self saveVideo:videoUrl toAlbumName:nil completionHandler:completionHandler];
}

// 将视频存入指定相册文件夹
+ (void)saveVideo:(NSURL *)videoUrl toAlbumName:(NSString *)albumName completionHandler:(void (^)(BOOL))completionHandler
{
    [self requestPhotoAuthorizationBlock:^(BOOL hasAuthorize) {
        if (hasAuthorize) {
            __block NSString *localIdentifier = nil;
            [[PHPhotoLibrary sharedPhotoLibrary] performChanges:^{
                PHAssetChangeRequest *changeRequest = [PHAssetChangeRequest creationRequestForAssetFromVideoAtFileURL:videoUrl];
                PHObjectPlaceholder *placeholderAsset = changeRequest.placeholderForCreatedAsset;
                localIdentifier = placeholderAsset.localIdentifier;
            } completionHandler:^(BOOL success, NSError * _Nullable error) {
                if (success) {
                    [self saveVideoToAlbum:albumName localIdentifier:localIdentifier completionHandler:completionHandler];
                }
            }];
        }
    }];
}


#pragma mark  - Private Method
// 保存图片到指定相册
+ (void)photoSaveImages:(NSArray<UIImage *> *)images toAlbum:(NSString *)albumName completionHandler:(void (^)(BOOL))completionHandler
{
    NSMutableArray <NSString *> *identifierArr = [NSMutableArray array];
    [[PHPhotoLibrary sharedPhotoLibrary] performChanges:^{
       
        [images enumerateObjectsUsingBlock:^(UIImage * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            PHAssetChangeRequest *request = [PHAssetChangeRequest creationRequestForAssetFromImage:obj];
            NSString *localIdentifier = request.placeholderForCreatedAsset.localIdentifier;
            if (localIdentifier) {
                [identifierArr addObject:localIdentifier];
            }
        }];
    } completionHandler:^(BOOL success, NSError * _Nullable error) {
        if (success) {
            [self saveImagesWithIdentifierArr:identifierArr toAlbumName:albumName completionHandler:completionHandler];
        }
    }];
}

+ (void)saveImagesWithIdentifierArr:(NSArray <NSString*>*)identifierArr toAlbumName:(nullable NSString *)albumName completionHandler:(void (^)(BOOL))completionHandler
{
    if (identifierArr.count == 0) {
        return;
    }
    if (!albumName) {
        NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
        
        albumName = [infoDictionary objectForKey:@"CFBundleName"];
        if (albumName == nil){
            albumName = FMALBUM;
        }
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        NSError *error = nil;
        PHAssetCollection *collection = nil;
        if (albumName && albumName.length > 0) {
            collection = [self createPhotoWithAlbumName:albumName];
        }
            
        [[PHPhotoLibrary sharedPhotoLibrary] performChangesAndWait:^{
            
            PHAsset *asset = [[PHAsset fetchAssetsWithLocalIdentifiers:identifierArr options:nil] lastObject];
            [[PHAssetCollectionChangeRequest changeRequestForAssetCollection:collection] addAssets:@[asset]];
        } error:&error];
        NSLog(@"error :%@", error);
        
        if (completionHandler) {
            if (error) {
                NSLog(@"保存图片失败!");
                completionHandler(NO);
            }else {
                NSLog(@"保存图片成功!");
                completionHandler(YES);
            }
        }
    });
}


// 创建相册
// @param albumName 相册名
+ (nullable PHAssetCollection *)createPhotoWithAlbumName:(NSString *)albumName
{
    //从已经存在的相簿中查找应用对应的相册
    PHFetchResult <PHAssetCollection *> *assetCollectioins = [PHAssetCollection fetchAssetCollectionsWithType:PHAssetCollectionTypeAlbum subtype:PHAssetCollectionSubtypeAlbumRegular options:nil];
    for (PHAssetCollection *collection in assetCollectioins) {
        if ([collection.localizedTitle isEqualToString:albumName]) {
            return collection;
        }
    }
    
    // 没找到，就创建新的相簿
    NSError *error;
    __block NSString *assetCollectionLocalIdentifier = nil;
    // 这里用wait请求，保证创建成功相册后才保存进去
    [[PHPhotoLibrary sharedPhotoLibrary] performChangesAndWait:^{
        
        assetCollectionLocalIdentifier = [PHAssetCollectionChangeRequest creationRequestForAssetCollectionWithTitle:albumName].placeholderForCreatedAssetCollection.localIdentifier;
        
    } error:&error];
    
    if (error) return nil;
    
    return [PHAssetCollection fetchAssetCollectionsWithLocalIdentifiers:@[assetCollectionLocalIdentifier] options:nil].lastObject;
}

// 保存视频到指定相册
+ (void)saveVideoToAlbum:(nullable NSString *)albumName localIdentifier:(nullable NSString *)localIdentifier completionHandler:(void(^)(BOOL success))completionHandler {
    
    if (!localIdentifier) {
        return;
    }
    if (!albumName) {
        NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
        
        albumName = [infoDictionary objectForKey:@"CFBundleName"];
        if (albumName == nil){
            albumName = FMALBUM;
        }
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        NSError *error = nil;
        PHAssetCollection *collection = nil;
        if (albumName && albumName.length > 0) {
            collection = [self createPhotoWithAlbumName:albumName];
        }
            
        [[PHPhotoLibrary sharedPhotoLibrary] performChangesAndWait:^{
            
            PHAsset *asset = [[PHAsset fetchAssetsWithLocalIdentifiers:@[localIdentifier] options:nil] lastObject];
            [[PHAssetCollectionChangeRequest changeRequestForAssetCollection:collection] addAssets:@[asset]];
            
        } error:&error];
        NSLog(@"error :%@", error);
        
        if (completionHandler) {
            if (error) {
                NSLog(@"保存视频失败!");
                completionHandler(NO);
            }else {
                NSLog(@"保存视频成功!");
                completionHandler(YES);
            }
        }
    });
}

@end

