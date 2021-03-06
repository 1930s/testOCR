//
//   ____        _       _  __     ______
//  | __ )  __ _| |_ ___| |_\ \   / / ___|
//  |  _ \ / _` | __/ __| '_ \ \ / / |
//  | |_) | (_| | || (__| | | \ V /| |___
//  |____/ \__,_|\__\___|_| |_|\_/  \____|
//
//  BatchViewController.m
//  testOCR
//
//  Created by Dave Scruton on 12/21/18.
//  Copyright © 2018 Beyond Green Partners. All rights reserved.
//

#import "BatchViewController.h"



@implementation BatchViewController

#define NOCAN_RUN_ALL_BATCHES

//=============DB VC=====================================================
-(id)initWithCoder:(NSCoder *)aDecoder {
    if ( !(self = [super initWithCoder:aDecoder]) ) return nil;

    bbb = [BatchObject sharedInstance];
    bbb.delegate = self;
    [bbb setParent:self];
    vv  = [Vendors sharedInstance];
    authorized = FALSE;
    // 2/4 add months control / options
    fiscalMonths = @[  //Month chooser...
                     @"01-JUL",
                     @"02-AUG",
                     @"03-SEP",
                     @"04-OCT",
                     @"05-NOV",
                     @"06-DEC",
                     @"07-JAN",
                     @"08-FEB",
                     @"09-MAR",
                     @"10-APR",
                     @"11-MAY",
                     @"12-JUN"
                   ];

    return self;
}


//=============Batch VC=====================================================
- (void)viewDidLoad {
    [super viewDidLoad];
    // 1/19 Add spinner busy indicator...
    CGSize csz   = [UIScreen mainScreen].bounds.size;
    spv = [[spinnerView alloc] initWithFrame:CGRectMake(0, 0, csz.width, csz.height)];
    [self.view addSubview:spv];

    [spv start : @"Get batch counts"];
    _outputText.text = @"...";
    _runButton.hidden = TRUE;

    [bbb getBatchCounts];
}

//=============Batch VC=====================================================
- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    //Check for authorization...
    if ([DBClientsManager authorizedClient] || [DBClientsManager authorizedTeamClient])
    {
        //NSLog(@" dropbox authorized...");
        authorized = TRUE;
        bbb.authorized = TRUE;
    } //end auth OK
    else
    {
        //NSLog(@" need to be authorized...");
        //FUnny: this produces a deprecated warning. it's dropbox boilerplate code!
        [DBClientsManager authorizeFromController:[UIApplication sharedApplication]
                                       controller:self
                                          openURL:^(NSURL *url) {
                                              [[UIApplication sharedApplication] openURL:url];
                                          }];
    } //End need auth
    haltingBatchToExitVC = FALSE;
    //Canned month for now...
    batchMonth = @"07-JAN";
    [self->_monthButton setTitle:batchMonth forState:UIControlStateNormal];

} //end viewDidAppear

//=============Batch VC=====================================================
-(void) dismiss
{
    //[_sfx makeTicSoundWithPitch : 8 : 52];
    [spv stop];
    [self dismissViewControllerAnimated : YES completion:nil];
    
}

//=============AddTemplate VC=====================================================
-(void) updateUI
{
   // NSLog(@" updateui step %d showr %d",step,showRotatedImage);
    NSString *s = @"Staged Files by Vendor:\n\n";
    for (NSString *vn in vv.vFolderNames)
    {
        int vc = [bbb getVendorFileCount:vn];
        //NSLog(@" v[%@]: %d",vn,vc);
        s = [s stringByAppendingString:[NSString stringWithFormat:@"%@ :%d\n",vn,vc]];
        
    }
    _outputText.text = s;
    
} //end updateUI

//=============Batch VC=====================================================
// 2/4 new button: fiscal month
- (IBAction)monthSelect:(id)sender
{
    [self monthMenu];
}

//=============Batch VC=====================================================
- (IBAction)cancelSelect:(id)sender
{
    if ([bbb.batchStatus isEqualToString:BATCH_STATUS_RUNNING])
    {
        [self exitBatchMenu];
    }
    else
        [self dismiss];
}

//=============Batch VC=====================================================
- (IBAction)runSelect:(id)sender {
    if (!authorized) return ; //can't get at dropbox w/o login! 

    bbb.batchMonth = batchMonth;
    NSMutableAttributedString *tatString = [[NSMutableAttributedString alloc]initWithString:@"Run Batches..."];
    [tatString addAttribute:NSFontAttributeName value:[UIFont boldSystemFontOfSize:25] range:NSMakeRange(0, tatString.length)];
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:
                                NSLocalizedString(@"Run Batches...",nil)
                                                                   message:nil
                                                            preferredStyle:UIAlertControllerStyleActionSheet];
    [alert setValue:tatString forKey:@"attributedTitle"];
    int vindex = 0;
    for (NSString *s in vv.vNames)
    {
        int vc = [bbb getVendorFileCount:vv.vFolderNames[vindex]];
        [vv.vFileCounts addObject: [NSNumber numberWithInt: vc]]; //Save filecounts for later
        if (vc > 0) //Don't add a batch run option for empty batch folders!
        {
            [alert addAction: [UIAlertAction actionWithTitle:s
                                                  style:UIAlertActionStyleDefault handler:^(UIAlertAction * action) {
                                                      self->vendorName = s;
                                                      self->_outputText.text = @"";
                                                      [self->spv start : @"Run Batch..."];
                                                      [self->bbb clearAndRunBatches : vindex];
                                                  }]];
        }
        vindex++; //Update vendor index (for checking vendor filecounts)
    }
    UIAlertAction *allAction    = [UIAlertAction actionWithTitle:NSLocalizedString(@"Run All",nil)
                                                           style:UIAlertActionStyleDefault handler:^(UIAlertAction * action) {
                                                               self->_outputText.text = @"";
                                                               [self->spv start : @"Run Batch..."];
                                                               [self->bbb clearAndRunBatches : -1];
                                                           }];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"Cancel",nil)
                                                           style:UIAlertActionStyleDefault handler:^(UIAlertAction * action) {
                                                           }];
    [alert addAction:allAction];
    [alert addAction:cancelAction];
    [self presentViewController:alert animated:YES completion:nil];
} //end runSelect

