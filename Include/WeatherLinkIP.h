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

#ifndef VWL_WEATHERLINKIP_H
#define VWL_WEATHERLINKIP_H

#include <cstdint>

namespace VWL
{
#define WL_MTU 1500

  uint8_t const commandReadLinkMemory[] = {'R', 'R', 'D'};
  uint8_t const commandReadArchiveMemory[] = {'S', 'R', 'D'};
  uint8_t const commandTest[] = {'T', 'E', 'S', 'T' };
  uint8_t const commandDMP[] = {'D', 'M', 'P'};
  uint8_t const commandDMPAFT[] = {'D', 'M', 'P', 'A', 'F', 'T'};
  uint8_t const commandCLRLOG[] = {'C', 'L', 'R', 'L', 'O', 'G'};
  uint8_t const commandSETTIME[] = {'S', 'E', 'T', 'T', 'I', 'M', 'E'};


  uint8_t const wlACK = 0x06;
  uint8_t const wlNACK = 0x21;
  uint8_t const wlCANCEL = 0x18;
  uint8_t const wlLF = 0x0A;
  uint8_t const wlCR = 0x0D;
  uint8_t const wlESC = 0x1B;

  uint8_t const memoryBank0 = 0;
  uint8_t const memoryBank1 = 1;

  struct SDate
  {
    unsigned int day:5;
    unsigned int month:4;
    unsigned int year:7;
  } __attribute__((packed));

  struct SArchiveRecord
  {
    SDate date;
    uint16_t time;
    int16_t temperatureOutside;
    int16_t temperatureHighOutside;
    int16_t temperatureLowOutside;
    uint16_t rainfall;
    uint16_t rainRateHigh;
    uint16_t barometer;
    uint16_t solarRadiation;
    uint16_t numberWindSamples;
    int16_t temperatureInside;
    uint8_t humidityInside;
    uint8_t humidityOutside;
    uint8_t windSpeedAverage;
    uint8_t windSpeedHigh;
    uint8_t windSpeedHighDirection;
    uint8_t prevailingWind;
    uint8_t averageUVIndex;
    uint8_t ET;
    uint16_t solarRadiationHigh;
    uint8_t UVIndexHigh;
    int8_t forecastRule;
    uint16_t leafTemperature;
    uint16_t leafWetness;
    uint32_t soilTemperatures;
    uint8_t recordType;
    uint8_t unused[9];
  } __attribute__((packed));

  struct SDumpPage
  {
    uint8_t byteSequence;
    SArchiveRecord record[5];
    uint32_t unused;
    uint16_t CRC;
  };

  struct SDMPAFTResponse
  {
    uint16_t pages;
    uint16_t firstRecord;
    uint16_t CRC;
  } __attribute__((packed));


}   // namespace VWL

#endif // VWL_WEATHERLINKIP_H
