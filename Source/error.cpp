//*********************************************************************************************************************************
//
// PROJECT:							Vantage Weather Library (VWL)
// FILE:								error
// SUBSYSTEM:						Error System
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

#include "../Include/error.h"

#include <QtCore>

#include "boost/lexical_cast.hpp"

namespace VWL
{
  std::map<size_t, std::string> CError::errorMessages;

  struct SErrorCodes
  {
    size_t errorCode_;
    std::string errorMessage;
  };

  SErrorCodes errorArray[] =
  {
    {0x0001, std::string("APPLICATION: Unable to open data file.")},
    {0x3002, std::string("DATABASE: Unknown rain guage size.")},
  };

  /// Returns a string indicating the error message.
  //
  // 2015-03-30/GGB - Function created.

  std::string CError::errorMessage() const
  {
    std::map <size_t, std::string> :: const_iterator errorData;

    if ((errorData = errorMessages.find(errorCode_)) == errorMessages.end() )
    {
        // Error message not found - Error code has not been defined.
        // This is a non-recoverable error.

      exit(0xFFFE);		// Non-recoverable error within an error
    };

    return (errorData->second);
  }

  // Static function to copy all the error messages from the array into the map.
  // The error messages do not have to be in order or contiguous in the array.
  //
  // 2015-03-30/GGB - Function created.

  void CError::loadErrorMessages()
  {
    size_t elements = sizeof(errorArray) / sizeof(SErrorCodes);   // Work out how many elements stored.
    size_t index;

    for (index = 0; index < elements; index++)
      errorMessages[errorArray[index].errorCode_] = errorArray[index].errorMessage;
  }

  /// Function to log the error message to the fileLogger()
  //
  // 2015-03-30/GGB - Function created.

  void CError::logErrorMessage() const
  {
    std::map<size_t, std::string>::const_iterator errorData;

    if ((errorData = errorMessages.find(errorCode_)) == errorMessages.end() )
    {
        // Error message not found - Error code has not been defined.
        // This is a non-recoverable error.

      GCL::logger::defaultLogger().logMessage(GCL::logger::error,
                                           "Non recoverable error within an error in GCL library. Error Code: " +
                                           boost::lexical_cast<std::string>(errorCode_) + ". Terminating");
      exit(0xFFFE);		// Non-recoverable error within an error
    }
    else
      GCL::logger::defaultLogger().logMessage(GCL::logger::warning,
                                           "GCL Error Code: " + boost::lexical_cast<std::string>(errorData->first) +
                                           " - " + errorData->second);
  }

  //********************************************************************************************************************************
  //
  // CCodeError
  //
  //********************************************************************************************************************************

  /// Displays the error message in a QMessageBox.
  //
  // 2015-03-30/GGB - Function created.

  std::string CCodeError::errorMessage() const
  {
    std::ostringstream o;

    o << "A code error has occurred in the GCL Library." << std::endl;
    o << "File name: " << fileName << " dated: " << timeStamp << std::endl;
    o << "Line number: " << lineNo << std::endl;

    return o.str();
  }

  /// Function to log the error message to the fileLogger()
  //
  // 2015-03-30/GGB - Function created.

  void CCodeError::logErrorMessage() const
  {

    //GCL::logger::defaultLogger().logMessage(GCL::logger::error, "A code error has occurred. Version: " + getReleaseString() +
    //                                     ". File Name: " + fileName + ". Line Number: " + boost::lexical_cast<std::string>(lineNo));
  }

} // namespace VWL
