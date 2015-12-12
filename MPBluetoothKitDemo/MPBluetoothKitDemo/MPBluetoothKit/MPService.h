//
//  MPService.h
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

@interface MPService : NSObject

/*!
 * @property UUID
 *
 * @discussion
 *      The Bluetooth UUID of the service.
 *
 */
@property(readonly, nonatomic, nullable) CBUUID *UUID;

/*!
 * @property peripheral
 *
 * @discussion
 *      A back-pointer to the peripheral this service belongs to.
 *
 */
@property(nonatomic, assign, readonly, nullable) MPPeripheral *peripheral;

/*!
 * @property isPrimary
 *
 * @discussion
 *      The type of the service (primary or secondary).
 *
 */
@property(readonly, nonatomic) BOOL isPrimary;

/*!
 * @property includedServices
 *
 * @discussion
 *      A list of included CBServices that have so far been discovered in this service.
 *
 */
@property(retain, readonly, nullable) NSArray<MPService *> *includedServices;

/*!
 * @property characteristics
 *
 * @discussion
 *      A list of CBCharacteristics that have so far been discovered in this service.
 *
 */
@property(retain, readonly, nullable) NSArray<MPCharacteristic *> *characteristics;

- (nullable instancetype)init NS_UNAVAILABLE;
- (nullable instancetype)initWithService:(nullable CBService *)service
                        andOwnPeripheral:(nullable MPPeripheral *)peripheral;

/*!
 *  @method discoverIncludedServices:WithBlock:
 *
 *  @param includedServiceUUIDs A list of <code>CBUUID</code> objects representing the included service types to be discovered. If <i>nil</i>,
 *								all of <i>service</i>s included services will be discovered, which is considerably slower and not recommended.
 *  @param block                callback with this block,(MPPeripheral *peripheral,CBService *service, NSError *error)
 *
 *  @discussion					Discovers the specified included service(s) of <i>self</i>.
 *
 *  @see						MPPeripheralDiscoverIncludedServicesBlock
 */
- (void)discoverIncludedServices:(nullable NSArray<CBUUID *> *)includedServiceUUIDs
                       withBlock:(nullable MPPeripheralDiscoverIncludedServicesBlock)block;

/*!
 *  @method discoverCharacteristics:WithBlock:
 *
 *  @param characteristicUUIDs	A list of <code>CBUUID</code> objects representing the characteristic types to be discovered. If <i>nil</i>,
 *								all characteristics of <i>service</i> will be discovered, which is considerably slower and not recommended.
 *  @param block                callback with this block,(MPPeripheral *peripheral,CBService *service,NSError *error)
 *
 *  @discussion					Discovers the specified characteristic(s) of <i>self</i>.
 *
 *  @see						MPPeripheralDiscoverCharacteristicsBlock
 */
- (void)discoverCharacteristics:(nullable NSArray<CBUUID *> *)characteristicUUIDs
                      withBlock:(nullable MPPeripheralDiscoverCharacteristicsBlock)block;

@end