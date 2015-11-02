//
//  MPDescriptor.h
//  MPBluetoothKit
//
//  Created by MacPu on 15/10/29.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "MPBluetoothKitBlocks.h"

@class MPPeripheral;
@class MPCharacteristic;

@interface MPDescriptor : NSObject

/*!
 * @property UUID
 *
 * @discussion
 *      The Bluetooth UUID of the descriptor.
 *
 */
@property(readonly, nonatomic, nullable) CBUUID *UUID;

/*!
 *  @property characteristic
 *
 *  @discussion
 *      A back-pointer to the characteristic this descriptor belongs to.
 *
 */
@property(nonatomic, assign, readonly, nullable) MPCharacteristic *characteristic;

/*!
 *  @property value
 *
 *  @discussion
 *      The value of the descriptor. The corresponding value types for the various descriptors are detailed in @link CBUUID.h @/link.
 *
 */
@property(retain, readonly, nullable) id value;

- (nullable instancetype)init NS_UNAVAILABLE;
- (nullable instancetype)initWithDescriptor:(nullable CBDescriptor *)descriptor andOwnPeripheral:(nullable MPPeripheral *)peripheral;

- (void)readValueForWithBlock:(nullable MPPeripheralReadValueForDescriptorsBlock)block;

- (void)writeValue:(nullable NSData *)data withBlock:(nullable MPPeripheralWriteValueForDescriptorsBlock)block;

@end