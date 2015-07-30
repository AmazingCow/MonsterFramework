//----------------------------------------------------------------------------//
//                 █      █                                                   //
//                 ████████                                                   //
//               ██        ██                                                 //
//              ███  █  █  ███    CameraView.cpp                              //
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

//Header
#include "MonsterFramework/include/UI/CameraView.h"
//CameraView Private Functions.
#include "MonsterFramework/src/UI/private/CameraView_Functions.h"

//Usings
USING_NS_STD_CC_CD_MF

// CTOR/DTOR //
CameraView::CameraView()
{
    //Empty..
}
CameraView::~CameraView()
{
    MF_LOG("CameraView - DTOR");
    CC_SAFE_FREE(m_pImageData);
}

// Public Methods //
//Camera Methods.
bool CameraView::canShowCamera() const
{
    return CameraView_CanAccessCamera();
}
bool CameraView::canShowCameraRoll() const
{
    return CameraView_CanAccessCameraRoll();
}

void CameraView::showCameraWithCallback(const CameraView::Callback &func)
{
    clearMemoryAllocatedToImageData();
    CameraView_ShowCamera(func, &m_pImageData, &m_length);

}
void CameraView::showCameraRollWithCallback(const CameraView::Callback &func)
{
    clearMemoryAllocatedToImageData();
    CameraView_ShowCameraRoll(func, &m_pImageData, &m_length);
}

//CleanUp Methods.
void CameraView::clearMemoryAllocatedToImageData()
{
    CC_SAFE_FREE(m_pImageData);
    m_length = 0;
}

//Image Getters.
CameraView::ByteArrayPtr CameraView::getImageData() const
{
    return m_pImageData;
}
CameraView::ByteArrayLength CameraView::getImageDataLength() const
{
    return m_length;
}
cc::Image* CameraView::getCCImage() const
{
    if(!m_pImageData)
        return nullptr;

    auto ccImage = new cc::Image();

    ccImage->initWithImageData(m_pImageData, m_length);
    ccImage->autorelease();

    return ccImage;
}
cc::Texture2D* CameraView::getTexture2d() const
{
    if(!m_pImageData)
        return nullptr;

    auto ccTexture = new cc::Texture2D();

    ccTexture->initWithImage(getCCImage());
    ccTexture->autorelease();

    return ccTexture;
}
cc::Sprite* CameraView::getSprite() const
{
    if(!m_pImageData)
        return nullptr;

    auto sprite = cc::Sprite::createWithTexture(getTexture2d());
    return sprite;
}

//Saving Methods.
void CameraView::saveImageToFilesystem(const std::string &path) const
{
}
void CameraView::saveImageToCameraRoll() const
{
}
