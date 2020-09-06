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
//                      Copyright 2015, 2017-2018, 2020 Gavin Blakeman.
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

#include "include/database.h"

  // Standard C++ library header files.

#include <string>
#include <tuple>

  // WCL header files

#include "include/error.h"
#include "include/settings.h"

  // Miscellaneous library header files.

#include <GCL>
#include <PCL>

namespace WCL
{

  CDatabase database;
  GCL::sqlWriter sqlWriter;

  /// @brief Checks if a record already exists.
  /// @param[in] siteID: The ID of the site to associate with the weather record.
  /// @param[in] instrumentID: The ID of the instrument with the weather record.
  /// @param[in] JD: The date of the record to search.
  /// @returns true - If a record exists for the day.
  /// @version 2015-06-03/GGB - Function created.

  bool CDatabase::dailyRecordExists(std::uint32_t siteID, std::uint32_t instrumentID, ACL::TJD const &JD)
  {
    bool returnValue = false;
    QSqlQuery query(database_);

    sqlWriter.resetQuery();
    std::string sqlString = sqlWriter.select({"TBL_DAYSUMMARY.MJD"}).from({"TBL_DAYSUMMARY"}).
                            where({
                                    GCL::sqlWriter::parameterTriple(std::string("MJD"), std::string("="), JD.MJD()),
                                    GCL::sqlWriter::parameterTriple(std::string("SITE_ID"), std::string("="), siteID),
                                    GCL::sqlWriter::parameterTriple(std::string("INSTRUMENT_ID"), std::string("="), instrumentID),
                                    }).string();

    if ( query.exec(QString::fromStdString(sqlString)) )
    {
      query.first();
      if (query.isValid())
      {
        returnValue = true;
      };
    };

    return returnValue;
  }

  /// Disconnects from the database.
  //
  // 2015-06-01/GGB - Function created.

  void CDatabase::disconnectFromDatabase()
  {
  }

  bool CDatabase::insertDailySummary(unsigned long siteID, unsigned long instrumentID, SDailySummary1 const &record1, SDailySummary2 const &record2, ACL::TJD const &JD)
  {
    QSqlError error;
    bool returnValue = false;
    QSqlQuery query(database_);

    if (!dailyRecordExists(siteID, instrumentID, JD))
    {
      sqlWriter.resetQuery();
      std::string sqlString = sqlWriter.insertInto("TBL_DAYSUMMARY").
                              values({
                                       {"SITE_ID", siteID},
                                       {"INSTRUMENT_ID", instrumentID},
                                       {"MJD", JD.MJD()},
                                       {"hiOutTemp", PCL::CTemperature::convert(static_cast<double>(record1.hiOutTemp)/10, PCL::TU_F, PCL::TU_K)},
                                       {"lowOutTemp", PCL::CTemperature::convert(static_cast<double>(record1.lowOutTemp)/10, PCL::TU_F, PCL::TU_K)},
                                       {"hiInTemp", PCL::CTemperature::convert(static_cast<double>(record1.hiInTemp)/10, PCL::TU_F, PCL::TU_K)},
                                       {"lowInTemp", PCL::CTemperature::convert(static_cast<double>(record1.lowInTemp)/10, PCL::TU_F, PCL::TU_K)},
                                       {"avgOutTemp", PCL::CTemperature::convert(static_cast<double>(record1.avgOutTemp)/10, PCL::TU_F, PCL::TU_K)},
                                       {"avgInTemp", PCL::CTemperature::convert(static_cast<double>(record1.avgInTemp)/10, PCL::TU_F, PCL::TU_K)},
                                       {"hiChill", PCL::CTemperature::convert(static_cast<double>(record1.hiChill)/10, PCL::TU_F, PCL::TU_K)},
                                       {"lowChill", PCL::CTemperature::convert(static_cast<double>(record1.lowChill)/10, PCL::TU_F, PCL::TU_K)},
                                       {"hiDew", PCL::CTemperature::convert(static_cast<double>(record1.hiDew)/10, PCL::TU_F, PCL::TU_K)},
                                       {"lowDew", PCL::CTemperature::convert(static_cast<double>(record1.lowDew)/10, PCL::TU_F, PCL::TU_K)},
                                       {"avgChill", PCL::CTemperature::convert(static_cast<double>(record1.avgChill)/10, PCL::TU_F, PCL::TU_K)},
                                       {"avgDew", PCL::CTemperature::convert(static_cast<double>(record1.avgDew)/10, PCL::TU_F, PCL::TU_K)},
                                       {"hiOutHum", static_cast<double>(record1.hiOutHum) / 10},
                                       {"lowOutHum", static_cast<double>(record1.lowOutHum) / 10},
                                       {"hiInHum", static_cast<double>(record1.hiInHum) / 10},
                                       {"lowInHum", static_cast<double>(record1.lowInHum) / 10},
                                       {"avgOutHum", static_cast<double>(record1.avgOutHum) / 10},
                                       {"hiBar", PCL::CPressure::convert(static_cast<double>(record1.hiBar)/1000, PCL::PU::INHG, PCL::PU::PA)},
                                       {"lowBar", PCL::CPressure::convert(static_cast<double>(record1.lowBar)/1000, PCL::PU::INHG, PCL::PU::PA)},
                                       {"avgBar", PCL::CPressure::convert(static_cast<double>(record1.avgBar)/1000, PCL::PU::INHG, PCL::PU::PA)},
                                       {"hiSpeed", PCL::CVelocity::convert(static_cast<double>(record1.hiSpeed) / 10, PCL::VU_MPH, PCL::VU_MPS) },
                                       {"avgSpeed", PCL::CVelocity::convert(static_cast<double>(record1.avgSpeed) / 10, PCL::VU_MPH, PCL::VU_MPS) },
                                       {"dailyRainTotal", PCL::CDistance::convert(static_cast<double>(record1.dailyRainTotal) / 1000, PCL::DU::INCH, PCL::DU::METER) * 1000},
                                       {"hiRainRate", PCL::CDistance::convert(static_cast<double>(record1.hiRainRate) / 1000, PCL::DU::INCH, PCL::DU::METER) * 1000},
                                       {"dailyUVDose", static_cast<unsigned int>(record1.dailyUVDose)},
                                       {"hiUV", static_cast<unsigned int>(record1.hiUV)},
                                       {"dailySolarEnergy", static_cast<unsigned int>(record2.dailySolarEnergy)},
                                       {"minSunlight", static_cast<unsigned int>(record2.minSunlight)},
                                     }).string();

      if (!query.exec(QString::fromStdString(sqlString)))
      {
        error = query.lastError();
      }
      else
      {
        returnValue = true;
      }
    };

    return returnValue;
  }

