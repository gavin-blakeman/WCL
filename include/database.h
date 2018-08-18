//*********************************************************************************************************************************
//
// PROJECT:							Weather Class Library (WCL)
// FILE:								database
// SUBSYSTEM:						Database class
// LANGUAGE:						C++
// TARGET OS:						WINDOWS/UNIX/LINUX/MAC
// LIBRARY DEPENDANCE:	QtSql, ACL, PCL
// NAMESPACE:						weatherlink
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2015, 2017-2018 Gavin Blakeman.
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

#ifndef WCL_DATABASE_H
#define WCL_DATABASE_H

#include <Qt>
#include <QSqlDatabase>

#include <ACL>

#include "include/WeatherLink.h"
#include "include/WeatherLinkIP.h"

namespace WCL
{
  QString const QDRV_MYSQL("QMYSQL");
  QString const QDRV_ORACLE("QOCI");
  QString const QDRV_ODBC("QODBC");
  QString const QDRV_SQLITE("QSQLITE");

  const int ROLE_FILTERID  = Qt::UserRole + 0;

  class CDatabase
  {
  private:
    virtual void ODBC();
    virtual void OracleXE();
    virtual void MySQL();
    virtual void SQLite();

  protected:
    QString szConnectionName;
    QSqlDatabase database_;

  public:
    CDatabase() : database_() {}

    virtual void connectToDatabase();
    virtual void disconnectFromDatabase();

    bool dailyRecordExists(unsigned long siteID, unsigned long instrumentID, ACL::TJD const &);
    bool insertDailySummary(unsigned long siteID, unsigned long instrumentID, SDailySummary1 const &, SDailySummary2 const &, const ACL::TJD &JD);
    bool insertRecord(unsigned long siteID, unsigned long instrumentID, SArchiveRecord &);
    bool insertRecord(unsigned long siteID, unsigned long instrumentID, SWeatherDataRecord const &, ACL::TJD const &);
    bool lastWeatherRecord(unsigned long siteID, unsigned long instrumentID, uint16_t &, uint16_t &);
    bool recordExists(unsigned long siteID, unsigned long instrumentID, ACL::TJD , uint16_t);
    void openDatabase();
    void closeDatabase();
  };

  CDatabase extern database;

} // namespace WCL

#endif // WCL_DATABASE_H
