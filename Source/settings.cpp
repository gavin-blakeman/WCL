//*********************************************************************************************************************************
//
// PROJECT:							Vantage Weather Library (VWL)
// FILE:								settings
// SUBSYSTEM:						Settings
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

#include "../Include/settings.h"

namespace VWL
{
  namespace settings
  {

    QSettings settings(ORG_NAME, APPL_NAME);

    /// Function to create default settings for ARID if there are no settings defined when the application starts.
    //
    // 2015-05-17/GGB - Function created.

    void createDefaultSettings()
    {
      settings.setValue(WEATHER_DATABASE, "SQLITE");
      settings.setValue(WEATHER_SQLITE_DRIVERNAME, "QSQLITE");
      settings.setValue(WEATHER_SQLITE_DATABASENAME, "Data/Weather.sqlite");
    }

  }  // namespace settings
}	// namespace WSd
