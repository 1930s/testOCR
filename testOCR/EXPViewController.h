//
//   _______  ________     ______
//  | ____\ \/ /  _ \ \   / / ___|
//  |  _|  \  /| |_) \ \ / / |
//  | |___ /  \|  __/ \ V /| |___
//  |_____/_/\_\_|     \_/  \____|
//
//  EXPViewController
//  testOCR
//
//  Created by Dave Scruton on 12/19/18.
//  Copyright © 2018 Beyond Green Partners. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MessageUI/MessageUI.h>
#import <UIKit/UIKit.h>
#import "DBKeys.h"
#import "OCRWord.h"
#import "OCRDocument.h"
#import "OCRTemplate.h"
#import "EXPObject.h"
#import "EXPTable.h"
#import "EXPCell.h"
#import "EXPDetailVC.h"
#import "spinnerView.h"

#define DB_MODE_NONE 200
#define DB_MODE_EXP 201
#define DB_MODE_INVOICE 202
#define DB_MODE_TEMPLATE 203

@interface EXPViewController : UIViewController <OCRTemplateDelegate,EXPTableDelegate,UITableViewDelegate,UITableViewDataSource,
                    MFMailComposeViewControllerDelegate>
{
    EXPTable *et;
    OCRTemplate *ot;
    
    NSString *tableName;
    int dbMode;
    NSString *batchIDLookup;
    NSString *vendorLookup;
    NSString *invoiceLookup;
    UIImage *barnIcon;
    UIImage *bigbuxIcon;
    UIImage *centIcon;
    UIImage *dollarIcon;
    UIImage *factoryIcon;
    UIImage *globeIcon;
    UIImage *hiIcon;
    
    NSString *sortBy;
    BOOL sortAscending;
    int selectedRow;

    UIRefreshControl *refreshControl;
    spinnerView *spv;
    
    NSArray *sortOptions;

    
}
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UITableView *table;
@property (weak, nonatomic) IBOutlet UIButton *selectButton;
@property (weak, nonatomic) IBOutlet UIView *headerView;

@property (weak, nonatomic) IBOutlet NSString *actData;
@property (weak, nonatomic) IBOutlet NSString *searchType;
@property (weak, nonatomic) IBOutlet UIButton *sortButton;
@property (weak, nonatomic) IBOutlet UIButton *sortDirButton;

@property (weak, nonatomic) IBOutlet NSString *invoiceNumber;

@property (nonatomic , assign) BOOL detailMode;

- (IBAction)doneSelect:(id)sender;
- (IBAction)menuSelect:(id)sender;
- (IBAction)sortSelect:(id)sender;
- (IBAction)sortDirSelect:(id)sender;
- (IBAction)selectSelect:(id)sender;

@end

