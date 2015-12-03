/**
 Copyright (c) 2015-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree. An additional grant
 of patent rights can be found in the PATENTS file in the same directory.
 */

#include <plist/String.h>
#include <plist/Boolean.h>
#include <plist/Real.h>
#include <plist/Integer.h>

#include <sstream>
#include <iomanip>

using plist::Object;
using plist::String;
using plist::Boolean;
using plist::Integer;
using plist::Real;

Object *String::
copy() const
{
    return new String(value());
}

std::unique_ptr<String> String::
Coerce(Object const *obj)
{
    String *result = nullptr;

    if (obj->type() == Type()) {
        result = CastTo<String>(obj->copy());
    } else if (Real const *real = CastTo<Real>(obj)) {
        std::ostringstream out;
        out << real->value();
        result = String::New(out.str());
    } else if (Integer const *integer = CastTo<Integer>(obj)) {
        result = String::New(std::to_string(integer->value()));
    } else if (Boolean const *boolean = CastTo<Boolean>(obj)) {
        result = String::New(boolean->value() ? "YES" : "NO");
    }

    return std::unique_ptr<String>(result);
}