  /// @brief Inserts a row (record) into the weather database.
  /// @details A check is made if the record already exists and if it does, the record will not be saved.
  //
  // 2015-03-29/GGB - Function created.

  bool CDatabase::insertRecord(unsigned long siteID, unsigned long instrumentID, SArchiveRecord &record)
  {
    QSqlError error;
    bool returnValue = false;
    QSqlQuery query(database_);
    ACL::TJD JD(record.date.year + 2000, record.date.month, record.date.day);

    if (record.time < 2500 && !recordExists(siteID, instrumentID, JD, record.time))
    {
      sqlWriter.resetQuery();
      std::string sqlString = sqlWriter.insertInto("TBL_ARCHIVE").
                              values({
                                       {"SITE_ID", siteID},
                                       {"INSTRUMENT_ID", instrumentID},
                                       {"MJD", JD.MJD()},
                                       {"TIME", static_cast<unsigned int>(record.time)},
                                       {"outsideTemp", PCL::CTemperature::convert(static_cast<double>(record.temperatureOutside)/10, PCL::TU_F, PCL::TU_K)},
                                       {"hiOutsideTemp", PCL::CTemperature::convert(static_cast<double>(record.temperatureHighOutside)/10, PCL::TU_F, PCL::TU_K)},
                                       {"lowOutsideTemp", PCL::CTemperature::convert(static_cast<double>(record.temperatureLowOutside)/10, PCL::TU_F, PCL::TU_K)},
                                       {"insideTemp", PCL::CTemperature::convert(static_cast<double>(record.temperatureInside)/10, PCL::TU_F, PCL::TU_K)},
                                       {"barometer", PCL::CPressure::convert(static_cast<double>(record.barometer)/1000, PCL::PU::INHG, PCL::PU::PA)},
                                       {"outsideHumidity", static_cast<unsigned int>(record.humidityOutside)},
                                       {"insideHumidity", static_cast<unsigned int>(record.humidityInside)},
                                       {"rain", static_cast<double>(record.rainfall) * 0.2},
                                       {"hiRainRate", static_cast<double>(record.rainRateHigh) * 0.2},
                                       {"windSpeed", PCL::CVelocity::convert(static_cast<double>(record.windSpeedAverage), PCL::VU_MPH, PCL::VU_MPS) },
                                       {"hiWindSpeed", PCL::CVelocity::convert(static_cast<double>(record.windSpeedHigh), PCL::VU_MPH, PCL::VU_MPS) },
                                       {"windDirection", static_cast<unsigned int>(record.prevailingWind)},
                                       {"solarRad", static_cast<unsigned int>(record.solarRadiation)},
                                       {"hiSolarRad", static_cast<unsigned int>(record.solarRadiationHigh)},
                                       {"UV", static_cast<unsigned int>(record.averageUVIndex)},
                                       {"hiUV", static_cast<unsigned int>(record.UVIndexHigh)}
                                     }).string();

      if (!query.exec(QString::fromStdString(sqlString)))
      {
        error = query.lastError();
      }
      else
      {
        returnValue = true;
      }
    };

    return returnValue;
  }

