#ifndef XCAMBASLER_H
#define XCAMBASLER_H

#include "xcam.h"
#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigECamera.h>

using namespace Pylon;

class XCamBasler : public XCam
{
public:
    XCamBasler();
    XCamBasler(CInstantCamera* cam);
    ~XCamBasler();

    bool Connect();
    bool IsOpen();
    unsigned char *Capture();

    CInstantCamera* Camera = NULL;

    unsigned char* data = NULL;
};

#endif // XCAMBASLER_H
