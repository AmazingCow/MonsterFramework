//----------------------------------------------------------------------------//
//                  _   _ ____   ___  ____                                    //
//                 | \ | |___ \ / _ \| __ )  ___  _   _ ____                  //
//                 |  \| | __) | | | |  _ \ / _ \| | | |_  /                  //
//                 | |\  |/ __/| |_| | |_) | (_) | |_| |/ /                   //
//                 |_| \_|_____|\___/|____/ \___/ \__, /___|                  //
//                                                |___/                       //
//                                                                            //
//                            Mateus Mesquita                                 //
//                       www.N2OBoyz.com/~n2omatt                             //
//                          N2OMatt@N2OBoyz.com                               //
//                                                                            //
//                   Copyright (C) 2015 Mateus Mesquita.                      //
//                       Copyright (C) 2015 N2OBoyz.                          //
//                                                                            //
//  This software is provided 'as-is', without any express or implied         //
//  warranty. In no event will the authors be held liable for any damages     //
//  arising from the use of this software.                                    //
//                                                                            //
//  Permission is granted to anyone to use this software for any purpose,     //
//  including commercial applications, and to alter it and redistribute it    //
//  freely, subject to the following restrictions:                            //
//                                                                            //
//  1. The origin of this software must not be misrepresented;                //
//     you must not claim that you wrote the original software.               //
//  2. If you use this software in a product, an acknowledgment in the        //
//     product IS HIGHLY APPRECIATED, both in source and binary forms.        //
//     If you will not acknowledge, just send me a email. We'll be VERY       //
//     happy to see our work being used by other people. :)                   //
//     (See opensource.N2OBoyz.com/acknowledgment.html for details).          //
//  3. Altered source versions must be plainly marked as such, and must not   //
//     be misrepresented as being the original software.                      //
//  4. This notice may not be removed or altered from any source              //
//     distribution.                                                          //
//  5. Most important, you must have fun. ;)                                  //
//                                                                            //
//       Visit OpenSource.N2OBoyz.com for more open-source projects.          //
//                                                                            //
//                            Enjoy :)                                        //
//----------------------------------------------------------------------------//

//Header
#include "MonsterFramework/include/UI/TwitterComposer.h"
//MonsterFramework
#include "./private/TwitterComposer_Functions.h"

//Usings
USING_NS_STD_CC_CD_MF

// Static Methods //
bool TwitterComposer::canSendTweet()
{
    return TwitterComposer_CanSendTweet();
}

// CTOR/DTOR //
TwitterComposer::TwitterComposer() :
m_pTarget(nullptr),
m_selector(nullptr)
{
    //Empty...
}
TwitterComposer::TwitterComposer(const std::string &text,
                                 cc::Node *pTarget, mf::SEL_TwitterComposerHandler selector) :
m_text(text),
m_pTarget(pTarget),
m_selector(selector)
{
    //Empty...
}

// Public Methods //
//Text/Image/URL
void TwitterComposer::setText(const std::string &text)
{
    m_text = text;
}
void TwitterComposer::addImage(const std::string &image, const std::string &ext)
{
    m_images.push_back(make_tuple(image, ext));
}
void TwitterComposer::addURL(const std::string &url)
{
    m_urls.push_back(url);
}

//Target
void TwitterComposer::setTarget(cc::Node *target, SEL_TwitterComposerHandler selector)
{
    m_pTarget  = target;
    m_selector = selector;
}

//Show
void TwitterComposer::showTwitterComposerUI()
{
    TwitterComposer_ShowTwitterComposer(m_text,
                                        m_images,
                                        m_urls,
                                        m_pTarget, m_selector);
}