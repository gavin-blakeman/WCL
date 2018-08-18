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

#ifndef VWL_ERROR_H
#define VWL_ERROR_H

#include <map>
#include <string>

#include <stdexcept>

#include <GCL>

namespace VWL
{
  struct CErrorMessage;

  class CError : public std::runtime_error
  {
  private:
    static std::map<size_t, std::string> errorMessages;
    size_t errorCode_;

  public:
    inline explicit CError(size_t newError) : std::runtime_error("OCWS Error"), errorCode_(newError) {}

    static void loadErrorMessages();

    virtual std::string errorMessage() const;
    virtual size_t GetErrorCode() const {return errorCode_;}
    virtual void logErrorMessage() const;
  };

  class CCodeError : public CError
  {
  private:
    std::string fileName;
    long lineNo;
    std::string timeStamp;

  public:
    inline explicit CCodeError(const std::string newFile, const std::string newTime, long newLine)
      : CError(0xFFFF), fileName(newFile), lineNo(newLine), timeStamp(newTime) {}

    inline virtual ~CCodeError() throw() {}

    virtual std::string errorMessage() const;
    virtual void logErrorMessage() const;
  };

#define ERROR(errorNo) (throw(VWL::CError(errorNo)))
#define CODEERROR throw (VWL::CCodeError( __FILE__, __TIMESTAMP__, (long) __LINE__) )

} // namespace VWL

#endif // VWL_ERROR_H
