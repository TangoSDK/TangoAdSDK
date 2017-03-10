//
//  TGAdCell.h
//  TangoNativeAdSample
//
//  Created by idogadaev on 28/02/17.
//  Copyright © 2017 com.sgiggle.tango3dev. All rights reserved.
//

#import <UIKit/UIKit.h>

@class TGNativeAd;
@class TGAdCell;

@protocol AdCellAdLoadInformationProtocol <NSObject>
- (void)nativeAd:(TGNativeAd *)nativeAd failedToLoadForCell:(TGAdCell *)cell;
@end

@interface TGAdCell : UITableViewCell
@property (nonatomic, strong) IBOutlet UIImageView * icon;
@property (nonatomic, strong) IBOutlet UIImageView * image;
@property (nonatomic, strong) IBOutlet UILabel * title;
@property (nonatomic, strong) IBOutlet UILabel * subtitle;
@property (nonatomic, strong) IBOutlet UIButton * ctaButton;

@property (nonatomic, strong) TGNativeAd * nativeAd;
@property (nonatomic, assign) BOOL adWasLoaded;
@property (nonatomic, weak) id<AdCellAdLoadInformationProtocol> adLoadDelegate;

- (void)setNativeAd:(TGNativeAd *)nativeAd fromCache:(BOOL)cached;

- (IBAction)onOpenTapped:(id)sender;
@end
