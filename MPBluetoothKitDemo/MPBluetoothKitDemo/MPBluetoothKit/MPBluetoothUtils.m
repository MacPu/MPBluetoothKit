//
//  MPBluetoothUtils.m
//  MPBluetoothKitDemo
//
//  Created by MacPu on 15/12/3.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import "MPBluetoothUtils.h"

@implementation MPBluetoothUtils

+ (int8_t)dataToByte:(NSData *)data {
    char val[data.length];
    [data getBytes:&val length:data.length];
    int8_t result = val[0];
    return result;
}

+ (int16_t)dataToInt16:(NSData *)data {
    char val[data.length];
    [data getBytes:&val length:data.length];
    int16_t result = (val[0] & 0x00FF) | (val[1] << 8 & 0xFF00);
    return result;
}

+ (int32_t)dataToInt32:(NSData *)data {
    char val[data.length];
    [data getBytes:&val length:data.length];
    int32_t result = ((val[0] & 0x00FF) |
                      (val[1] << 8 & 0xFF00) |
                      (val[2] << 16 & 0xFF0000) |
                      (val[3] << 24 & 0xFF000000));
    
    return result;
}

@end
