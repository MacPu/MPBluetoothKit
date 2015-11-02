//
//  MPService.m
//  MPBluetoothKit
//
//  Created by MacPu on 15/10/29.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import "MPService.h"
#import "MPPeripheral.h"
#import "MPCharacteristic.h"

@interface MPService()

@property (nonatomic, strong) CBService *service;
@property (nonatomic, weak) MPPeripheral *ownPeipheral;

@end

@implementation MPService

-(instancetype)initWithService:(CBService *)service andOwnPeripheral:(MPPeripheral *)peripheral
{
    self = [super init];
    if (self) {
        _service = service;
        _ownPeipheral = peripheral;
    }
    return self;
}

- (CBUUID *)UUID
{
    return _service.UUID;
}

- (MPPeripheral *)peripheral
{
    return _ownPeipheral;
}

- (BOOL)isPrimary
{
    return _service.isPrimary;
}

- (NSArray<MPService *> *)includedServices
{
    NSMutableArray *array = [[NSMutableArray alloc] init];
    for(CBService *service in _service.includedServices){
        [array addObject:[[MPService alloc] initWithService:service andOwnPeripheral:_ownPeipheral]];
    }
    return array;
}

- (NSArray<MPCharacteristic *> *)characteristics
{
    NSMutableArray *array = [[NSMutableArray alloc] init];
    for(CBCharacteristic *characteristic in _service.characteristics){
        [array addObject:[[MPCharacteristic alloc] initWithCharacteristic:characteristic andOwnPeripheral:_ownPeipheral]];
    }
    return array;
}

- (void)discoverCharacteristics:(NSArray<CBUUID *> *)characteristicUUIDs withBlock:(MPPeripheralDiscoverCharacteristicsBlock)block
{
    if(_ownPeipheral){
        [_ownPeipheral discoverCharacteristics:characteristicUUIDs forService:self withBlock:[block copy]];
    }
}

- (void)discoverIncludedServices:(NSArray<CBUUID *> *)includedServiceUUIDs withBlock:(MPPeripheralDiscoverIncludedServicesBlock)block
{
    if(_ownPeipheral){
        [_ownPeipheral discoverIncludedServices:includedServiceUUIDs forService:self withBlock:[block copy]];
    }
}

@end