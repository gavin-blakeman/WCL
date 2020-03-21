//*********************************************************************************************************************************
//
// PROJECT:							Weather Class Library (WCL)
// FILE:								GeneralFunctions
// SUBSYSTEM:						General functions for the library
// LANGUAGE:						C++
// TARGET OS:						WINDOWS/UNIX/LINUX/MAC
// LIBRARY DEPENDANCE:	QtSql, ACL
// NAMESPACE:						weatherlink
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2015, 2020 Gavin Blakeman.
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
// OVERVIEW:						Implments classes and structures for retrieving data from the .WLK weatherlink files.
//
// HISTORY:             2015-03-29 GGB - File Created
//
//*********************************************************************************************************************************

#ifndef WCL_GENERALFUNCTIONS_H
#define VWL_GENERALFUNCTIONS_H

  // Standard C++ library header files

#include <cstddef>
#include <cstdint>

namespace WCL
{

  std::uint16_t calculateCRC(std::uint8_t *, std::size_t startIndex, std::size_t byteCount);

}   // namespace WCL

#endif // VWL_GENERALFUNCTIONS_H