  bool CDatabase::insertRecord(unsigned long siteID, unsigned long instrumentID, const SWeatherDataRecord &record, ACL::TJD const &JD)
  {
    QSqlError error;
    bool returnValue = false;
    QSqlQuery query(database_);
    double dRain, dRate;
    unsigned int modifiedTime, time = record.packedTime;

      // Calculate the correct time value

    modifiedTime = time / 60;                   // Hours
    modifiedTime *= 100;
    modifiedTime += time % 60;                  // Minutes

      // Determine the rain collector type.

    switch(record.rain & 0xF000)
    {
      case 0x0000:
        dRain = 2.54;
        break;
      case 0x1000:
        dRain = 0.254;
        break;
      case 0x2000:
        dRain = 0.2;
        break;
      case 0x3000:
        dRain = 1.0;
        break;
      case 0x6000:
        dRain = 0.1;
        break;
      default:
        CODE_ERROR;
        break;
      };

      dRate = record.hiRainRate * dRain;
      dRain *= record.rain & 0xFFF;

    if (!recordExists(siteID, instrumentID, JD, modifiedTime))
    {
      sqlWriter.resetQuery();
      std::string sqlString = sqlWriter.insertInto("TBL_ARCHIVE").
                              values({
                                       {"SITE_ID", siteID},
                                       {"INSTRUMENT_ID", instrumentID},
                                       {"MJD", JD.MJD()},
                                       {"TIME", static_cast<unsigned int>(modifiedTime)},
                                       {"outsideTemp", PCL::CTemperature::convert(static_cast<double>(record.outsideTemp)/10, PCL::TU_F, PCL::TU_K)},
                                       {"hiOutsideTemp", PCL::CTemperature::convert(static_cast<double>(record.hiOutsideTemp)/10, PCL::TU_F, PCL::TU_K)},
                                       {"lowOutsideTemp", PCL::CTemperature::convert(static_cast<double>(record.lowOutsideTemp)/10, PCL::TU_F, PCL::TU_K)},
                                       {"insideTemp", PCL::CTemperature::convert(static_cast<double>(record.insideTemp)/10, PCL::TU_F, PCL::TU_K)},
                                       {"barometer", PCL::CPressure::convert(static_cast<double>(record.barometer)/1000, PCL::PU::INHG, PCL::PU::PA)},
                                       {"outsideHumidity", static_cast<double>(record.outsideHum) / 10},
                                       {"insideHumidity", static_cast<double>(record.insideHum) / 10},
                                       {"rain", dRain},
                                       {"hiRainRate", dRate},
                                       {"windSpeed", PCL::CVelocity::convert(static_cast<double>(record.windSpeed), PCL::VU_MPH, PCL::VU_MPS) },
                                       {"hiWindSpeed", PCL::CVelocity::convert(static_cast<double>(record.hiWindSpeed), PCL::VU_MPH, PCL::VU_MPS) },
                                       {"windDirection", static_cast<unsigned int>(record.windDirection)},
                                       {"solarRad", static_cast<unsigned int>(record.solarRad)},
                                       {"hiSolarRad", static_cast<unsigned int>(record.hiSolarRad)},
                                       {"UV", static_cast<unsigned int>(record.UV)},
                                       {"hiUV", static_cast<unsigned int>(record.hiUV)}
                                     }).string();

      if (!query.exec(QString::fromStdString(sqlString)))
      {
        error = query.lastError();
      }
      else
      {
        returnValue = true;
      }
    };

    return returnValue;
  }

