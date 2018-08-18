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
//                      Copyright 2015, 2018 Gavin Blakeman.
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

#ifndef VWL_SETTINGS_H
#define VWL_SETTINGS_H

#include <Qt>
#include <QSettings>

namespace WCL
{
  namespace settings
  {
    QString const FILENAME                                  ("/etc/WSd/WSd.conf");

    QString const ORG_NAME                                  ("GPLv2");
    QString const APPL_NAME                                 ("VWL");

      // WSd device related information

    QString const WS_IPADDRESS                              ("WS/IPAddress");
    QString const WS_PORT                                   ("WS/Port");
    QString const WS_POLLINTERVAL                           ("WS/Poll Interval");

      // Definitions for the Weather Database section

    QString const WEATHER_DATABASE                          ("Weather Database/Database");

    QString const WEATHER_ORACLE_DRIVERNAME                 ("Weather Database/Oracle XE/DriverName");
    QString const WEATHER_ORACLE_HOSTNAME                   ("Weather Database/Oracle XE/HostName");
    QString const WEATHER_ORACLE_DATABASENAME               ("Weather Database/Oracle XE/DatabaseName");
    QString const WEATHER_ORACLE_USERNAME                   ("Weather Database/Oracle XE/UserName");
    QString const WEATHER_ORACLE_PASSWORD                   ("Weather Database/Oracle XE/Password");
    QString const WEATHER_ORACLE_PORT                       ("Weather Database/Oracle XE/Port");

    QString const WEATHER_ODBC_DRIVERNAME                   ("Weather Database/ODBC/DriverName");
    QString const WEATHER_ODBC_DATASOURCENAME				        ("Weather Database/ODBC/DataSourceName");

    QString const WEATHER_MYSQL_DRIVERNAME                  ("Weather Database/MySQL/DriverName");
    QString const WEATHER_MYSQL_HOSTADDRESS                 ("Weather Database/MySQL/HostAddress");
    QString const WEATHER_MYSQL_DATABASENAME                ("Weather Database/MySQL/DatabaseName");
    QString const WEATHER_MYSQL_PORT                        ("Weather Database/MySQL/Port");
    QString const WEATHER_MYSQL_USERNAME                    ("Weather Database/MySQL/UserName");
    QString const WEATHER_MYSQL_PASSWORD                    ("Weather Database/MySQL/Password");

    QString const WEATHER_SQLITE_DRIVERNAME                 ("Weather Database/SQLite/DriverName");
    QString const WEATHER_SQLITE_DATABASENAME               ("Weather Database/SQLite/DatabaseName");

    QSettings extern settings;

    void createDefaultSettings();
  }

}

#endif // SETTINGS_H
