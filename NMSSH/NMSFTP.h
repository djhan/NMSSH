#import "NMSSH.h"

@class NMSSHSession, NMSFTPFile;

/**
 NMSFTP provides functionality for working with SFTP servers.
 */
@interface NMSFTP : NSObject

/** A valid NMSSHSession instance */
@property (nonatomic, nonnull, readonly) NMSSHSession *session;

/** Property that keeps track of connection status to the server */
@property (nonatomic, readonly, getter = isConnected) BOOL connected;

/** Property that set/get read buffer size */
@property (nonatomic) NSUInteger bufferSize;

///-----------------------------------------------------------------------------
/// @name Initializer
/// ----------------------------------------------------------------------------

/**
 Create a new NMSFTP instance and connect it.

 @param session A valid, connected, NMSSHSession instance
 @returns Connected NMSFTP instance
 */
+ (nonnull instancetype)connectWithSession:(nonnull NMSSHSession *)session;

/**
 Create a new NMSFTP instance.

 @param session A valid, connected, NMSSHSession instance
 @returns New NMSFTP instance
 */
- (nonnull instancetype)initWithSession:(nonnull NMSSHSession *)session;

/// ----------------------------------------------------------------------------
/// @name Connection
/// ----------------------------------------------------------------------------

/**
 Create and connect to a SFTP session

 @returns Connection status
 */
- (BOOL)connect;

/**
 Disconnect SFTP session
 */
- (void)disconnect;

/// ----------------------------------------------------------------------------
/// @name Manipulate file system entries
/// ----------------------------------------------------------------------------

/**
 Move or rename an item

 @param sourcePath Item to move
 @param destPath Destination to move to
 @returns Move success
 */
- (BOOL)moveItemAtPath:(nonnull NSString *)sourcePath toPath:(nonnull NSString *)destPath;

/// ----------------------------------------------------------------------------
/// @name Manipulate directories
/// ----------------------------------------------------------------------------

/**
 Test if a directory exists at the specified path.

 Note: Will return NO if a file exists at the path, but not a directory.

 @param path Path to check
 @returns YES if file exists
 */
- (BOOL)directoryExistsAtPath:(nonnull NSString *)path;

/**
 Create a directory at path

 @param path Path to directory
 @returns Creation success
 */
- (BOOL)createDirectoryAtPath:(nonnull NSString *)path;

/**
 Remove directory at path

 @param path Existing directory
 @returns Remove success
 */
- (BOOL)removeDirectoryAtPath:(nonnull NSString *)path;

/**
 Get a list of files for a directory path

 @param path Existing directory to list items from
 @returns List of relative paths
 */
- (nullable NSArray<NMSFTPFile *> *)contentsOfDirectoryAtPath:(nonnull NSString *)path;
/**
 완료 핸들러로 리스트 항목을 가져오는 메쏘드

 @param path 리스트를 가져올 경로
 @param completion 완료 핸들러. NSError 로 에러, NSArray 로 결과 반환
 @returns `NSProgress` 반환. 접근 실패시 nil 반환
 */
- (NSProgress * _Nullable)contentsOfDirectoryWithProgressAtPath:(NSString * _Nonnull)path
                                                     completion:(void(^ _Nonnull)(NSError * _Nullable error, NSArray * _Nullable content))completion;

/// ----------------------------------------------------------------------------
/// @name Manipulate symlinks and files
/// ----------------------------------------------------------------------------

/**
 Reads the attributes from a file.

 @param path An existing file path
 @return A NMSFTPFile that contains the fetched file attributes.
 */
- (nullable NMSFTPFile *)infoForFileAtPath:(nonnull NSString *)path;

/**
 Test if a file exists at the specified path.

 Note: Will return NO if a directory exists at the path, but not a file.

 @param path Path to check
 @returns YES if file exists
 */
- (BOOL)fileExistsAtPath:(nonnull NSString *)path;

/**
 Create a symbolic link

 @param linkPath Path that will be linked to
 @param destPath Path the link will be created at
 @returns Creation success
 */
- (BOOL)createSymbolicLinkAtPath:(nonnull NSString *)linkPath
             withDestinationPath:(nonnull NSString *)destPath;

/**
 Remove file at path

 @param path Path to existing file
 @returns Remove success
 */
- (BOOL)removeFileAtPath:(nonnull NSString *)path;

/**
 Read the contents of a file

 @param path An existing file path
 @returns File contents
 */
- (nullable NSData *)contentsAtPath:(nonnull NSString *)path;

/**
 Refer to contentsAtPath:

 This adds the ability to get periodic updates to bytes received.
 
 @param path An existing file path
 @param progress Method called periodically with number of bytes downloaded and total file size.
        Returns NO to abort. 
 @returns File contents
 */
- (nullable NSData *)contentsAtPath:(nonnull NSString *)path progress:(BOOL (^_Nullable)(NSUInteger got, NSUInteger totalBytes))progress;

/**
 특정 경로의 데이터를 특정 영역만 추출해 반환

 @param path An existing file path
 @param offset 시작 지점
 @param length  데이터 크기
 @param progress 가져온 데이터 / 전체 크기 반환
 @returns 가져온 데이터를 반환
 */
