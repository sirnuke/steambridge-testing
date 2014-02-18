#!/bin/sh
LIBRARIES=""
INCLUDEPATH=""
LIBRARYPATH=""
DEFINES=""
winemaker bridge.dll --nosource-fix --dll --nomfc --wine32 $DEFINES $INCLUDEPATH $LIBRARYPATH $LIBRARIES
# There HAS to be a better way to do this
sed -i 's/-m32/-m32 -Wall -Wextra -pipe -g/g' bridge.dll/Makefile
