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
//                      Copyright 2015, 2018-2020 Gavin Blakeman.
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
// CLASSES INCLUDED:    CDatabase
//
// CLASS HIERARCHY:     CWeatherLinkDatabaseFile
//
// HISTORY:             2015-03-29 GGB - File Created
//
//*********************************************************************************************************************************

#include "include/GeneralFunctions.h"

#include "include/Ccitt.h"

namespace WCL
{
  /// @brief      Calculates the CRC for adding an additional byte.
  /// @param[in]  data:
  /// @param[in]  startIndex:
  /// @param[in]  byteCount:
  /// @version  2015-05-18/GGB - Function created.

  uint16_t calculateCRC(std::uint8_t *data, std::size_t startIndex, std::size_t byteCount)
  {
    std::size_t index;
    std::size_t extent = startIndex + byteCount;
    std::uint16_t CRC = 0;

    for (index = startIndex; index < extent; index++)
    {
      CRC  = crc_table[(CRC >> 8) ^ data[index]] ^ (CRC << 8);
    };

    return CRC;
  }

} // namespace WCL
