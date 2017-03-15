//
//  TGAdCell.m
//  TangoNativeAdSample
//
//  Created by idogadaev on 28/02/17.
//  Copyright © 2017 Tango.me. All rights reserved.
//

#import "TGAdCell.h"
#import <TangoAdSDK/TangoAdSDK.h>

@interface TGAdCell()<TGNativeAdDelegate>

@end

@implementation TGAdCell

- (void)prepareForReuse {
  [self.nativeAd.icon cancelLoad];
  [self.nativeAd.image cancelLoad];
  [self.nativeAd unregisterView];
  self.nativeAd.delegate = nil;
  self.nativeAd = nil;
  self.adWasLoaded = NO;
  self.image.image = nil;
  self.icon.image = nil;
}
- (void)awakeFromNib {
  [super awakeFromNib];
  UIColor * color = [UIColor colorWithRed:0.15f green:0.8f blue:0.65f alpha:1.0f];
  self.ctaButton.layer.borderColor = color.CGColor;
  self.ctaButton.layer.borderWidth = 1.0f;
  [self.ctaButton setTitleColor:color forState:UIControlStateNormal];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (void)setNativeAd:(TGNativeAd *)nativeAd fromCache:(BOOL)cached{
  _nativeAd = nativeAd;
  _adWasLoaded = cached;
  if (cached) {
    [self loadImagesForAd:nativeAd];
    self.title.text = nativeAd.title;
    self.subtitle.text = nativeAd.subtitle;
  }
  else {
    nativeAd.delegate = self;
    [nativeAd loadAd];
  }
}


- (void)loadImagesForAd:(TGNativeAd *)nativeAd {
  [nativeAd.image loadImageAsyncWithBlock:^(UIImage * _Nullable image) {
    dispatch_async(dispatch_get_main_queue(), ^{
      self.image.image = image;
      self.image.contentMode = UIViewContentModeScaleAspectFit;
    });
  }];
  [nativeAd.icon loadImageAsyncWithBlock:^(UIImage * _Nullable image) {
    dispatch_async(dispatch_get_main_queue(), ^{
      self.icon.image = image;
      self.icon.contentMode = UIViewContentModeScaleAspectFit;
    });
  }];
}

- (void)nativeAdDidLoad:(TGNativeAd *)nativeAd {
  dispatch_async(dispatch_get_main_queue(), ^{
    [self loadImagesForAd:nativeAd];
    self.adWasLoaded = YES;
    self.title.text = nativeAd.title;
    self.subtitle.text = nativeAd.subtitle;
    if (nativeAd.ctaText.length > 0) {
      [self.ctaButton setTitle:nativeAd.ctaText forState:UIControlStateNormal];
    }
  });
}

- (void)nativeAd:(TGNativeAd *)nativeAd didFailWithError:(NSError *)error {
  dispatch_async(dispatch_get_main_queue(), ^{
    self.title.text = @"Ad was not loaded";
    self.image.image = nil;
    self.icon.image = nil;
    self.subtitle.text = error.description;
    if (self.adLoadDelegate != nil) {
      [self.adLoadDelegate nativeAd:nativeAd failedToLoadForCell:self];
    }
  });
}

- (IBAction)onOpenTapped:(id)sender {
  NSLog(@"open tapped");
}

@end
