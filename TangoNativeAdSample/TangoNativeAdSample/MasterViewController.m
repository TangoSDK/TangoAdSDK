//
//  MasterViewController.m
//  TangoNativeAdSample
//
//  Created by idogadaev on 28/02/17.
//  Copyright © 2017 Tango.me. All rights reserved.
//

#import "MasterViewController.h"
#import "DetailViewController.h"
#import "AppDelegate.h"
#import "TGAdCell.h"
#import <CoreLocation/CoreLocation.h>
#import <TangoAdSDK/TangoAdSDK.h>

@interface MasterViewController ()<AdCellAdLoadInformationProtocol>
@property (nonatomic, strong) NSMutableSet * failedAdIndexes;
@property (nonatomic, strong) NSMutableArray * adsCache;
@property (nonatomic, strong) CLLocationManager * manager;
@end

@implementation MasterViewController

- (NSDictionary *)dataEntryAtIndex:(NSIndexPath *)indexPath {
  static NSArray * data = nil;
  if (data == nil) {
    data   =    @[@{@"title":@"Home", @"link":@"http://www.tango.me"},
                            @{@"title":@"Fiesta", @"link":@"https://heyfiesta.com"},
                            @{@"title":@"Games", @"link":@"http://www.tango.me/games"},
                            @{@"title":@"Download", @"link":@"http://www.tango.me/download"},
                            @{@"title":@"Advertisers", @"link":@"http://www.tango.me/advertisers"},
                            @{@"title":@"Business Partners",@"link":@"http://www.tango.me/business-partners"},
                            @{@"title":@"Careers", @"link":@"http://www.tango.me/careers"},
                            @{@"title":@"About Us", @"link":@"http://www.tango.me/about-us"},
                            @{@"title":@"Press", @"link":@"http://www.tango.me/press"},
                            @{@"title":@"Contact Us", @"link":@"http://www.tango.me/contact-us"},
                            @{@"title":@"Blog", @"link": @"http://www.tango.me/blog"}];
  }
  NSInteger index = indexPath.row % data.count;
  return data[index];
}

- (void)viewDidLoad {
  [super viewDidLoad];
  self.failedAdIndexes = [NSMutableSet set];
  self.adsCache = [NSMutableArray array];
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
  self.manager = [[CLLocationManager alloc] init];
  [self.manager  requestWhenInUseAuthorization];
}

- (void)applicationDidBecomeActive:(NSNotification *)notification {
  [self.failedAdIndexes removeAllObjects];
  [self.tableView reloadData];
}

- (void)dealloc {
  [[NSNotificationCenter defaultCenter] removeObserver:self];
}
- (void)viewWillAppear:(BOOL)animated {
  self.clearsSelectionOnViewWillAppear = self.splitViewController.isCollapsed;
  [super viewWillAppear:animated];
}


- (void)didReceiveMemoryWarning {
  [super didReceiveMemoryWarning];
  // Dispose of any resources that can be recreated.
}


#pragma mark - Table View

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
  return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
  return 100500;//self.objects.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
  if ((indexPath.row%3) == 0) {
    if ([self.failedAdIndexes containsObject:@(indexPath.row)]) {
      return 0.0f;
    }
    return 350.0f;
  }
  else {
    return 44.0f;
  }
  
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
  if ((indexPath.row%3) == 0) {
    TGAdCell *adcell = (TGAdCell *)cell;
    [adcell.nativeAd registerViewForInteraction:adcell.contentView withViewController:self];
  }
}

- (BOOL)cacheAds {
  AppDelegate * delegate = (AppDelegate *)[UIApplication sharedApplication].delegate;
  return delegate.cacheAds;
}

- (void)tableView:(UITableView *)tableView didEndDisplayingCell:(nonnull UITableViewCell *)cell forRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
  if ((indexPath.row%3) == 0) {
    TGAdCell *adcell = (TGAdCell *)cell;
    if ([self cacheAds] && adcell.nativeAd != nil && adcell.adWasLoaded) {
      if (![self.adsCache containsObject:adcell.nativeAd]) {
        [self.adsCache addObject:adcell.nativeAd];
      }
    }
    [adcell.nativeAd unregisterView];
    adcell.nativeAd = nil;
  }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
  UITableViewCell *cell = nil;
  if ((indexPath.row%3) == 0) {
    BOOL adFromCache = NO;
    TGNativeAd * ad =  nil;
    if ([self cacheAds] && self.adsCache.count > 0) {
      ad = self.adsCache.firstObject;
      [self.adsCache removeObject:ad];
      adFromCache = YES;
    }
    else {
      ad = [[TGNativeAd alloc] initWithAdUnitId:@"carousel_feed_placeholder"];
    }
    TGAdCell *adcell = [tableView dequeueReusableCellWithIdentifier:@"TGAdCellIdentifier" forIndexPath:indexPath];
    [adcell setNativeAd:ad fromCache:adFromCache];
    adcell.adLoadDelegate = self;
    if (!adFromCache) {
      NSString * text = @"Loading...";
      adcell.title.text = text;
      adcell.subtitle.text = @"";
    }
    cell = adcell;
  }
  else {
    cell = [tableView dequeueReusableCellWithIdentifier:@"Cell" forIndexPath:indexPath];
    
    NSDictionary * data = [self dataEntryAtIndex:indexPath];
    NSString * text = data[@"title"];
    cell.textLabel.text = text;
  }
  [cell setNeedsDisplay];
  return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
  NSDictionary * data = [self dataEntryAtIndex:indexPath];
  NSString * link = data[@"link"];
  [[UIApplication sharedApplication] openURL:[NSURL URLWithString:link]];
  [self.tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (void)nativeAd:(TGNativeAd *)nativeAd failedToLoadForCell:(TGAdCell *)cell {
  NSIndexPath * indexPath = [self.tableView indexPathForCell:cell];
  if (indexPath != nil) {
    if ([self cacheAds]) {
      [self.adsCache removeObject:nativeAd];
    }
    [self.failedAdIndexes addObject:@(indexPath.row)];
    [self.tableView reloadRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
  }
}

@end