//=============Batch VC=====================================================
// Yes/No to exit UI on batch running...
-(void) exitBatchMenu
{
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:
                                NSLocalizedString(@"Batch Running. Stop Batch?",nil)
                                                                   message:nil
                                                            preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *yesAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"YES",nil)
                                                        style:UIAlertActionStyleDefault handler:^(UIAlertAction * action) {
                                                            self->haltingBatchToExitVC = TRUE;
                                                            [self->bbb haltBatch];
                                                        }];
    UIAlertAction *noAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"NO",nil)
                                                       style:UIAlertActionStyleDefault handler:^(UIAlertAction * action) {
                                                       }];
    //DHS 3/13: Add owner's ability to delete puzzle
    [alert addAction:yesAction];
    [alert addAction:noAction];
    [self presentViewController:alert animated:YES completion:nil];
    
} //end exitBatchMenu

//=============Batch VC=====================================================
// For selecting fiscal month
-(void) monthMenu
{
    NSMutableAttributedString *tatString = [[NSMutableAttributedString alloc]initWithString:@"Select Fiscal Month"];
    [tatString addAttribute:NSFontAttributeName value:[UIFont boldSystemFontOfSize:25] range:NSMakeRange(0, tatString.length)];
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:
                                NSLocalizedString(@"Select Database Table",nil)
                                                                   message:nil
                                                            preferredStyle:UIAlertControllerStyleActionSheet];
    
    [alert setValue:tatString forKey:@"attributedTitle"];
    
    for (NSString *month in fiscalMonths)
    {
        [alert addAction:[UIAlertAction actionWithTitle:NSLocalizedString(month,nil)
                                 style:UIAlertActionStyleDefault handler:^(UIAlertAction * action) {
                                     self->batchMonth = month;
                                     [self->_monthButton setTitle:month forState:UIControlStateNormal];
                                 }]];
    }
    
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"Cancel",nil)
                                                           style:UIAlertActionStyleDefault handler:^(UIAlertAction * action) {
                                                           }];
    [alert addAction:cancelAction];
    [self presentViewController:alert animated:YES completion:nil];
    
} //end monthMenu


#pragma mark - batchObjectDelegate

//=============<batchObjectDelegate>=====================================================
-(void) didGetBatchCounts
{
    _titleLabel.text = @"Checking Dropbox...";

    dispatch_async(dispatch_get_main_queue(), ^{
        [self updateUI];
        self->_runButton.hidden = FALSE; //OK we can run batches now
        self->_titleLabel.text = @"Batch Processor Ready";;
        [self->spv stop];
    });
}

//=============<batchObjectDelegate>=====================================================
- (void)didCompleteBatch
{
    dispatch_async(dispatch_get_main_queue(), ^{
        self->_titleLabel.text = @"Batch Complete!";
        NSArray *eee = [self->bbb getErrors];
        int ecount   = (int)eee.count;
        NSArray *www = [self->bbb getWarnings];
        int wcount   = (int)www.count;
        [self addToOutputText : [NSString stringWithFormat:@"Batch Complete, Errors:%d Warnings:%d",ecount,wcount]];
        [self->spv stop];
        if (self->haltingBatchToExitVC) [self dismiss];

    });

}

//=============<batchObjectDelegate>=====================================================
- (void)didFailBatch
{
    NSLog(@" batch FAILURE!");
    dispatch_async(dispatch_get_main_queue(), ^{
        [self->spv stop];
    });
}

//=============<batchObjectDelegate>=====================================================
- (void)didUpdateBatchToParse
{
    //NSLog(@" ok batch didUpdateBatchToParse");
}

//=============Batch VC=====================================================
//DHS 1/28 adds text, scrolls text area too!
-(void) addToOutputText : (NSString*)s
{
    NSString *os = self->_outputText.text;
    _outputText.text = [NSString stringWithFormat:@"%@\n%@",os,s];
    // ...and autoscroll UP
    if(self->_outputText.text.length > 0 ) {
        NSRange bottom = NSMakeRange(_outputText.text.length -1, 1);
        [_outputText scrollRangeToVisible:bottom];
    }

}

//=============<batchObjectDelegate>=====================================================
- (void)batchUpdate : (NSString *) s
{
    dispatch_async(dispatch_get_main_queue(), ^{
        self->_titleLabel.text = s;
        [self addToOutputText:s];
    });
}


@end
