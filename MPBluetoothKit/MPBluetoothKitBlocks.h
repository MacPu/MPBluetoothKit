//
//  MPBluetoothKitBlocks.h
//  MPBluetoothKit
//
//  Created by MacPu on 15/10/29.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

@class MPCentralManager;
@class MPPeripheral;
@class MPCharacteristic;
@class MPService;
@class MPDescriptor;

#ifndef MPBluetoothKitBlocks_h
#define MPBluetoothKitBlocks_h

#pragma mark - about central blocks
/**
 ---------------------------------------------------------------------------------------------
 about central blocks
 ---------------------------------------------------------------------------------------------
 */

/** Central manager did discover Peripheral Block */
typedef void (^MPCentralDidDiscoverPeripheralBlock)(MPCentralManager *centralManager,MPPeripheral *peripheral,NSDictionary *advertisementData,NSNumber *RSSI);

/** Central did connect peripheral block */
typedef void (^MPCentralDidConnectPeripheralBlock)(MPCentralManager *centralManager,MPPeripheral *peripheral);

/** central did disconnect peripheral block */
typedef void (^MPCentralDidDisconnectPeripheralBlock)(MPCentralManager *centralManager,MPPeripheral *peripheral,NSError *error);

/** central did update state block */
typedef void (^MPCentralDidUpdateStateBlock)(MPCentralManager *centralManager);

/** central did fail to connect peripheral block */
typedef void (^MPCentralDidFailToConnectPeripheralBlock)(MPCentralManager *centralManager,MPPeripheral *peripheral,NSError *error);



#pragma mark - about peripheral blocks

/**
 ---------------------------------------------------------------------------------------------
 about peripheral blocks
 ---------------------------------------------------------------------------------------------
 */

/** Discovered Services Block */
typedef void (^MPPeripheralDiscoverServicesBlock)(MPPeripheral *peripheral, NSError *error);

/** Discovered Included Services Block */
typedef void (^MPPeripheralDiscoverIncludedServicesBlock)(MPPeripheral *peripheral,MPService *service, NSError *error);

/** Discovered Characteristics Block */
typedef void (^MPPeripheralDiscoverCharacteristicsBlock)(MPPeripheral *peripheral,MPService *service,NSError *error);

/** Read Value For Characteristic Block */
typedef void (^MPPeripheralReadValueForCharacteristicBlock)(MPPeripheral *peripheral,MPCharacteristic *characteristic,NSError *error);

/** Writed Value For Characteristics Block */
typedef void (^MPPeripheralWriteValueForCharacteristicsBlock)(MPPeripheral *peripheral,MPCharacteristic *characteristic,NSError *error);

/** Notified Value For Characteristics Block */
typedef void (^MPPeripheralNotifyValueForCharacteristicsBlock)(MPPeripheral *peripheral,MPCharacteristic *characteristic,NSError *error);

/** Discovered Descriptors For Characteristic Block */
typedef void (^MPPeripheralDiscoverDescriptorsForCharacteristicBlock)(MPPeripheral *peripheral,MPCharacteristic *service,NSError *error);

/** Read Value For DescriptorsBlock */
typedef void (^MPPeripheralReadValueForDescriptorsBlock)(MPPeripheral *peripheral,MPDescriptor *descriptor,NSError *error);

/** Writed Value For Descriptors Block */
typedef void (^MPPeripheralWriteValueForDescriptorsBlock)(MPPeripheral *peripheral,MPDescriptor *descriptor,NSError *error);

/** Red RSSI Block */
typedef void (^MPPeripheralRedRSSIBlock)(MPPeripheral *peripheral,NSNumber *RSSI, NSError *error);

#endif /* MPBluetoothKitBlocks_h */
