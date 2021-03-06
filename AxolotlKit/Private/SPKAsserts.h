//
//  Copyright (c) 2018 Open Whisper Systems. All rights reserved.
//

#import "SPKLogger.h"

NS_ASSUME_NONNULL_BEGIN

#ifndef OWSAssert

#ifdef DEBUG

#define USE_ASSERTS

#define CONVERT_TO_STRING(X) #X
#define CONVERT_EXPR_TO_STRING(X) CONVERT_TO_STRING(X)

// OWSAssert() and OWSFailDebug() should be used in Obj-C methods.
// OWSCAssert() and OWSCFailDebug() should be used in free functions.

#define OWSAssert(X)                                                                                                   \
    do {                                                                                                               \
        if (!(X)) {                                                                                                    \
            OWSLogError(@"%s Assertion failed: %s", __PRETTY_FUNCTION__, CONVERT_EXPR_TO_STRING(X));                   \
            [DDLog flushLog];                                                                                          \
            NSAssert(0, @"Assertion failed: %s", CONVERT_EXPR_TO_STRING(X));                                           \
        }                                                                                                              \
    } while (NO)

#define OWSCAssert(X)                                                                                                  \
    do {                                                                                                               \
        if (!(X)) {                                                                                                    \
            OWSLogError(@"%s Assertion failed: %s", __PRETTY_FUNCTION__, CONVERT_EXPR_TO_STRING(X));                   \
            [DDLog flushLog];                                                                                          \
            NSCAssert(0, @"Assertion failed: %s", CONVERT_EXPR_TO_STRING(X));                                          \
        }                                                                                                              \
    } while (NO)

#define OWSFailWithoutLogging(message, ...)                                                                            \
    do {                                                                                                               \
        NSString *formattedMessage = [NSString stringWithFormat:message, ##__VA_ARGS__];                               \
        NSAssert(0, formattedMessage);                                                                                 \
    } while (NO)


#define OWSCFailWithoutLogging(message, ...)                                                                           \
    do {                                                                                                               \
        NSString *formattedMessage = [NSString stringWithFormat:message, ##__VA_ARGS__];                               \
        NSCAssert(0, formattedMessage);                                                                                \
    } while (NO)

#define OWSFailNoFormat(message)                                                                                       \
    do {                                                                                                               \
        OWSLogError(@"%@", message);                                                                                   \
        [DDLog flushLog];                                                                                              \
        NSAssert(0, message);                                                                                          \
    } while (NO)

#define OWSCFailNoFormat(message)                                                                                      \
    do {                                                                                                               \
        OWSLogError(@"%@", message);                                                                                   \
        [DDLog flushLog];                                                                                              \
        NSCAssert(0, message);                                                                                         \
    } while (NO)

#else

#define OWSAssert(X)
#define OWSCAssert(X)
#define OWSFailWithoutLogging(message, ...)
#define OWSCFailWithoutLogging(message, ...)
#define OWSFailNoFormat(X)
#define OWSCFailNoFormat(X)

#endif

#endif

#define OWSAbstractMethod() OWSFailDebug(@"%@ Method needs to be implemented by subclasses.", self.logTag)

// This macro is intended for use in Objective-C.
#define OWSAssertIsOnMainThread() OWSCAssert([NSThread isMainThread])

#define OWSFailDebug(_messageFormat, ...)                                                                              \
    do {                                                                                                               \
        OWSLogError(_messageFormat, ##__VA_ARGS__);                                                                    \
        [DDLog flushLog];                                                                                              \
        OWSFailWithoutLogging(_messageFormat, ##__VA_ARGS__);                                                          \
    } while (0)

#define OWSCFailDebug(_messageFormat, ...)                                                                             \
    do {                                                                                                               \
        OWSLogError(_messageFormat, ##__VA_ARGS__);                                                                    \
        [DDLog flushLog];                                                                                              \
        OWSCFailWithoutLogging(_messageFormat, ##__VA_ARGS__);                                                         \
    } while (NO)


#define OWSFail(_messageFormat, ...)                                                                                   \
    do {                                                                                                               \
        OWSFailDebug(_messageFormat, ##__VA_ARGS__);                                                                   \
        exit(0);                                                                                                       \
    } while (0)

#define OWSCFail(_messageFormat, ...)                                                                                  \
    do {                                                                                                               \
        OWSCFailDebug(_messageFormat, ##__VA_ARGS__);                                                                  \
        exit(0);                                                                                                       \
    } while (NO)

// Avoids Clang analyzer warning:
//   Value stored to 'x' during it's initialization is never read
#define SUPPRESS_DEADSTORE_WARNING(x)                                                                                  \
    do {                                                                                                               \
        (void)x;                                                                                                       \
    } while (0)

__attribute__((annotate("returns_localized_nsstring"))) static inline NSString *LocalizationNotNeeded(NSString *s)
{
    return s;
}

#define OWSRaiseException(name, formatParam, ...)                                                                      \
    do {                                                                                                               \
        OWSLogError(@"Exception: %@ %@", name, [NSString stringWithFormat:formatParam, ##__VA_ARGS__]);                \
        [DDLog flushLog];                                                                                              \
        @throw [NSException exceptionWithName:name                                                                     \
                                       reason:[NSString stringWithFormat:formatParam, ##__VA_ARGS__]                   \
                                     userInfo:nil];                                                                    \
    } while (NO)

#define OWSRaiseExceptionWithUserInfo(name, userInfoParam, formatParam, ...)                                           \
    do {                                                                                                               \
        OWSLogError(                                                                                                   \
            @"Exception: %@ %@ %@", name, userInfoParam, [NSString stringWithFormat:formatParam, ##__VA_ARGS__]);      \
        [DDLog flushLog];                                                                                              \
        @throw [NSException exceptionWithName:name                                                                     \
                                       reason:[NSString stringWithFormat:formatParam, ##__VA_ARGS__]                   \
                                     userInfo:userInfoParam];                                                          \
    } while (NO)

NS_ASSUME_NONNULL_END
