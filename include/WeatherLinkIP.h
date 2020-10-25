//*********************************************************************************************************************************
//
// PROJECT:							Vantage Weather Library (VWL)
// FILE:								WeatherLinkIP
// SUBSYSTEM:						Functions to use the serial interface
// LANGUAGE:						C++
// TARGET OS:						WINDOWS/UNIX/LINUX/MAC
// LIBRARY DEPENDANCE:	QtSql, ACL
// NAMESPACE:						weatherlink
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2015, 2018, 2020 Gavin Blakeman.
//                      This file is part of the Weather Class Library (WCL)
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

#ifndef VWL_WEATHERLINKIP_H
#define VWL_WEATHERLINKIP_H

  // Standard C++ library header files.

#include <cstdint>

namespace WCL
{
  std::uint64_t const WL_MTU = 1500;

  std::uint8_t const commandReadLinkMemory[] = {'R', 'R', 'D'};
  std::uint8_t const commandReadArchiveMemory[] = {'S', 'R', 'D'};
  std::uint8_t const commandTest[] = {'T', 'E', 'S', 'T' };
  std::uint8_t const commandDMP[] = {'D', 'M', 'P'};
  std::uint8_t const commandDMPAFT[] = {'D', 'M', 'P', 'A', 'F', 'T'};
  std::uint8_t const commandCLRLOG[] = {'C', 'L', 'R', 'L', 'O', 'G'};
  std::uint8_t const commandSETTIME[] = {'S', 'E', 'T', 'T', 'I', 'M', 'E'};
  std::uint8_t const commandSETPER[] = {'S', 'E', 'T', 'P', 'E', 'R'};

  std::uint8_t const wlACK = 0x06;
  std::uint8_t const wlNACK = 0x21;
  std::uint8_t const wlCANCEL = 0x18;
  std::uint8_t const wlLF = 0x0A;
  std::uint8_t const wlCR = 0x0D;
  std::uint8_t const wlESC = 0x1B;

  std::uint8_t const memoryBank0 = 0;
  std::uint8_t const memoryBank1 = 1;

  struct SDate
  {
    unsigned int day:5;
    unsigned int month:4;
    unsigned int year:7;
  } __attribute__((packed));

  struct SArchiveRecord
  {
    SDate date;
    std::uint16_t time;
    std::int16_t temperatureOutside;
    std::int16_t temperatureHighOutside;
    std::int16_t temperatureLowOutside;
    std::uint16_t rainfall;
    std::uint16_t rainRateHigh;
    std::uint16_t barometer;
    std::uint16_t solarRadiation;
    std::uint16_t numberWindSamples;
    std::int16_t temperatureInside;
    std::uint8_t humidityInside;
    std::uint8_t humidityOutside;
    std::uint8_t windSpeedAverage;
    std::uint8_t windSpeedHigh;
    std::uint8_t windSpeedHighDirection;
    std::uint8_t prevailingWind;
    std::uint8_t averageUVIndex;
    std::uint8_t ET;
    std::uint16_t solarRadiationHigh;
    std::uint8_t UVIndexHigh;
    std::int8_t forecastRule;
    std::uint16_t leafTemperature;
    std::uint16_t leafWetness;
    std::uint32_t soilTemperatures;
    std::uint8_t recordType;
    std::uint8_t unused[9];
  } __attribute__((packed));

  struct SDumpPage
  {
    std::uint8_t byteSequence;
    SArchiveRecord record[5];
    std::uint32_t unused;
    std::uint16_t CRC;
  };

  struct SDMPAFTResponse
  {
    std::uint16_t pages;
    std::uint16_t firstRecord;
    std::uint16_t CRC;
  } __attribute__((packed));


}   // namespace WCL

#endif // WCL_WEATHERLINKIP_H
