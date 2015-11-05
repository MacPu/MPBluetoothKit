#MPBluetoothKit
This is a block-based framework for building Bluetooth iOS apps using the CoreBluetooth Framework.Its a very powerful and useful,and very easy to use it . originally developed for BI-CI

####Version
v0.1

## Why you should use this framework
+ ObjectiveC Block-based API for Bluetooth LE communication.
+ It provide a easiest way to use CoreBluetooth framework.
+ This project is activity.
+ It provide some very useful tools

##How to use it

### import it
```object-c
import "MPBluetoothKit.h"
```

###Scan for peripheral
```object-c
MPCentralManager *centralManager = [[MPCentralManager alloc] initWithQueue:queue options:options];
[centralManager scanForPeripheralsWithServices:nil options:nil withBlock:^(MPCentralManager *centralManager,MPPeripheral *peripheral,NSDictionary *advertisementData,NSNumber *RSSI){

  }];
```

###Connecting to a Peripheral

```object-c
[centralManager connectPeripheral:peripheral options:nil withSuccessBlock:^(MPCentralManager *centralManager, MPPeripheral *peripheral) {

  }withDisConnectBlock:^(MPCentralManager *centralManager, MPPeripheral *peripheral, NSError *error) {

    }];
```

###Read a Characteristic
there is two way to read a Characteristic

```object-c
[peripheral readValueForCharacteristic:(nullable MPCharacteristic *)characteristic withBlock:^(MPPeripheral *peripheral,MPCharacteristic *characteristic,NSError *error){

  }];
```
```object-c
[characteristic readValueWithBlock:^(MPPeripheral *peripheral,MPCharacteristic *characteristic,NSError *error){

  }];
```
###Write to a Characteristic
there is two way to write to a characteristic

```object-c

[peripheral writeValue:(nullable NSData *)data
 forCharacteristic:(nullable MPCharacteristic *)characteristic
              type:(CBCharacteristicWriteType)type
         withBlock:^(MPPeripheral *peripheral,MPCharacteristic *characteristic,NSError *error){
         }];
```
```object-c
[characteristic writeValue:(nullable NSData *)data
              type:(CBCharacteristicWriteType)type
         withBlock:^(MPPeripheral *peripheral,MPCharacteristic *characteristic,NSError *error){
         }];
```


more detail on MPBluetoothKit

##Required
+ CoreBluetooth.framework
+ iOS 7.0 or later

##TODO
v0.2
+ add WatchDog  reconnect when disconnected peripheral
