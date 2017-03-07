//
//  TGAdMacros.h
//  TangoAdSDK
//
// Copyright 2012-2017, TangoMe Inc ("Tango").  The SDK provided herein includes
// software and other technology provided by Tango that is subject to copyright and
// other intellectual property protections. All rights reserved.  Use only in
// accordance with the Evaluation License Agreement provided to you by Tango.
//
// Please read Tango_SDK_Evaluation_License_agreement_v1-2.docx
//

#ifndef TGAdMacros_h
#define TGAdMacros_h

#define TG_CLASS_EXPORT __attribute__((visibility("default")))
#define TG_DEPRECATED __attribute__((deprecated))

#if __has_feature(objc_generics)
#define TG_NSArrayOf(x) NSArray<x>
#define TG_NSMutableArrayOf(x) NSMutableArray<x>
#define TG_NSDictionaryOf(x,y) NSDictionary<x, y>
#define TG_NSMutableDictionaryOf(x, y) NSMutableDictionary<x, y>
#define TG_NSSetOf(x) NSSet<x>
#define TG_NSMutableSetOf(x) NSMutableSet<x>
#else
#define TG_NSArrayOf(x) NSArray
#define TG_NSMutableArrayOf(x) NSMutableArray
#define TG_NSDictionaryOf(x,y) NSDictionary
#define TG_NSMutableDictionaryOf(x, y) NSMutableDictionary
#define TG_NSSetOf(x) NSSet
#define TG_NSMutableSetOf(x) NSMutableSet
#define __covariant
#endif

#if ! __has_feature(nullability)
#define NS_ASSUME_NONNULL_BEGIN
#define NS_ASSUME_NONNULL_END
#define nullable
#define __nullable
#endif

#ifndef TG_SUBCLASSING_RESTRICTED
#if defined(__has_attribute) && __has_attribute(objc_subclassing_restricted)
#define TG_SUBCLASSING_RESTRICTED __attribute__((objc_subclassing_restricted))
#else
#define TG_SUBCLASSING_RESTRICTED
#endif
#endif

#endif /* TGAdMacros_h */
