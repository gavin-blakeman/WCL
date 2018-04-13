//*********************************************************************************************************************************
//
// PROJECT:							Weather Class Library
// FILE:								WeatherLink
// SUBSYSTEM:						Database class
// LANGUAGE:						C++
// TARGET OS:						WINDOWS/UNIX/LINUX/MAC
// LIBRARY DEPENDANCE:	QtSql
// NAMESPACE:						WCL
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2011-2017 Gavin Blakeman.
//                      This file is part of the Weather Class Library (WCL)
//
//                      WCL is free software: you can redistribute it and/or modify it under the terms of the GNU General
//                      Public License as published by the Free Software Foundation, either version 2 of the License, or (at your
//                      option) any later version.
//
//                      WCLimplied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
//                      for more details.
//
//                      You should have received a copy of the GNU General Public License along with WCL.  If not, see
//                      <http://www.gnu.org/licenses/>.
//
// OVERVIEW:						Implments classes and structures for retrieving data from the .WLK weatherlink files.
//
// CLASSES INCLUDED:    CWeatherLinkDatabaseFile - Class for interfacing to weatherlink database file.
//
// CLASS HIERARCHY:     CWeatherLinkDatabaseFile
//
// HISTORY:             2011-07-24/GGB - Development of classes for openAIRS
//
//*********************************************************************************************************************************

#include "../Include/WeatherLink.h"

namespace WCL
{
  char idCode[] = {'W', 'D', 'A', 'T', '5', '.', '3', 0, 0, 0, 0, 0, 0, 0, 5, 3};

	//********************************************************************************************************************************
	//
	// CWeatherLinkDatabaseFile
	//
	//********************************************************************************************************************************

  /// @brief Class constructor.
  /// @param[in] szFileName - Name of the file to open.
  /// @throws None.
  /// @version 2011-07-26/GGB - Function created.

  CWeatherLinkDatabaseFile::CWeatherLinkDatabaseFile(const boost::filesystem::path &szFileName) :
    wlf(szFileName.c_str(), std::ifstream::in | std::ifstream::binary), bFileOpen(false), 
    bDayRecordValid(false), bArchiveRecordValid(false), archiveIndex(0)
	{
  }

  /// Class destructor. Ensures that all dynamic memory is released. Also ensures all files are closed.
  //
  // 2011-07-30/GGB - Function created.

  CWeatherLinkDatabaseFile::~CWeatherLinkDatabaseFile()
  {
    closeFile();
    wlf.close();
  }

  /// Closes the file.
  //
  // 2011-07-30/GGB - Function created.

  bool CWeatherLinkDatabaseFile::closeFile()
  {
    if (bFileOpen)
    {
      bFileOpen = false;
      bDayRecordValid = false;
      bArchiveRecordValid = false;
    };
    
    return true;
  }

  bool CWeatherLinkDatabaseFile::firstArchiveRecord()
  {
    return true;
  }

  // Moves the day record pointer to the first day record and retrieves the first day record.
  //
  // 2011-07-30/GGB - Function created.

  bool CWeatherLinkDatabaseFile::firstDayRecord()
  {
    return true;
  }

  // Returns the archive Record or the Null archive record.
  //
  // 2011-07-30/GGB - Function created

  SWeatherDataRecord const &CWeatherLinkDatabaseFile::getArchiveRecord() const
  {
    if (bArchiveRecordValid)
    {
      return archiveRecord;
    }
    else
    {
      return archiveRecordNull;
    }
  }

  // Returns the dailySummary or the Null daily summary.
  //
  // 2011-07-30/GGB - Function created.

  SDailySummary1 const &CWeatherLinkDatabaseFile::getDailySummary1() const
  {
    if (bDayRecordValid)
    {
      return dailySummary1;
    }
    else
    {
      return dailySummary1Null;
    }
  }

  // Returns the dailySummary or the Null daily summary.
  //
  // 2011-07-30/GGB - Function Created.

  SDailySummary2 const &CWeatherLinkDatabaseFile::getDailySummary2() const
  {
    if (bDayRecordValid)
    {
      return dailySummary2;
    }
    else
    {
      return dailySummary2Null;
    }
  }

