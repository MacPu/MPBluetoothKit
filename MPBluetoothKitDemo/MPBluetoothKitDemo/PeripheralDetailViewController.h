//
//  PeripheralDetailViewController.h
//  MPBluetoothKitDemo
//
//  Created by MacPu on 15/11/30.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MPBluetoothKit.h"

@interface PeripheralDetailViewController : UITableViewController

@property (nonatomic, strong) MPPeripheral *peripheral;

@end
