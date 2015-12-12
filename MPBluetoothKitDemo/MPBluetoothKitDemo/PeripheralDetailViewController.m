//
//  PeripheralDetailViewController.m
//  MPBluetoothKitDemo
//
//  Created by MacPu on 15/11/30.
//  Copyright © 2015年 www.imxingzhe.com. All rights reserved.
//

#import "PeripheralDetailViewController.h"

NSString *const kCharacteristicCell = @"kCharacteristicCell";
NSString *const kServiceCell = @"kServiceCell";

@interface PeripheralDetailViewController ()

@end

@implementation PeripheralDetailViewController

- (instancetype)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:UITableViewStyleGrouped];
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.title = _peripheral.name;
    [self discoverServices];
    
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:kCharacteristicCell];
    [self.tableView registerClass:[UITableViewHeaderFooterView class] forHeaderFooterViewReuseIdentifier:kServiceCell];
}

- (void)discoverServices
{
    __weak typeof(self) weakSelf = self;
    [_peripheral discoverServices:nil withBlock:^(MPPeripheral *peripheral, NSError *error) {
        for(MPService *service in peripheral.services){
            [weakSelf discoverCharacteristicForServices:service];
        }
    }];
}

- (void)discoverCharacteristicForServices:(MPService *)service
{
    __weak typeof(self) weakSelf = self;
    [service discoverCharacteristics:nil withBlock:^(MPPeripheral *peripheral, MPService *service, NSError *error) {
        [weakSelf.tableView reloadData];
    }];
}

#pragma mark - UITableViewDelegate UITableViewDatasource

 - (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return  [_peripheral.services count];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    MPService *service = [_peripheral.services objectAtIndex:section];
    return [service.characteristics count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kCharacteristicCell forIndexPath:indexPath];
    
    MPService *service = [_peripheral.services objectAtIndex:indexPath.section];
    MPCharacteristic *charactristic = [service.characteristics objectAtIndex:indexPath.row];
    
    cell.textLabel.text = [NSString stringWithFormat:@"Charactristic UUID:%@",[charactristic.UUID UUIDString]];
    
    return cell;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    UITableViewHeaderFooterView *headerView = [tableView dequeueReusableHeaderFooterViewWithIdentifier:kServiceCell];
    if(!headerView){
        headerView = [[UITableViewHeaderFooterView alloc] init];
    }
    
     MPService *service = [_peripheral.services objectAtIndex:section];
    headerView.textLabel.text = [NSString stringWithFormat:@"Service UUID:%@",[service.UUID UUIDString]];
    return headerView;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 50.f;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 0.0001f;
}

@end
