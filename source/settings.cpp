﻿//*********************************************************************************************************************************
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
//                      You should have received a copy of the GNU General Public License along with WCL.  If not, see
//                      <http://www.gnu.org/licenses/>.
//
// OVERVIEW:						Implements classes and structures for retrieving data from the .WLK weatherlink files.
//
// CLASSES INCLUDED:    CDatabase
//
// CLASS HIERARCHY:     CWeatherLinkDatabaseFile
//
// HISTORY:             2015-03-29 GGB - File Created
//
//*********************************************************************************************************************************

#include "include/settings.h"

namespace WCL
{
  namespace settings
  {

    QSettings settings(ORG_NAME, APPL_NAME);

    /// @brief Function to create default settings for the weather database if there are no settings defined when the application
    ///        starts.
    /// @throws None.
    /// @version 2015-05-17/GGB - Function created.

    void createDefaultSettings()
    {
      settings.setValue(WEATHER_DATABASE, "SQLITE");
      settings.setValue(WEATHER_SQLITE_DRIVERNAME, "QSQLITE");
      settings.setValue(WEATHER_SQLITE_DATABASENAME, "Data/Weather.sqlite");
    }

  }  // namespace settings
}	// namespace WSd
