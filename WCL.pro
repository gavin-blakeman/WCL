##----------------------------------------------------------------------------------------------------------------------------------
##
## PROJECT:							Weather Class Library
## FILE:								WCL.pro
## SUBSYSTEM:						Project File
## LANGUAGE:						C++
## TARGET OS:						WINDOWS/UNIX/LINUX/MAC
## LIBRARY DEPENDANCE:	None.
## NAMESPACE:						N/A
## AUTHOR:							Gavin Blakeman.
## LICENSE:             GPLv2
##
##                      Copyright 2011-2018 Gavin Blakeman.
##                      This file is part of the Weather Class Library (WCL).
##
##                      WCL is free software: you can redistribute it and/or modify it under the terms of the GNU General
##                      Public License as published by the Free Software Foundation, either version 2 of the License, or (at your
##                      option) any later version.
##
##                      WCL implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
##                      for more details.
##
##                      You should have received a copy of the GNU General Public License along with WCL.  If not, see
##                      <http://www.gnu.org/licenses/>.
##
## OVERVIEW:						Project file for compiling the project
##
## HISTORY:             2011-10-09/GGB - Development of classes for openAIRS
##
##----------------------------------------------------------------------------------------------------------------------------------

QT       -= core gui

TARGET = WCL
TEMPLATE = lib
CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++17

win32:CONFIG(release, debug|release) {
  DESTDIR = "../Library/win32/release"
  OBJECTS_DIR = "../Library/win32/release/object/WCL"
}
else:win32:CONFIG(debug, debug|release) {
  DESTDIR = "../Library/win32/debug"
  OBJECTS_DIR = "../Library/win32/debug/object/WCL"
}
else:unix:CONFIG(release, debug|release) {
  DESTDIR = ""
  OBJECTS_DIR = "objects"
}
else:unix:CONFIG(debug, debug|release) {
  DESTDIR = ""
  OBJECTS_DIR = "objects"
}

INCLUDEPATH += \
  "../boost 1.62" \
  "../cfitsio" \
  "../ACL" \
  "../GCL" \
  "../PCL"

SOURCES += \
    source/WeatherLink.cpp \

HEADERS += \
    include/Ccitt.h \
    include/database.h \
    include/error.h \
    include/GeneralFunctions.h \
    include/settings.h \
    include/WeatherLink.h \
    include/WeatherLinkIP.h


