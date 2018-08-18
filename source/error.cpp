//*********************************************************************************************************************************
//
// PROJECT:							Weather Class Library
// FILE:								error
// SUBSYSTEM:						Error Message Definition
// LANGUAGE:						C++
// TARGET OS:						None.
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:						WCL
// AUTHOR:							Gavin Blakeman (GGB)
// LICENSE:             GPLv2
//
//                      Copyright 2018 Gavin Blakeman.
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

#include "../include/common.h"

  // Standard libraries

#include <string>
#include <vector>

  // GCL Library

#include <GCL>

namespace WCL
{
  class CLoader
  {
  private:
    void loadErrorMessages();

  public:
    CLoader();
  };

  static CLoader loader();    // Calls the loadErrorMessageFunction on creation during startup.

  CLoader::CLoader()
  {
    loadErrorMessages();
  }

  /// @brief Adds the WCL library error codes into the GCL error object.
  /// @throws None.
  /// @version  2018-08-18/GGB - Function created.

  void CLoader::loadErrorMessages()
  {
    std::vector<std::pair<GCL::TErrorCode, std::string>> errors =
    {
      {0x0001, "APPLICATION: Unable to open data file."},
      {0x0002, "DATABASE: Database Settings incorrect."},
      {0x0005, "DATABSE: Unable to open OracleXE database."},
      {0x0006, "DATABASE: Unable to Open MySQL database."},
      {0x000A, "DATABASE: Unable to open SQLite database"},
      {0x3002, "DATABASE: Unknown rain guage size."},
    };

    std::for_each(errors.begin(), errors.end(),
                  [] (std::pair<GCL::TErrorCode, std::string> p) { GCL::CError::addErrorMessage("WCL", p.first, p.second); });
  }

}
