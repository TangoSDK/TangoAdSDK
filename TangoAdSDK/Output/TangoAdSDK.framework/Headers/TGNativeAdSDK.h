//
//  TGNativeAd.h
//  TangoAdSDK
//
// Copyright 2012-2017, TangoMe Inc ("Tango").  The SDK provided herein includes
// software and other technology provided by Tango that is subject to copyright and
// other intellectual property protections. All rights reserved.  Use only in
// accordance with the Evaluation License Agreement provided to you by Tango.
//
// Please read Tango_SDK_Evaluation_License_agreement_v1-2.docx
//

#ifndef TGNativeAdSDK_h
#define TGNativeAdSDK_h

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "TGAdMacros.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, TGNativeAdSDKUserGender) {
  TGNativeAdSDKUserGenderUnknown,
  TGNativeAdSDKUserGenderMale,
  TGNativeAdSDKUserGenderFemale,
  TGNativeAdSDKUserGenderBoth
};


//first call to SDK must be:
//[[TGNativeAdSDK sharedInstance] initializeSDK];
@interface TGNativeAdSDK : NSObject
+(instancetype)sharedInstance;
@property (nonatomic,assign) NSUInteger userAge;
@property (nonatomic,assign) TGNativeAdSDKUserGender userGender;
- (void)initializeSDK; //must be called on main thread
@end


NS_ASSUME_NONNULL_END

#endif /* TGNativeAdSDK_h */
