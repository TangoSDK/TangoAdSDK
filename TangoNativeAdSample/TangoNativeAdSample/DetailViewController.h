//
//  DetailViewController.h
//  TangoNativeAdSample
//
//  Created by idogadaev on 28/02/17.
//  Copyright © 2017 com.sgiggle.tango3dev. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DetailViewController : UIViewController

@property (strong, nonatomic) NSDate *detailItem;
@property (weak, nonatomic) IBOutlet UILabel *detailDescriptionLabel;

@end

