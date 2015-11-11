//
//  MPCharacteristic.h
//  MPBluetoothKit
//
//  Created by MacPu on 15/10/29.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "MPBluetoothKitBlocks.h"

@class MPPeripheral;
@class MPService;
@class MPDescriptor;

@interface MPCharacteristic : NSObject

/*!
 * @property UUID
 *
 * @discussion
 *      The Bluetooth UUID of the characteristic.
 *
 */
@property(readonly, nonatomic, nullable) CBUUID *UUID;

/*!
 * @property service
 *
 *  @discussion
 *      A back-pointer to the service this characteristic belongs to.
 *
 */
@property(assign, readonly, nonatomic, nullable) MPService *service;

/*!
 * @property properties
 *
 *  @discussion
 *      The properties of the characteristic.
 *
 */
@property(readonly, nonatomic) CBCharacteristicProperties properties;

/*!
 * @property value
 *
 *  @discussion
 *      The value of the characteristic.
 *
 */
@property(retain, readonly, nullable) NSData *value;

/*!
 * @property descriptors
 *
 *  @discussion
 *      A list of the CBDescriptors that have so far been discovered in this characteristic.
 *
 */
@property(retain, readonly, nullable) NSArray<MPDescriptor *> *descriptors;

/*!
 * @property isBroadcasted
 *
 *  @discussion
 *      Whether the characteristic is currently broadcasted or not.
 *
 */
@property(readonly) BOOL isBroadcasted NS_DEPRECATED(NA, NA, 5_0, 8_0);

/*!
 * @property isNotifying
 *
 *  @discussion
 *      Whether the characteristic is currently notifying or not.
 *
 */
@property(readonly) BOOL isNotifying;

@property (nonatomic, weak, readonly, nullable) MPPeripheral *ownPeripheral;

- (nullable instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithCharacteristic:(nullable CBCharacteristic *)characteristic andOwnPeripheral:(nullable MPPeripheral *)peripheral;

- (void)readValueWithBlock:(nullable MPPeripheralReadValueForCharacteristicBlock)block;

- (void)writeValue:(nullable NSData *)data
              type:(CBCharacteristicWriteType)type
         withBlock:(nullable MPPeripheralWriteValueForCharacteristicsBlock)block;

- (void)setNotifyValue:(BOOL)enabled
             withBlock:(nullable MPPeripheralNotifyValueForCharacteristicsBlock)block;

- (void)discoverDescriptorsWithBlock:(nullable MPPeripheralDiscoverDescriptorsForCharacteristicBlock)block;

@end