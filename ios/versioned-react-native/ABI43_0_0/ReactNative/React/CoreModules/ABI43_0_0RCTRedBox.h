/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <UIKit/UIKit.h>

#import <ABI43_0_0React/ABI43_0_0RCTBridge.h>
#import <ABI43_0_0React/ABI43_0_0RCTBridgeModule.h>
#import <ABI43_0_0React/ABI43_0_0RCTErrorCustomizer.h>

@class ABI43_0_0RCTJSStackFrame;

typedef void (^ABI43_0_0RCTRedBoxButtonPressHandler)(void);

@interface ABI43_0_0RCTRedBox : NSObject <ABI43_0_0RCTBridgeModule>

- (void)registerErrorCustomizer:(id<ABI43_0_0RCTErrorCustomizer>)errorCustomizer;
- (void)showError:(NSError *)error;
- (void)showErrorMessage:(NSString *)message;
- (void)showErrorMessage:(NSString *)message withDetails:(NSString *)details;
- (void)showErrorMessage:(NSString *)message withRawStack:(NSString *)rawStack;
- (void)showErrorMessage:(NSString *)message withRawStack:(NSString *)rawStack errorCookie:(int)errorCookie;
- (void)showErrorMessage:(NSString *)message withStack:(NSArray<NSDictionary *> *)stack;
- (void)updateErrorMessage:(NSString *)message withStack:(NSArray<NSDictionary *> *)stack;
- (void)showErrorMessage:(NSString *)message withStack:(NSArray<NSDictionary *> *)stack errorCookie:(int)errorCookie;
- (void)updateErrorMessage:(NSString *)message withStack:(NSArray<NSDictionary *> *)stack errorCookie:(int)errorCookie;
- (void)showErrorMessage:(NSString *)message withParsedStack:(NSArray<ABI43_0_0RCTJSStackFrame *> *)stack;
- (void)updateErrorMessage:(NSString *)message withParsedStack:(NSArray<ABI43_0_0RCTJSStackFrame *> *)stack;
- (void)showErrorMessage:(NSString *)message
         withParsedStack:(NSArray<ABI43_0_0RCTJSStackFrame *> *)stack
             errorCookie:(int)errorCookie;
- (void)updateErrorMessage:(NSString *)message
           withParsedStack:(NSArray<ABI43_0_0RCTJSStackFrame *> *)stack
               errorCookie:(int)errorCookie;

- (void)dismiss;

- (void)addCustomButton:(NSString *)title onPressHandler:(ABI43_0_0RCTRedBoxButtonPressHandler)handler;

/** Overrides bridge.bundleURL. Modify on main thread only. You shouldn't need to use this. */
@property (nonatomic, strong) NSURL *overrideBundleURL;

/** Overrides the default behavior of calling [bridge reload] on reload. You shouldn't need to use this. */
@property (nonatomic, strong) dispatch_block_t overrideReloadAction;

@end

/**
 * This category makes the red box instance available via the ABI43_0_0RCTBridge, which
 * is useful for any class that needs to access the red box or error log.
 */
@interface ABI43_0_0RCTBridge (ABI43_0_0RCTRedBox)

@property (nonatomic, readonly) ABI43_0_0RCTRedBox *redBox;

@end
