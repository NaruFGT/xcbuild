/**
 Copyright (c) 2016-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree.
 */

#ifndef __xcdriver_LicenseAction_h
#define __xcdriver_LicenseAction_h

namespace xcdriver {

/*
 * Prints licensing information.
 */
class LicenseAction {
private:
    LicenseAction();
    ~LicenseAction();

public:
    static int
    Run();
};

}

#endif // !__xcdriver_LicenseAction_h
