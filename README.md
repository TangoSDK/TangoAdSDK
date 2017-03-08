# TangoAdSDK-iOS

## Table of Contents
* [Prerequisites](##prerequisites)
* [Installation](#installation)
* [Native Ads](#native-ads)
* [Ad Events](#ad-events)
* [Sample App](#sample-app)

## Prerequisites

### Ad unit id 

Ad unit id is a string that identify particular ad unit. Please use 'carousel_feed_placeholder' in testing app and contact [ads@tango.me](ads@tango.me) for the real ad unit id in production app. 

## Installation

Please refer to [Tango Native Ad Sample](https://github.com/TangoSDK/TangoAdSDK-iOS/tree/master/TangoNativeAdSample) 

## Native Ads

Native is a set of ad creatives that allow publishers to render them in the similar style as other elements in their apps. With native ads, publishers are able to provide user a consistent and unobstrusive experience. 

A native ad include the following creatives:

1. Title: the title of the native ad

2. Subtitle: the subtitle of the native ad, typically a short description

3. Cta text (optional): the 'call to action' text, for example "Install"

4. Icon: the icon image of the native ad 

5. Image: the main image of the native ad

6. Star rating (optional): specifically for app install ads, represent the star rating of the app 


### Loading native ads

Step 1. Create an instance of TGNativeAd and initialize it with an ad unit id. 
```objectivec
  TGNativeAd * nativeAd = [[TGNativeAd alloc] initWithAdUnitId:@"carousel_feed_placeholder"];
```

Step 2. Implement TGNativeAdDelegate to handle events from TGNativeAd. All methods are optional. 
```objectivec
- (void)nativeAdDidLoad:(TGNativeAd *)nativeAd {
  // This will be called when a native ad is loaded successfully. 
}

- (void)nativeAd:(TGNativeAd *)nativeAd didFailWithError:(NSError *)error {
  // This will be called when a native ad is failed to load. 
}

```

Step 3. Set the delegate. 
```objectivec
nativeAd.delegate = self; 
```

Step 4. Load an ad from server. 
```objectivec
[nativeAd loadAd]
```

Step 5. When a native ad is loaded successfully, load the icon and the main image. 
```objectivec
  [nativeAd.image loadImageAsyncWithBlock:^(UIImage * _Nullable image) {
    dispatch_async(dispatch_get_main_queue(), ^{
      // save the main image 
    });
  }];
  [nativeAd.icon loadImageAsyncWithBlock:^(UIImage * _Nullable image) {
    dispatch_async(dispatch_get_main_queue(), ^{
      // save the icon image
    });
  }];
```

Step 6. Register view for interaction
```objectivec
  [nativeAd registerViewForInteraction:contentView withViewController:self];
```

Step 7. Render the creatives of the native ad with the registered `contentView`. 
```objectivec
nativeAd.title
nativeAd.subtitle
nativeAd.ctaText
nativeAd.icon
nativeAd.image
nativeAd.star_rating
```

Step 8. When the ad display is finished, unregister the view 
```objectivec
  [nativeAd unregisterView];
```

## Ad Events

Besides nativeAdDidLoad and didFailWithError, the app will be notified when the following events taken place in TGNativeAd if corresponding methods in TGNativeAdDelegate are implemented.

1. nativeAdWillLogImpression: the event of a TGNativeAd impression being logged

2. nativeAdDidClick: the event of a TGNativeAd being clicked

3. nativeAdDidFinishHandlingClick: the event of a TGNativeAd finishing the click activity


## Sample App

* [Tango Native Ad Sample](https://github.com/TangoSDK/TangoAdSDK-iOS/tree/master/TangoNativeAdSample)

