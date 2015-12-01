//
//  MPCentralManager.m
//  MPBluetoothKit
//
//  Created by MacPu on 15/10/29.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import "MPCentralManager.h"

#import "MPPeripheral.h"
#import "MPCharacteristic.h"
#import "MPService.h"
#import "MPDescriptor.h"

@interface MPPeripheral()

@property (nonatomic, strong) CBPeripheral *peripheral;

@end

@interface MPCentralManager()<CBCentralManagerDelegate>
{
    MPCentralDidDiscoverPeripheralBlock _didDiscoverPeripheralBlock;
    MPCentralDidConnectPeripheralBlock _didConnectPeripheralBlock;
    MPCentralDidFailToConnectPeripheralBlock _didFailToConnectPeripheralBlock;
    MPCentralDidDisconnectPeripheralBlock _didDisconnectPeripheralBlock;
}

@property (nonatomic, strong) CBCentralManager *centralManager;
@property (nonatomic, strong, readwrite) NSMutableArray *discoveredPeripherals;
@property (nonatomic, strong, readwrite) MPPeripheral *connectedPeripheral;

@end

@implementation MPCentralManager

- (instancetype)initWithQueue:(dispatch_queue_t)queue
{
    return [self initWithQueue:queue options:nil];
}

- (instancetype)initWithQueue:(dispatch_queue_t)queue options:(NSDictionary<NSString *,id> *)options
{
    self = [super init];
    if (self) {
        _centralManager = [[CBCentralManager alloc] initWithDelegate:self queue:queue options:options];
        _discoveredPeripherals = [[NSMutableArray alloc] init];
    }
    return self;
}

- (CBCentralManagerState)state
{
    return _centralManager.state;
}

- (NSArray<MPPeripheral *> *)retrievePeripheralsWithIdentifiers:(NSArray<NSUUID *> *)identifiers
{
    NSArray *peripherals = [_centralManager retrievePeripheralsWithIdentifiers:identifiers];
    NSMutableArray *array = [[NSMutableArray alloc] initWithCapacity:peripherals.count];
    for(CBPeripheral *peripheral in peripherals){
        MPPeripheral *p = [[MPPeripheral alloc] initWithPeripheral:peripheral];
        [array addObject:p];
    }
    return array;
}

- (NSArray<MPPeripheral *> *)retrieveConnectedPeripheralsWithServices:(NSArray<CBUUID *> *)serviceUUIDs
{
    NSArray *peripherals = [_centralManager retrieveConnectedPeripheralsWithServices:serviceUUIDs];
    NSMutableArray *array = [[NSMutableArray alloc] initWithCapacity:peripherals.count];
    for(CBPeripheral *peripheral in peripherals){
        MPPeripheral *p = [[MPPeripheral alloc] initWithPeripheral:peripheral];
        [array addObject:p];
    }
    return array;
}

- (void)scanForPeripheralsWithServices:(NSArray<CBUUID *> *)serviceUUIDs
                               options:(NSDictionary<NSString *,id> *)options
                             withBlock:(MPCentralDidDiscoverPeripheralBlock)block
{
    _didDiscoverPeripheralBlock = block;
    [_centralManager scanForPeripheralsWithServices:serviceUUIDs options:options];
}

- (void)stopScan
{
    [_discoveredPeripherals removeAllObjects];
    [_centralManager stopScan];
}

- (void)connectPeripheral:(MPPeripheral *)peripheral
                  options:(NSDictionary<NSString *,id> *)options
         withSuccessBlock:(MPCentralDidConnectPeripheralBlock)successBlock
      withDisConnectBlock:(nullable MPCentralDidDisconnectPeripheralBlock)disconnectBlock
{
    _didConnectPeripheralBlock = successBlock;
    _didDisconnectPeripheralBlock = disconnectBlock;
    [_centralManager connectPeripheral:peripheral.peripheral options:options];
}

- (void)cancelPeripheralConnection:(MPPeripheral *)peripheral withBlock:(MPCentralDidDisconnectPeripheralBlock)block
{
    _didDisconnectPeripheralBlock = block;
    [_centralManager cancelPeripheralConnection:peripheral.peripheral];
}

#pragma mark - CBCentralManagerDelegate

- (void)centralManagerDidUpdateState:(CBCentralManager *)central
{
    _centralManager = central;
    [_discoveredPeripherals removeAllObjects];
    if(_updateStateBlock){
        _updateStateBlock(self);
    }
}

- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral
{
    if(_didConnectPeripheralBlock){
        _connectedPeripheral = [[MPPeripheral alloc] initWithPeripheral:peripheral];
        _didConnectPeripheralBlock(self,[[MPPeripheral alloc] initWithPeripheral:peripheral]);
    }
}

- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
{
    if(_didDisconnectPeripheralBlock){
        _didDisconnectPeripheralBlock(self,[[MPPeripheral alloc] initWithPeripheral:peripheral],error);
    }
}

- (void)centralManager:(CBCentralManager *)central
 didDiscoverPeripheral:(CBPeripheral *)peripheral
     advertisementData:(NSDictionary<NSString *,id> *)advertisementData
                  RSSI:(NSNumber *)RSSI
{
    MPPeripheral *mPeripheral = [[MPPeripheral alloc] initWithPeripheral:peripheral];
    BOOL shouldShow = YES;
    NSInteger index = NSNotFound;
    
    if(_filter){
        shouldShow = [_filter centralManager:self shouldShowPeripheral:mPeripheral advertisementData:advertisementData];
    }
    
    if(shouldShow){
        for(MPPeripheral *kPeripheral in _discoveredPeripherals){
            if([kPeripheral.identifier.UUIDString isEqualToString:mPeripheral.identifier.UUIDString]){
                index = [_discoveredPeripherals indexOfObject:kPeripheral];
            }
        }
        
        if(index != NSNotFound){
            [_discoveredPeripherals replaceObjectAtIndex:index withObject:mPeripheral];
        }
        else{
            [_discoveredPeripherals addObject:mPeripheral];
        }
        
        if(_didDiscoverPeripheralBlock){
            _didDiscoverPeripheralBlock(self,mPeripheral,advertisementData,RSSI);
        }
    }
}

- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
{
    if(_didFailToConnectPeripheralBlock){
        _didFailToConnectPeripheralBlock(self,[[MPPeripheral alloc] initWithPeripheral:peripheral],error);
    }
}

@end
