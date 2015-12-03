//
//  MPBluetoothUtils.h
//  MPBluetoothKitDemo
//
//  Created by MacPu on 15/12/3.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MPBluetoothUtils : NSObject

/**
 * Convert data to byte
 * @param data data to convert
 * @return 8-bit integer
 */
+ (int8_t)dataToByte:(NSData *)data;

/**
 * Convert data to 16-bit integer
 * @param data data to convert
 * @return 16-bit integer
 
 */
+ (int16_t)dataToInt16:(NSData *)data;

/**
 * Convert data to 32-bit integer
 * @param data data to convert
 * @return 32-bit integer
 */
+ (int32_t)dataToInt32:(NSData *)data;

@end
