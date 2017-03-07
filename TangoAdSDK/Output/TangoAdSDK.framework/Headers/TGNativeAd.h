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

#ifndef TGNativeAd_h
#define TGNativeAd_h

#import <UIKit/UIKit.h>
#import "TGAdMacros.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, TGNativeAdError) {
  TGNativeAdErrorZeroData = 100,
  TGNativeAdErrorBadJsonData,
  TGNativeAdErrorEmptyAdData,
};

@protocol TGNativeAdDelegate;
@class TGAdImage;

/*!
 @class TGNativeAd
 
 @abstract
 The TGNativeAd represents a set of ad elements to construct custom ad views.
 */
TG_CLASS_EXPORT TG_SUBCLASSING_RESTRICTED
@interface TGNativeAd : NSObject

/*!
 @property
 @abstract Typed access to the id of the ad unit.
 */
@property (nonatomic, copy, readonly, nonnull) NSString *adUnitId;

/*!
 @property
 @abstract Typed access to the title.
 */
@property (nonatomic, copy, readonly, nullable) NSString *title;

/*!
 @property
 @abstract Typed access to the subtitle.
 */
@property (nonatomic, copy, readonly, nullable) NSString *subtitle;

/*!
 @property
 @abstract Typed access to the call to action text of the ad, for example "Install".
 */
@property (nonatomic, copy, readonly, nullable) NSString *ctaText;

/*!
 @property
 @abstract Typed access to the icon image. See `TGAdImage` for details.
 */
@property (nonatomic, strong, readonly, nullable) TGAdImage *icon;

/*!
 @property
 @abstract Typed access to the main image. See `TGAdImage` for details.
 */
@property (nonatomic, strong, readonly, nullable) TGAdImage *image;

/*!
 @property
 @abstract Typed access to the star rating
 */
@property (nonatomic, assign, readonly) CGFloat star_rating;

/*!
 @property
 @abstract the delegate
 */
@property (nonatomic, weak, nullable) id<TGNativeAdDelegate> delegate;

/*!
 @method
 
 @abstract This is a method to initialize a TGNativeAd object with the given ad unit id.
 
 @param adUnitId The id of the ad unit. Please contact ads@tango.me for creating new ad unit.
 */
- (instancetype)initWithAdUnitId:(NSString *) adUnitId NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @method
 
 @abstract
 This is a method to associate a TGNativeAd with the UIView used to display the native ads.
 
 @param view The UIView created to render all the native ad elements.
 
 @param viewController The UIViewController that will be used to present SKStoreProductViewController or the in-app browser. If nil is passed, the top view controller currently shown will be used.

 */
- (void)registerViewForInteraction:(UIView *)view
                withViewController:(nullable UIViewController *)viewController;

/*!
 @method
 
 @abstract This is a method to disconnect a TGNativeAd with the UIView used to display the native ads.
 */
- (void)unregisterView;

/*!
 @method
 
 @abstract
 Begins loading the TGNativeAd content.
 
 */
- (void)loadAd;

@end


/*!
 @protocol
 
 @abstract The methods of the TGNativeAdDelegate protocol allow the adopting delegate to respond to messages from the TGNativeAd class such as whether the native ad has been successfully loaded.
 */
@protocol TGNativeAdDelegate <NSObject>

@optional

/*!
 @method
 
 @abstract Sent when an TGNativeAd has been successfully loaded.
 
 @param nativeAd The TGNativeAd object that sends the message.
 */
- (void)nativeAdDidLoad:(TGNativeAd *)nativeAd;

/*!
 @method
 
 @abstract Sent before the impression of an TGNativeAd object will be logged.
 
 @param nativeAd The TGNativeAd object that sends the message.
 */
- (void)nativeAdWillLogImpression:(TGNativeAd *)nativeAd;

/*!
 @method
 
 @abstract Sent when an TGNativeAd failed to load.
 
 @param nativeAd The TGNativeAd object that sends the message.
 @param error An error object that contains the details of the error.
 */
- (void)nativeAd:(TGNativeAd *)nativeAd didFailWithError:(NSError *)error;

/*!
 @method
 
 @abstract Sent after an ad has been clicked by the person.
 
 @param nativeAd The TGNativeAd object that sends the message.
 */
- (void)nativeAdDidClick:(TGNativeAd *)nativeAd;

/*!
 @method
 
 @abstract When an ad is clicked, the modal view will be presented. And when the user finishes the
 interaction with the modal view and dismiss it, this message will be sent, returning control
 to the application.
 
 @param nativeAd The TGNativeAd object that sends the message.
 */
- (void)nativeAdDidFinishHandlingClick:(TGNativeAd *)nativeAd;

@end

/*!
 @class TGAdImage
 @abstract Represents an image creative.
 */
TG_CLASS_EXPORT
@interface TGAdImage : NSObject

/*!
 @property
 @abstract Typed access to the image url.
 */
@property (nonatomic, copy, readonly, nonnull) NSURL *url;
/*!
 @property
 @abstract Typed access to the image width.
 */
@property (nonatomic, assign, readonly) NSInteger width;
/*!
 @property
 @abstract Typed access to the image height.
 */
@property (nonatomic, assign, readonly) NSInteger height;

/*!
 @method
 
 @abstract This is a method to initialize an TGAdImage.
 
 @param url the image url.
 @param width the image width.
 @param height the image height.
 */
- (instancetype)initWithURL:(NSURL *)url
                      width:(NSInteger)width
                     height:(NSInteger)height NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
/*!
 @method
 
 @abstract Load an image from self.url or the cache.
 
 @param block Block to handle the loaded image.
 */
- (void)loadImageAsyncWithBlock:(nullable void (^)(UIImage * __nullable image))block;

- (void)cancelLoad;

@end


NS_ASSUME_NONNULL_END

#endif /* TGNativeAd_h */
