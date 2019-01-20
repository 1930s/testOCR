///
/// Copyright (c) 2016 Dropbox, Inc. All rights reserved.
///
/// Auto-generated by Stone, do not modify.
///

#import <Foundation/Foundation.h>

#import "DBSerializableProtocol.h"

@class DBFILESRelocationBatchError;
@class DBFILESRelocationBatchJobStatus;
@class DBFILESRelocationBatchResult;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - API Object

///
/// The `RelocationBatchJobStatus` union.
///
/// This class implements the `DBSerializable` protocol (serialize and
/// deserialize instance methods), which is required for all Obj-C SDK API route
/// objects.
///
@interface DBFILESRelocationBatchJobStatus : NSObject <DBSerializable, NSCopying>

#pragma mark - Instance fields

/// The `DBFILESRelocationBatchJobStatusTag` enum type represents the possible
/// tag states with which the `DBFILESRelocationBatchJobStatus` union can exist.
typedef NS_ENUM(NSInteger, DBFILESRelocationBatchJobStatusTag) {
  /// The asynchronous job is still in progress.
  DBFILESRelocationBatchJobStatusInProgress,

  /// The copy or move batch job has finished.
  DBFILESRelocationBatchJobStatusComplete,

  /// The copy or move batch job has failed with exception.
  DBFILESRelocationBatchJobStatusFailed,

};

/// Represents the union's current tag state.
@property (nonatomic, readonly) DBFILESRelocationBatchJobStatusTag tag;

/// The copy or move batch job has finished. @note Ensure the `isComplete`
/// method returns true before accessing, otherwise a runtime exception will be
/// raised.
@property (nonatomic, readonly) DBFILESRelocationBatchResult *complete;

/// The copy or move batch job has failed with exception. @note Ensure the
/// `isFailed` method returns true before accessing, otherwise a runtime
/// exception will be raised.
@property (nonatomic, readonly) DBFILESRelocationBatchError *failed;

#pragma mark - Constructors

///
/// Initializes union class with tag state of "in_progress".
///
/// Description of the "in_progress" tag state: The asynchronous job is still in
/// progress.
///
/// @return An initialized instance.
///
- (instancetype)initWithInProgress;

///
/// Initializes union class with tag state of "complete".
///
/// Description of the "complete" tag state: The copy or move batch job has
/// finished.
///
/// @param complete The copy or move batch job has finished.
///
/// @return An initialized instance.
///
- (instancetype)initWithComplete:(DBFILESRelocationBatchResult *)complete;

///
/// Initializes union class with tag state of "failed".
///
/// Description of the "failed" tag state: The copy or move batch job has failed
/// with exception.
///
/// @param failed The copy or move batch job has failed with exception.
///
/// @return An initialized instance.
///
- (instancetype)initWithFailed:(DBFILESRelocationBatchError *)failed;

- (instancetype)init NS_UNAVAILABLE;

#pragma mark - Tag state methods

///
/// Retrieves whether the union's current tag state has value "in_progress".
///
/// @return Whether the union's current tag state has value "in_progress".
///
- (BOOL)isInProgress;

///
/// Retrieves whether the union's current tag state has value "complete".
///
/// @note Call this method and ensure it returns true before accessing the
/// `complete` property, otherwise a runtime exception will be thrown.
///
/// @return Whether the union's current tag state has value "complete".
///
- (BOOL)isComplete;

///
/// Retrieves whether the union's current tag state has value "failed".
///
/// @note Call this method and ensure it returns true before accessing the
/// `failed` property, otherwise a runtime exception will be thrown.
///
/// @return Whether the union's current tag state has value "failed".
///
- (BOOL)isFailed;

///
/// Retrieves string value of union's current tag state.
///
/// @return A human-readable string representing the union's current tag state.
///
- (NSString *)tagName;

@end

#pragma mark - Serializer Object

///
/// The serialization class for the `DBFILESRelocationBatchJobStatus` union.
///
@interface DBFILESRelocationBatchJobStatusSerializer : NSObject

///
/// Serializes `DBFILESRelocationBatchJobStatus` instances.
///
/// @param instance An instance of the `DBFILESRelocationBatchJobStatus` API
/// object.
///
/// @return A json-compatible dictionary representation of the
/// `DBFILESRelocationBatchJobStatus` API object.
///
+ (nullable NSDictionary<NSString *, id> *)serialize:(DBFILESRelocationBatchJobStatus *)instance;

///
/// Deserializes `DBFILESRelocationBatchJobStatus` instances.
///
/// @param dict A json-compatible dictionary representation of the
/// `DBFILESRelocationBatchJobStatus` API object.
///
/// @return An instantiation of the `DBFILESRelocationBatchJobStatus` object.
///
+ (DBFILESRelocationBatchJobStatus *)deserialize:(NSDictionary<NSString *, id> *)dict;

@end

NS_ASSUME_NONNULL_END