  /// Returns the number of records in the file.
  //
  // 2011-07-31/GGB - Function created.

  long CWeatherLinkDatabaseFile::getRecordCount() const 
  { 
    if (bFileOpen)
    {
      return headerBlock.totalRecords;
    }
    else
    {
      return -1;
    }
  }
    
  /// Moves the file to the next archive record for the day and loads the archive record
  //
  // 2011-07-31/GGB - Function created.

  bool CWeatherLinkDatabaseFile::nextArchiveRecord()
  {
    if (archiveIndex >= (headerBlock.dayIndex[dayIndex].recordsInDay - 3))
    {
      bArchiveRecordValid = false;
      return false;
    }
    else
    {
      archiveIndex++;
      wlf.seekg(sizeof(SHeaderBlock) + (sizeof(SDailySummary1) * (headerBlock.dayIndex[dayIndex].startPos + 2)) 
        + (sizeof(SWeatherDataRecord) * archiveIndex));
      
      wlf.read(reinterpret_cast<char *>(&archiveRecord), sizeof(SWeatherDataRecord));

      if (wlf.gcount() != sizeof(SWeatherDataRecord))
      {
        bArchiveRecordValid = false;
        return false;
      }
      else if (archiveRecord.dataType == 1)
      {
        bArchiveRecordValid = true;    
        return true;
      }
      else
      {
        bArchiveRecordValid = false;
        return false;
      };
    };
  }

  // Moves the current day record to the next day record. 
  // This also loads the daily summaries and invalidates the archive records.
  //
  //

  bool CWeatherLinkDatabaseFile::nextDayRecord()
  {
    bool bDataValid = false;

    if (dayIndex >= 31)
    {
      bDayRecordValid = false;
      bArchiveRecordValid = false;
      dayIndex = 0;
      return false;
    }
    else
    {
      while ( (dayIndex <= 30) && (!bDataValid) )
      { 
          // Search for the next valid day record.

        dayIndex++;
        if (headerBlock.dayIndex[dayIndex].recordsInDay != 0)
        {
          bDataValid = true;
        }
      };

      if (bDataValid)
      {
          // Load the daily summary records.

        wlf.seekg(sizeof(SHeaderBlock) + sizeof(SDailySummary1) * headerBlock.dayIndex[dayIndex].startPos);
        wlf.read(reinterpret_cast<char *>(&dailySummary1), sizeof(SDailySummary1));
        wlf.read(reinterpret_cast<char *>(&dailySummary2), sizeof(SDailySummary2));

        if (dailySummary1.dataType == 2 && dailySummary2.dataType == 3)
        {
          bDayRecordValid = true;
          bArchiveRecordValid = false;
          archiveIndex = -1;
        
          return true;
        }
        else
        {
          bDayRecordValid = false;
          bArchiveRecordValid = false;
          archiveIndex = -1;
  
          return false;
        };
      }
      else
      {
        bDayRecordValid = false;
        bArchiveRecordValid = false;
        dayIndex = 0;
        return false;
      };
    };
  }

  // Opens the file and verifys that the file is of the correct type.
  //
  // 2011-07-30/GGB - Function created.

  bool CWeatherLinkDatabaseFile::openFile()
  {
    size_t nIndex;
    bool bEquiv = true;

    if (bFileOpen)
    {
      return true;
    }
    else
    {
      if (wlf.fail())
      {
        return false;     // Error when the file was constructed.
      }
      else
      {
          // Check the file details.

        wlf.read((char *) &headerBlock, sizeof(headerBlock));

        for (nIndex = 0; (nIndex < sizeof(idCode)) && bEquiv; nIndex++)     // Check the file type is correct.
        {
          if (headerBlock.idCode[nIndex] != idCode[nIndex])
            bEquiv = false;
        };

        if (!bEquiv)
        {
          return false;
        }
        else
        {
          dayIndex = 0;
          bFileOpen = true;
          bDayRecordValid = false;
          bArchiveRecordValid = false;
          return true;
        };
      
      };
    };
  }

}	// namespace VWL
