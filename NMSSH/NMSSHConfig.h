#import "NMSSH.h"

// MARK: - Error Constant -
/**
 * 에러 도메인
 */
extern NSString* _Nonnull const SSHErrorDomain;

/**
 * 에러 종류
 */
typedef NS_ENUM(NSInteger, SSHErrorCode) {
    /// 연결 실패 에러
    SSHConnectionError,

    /// 인증 실패 에러
    SSHAuthenticationError,

    /// 디렉토리를 읽을 수 없음
    SSHReadDirectoryError,

    /// 수신 실패 에러
    SSHReceiveError,
    /// 송신 실패 에러
    SSHSendError,

    /// 사용자 중지
    SSHAbortedError,
    
    /// 알 수 없는 에러
    SSHUnknownError,
};

// MARK: - NMSSHHostConfig Class -

@class NMSSHHostConfig;

/**
 NMSSHConfig parses ssh config files and returns matching entries for a given
 host name.
 */
@interface NMSSHConfig : NSObject

/** The array of parsed NMSSHHostConfig objects. */
@property (nonatomic, nonnull, readonly) NSArray<NMSSHHostConfig *> *hostConfigs;

/**
 Creates a new NMSSHConfig, reads the given {filename} and parses it.

 @param filename Path to an ssh config file.
 @returns NMSSHConfig instance or nil if the config file couldn't be parsed.
 */
+ (nullable instancetype)configFromFile:(nonnull NSString *)filename;

/**
 Initializes an NMSSHConfig from a config file's contents in a string.

 @param contents A config file's contents.
 @returns An NMSSHConfig object or nil if the contents were malformed.
 */
- (nullable instancetype)initWithString:(nonnull NSString *)contents;

/**
 Searches the config for an entry matching {host}.

 @param host A host name to search for.
 @returns An NMSSHHostConfig object whose patterns match host or nil if none is
     found.
 */
- (nullable NMSSHHostConfig *)hostConfigForHost:(nonnull NSString *)host;

@end
