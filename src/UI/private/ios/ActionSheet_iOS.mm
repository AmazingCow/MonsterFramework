//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    ActionSheet_iOS.mm                          //
//              █ █        █ █    MonsterFramework                            //
//               ████████████                                                 //
//             █              █   Copyright (c) 2015 AmazingCow               //
//            █     █    █     █  www.AmazingCow.com                          //
//            █     █    █     █                                              //
//             █              █   N2OMatt - n2omatt@amazingcow.com            //
//               ████████████     www.amazingcow.com/n2omatt                  //
//                                                                            //
//                                                                            //
//                  This software is licensed as BSD-3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment.opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must notbe misrepresented as being the original software.       //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

//Prevent this file being included on non Apple devices.
#ifdef MONSTERFRAMEWORK_IOS

//std
#include <vector>
#include <string>
//Cocoa
#import <UIKit/UIKit.h>
//MonsterFramework
#include "MonsterFramework/include/Utils/MonsterFramework_Utils.h"
#include "MonsterFramework/src/UI/private/ActionSheet_Functions.h"
#include "MonsterFramework/src/Utils/private/Private_Utils.h"

//Usings
USING_NS_STD_CC_CD_MF

// Interface //
@interface ActionSheet_iOS : NSObject <UIActionSheetDelegate>
{
    ActionSheet::Callback _callback;
}

- (id)initWithCallback:(const ActionSheet::Callback &)callback;

- (void)showActionSheetWithTitle:(const string &)title
               cancelButtonTitle:(const string &)cancelButtonTitle
          destructiveButtonTitle:(const string &)destructiveButtonTitle
               otherButtonTitles:(const vector<string> &)otherButtonTitles;

- (NSString *)NSStringOrNilIfEmpty:(const string &)str;

@end


// Implementation //
@implementation ActionSheet_iOS

// Init //
- (id)initWithCallback:(const ActionSheet::Callback &)callback
{
    if(self = [super init])
    {
        _callback = callback;
    }
    return self;
}

// Actions //
- (void)showActionSheetWithTitle:(const string &)title
               cancelButtonTitle:(const string &)cancelButtonTitle
          destructiveButtonTitle:(const string &)destructiveButtonTitle
               otherButtonTitles:(const vector<string> &)otherButtonTitles
{
    //Turn Title, CancelButtonTitle and DestructiveButtonTitle
    //into a ObjC friendly format.
    NSString *titleStr                  = [self NSStringOrNilIfEmpty:title];
    NSString *cancelButtonTitleStr      = [self NSStringOrNilIfEmpty:cancelButtonTitle];
    NSString *destructiveButtonTitleStr = [self NSStringOrNilIfEmpty:destructiveButtonTitle];

    //Buid the UIActionSheet.
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:titleStr
                                                             delegate:self
                                                    cancelButtonTitle:cancelButtonTitleStr
                                               destructiveButtonTitle:destructiveButtonTitleStr
                                                    otherButtonTitles:nil, nil];

    //We need add the OtherButtonTitles into the UIActionSheet so we will iterate
    //for each item in vector and turn it on NSString and add the result on UIActionSheet
    for(auto &title : otherButtonTitles)
    {
        NSString *currentStr = MF_STR_CPP2NS(title);
        [actionSheet addButtonWithTitle:currentStr];
    }

    //Get the referece to RootViewController of application
    //and present the Twitter controller into it.
    UIViewController *rvc = MF_GETAPPRVC();
    [actionSheet showInView:rvc.view];
}

// Helpers //
- (NSString *)NSStringOrNilIfEmpty:(const string &)str
{
    return (str == "") ? nil : [NSString stringWithUTF8String:str.c_str()];
}

// UIActionSheet Delegate //
- (void)actionSheet:(UIActionSheet *)actionSheet didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    //Call the callback, if it exists.
    if(_callback)
    {
        _callback(MF_STR_NS2CPP([actionSheet buttonTitleAtIndex:buttonIndex]),
                  buttonIndex);
    }

    //Memory clean up.
    //The actionShet is straightforward but the self is because we can not
    //mantain self as autorelease so when the user dismiss the mail controller
    //the work of this class is already done too then we must clean up it.
    [actionSheet release];
    [self release];
}
@end

// AlertView_Functions Implementations //
void mf::ActionSheet_ShowActionSheet(const string &title,
                                     const string &cancelButtonTitle,
                                     const string &destructiveButtonTitle,
                                     const vector<string> otherButtonTitles,
                                     const ActionSheet::Callback &callback)
{
    ActionSheet_iOS *instance = [[ActionSheet_iOS alloc] initWithCallback:callback];

    [instance showActionSheetWithTitle:title
                     cancelButtonTitle:cancelButtonTitle
                destructiveButtonTitle:destructiveButtonTitle
                     otherButtonTitles:otherButtonTitles];
}
#endif //MONSTERFRAMEWORK_IOS
