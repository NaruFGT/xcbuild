/**
 Copyright (c) 2015-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree.
 */

#include <pbxbuild/Tool/Context.h>

namespace Tool = pbxbuild::Tool;

Tool::Context::
Context(
    xcsdk::SDK::Target::shared_ptr const &sdk,
    std::vector<xcsdk::SDK::Toolchain::shared_ptr> const &toolchains,
    std::string const &workingDirectory,
    Tool::SearchPaths const &searchPaths) :
    _sdk                            (sdk),
    _toolchains                     (toolchains),
    _workingDirectory               (workingDirectory),
    _searchPaths                    (searchPaths),
    _currentPhaseInvocationPriority (0)
{
}

Tool::Context::
~Context()
{
}
