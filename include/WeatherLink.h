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
//                      Copyright 2011-2020 Gavin Blakeman.
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

  // Standard C++ library header files

#include <cstdint>
#include <fstream>
#include <string>

  // Miscellaneous library header files

#include <boost/filesystem.hpp>

namespace WCL
{
  struct DayIndex
  {
    std::int16_t recordsInDay;
    std::int32_t startPos;
  } __attribute__((packed));

  struct SHeaderBlock
  {
    std::uint8_t idCode[16];
    std::int32_t totalRecords;
    DayIndex dayIndex[32];        // Index 0 not used. Index 1 = first day.
  } __attribute__((packed));

  struct SDailySummary1
  {
    std::int8_t dataType;
    std::int8_t reserved;
    std::int16_t dataSpan;
    std::int16_t hiOutTemp, lowOutTemp;
    std::int16_t hiInTemp, lowInTemp;
    std::int16_t avgOutTemp, avgInTemp;
    std::int16_t hiChill, lowChill;
    std::int16_t hiDew, lowDew;
    std::int16_t avgChill, avgDew;
    std::int16_t hiOutHum, lowOutHum;
    std::int16_t hiInHum, lowInHum;
    std::int16_t avgOutHum;
    std::int16_t hiBar, lowBar;
    std::int16_t avgBar;
    std::int16_t hiSpeed, avgSpeed;
    std::int16_t dailyWindRunTotal;
    std::int16_t hi10MinSpeed;
    std::int8_t dirHiSpeed, hi10MinDir;
    std::int16_t dailyRainTotal;
    std::int16_t hiRainRate;
    std::int16_t dailyUVDose;
    std::int8_t hiUV;
    std::int8_t timeValues[27];
  } __attribute__((packed));

  struct SDailySummary2
  {
    std::int8_t dataType;
    std::int8_t reserved;
    std::uint16_t todaysWeather;
    std::int16_t numWindPackets;
    std::int16_t hiSolar;
    std::int16_t dailySolarEnergy;
    std::int16_t minSunlight;
    std::int16_t dailyETTotal;
    std::int16_t hiHeat, lowHeat;
    std::int16_t avgHeat;
    std::int16_t hiTHSW, lowTHSW;
    std::int16_t hiTHW, lowTHW;
    std::int16_t integratedHeatDD65;
    std::int16_t hiWetBulb, lowWetBulb;
    std::int16_t avgWetBuld;
    std::int8_t dirBins[24];
    std::int8_t timeValues[15];
    std::int16_t integratedCoolDD65;
    std::int8_t reserved2[11];
  } __attribute__((packed));

  struct SWeatherDataRecord
  {
    std::int8_t dataType;
    std::int8_t archiveInterval;
    std::int8_t iconFlags;
    std::int8_t moreFlags;
    std::int16_t packedTime;
    std::int16_t outsideTemp;
    std::int16_t hiOutsideTemp;
    std::int16_t lowOutsideTemp;
    std::int16_t insideTemp;
    std::int16_t barometer;
    std::int16_t outsideHum;
    std::int16_t insideHum;
    std::uint16_t rain;
    std::int16_t hiRainRate;
    std::int16_t windSpeed;
    std::int16_t hiWindSpeed;
    std::int8_t windDirection;
    std::int8_t hiWindDirection;
    std::int16_t numWindSamples;
    std::int16_t solarRad, hiSolarRad;
    std::int8_t UV, hiUV;
    std::int8_t leafTemp[4];
    std::int16_t extraRad;
    std::int16_t newSensors[6];
    std::int8_t forecast;
    std::int8_t ET;
    std::int8_t soilTemp[6];
    std::int8_t soilMoisture[6];
    std::int8_t leafWetness[4];
    std::int8_t extraTemp[7];
    std::int8_t extraHum[7];
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
