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
- (nullable instancetype)initWithDescriptor:(nullable CBDescriptor *)descriptor
                           andOwnPeripheral:(nullable MPPeripheral *)peripheral;

/*!
 *  @method readValueWithBlock:
 *
 *  @param block        callback with this block.
 *
 *  @discussion			Reads the value of <i>self</i>.
 *
 *  @see                MPPeripheralReadValueForDescriptorsBlock
 */
- (void)readValueWithBlock:(nullable MPPeripheralReadValueForDescriptorsBlock)block;

/*!
 *  @method writeValue:withBlock:
 *
 *  @param data			The value to write.
 *  @param block        callback with this block.
 *
 *  @discussion			Writes <i>data</i> to <i>self</i>'s value. Client characteristic configuration descriptors cannot be written using
 *						this method, and should instead use @link setNotifyValue:forCharacteristic: @/link.
 *
 *  @see                MPPeripheralReadValueForDescriptorsBlock
 */
- (void)writeValue:(nullable NSData *)data withBlock:(nullable MPPeripheralWriteValueForDescriptorsBlock)block;

@end