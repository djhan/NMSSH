/**
 - Important:
 - 원래 포함된 openssl/libssh2 library 파일이 x86 타겟으로 작성
 - 하기 링크 등을 참고
 - [링크](https://stackoverflow.com/questions/25530429/build-multiarch-openssl-on-os-x)
 - 단, 마지막으로 최종 빌드까지 성공한 것은, 하기 링크의 스크립트
 - 아래 스크립트를 이용하면 arm64 타겟으로 생성시, 팻바이너리 라이브러리로 openssl/libssh2 를 생성해 줌
 - [링크](https://github.com/Frugghi/iSSH2)
 */

#import <Foundation/Foundation.h>

#ifndef _NMSSH_
#define _NMSSH_

#import "libssh2.h"
#import "libssh2_sftp.h"

#import "NMSSHSessionDelegate.h"
#import "NMSSHChannelDelegate.h"

#import "NMSSHSession.h"
#import "NMSSHChannel.h"
#import "NMSFTP.h"
#import "NMSFTPFile.h"
#import "NMSSHConfig.h"
#import "NMSSHHostConfig.h"

#import "NMSSHLogger.h"

#endif