  /// @brief Connects to the database.
  //
  // 2015-04-01/GGB - Function created

  void CDatabase::connectToDatabase()
  {
    TRACEENTER;

    QString szDatabase(settings::settings.value(settings::WEATHER_DATABASE, QVariant("MYSQL")).toString());

    DEBUGMESSAGE("database == " + szDatabase.toStdString());

    szDatabase.toUpper();

    if (szDatabase == "ORACLE XE")
      OracleXE();
    else if (szDatabase == "ODBC")
      ODBC();
    else if (szDatabase == "MYSQL")
      MySQL();
    else if (szDatabase == "SQLITE")
      SQLite();
    else
    {
      DEBUGMESSAGE("Database type is not known.");
      WCL_ERROR(0x0003);
    };
    TRACEEXIT;
  }

  /// @brief Gets the time of the last weather record.
  //
  /// @version 2015-05-18/GGB - Function created.

  bool CDatabase::lastWeatherRecord(unsigned long siteID, unsigned long instrumentID, uint16_t &MJD, uint16_t &time)
  {
    bool returnValue = false;
    QSqlQuery query(database_);

    sqlWriter.resetQuery();
    std::string sqlString = sqlWriter.select({"TBL_ARCHIVE.MJD", "TBL_ARCHIVE.TIME"}).from({"TBL_ARCHIVE"}).
                            orderBy({
                                      {"MJD", GCL::sqlWriter::DESC},
                                      {"TIME", GCL::sqlWriter::DESC}
                                    }).string();

    if ( query.exec(QString::fromStdString(sqlString)) )
    {
      query.first();
      if (query.isValid())
      {
        MJD = query.value(0).toLongLong();
        time = query.value(1).toLongLong();
        returnValue = true;
      };
    }
    else
    {
      QSqlError error = query.lastError();

        // No record found. Default to realistic values.

      siteID = 0;
      instrumentID = 0;
    };

    return returnValue;
  }

  /// @brief Function for opening an ODBC database.
  /// @details Reads information from the settings and then creates the database connection.
  /// @throws An exception is thrown if the connection cannot be created.
  /// @version 2015-03-30/GGB - Function created.

  void CDatabase::ODBC()
  {
    szConnectionName = settings::settings.value(settings::WEATHER_ODBC_DRIVERNAME, QVariant(QString("QODBC"))).toString();
    database_ = QSqlDatabase::addDatabase(szConnectionName);
    database_.setDatabaseName(settings::settings.value(settings::WEATHER_ODBC_DATASOURCENAME,
                                                        QVariant(QString("OCWS"))).toString());

    if (!database_.open())
    {
      WCL_ERROR(0x0004);		// Unable to contact ODBC driver.
    };
  }

  /// @brief Procedure to open SQLite database.
  /// @throws 0x000A - DATABASE: Unable to contact SQLite driver
  /// @version 2013-01-25/GGB - Function created.

  void CDatabase::SQLite()
  {
    QVariant driverName = settings::settings.value(settings::WEATHER_SQLITE_DRIVERNAME, QVariant(QString("QSQLITE")));

    if (driverName.isNull())
    {
      WCL_ERROR(0x0002);	// Database settings not correct.
    }
    else
    {
      szConnectionName = QString("WEATHER");
      database_ = QSqlDatabase::addDatabase(driverName.toString(), szConnectionName);
      database_.setDatabaseName(settings::settings.value(settings::WEATHER_SQLITE_DATABASENAME,
                                                           QVariant(QString("Data/WEATHER.sqlite"))).toString());

      if ( !database_.open() )
      {
        WCL_ERROR(0x000A);
      };
    };
  }

  /// @brief Function for opening an OracleXE database. Reads the relevant informaiton from the settings and then creates
  ///        the database connection.
  /// @throws An exception is thrown if the connection cannot be created.
  /// @version 2015-04-01/GGB - Function created.