- (nullable NSData *)contentsAtPath:(nonnull NSString *)path
                         fromOffset:(uint64_t)offset
                             length:(uint64_t)length
                           progress:(nonnull BOOL (^)(NSUInteger, NSUInteger))progress;

/**
 Refer to contentsAtPath:
 
 This adds the ability to get periodic updates to bytes received.
 
 @param path An existing file path
 @param stream Stream to write bytes to
 @param progress Method called periodically with number of bytes downloaded and total file size. Returns NO to abort.
 @return File read success
 */
- (BOOL)contentsAtPath:(nonnull NSString *)path toStream:(nonnull NSOutputStream *)stream progress:(BOOL (^_Nullable)(NSUInteger, NSUInteger))progress;

/**
 Overwrite the contents of a file

 If no file exists, one is created.

 @param contents Bytes to write
 @param path File path to write bytes at
 @returns Write success
 */
- (BOOL)writeContents:(nonnull NSData *)contents toFileAtPath:(nonnull NSString *)path;

/**
 Refer to writeContents:toFileAtPath:
 
 This adds the ability to get periodic updates to bytes sent.
 
 @param contents Bytes to write
 @param path File path to write bytes at
 @param progress Method called periodically with number of bytes sent.
        Returns NO to abort.
 @returns Write success
 */
- (BOOL)writeContents:(nonnull NSData *)contents toFileAtPath:(nonnull NSString *)path progress:(BOOL (^_Nullable)(NSUInteger sent))progress;

/**
 Overwrite the contents of a file

 If no file exists, one is created.

 @param localPath File path to read bytes at
 @param path File path to write bytes at
 @returns Write success
 */
- (BOOL)writeFileAtPath:(nonnull NSString *)localPath toFileAtPath:(nonnull NSString *)path;

/**
 Refer to writeFileAtPath:toFileAtPath:
 
 This adds the ability to get periodic updates to bytes sent.
 
 @param localPath File path to read bytes at
 @param path File path to write bytes at
 @param progress Method called periodically with number of bytes sent.
        Returns NO to abort.
 @returns Write success
 */
- (BOOL)writeFileAtPath:(nonnull NSString *)localPath toFileAtPath:(nonnull NSString *)path progress:(BOOL (^_Nullable)(NSUInteger sent))progress;

/**
 Overwrite the contents of a file

 If no file exists, one is created.

 @param inputStream Stream to read bytes from
 @param path File path to write bytes at
 @returns Write success
 */
- (BOOL)writeStream:(nonnull NSInputStream *)inputStream toFileAtPath:(nonnull NSString *)path;

/**
 Refer to writeStream:toFileAtPath:
 
 This adds the ability to get periodic updates to bytes sent.
 
 @param inputStream Stream to read bytes from
 @param path File path to write bytes at
 @param progress Method called periodically with number of bytes sent.
        Returns NO to abort.
 @returns Write success
 */
- (BOOL)writeStream:(nonnull NSInputStream *)inputStream toFileAtPath:(nonnull NSString *)path progress:(BOOL (^_Nullable)(NSUInteger sent))progress;

/**
 Start or resume writing the contents of a file

 If no file exists, one is created.
 If the file already exists the size of the output file will be used as offset
 and the input file will be appended to the output file, starting at that offset.

 @param localPath File path to read bytes at
 @param path File path to write bytes at
 @param progress Method called periodically with number of bytes appended and total bytes.
        Returns NO to abort.
 @returns Write success
 */
- (BOOL)resumeFileAtPath:(nonnull NSString *)localPath toFileAtPath:(nonnull NSString *)path progress:(BOOL (^_Nullable)(NSUInteger delta, NSUInteger totalBytes))progress;

/**
 Start or resume writing the contents of a file

 If no file exists, one is created.
 If the file already exists the size of the output file will be used as offset
 and the inputstream will be appended to the output file, starting at that offset.

 @param inputStream Stream to read bytes from
 @param path File path to write bytes at
 @param progress Method called periodically with number of bytes appended and total bytes.
        Returns NO to abort.
 @returns Write success
 */
- (BOOL)resumeStream:(nonnull NSInputStream *)inputStream toFileAtPath:(nonnull NSString *)path progress:(BOOL (^_Nullable)(NSUInteger delta, NSUInteger totalBytes))progress;

/**
 Append contents to the end of a file

 If no file exists, one is created.

 @param contents Bytes to write
 @param path File path to write bytes at
 @returns Append success
 */
- (BOOL)appendContents:(nonnull NSData *)contents toFileAtPath:(nonnull NSString *)path;

/**
 Append contents to the end of a file

 If no file exists, one is created.

 @param inputStream Stream to write bytes from
 @param path File path to write bytes at
 @returns Append success
 */
- (BOOL)appendStream:(nonnull NSInputStream *)inputStream toFileAtPath:(nonnull NSString *)path;

/**
 Copy a file remotely.
 
 @param fromPath Path to copy from
 @param toPath Path to copy to
 */
- (BOOL)copyContentsOfPath:(nonnull NSString *)fromPath toFileAtPath:(nonnull NSString *)toPath progress:(BOOL (^_Nullable)(NSUInteger copied, NSUInteger totalBytes))progress;

@end
