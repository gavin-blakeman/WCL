//*********************************************************************************************************************************
//
// PROJECT:							Weather Class Library
// FILE:								common
// SUBSYSTEM:						Common definitions
// LANGUAGE:						C++
// TARGET OS:						None.
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:						WCL
// AUTHOR:							Gavin Blakeman (GGB)
// LICENSE:             GPLv2
//
//                      Copyright 2018, 2020 Gavin Blakeman.
//                      This file is part of the Weather Class Library (WCL).
//
//                      WCL is free software: you can redistribute it and/or modify it under the terms of the GNU General
//                      Public License as published by the Free Software Foundation, either version 2 of the License, or (at your
//                      option) any later version.
//
//                      WCL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
//                      implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
//                      for more details.
//
//                      You should have received a copy of the GNU General Public License along with WCL.  If not, see
//                      <http://www.gnu.org/licenses/>.
//
// OVERVIEW:						Common definitions that can be used by multiple files
//
//
// CLASSES INCLUDED:		None
//
// CLASS HIERARCHY:     None.
//
// FUNCTIONS INCLUDED:  std::string getVersionString()
//
// HISTORY:             2018-08-18 GGB - File created.
//
//*********************************************************************************************************************************

#ifndef WCL_COMMON_H
#define WCL_COMMON_H

#include <string>

namespace ACL
{

  std::string const LIBRARYNAME       = "WCL";

  std::string getVersionString();

}   // namespace ACL

#endif // ACL_COMMON_H