  void CDatabase::OracleXE()
  {
    QVariant driverName = settings::settings.value(settings::WEATHER_ORACLE_DRIVERNAME, QVariant(QString("QOCI")));

    if ( driverName.isNull() )
    {
      WCL_ERROR(0x0002);	// Database settings not correct.
    }
    else
    {
      szConnectionName = settings::settings.value(settings::WEATHER_ORACLE_DRIVERNAME, QVariant(QString("QOCI"))).toString();
      database_ = QSqlDatabase::addDatabase(szConnectionName);
      database_.setHostName(settings::settings.value(settings::WEATHER_ORACLE_HOSTNAME, QVariant(QString("localhost"))).toString());
      database_.setDatabaseName(settings::settings.value(settings::WEATHER_ORACLE_DATABASENAME, QVariant(QString("xe"))).toString());
      database_.setUserName(settings::settings.value(settings::WEATHER_ORACLE_USERNAME, QVariant(QString("ATID"))).toString());
      database_.setPassword(settings::settings.value(settings::WEATHER_ORACLE_PASSWORD, QVariant(QString("ATID"))).toString());
      database_.setPort(settings::settings.value(settings::WEATHER_ORACLE_PORT, QVariant(1521)).toInt());

      if ( !database_.open() )
      {
        WCL_ERROR(0x0005);
      };
    };
  }

  /// @brief Function for connecting to a MySQL database. Reads the information from the settings and then creates the database
  ///        connection.
  /// @exceptions An exception is thrown if the connection cannot be created.
  //
  // 2015-04-01/GGB - Function Created

  void CDatabase::MySQL()
  {
    TRACEENTER;
    QVariant driverName = settings::settings.value(settings::WEATHER_MYSQL_DRIVERNAME, QVariant(QString("QMYSQL")));

    if (driverName.isNull())
    {
      WCL_ERROR(0x0002);	// Database settings not correct.
    }
    else
    {
      szConnectionName = QString("WEATHER");
      database_ = QSqlDatabase::addDatabase(driverName.toString(), szConnectionName);
      database_.setHostName(settings::settings.value(settings::WEATHER_MYSQL_HOSTADDRESS, QVariant(QString("localhost"))).toString());
      database_.setDatabaseName(settings::settings.value(settings::WEATHER_MYSQL_DATABASENAME, QVariant(QString("WEATHER"))).toString());
      database_.setUserName(settings::settings.value(settings::WEATHER_MYSQL_USERNAME, QVariant(QString("WEATHER"))).toString());
      database_.setPassword(settings::settings.value(settings::WEATHER_MYSQL_PASSWORD, QVariant(QString("WEATHER"))).toString());
      database_.setPort(settings::settings.value(settings::WEATHER_MYSQL_PORT, QVariant(3306)).toInt());

      if ( !database_.open() )
      {
        DEBUGMESSAGE("Unable to open database.");
        QSqlError error = database_.lastError();
        WCL_ERROR(0x0006);
      };
    };
    TRACEEXIT;
  }

  /// Checks if a record exists.
  //
  // 2015-06-03/GGB - Function created.

  bool CDatabase::recordExists(unsigned long siteID, unsigned long instrumentID, ACL::TJD JD, uint16_t time)
  {
    bool returnValue = false;
    QSqlQuery query(database_);

    sqlWriter.resetQuery();
    std::string sqlString = sqlWriter.select({"TBL_ARCHIVE.MJD", "TBL_ARCHIVE.TIME"}).from({"TBL_ARCHIVE"}).
                            where({
                                    GCL::sqlWriter::parameterTriple(std::string("MJD"), std::string("="), JD.MJD()),
                                    GCL::sqlWriter::parameterTriple(std::string("TIME"), std::string("="), static_cast<unsigned int>(time)),
                                    GCL::sqlWriter::parameterTriple(std::string("SITE_ID"), std::string("="), siteID),
                                    GCL::sqlWriter::parameterTriple(std::string("INSTRUMENT_ID"), std::string("="), instrumentID),
                                    }).string();

    if ( query.exec(QString::fromStdString(sqlString)) )
    {
      query.first();
      if (query.isValid())
      {
        returnValue = true;
      };
    };

    return returnValue;
  }

  void CDatabase::openDatabase()
  {
    if ( !database_.open() )
    {
      DEBUGMESSAGE("Unable to open database.");
      QSqlError error = database_.lastError();
      WCL_ERROR(0x0006);
    };
  }


    void CDatabase::closeDatabase()
    {
      if (database_.isOpen())
      {
        database_.close();
      };
    }


} // namespace WCL
