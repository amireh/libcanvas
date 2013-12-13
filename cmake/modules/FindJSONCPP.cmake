# FindJSONCPP.cmake
# --
# Find the JSONCPP library
#
# This module defines:
#   JSONCPP_INCLUDE_DIRS - where to find json/json.h
#   JSONCPP_LIBRARIES    - the jsoncpp library
#   JSONCPP_FOUND        - True if jsoncpp was found

Include(FindModule)
FIND_MODULE(JSONCPP json/json.h "" "" jsoncpp "" "")
