//*********************************************************************************************************************************
//
// PROJECT:							Vantage Weather Library (VWL)
// FILE:								GeneralFunctions
// SUBSYSTEM:						General functions for the library
// LANGUAGE:						C++
// TARGET OS:						WINDOWS/UNIX/LINUX/MAC
// LIBRARY DEPENDANCE:	QtSql, ACL
// NAMESPACE:						weatherlink
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2015 Gavin Blakeman.
//                      This file is part of the Vantage Weather library (VWL).
//
//                      VWL is free software: you can redistribute it and/or modify it under the terms of the GNU General
//                      Public License as published by the Free Software Foundation, either version 2 of the License, or (at your
//                      option) any later version.
//
//                      VWL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
//                      implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
//                      for more details.
//
//                      You should have received a copy of the GNU General Public License along with VWL.  If not, see
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

#include "../Include/GeneralFunctions.h"

#include "../Include/Ccitt.h"

namespace VWL
{
  /// Calculates the CRC for adding an additional byte.
  //
  // 2015-05-18/GGB - Function created.

  uint16_t calculateCRC(uint8_t *data, size_t startIndex, size_t byteCount)
  {
    size_t index;
    size_t extent = startIndex + byteCount;
    uint16_t CRC = 0;

    for (index = startIndex; index < extent; index++)
    {
      CRC  =crc_table[(CRC >> 8) ^ data[index]] ^ (CRC << 8);
    };

    return CRC;
  }

} // namespace WEATHERLINK
