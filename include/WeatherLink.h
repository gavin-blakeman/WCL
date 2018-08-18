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
//                      Copyright 2011-2018 Gavin Blakeman.
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

#pragma once

#ifndef WCL_WEATHERLINK_H
#define WCL_WEATHERLINK_H

#include <cstdint>
#include <fstream>
#include <string>

#include <boost/filesystem.hpp>

namespace WCL
{
  struct DayIndex
  {
    boost::int16_t recordsInDay;
    boost::int32_t startPos;
  };

  struct SHeaderBlock
  {
    boost::uint8_t idCode[16];
    boost::int32_t totalRecords;
    DayIndex dayIndex[32];        // Index 0 not used. Index 1 = first day.
  } __attribute__((packed));

  struct SDailySummary1
  {
    boost::int8_t dataType;
    boost::int8_t reserved;
    boost::int16_t dataSpan;
    boost::int16_t hiOutTemp, lowOutTemp;
    boost::int16_t hiInTemp, lowInTemp;
    boost::int16_t avgOutTemp, avgInTemp;
    boost::int16_t hiChill, lowChill;
    boost::int16_t hiDew, lowDew;
    boost::int16_t avgChill, avgDew;
    boost::int16_t hiOutHum, lowOutHum;
    boost::int16_t hiInHum, lowInHum;
    boost::int16_t avgOutHum;
    boost::int16_t hiBar, lowBar;
    boost::int16_t avgBar;
    boost::int16_t hiSpeed, avgSpeed;
    boost::int16_t dailyWindRunTotal;
    boost::int16_t hi10MinSpeed;
    boost::int8_t dirHiSpeed, hi10MinDir;
    boost::int16_t dailyRainTotal;
    boost::int16_t hiRainRate;
    boost::int16_t dailyUVDose;
    boost::int8_t hiUV;
    boost::int8_t timeValues[27];
  } __attribute__((packed));

  struct SDailySummary2
  {
    boost::int8_t dataType;
    boost::int8_t reserved;
    boost::uint16_t todaysWeather;
    boost::int16_t numWindPackets;
    boost::int16_t hiSolar;
    boost::int16_t dailySolarEnergy;
    boost::int16_t minSunlight;
    boost::int16_t dailyETTotal;
    boost::int16_t hiHeat, lowHeat;
    boost::int16_t avgHeat;
    boost::int16_t hiTHSW, lowTHSW;
    boost::int16_t hiTHW, lowTHW;
    boost::int16_t integratedHeatDD65;
    boost::int16_t hiWetBulb, lowWetBulb;
    boost::int16_t avgWetBuld;
    boost::int8_t dirBins[24];
    boost::int8_t timeValues[15];
    boost::int16_t integratedCoolDD65;
    boost::int8_t reserved2[11];
  } __attribute__((packed));

  struct SWeatherDataRecord
  {
    boost::int8_t dataType;
    boost::int8_t archiveInterval;
    boost::int8_t iconFlags;
    boost::int8_t moreFlags;
    boost::int16_t packedTime;
    boost::int16_t outsideTemp;
    boost::int16_t hiOutsideTemp;
    boost::int16_t lowOutsideTemp;
    boost::int16_t insideTemp;
    boost::int16_t barometer;
    boost::int16_t outsideHum;
    boost::int16_t insideHum;
    boost::uint16_t rain;
    boost::int16_t hiRainRate;
    boost::int16_t windSpeed;
    boost::int16_t hiWindSpeed;
    boost::int8_t windDirection;
    boost::int8_t hiWindDirection;
    boost::int16_t numWindSamples;
    boost::int16_t solarRad, hiSolarRad;
    boost::int8_t UV, hiUV;
    boost::int8_t leafTemp[4];
    boost::int16_t extraRad;
    boost::int16_t newSensors[6];
    boost::int8_t forecast;
    boost::int8_t ET;
    boost::int8_t soilTemp[6];
    boost::int8_t soilMoisture[6];
    boost::int8_t leafWetness[4];
    boost::int8_t extraTemp[7];
    boost::int8_t extraHum[7];
  } __attribute__((packed));

  class CWeatherLinkDatabaseFile
  {
  private:
    boost::filesystem::path fileName;
    std::ifstream wlf;

    bool bFileOpen;
    bool bDayRecordValid;
    bool bArchiveRecordValid;

    int dayIndex;
    int archiveIndex;

    SHeaderBlock headerBlock;
    SDailySummary1 dailySummary1;
    SDailySummary2 dailySummary2;

    SDailySummary1 dailySummary1Null;
    SDailySummary2 dailySummary2Null;

    SWeatherDataRecord archiveRecord;
    SWeatherDataRecord archiveRecordNull;

  protected:
  public:
    CWeatherLinkDatabaseFile(boost::filesystem::path const &);
    virtual ~CWeatherLinkDatabaseFile();

    bool openFile();
    bool closeFile();

    bool firstDayRecord();
    bool nextDayRecord();

    bool firstArchiveRecord();
    bool nextArchiveRecord();

    long getRecordCount() const;
    SDailySummary1 const &getDailySummary1() const;
    SDailySummary2 const &getDailySummary2() const;
    SWeatherDataRecord const &getArchiveRecord() const;
    int const &getDay() const { return dayIndex;}

  };


}  // namespace WCL

#endif // WCL_WEATHERLINK_H
