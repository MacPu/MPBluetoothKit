#AAAssetsPicker

##Perview



![I](1.jpg)
![I](2.jpg)
![I](3.jpg)

##How to use it

``` objective-c
AAAssetsPickerViewController *controller = [[AAAssetsPickerViewController alloc] init];
controller.selectedAssets = _selectedAssets;
controller.delegate = self;
controller.assetsFilter = [ALAssetsFilter allAssets];
[self.navigationController pushViewController:controller animated:YES];
```


``` objective-c
@protocol AAAssetsPickerViewControllerDelegate <NSObject>

- (void)assetsPickerViewController:(AAAssetsPickerViewController *)assetsPickerViewController didFinishPickingAssets:(NSArray *)assets;

@optional

- (BOOL)assetsPickerViewController:(AAAssetsPickerViewController *)assetsPickerViewController shouldShowAssetsGroup:(ALAssetsGroup *)assetsGroup;
- (BOOL)assetsPickerViewController:(AAAssetsPickerViewController *)assetsPickerViewController shouldShowAsset:(ALAsset *)asset;
- (BOOL)assetsPickerViewController:(AAAssetsPickerViewController *)assetsPickerViewController isDefaultAssetsGroup:(ALAssetsGroup *)assetsGroup;
- (BOOL)assetsPickerViewController:(AAAssetsPickerViewController *)assetsPickerViewController shouldSelectAsset:(ALAsset *)asset;
- (void)assetsPickerViewController:(AAAssetsPickerViewController *)assetsPickerViewController didSelectedAsset:(ALAsset *)asset;
- (void)assetsPickerViewController:(AAAssetsPickerViewController *)assetsPickerViewController didDeselectedAsset:(ALAsset *)asset;

@end
```
