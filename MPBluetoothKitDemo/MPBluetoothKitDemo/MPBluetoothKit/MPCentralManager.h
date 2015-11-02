//
//  MPCentralManager.h
//  MPBluetoothKit
//
//  Created by MacPu on 15/10/29.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "MPBluetoothKitBlocks.h"
#import "MPPeripheral.h"

@class MPCentralManager;

@protocol MPCentralManagerPeripheralFilter <NSObject>

- (BOOL)centralManager:(nullable MPCentralManager *)centralManager
  shouldShowPeripheral:(nullable MPPeripheral *)peripheral
     advertisementData:(nullable NSDictionary<NSString *,id> *)advertisementData;

@end

@interface MPCentralManager : NSObject

/*!
 *  @property state
 *
 *  @discussion The current state of the central, initially set to <code>CBCentralManagerStateUnknown</code>. Updates are provided by required
 *              delegate method {@link centralManagerDidUpdateState:}.
 *
 */
@property(readonly) CBCentralManagerState state;

@property (nonatomic, copy, nullable) MPCentralDidUpdateStateBlock updateStateBlock;

@property (nonatomic, strong, readonly, nullable) MPPeripheral *connectedPeripheral;
@property (nonatomic, strong, readonly, nullable) NSMutableArray<MPPeripheral *> *discoveredPeripherals;
@property (nonatomic, weak, nullable) id<MPCentralManagerPeripheralFilter> filter;

- (nullable instancetype)init NS_UNAVAILABLE;

/*!
 *  @method initWithQueue:
 *
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *
 *  @discussion     The initialization call. The events of the central role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 */
- (nullable instancetype)initWithQueue:(nullable dispatch_queue_t)queue;

/*!
 *  @method initWithQueue:options:
 *
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *  @param options  An optional dictionary specifying options for the manager.
 *
 *  @discussion     The initialization call. The events of the central role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 *	@seealso		CBCentralManagerOptionShowPowerAlertKey
 *	@seealso		CBCentralManagerOptionRestoreIdentifierKey
 *
 */
- (nullable instancetype)initWithQueue:(nullable dispatch_queue_t)queue
                               options:(nullable NSDictionary<NSString *, id> *)options NS_AVAILABLE(NA, 7_0) NS_DESIGNATED_INITIALIZER;

/*!
 *  @method retrievePeripheralsWithIdentifiers:
 *
 *  @param identifiers	A list of <code>NSUUID</code> objects.
 *
 *  @discussion			Attempts to retrieve the <code>CBPeripheral</code> object(s) with the corresponding <i>identifiers</i>.
 *
 *	@return				A list of <code>CBPeripheral</code> objects.
 *
 */
- (nullable NSArray<MPPeripheral *> *)retrievePeripheralsWithIdentifiers:(nullable NSArray<NSUUID *> *)identifiers NS_AVAILABLE(NA, 7_0);

/*!
 *  @method retrieveConnectedPeripheralsWithServices
 *
 *  @discussion Retrieves all peripherals that are connected to the system and implement any of the services listed in <i>serviceUUIDs</i>.
 *				Note that this set can include peripherals which were connected by other applications, which will need to be connected locally
 *				via {@link connectPeripheral:options:} before they can be used.
 *
 *	@return		A list of <code>CBPeripheral</code> objects.
 *
 */
- (nullable NSArray<MPPeripheral *> *)retrieveConnectedPeripheralsWithServices:(nullable NSArray<CBUUID *> *)serviceUUIDs NS_AVAILABLE(NA, 7_0);

/*!
 *  @method scanForPeripheralsWithServices:options:
 *
 *  @param serviceUUIDs A list of <code>CBUUID</code> objects representing the service(s) to scan for.
 *  @param options      An optional dictionary specifying options for the scan.
 *
 *  @discussion         Starts scanning for peripherals that are advertising any of the services listed in <i>serviceUUIDs</i>. Although strongly discouraged,
 *                      if <i>serviceUUIDs</i> is <i>nil</i> all discovered peripherals will be returned. If the central is already scanning with different
 *                      <i>serviceUUIDs</i> or <i>options</i>, the provided parameters will replace them.
 *                      Applications that have specified the <code>bluetooth-central</code> background mode are allowed to scan while backgrounded, with two
 *                      caveats: the scan must specify one or more service types in <i>serviceUUIDs</i>, and the <code>CBCentralManagerScanOptionAllowDuplicatesKey</code>
 *                      scan option will be ignored.
 *
 *  @see                centralManager:didDiscoverPeripheral:advertisementData:RSSI:
 *  @seealso            CBCentralManagerScanOptionAllowDuplicatesKey
 *	@seealso			CBCentralManagerScanOptionSolicitedServiceUUIDsKey
 *
 */
- (void)scanForPeripheralsWithServices:(nullable NSArray<CBUUID *> *)serviceUUIDs
                               options:(nullable NSDictionary<NSString *, id> *)options
                             withBlock:(nullable MPCentralDidDiscoverPeripheralBlock)block;

/*!
 *  @method stopScan:
 *
 *  @discussion Stops scanning for peripherals.
 *
 */
- (void)stopScan;

/*!
 *  @method connectPeripheral:options:
 *
 *  @param peripheral   The <code>CBPeripheral</code> to be connected.
 *  @param options      An optional dictionary specifying connection behavior options.
 *
 *  @discussion         Initiates a connection to <i>peripheral</i>. Connection attempts never time out and, depending on the outcome, will result
 *                      in a call to either {@link centralManager:didConnectPeripheral:} or {@link centralManager:didFailToConnectPeripheral:error:}.
 *                      Pending attempts are cancelled automatically upon deallocation of <i>peripheral</i>, and explicitly via {@link cancelPeripheralConnection}.
 *
 *  @see                BCCentralDidConnectPeripheralBlock
 *  @see                BCCentralDidDisconnectPeripheralBlock
 *  @seealso            CBConnectPeripheralOptionNotifyOnConnectionKey
 *  @seealso            CBConnectPeripheralOptionNotifyOnDisconnectionKey
 *  @seealso            CBConnectPeripheralOptionNotifyOnNotificationKey
 *
 */
- (void)connectPeripheral:(nullable MPPeripheral *)peripheral
                  options:(nullable NSDictionary<NSString *, id> *)options
         withSuccessBlock:(nullable MPCentralDidConnectPeripheralBlock)successBlock
      withDisConnectBlock:(nullable MPCentralDidDisconnectPeripheralBlock)disconnectBlock;

/*!
 *  @method cancelPeripheralConnection:
 *
 *  @param peripheral   A <code>CBPeripheral</code>.
 *
 *  @discussion         Cancels an active or pending connection to <i>peripheral</i>. Note that this is non-blocking, and any <code>CBPeripheral</code>
 *                      commands that are still pending to <i>peripheral</i> may or may not complete.
 *
 *  @see                BCCentralDidDisconnectPeripheralBlock
 *
 */
- (void)cancelPeripheralConnection:(nullable MPPeripheral *)peripheral withBlock:(nullable MPCentralDidDisconnectPeripheralBlock)block;


@end
