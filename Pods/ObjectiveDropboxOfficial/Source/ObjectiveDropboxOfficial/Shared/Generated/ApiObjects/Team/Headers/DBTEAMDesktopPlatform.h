///
/// Copyright (c) 2016 Dropbox, Inc. All rights reserved.
///
/// Auto-generated by Stone, do not modify.
///

#import <Foundation/Foundation.h>

#import "DBSerializableProtocol.h"

@class DBTEAMDesktopPlatform;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - API Object

///
/// The `DesktopPlatform` union.
///
/// This class implements the `DBSerializable` protocol (serialize and
/// deserialize instance methods), which is required for all Obj-C SDK API route
/// objects.
///
@interface DBTEAMDesktopPlatform : NSObject <DBSerializable, NSCopying>

#pragma mark - Instance fields

/// The `DBTEAMDesktopPlatformTag` enum type represents the possible tag states
/// with which the `DBTEAMDesktopPlatform` union can exist.
typedef NS_ENUM(NSInteger, DBTEAMDesktopPlatformTag) {
  /// Official Windows Dropbox desktop client.
  DBTEAMDesktopPlatformWindows,

  /// Official Mac Dropbox desktop client.
  DBTEAMDesktopPlatformMac,

  /// Official Linux Dropbox desktop client.
  DBTEAMDesktopPlatformLinux,

  /// (no description).
  DBTEAMDesktopPlatformOther,

};

/// Represents the union's current tag state.
@property (nonatomic, readonly) DBTEAMDesktopPlatformTag tag;

#pragma mark - Constructors

///
/// Initializes union class with tag state of "windows".
///
/// Description of the "windows" tag state: Official Windows Dropbox desktop
/// client.
///
/// @return An initialized instance.
///
- (instancetype)initWithWindows;

///
/// Initializes union class with tag state of "mac".
///
/// Description of the "mac" tag state: Official Mac Dropbox desktop client.
///
/// @return An initialized instance.
///
- (instancetype)initWithMac;

///
/// Initializes union class with tag state of "linux".
///
/// Description of the "linux" tag state: Official Linux Dropbox desktop client.
///
/// @return An initialized instance.
///
- (instancetype)initWithLinux;

///
/// Initializes union class with tag state of "other".
///
/// @return An initialized instance.
///
- (instancetype)initWithOther;

- (instancetype)init NS_UNAVAILABLE;

#pragma mark - Tag state methods

///
/// Retrieves whether the union's current tag state has value "windows".
///
/// @return Whether the union's current tag state has value "windows".
///
- (BOOL)isWindows;

///
/// Retrieves whether the union's current tag state has value "mac".
///
/// @return Whether the union's current tag state has value "mac".
///
- (BOOL)isMac;

///
/// Retrieves whether the union's current tag state has value "linux".
///
/// @return Whether the union's current tag state has value "linux".
///
- (BOOL)isLinux;

///
/// Retrieves whether the union's current tag state has value "other".
///
/// @return Whether the union's current tag state has value "other".
///
- (BOOL)isOther;

///
/// Retrieves string value of union's current tag state.
///
/// @return A human-readable string representing the union's current tag state.
///
- (NSString *)tagName;

@end

#pragma mark - Serializer Object

///
/// The serialization class for the `DBTEAMDesktopPlatform` union.
///
@interface DBTEAMDesktopPlatformSerializer : NSObject

///
/// Serializes `DBTEAMDesktopPlatform` instances.
///
/// @param instance An instance of the `DBTEAMDesktopPlatform` API object.
///
/// @return A json-compatible dictionary representation of the
/// `DBTEAMDesktopPlatform` API object.
///
+ (nullable NSDictionary<NSString *, id> *)serialize:(DBTEAMDesktopPlatform *)instance;

///
/// Deserializes `DBTEAMDesktopPlatform` instances.
///
/// @param dict A json-compatible dictionary representation of the
/// `DBTEAMDesktopPlatform` API object.
///
/// @return An instantiation of the `DBTEAMDesktopPlatform` object.
///
+ (DBTEAMDesktopPlatform *)deserialize:(NSDictionary<NSString *, id> *)dict;

@end

NS_ASSUME_NONNULL_END
