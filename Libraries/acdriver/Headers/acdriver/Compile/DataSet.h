/**
 Copyright (c) 2015-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree.
 */

#ifndef __acdriver_Compile_DataSet_h
#define __acdriver_Compile_DataSet_h

#include <xcassets/Asset/Asset.h>
#include <xcassets/Asset/DataSet.h>

#include <memory>

namespace libutil { class Filesystem; }

namespace acdriver {

class Result;

namespace Compile {

class Output;

class DataSet {
private:
    DataSet();
    ~DataSet();

public:
    static bool Compile(
        xcassets::Asset::DataSet const *dataSet,
        libutil::Filesystem *filesystem,
        Output *compileOutput,
        Result *result);
};

}
}

#endif // !__acdriver_Compile_DataSet_h
