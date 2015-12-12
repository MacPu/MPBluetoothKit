//
//  MPDescriptor.m
//  MPBluetoothKit
//
//  Created by MacPu on 15/10/29.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import "MPDescriptor.h"
#import "MPPeripheral.h"
#import "MPCharacteristic.h"

@interface MPDescriptor()
{
    MPCharacteristic *_ownCharactreistic;
}

@property (nonatomic, strong) CBDescriptor *descriptor;
@property (nonatomic, weak) MPPeripheral *ownPeripheral;

@end

@implementation MPDescriptor

- (instancetype)initWithDescriptor:(CBDescriptor *)descriptor andOwnPeripheral:(MPPeripheral *)peripheral
{
    self = [super init];
    if (self) {
        _descriptor = descriptor;
        _ownPeripheral = peripheral;
    }
    return self;
}

- (CBUUID *)UUID
{
    return _descriptor.UUID;
}

- (MPCharacteristic *)characteristic
{
    if(!_ownCharactreistic){
        _ownCharactreistic = [[MPCharacteristic alloc] initWithCharacteristic:_descriptor.characteristic andOwnPeripheral:_ownPeripheral];
    }
    return _ownCharactreistic;
}

- (id)value
{
    return _descriptor.value;
}

- (void)readValueWithBlock:(MPPeripheralReadValueForDescriptorsBlock)block
{
    if(_ownPeripheral){
        [_ownPeripheral readValueForDescriptor:self withBlock:[block copy]];
    }
}

- (void)writeValue:(NSData *)data withBlock:(MPPeripheralWriteValueForDescriptorsBlock)block
{
    if(_ownPeripheral){
        [_ownPeripheral writeValue:data forDescriptor:self withBlock:[block copy]];
    }
}

@end