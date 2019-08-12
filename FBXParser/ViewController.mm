//
//  ViewController.m
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/1.
//  Copyright © 2019 Park. All rights reserved.
//

#import "ViewController.h"
#include "PORSFBXImporter.hpp"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    PORSFBXImporter import;
    NSString *path_model = [[NSBundle mainBundle]
                            pathForResource:@"head" ofType:@"FBX"];
    
    import.LoadFBXFile([path_model UTF8String]);
    
}


@end
