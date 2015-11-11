//
//  MPCharacteristic.m
//  MPBluetoothKit
//
//  Created by MacPu on 15/10/29.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import "MPCharacteristic.h"
#import "MPPeripheral.h"
#import "MPService.h"

@interface MPCharacteristic()
{
    MPService *_service;
}

@property (nonatomic, strong) CBCharacteristic *characteristic;
@property (nonatomic, weak, readwrite) MPPeripheral *ownPeripheral;


@end

@implementation MPCharacteristic

- (instancetype)initWithCharacteristic:(CBCharacteristic *)characteristic andOwnPeripheral:(MPPeripheral *)peripheral
{
    self = [super init];
    if(self){
        _characteristic = characteristic;
        _ownPeripheral = peripheral;
    }
    return self;
}

- (CBUUID *)UUID
{
    return _characteristic.UUID;
}

- (MPService *)service
{
    if(!_service){
        _service = [[MPService alloc] initWithService:_characteristic.service andOwnPeripheral:_ownPeripheral];
    };
    return _service;
}

- (CBCharacteristicProperties)properties
{
    return _characteristic.properties;
}

- (NSData *)value
{
    return _characteristic.value;
}

- (NSArray<MPDescriptor *> *)descriptors
{
    return nil;
}

- (BOOL)isBroadcasted
{
    return _characteristic.isBroadcasted;
}

- (BOOL)isNotifying
{
    return _characteristic.isNotifying;
}

- (void)readValueWithBlock:(MPPeripheralReadValueForCharacteristicBlock)block
{
    if(_ownPeripheral){
        [_ownPeripheral readValueForCharacteristic:self withBlock:[block copy]];
    }
}

- (void)writeValue:(NSData *)data type:(CBCharacteristicWriteType)type withBlock:(MPPeripheralWriteValueForCharacteristicsBlock)block
{
    if(_ownPeripheral){
        [_ownPeripheral writeValue:data forCharacteristic:self type:type withBlock:[block copy]];
    }
}


- (void)setNotifyValue:(BOOL)enabled withBlock:(MPPeripheralNotifyValueForCharacteristicsBlock)block
{
    if(_ownPeripheral){
        [_ownPeripheral setNotifyValue:enabled forCharacteristic:self withBlock:[block copy]];
    }
}

- (void)discoverDescriptorsWithBlock:(MPPeripheralDiscoverDescriptorsForCharacteristicBlock)block
{
    if(_ownPeripheral){
        [_ownPeripheral discoverDescriptorsForCharacteristic:self withBlock:[block copy]];
    }
}

@end
