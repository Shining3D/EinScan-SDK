// ==========================================================================
// File name:	sn3DStringHelper.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	
// -
// Histroy:		
// ============================================================================

#ifndef _sn3DStringHelper_H
#define _sn3DStringHelper_H

#include <string>
#include <vector>
#include "sn3Dglobaldef.h"

namespace sn3DCore {

	// Convert the string given to a number. Returns true if successful.
	bool  strToNum(std::tstring s, double& num);
	
	// Converts the number given to a string.
	std::tstring  numToStr(double num);
	
	// Convert the string given to a int. Returns true if successful.
	bool  strToInt(std::tstring s, int& num);
	
	// Convert the string given to a float. Returns true if successful.
	bool  strToFloat(std::tstring s, float& num);
	
	// Converts num to a string
	std::tstring  intToStr(int i);
	
	// Converts float to a string
	std::tstring  floatToStr(float f);
	
	// Trims the string (deletes spaces at the beginning and the end)
	std::tstring  trimStr(std::tstring s);
	
	// Deletes the leading spaces in the string and returns the result
	std::tstring  lTrimStr(std::tstring s);
	
	// Deletes the trailing spaces in the string and returns the result
	std::tstring  rTrimStr(std::tstring s);
	
	// Converts the string into lower case and returns the result
	std::tstring  strLCase(std::tstring s);
	
	// Converts the string into upper case and returns the result
	std::tstring  strUCase(std::tstring s);
	
	// Removes all double spaces from the string (i.e. makes them single spaces)
	std::tstring  removeDblSpace(std::tstring s);
	
	// Extracts the characters up to a certain character (see detailed descr.)
	std::tstring  extractToChar(std::tstring& s, TCHAR c);

	
	// Splits s into substrings, splitted by splitchars
	// Example: splitString( "hello world!\n bye", " \n" ) ----> "hello", "world!", "bye"
	std::vector<std::tstring>  splitString( const std::tstring &s, const std::tstring &splitchars);

	
	// Example: "dir/test.abc" -> "test.abc"
	std::tstring  removePathFromFilename( const std::tstring &filename );
	
	// Example: "dir/test.abc" -> "dir/"
	std::tstring  removeFilenameFromPath( const std::tstring &filename );

	// Cuts string ( by removing all characters behind maxLength), if length > maxLength 
	std::tstring  cutString( const std::tstring str, unsigned int maxLength );

	// Replaces every substring in str with rStr
	std::tstring  replaceSubStrings( const std::tstring str, const std::tstring substring, const std::tstring rStr );

	// returns a string with format [y years][d days ][h:][m:]s.ms calculated from time, time in ms
	std::tstring  getTimeString( unsigned int time, bool milliseconds=false );

	// returns string with the file name ending or "." if no ending exists, e.g. input:"dir/myFile.txt" output:".txt"
	std::tstring  extractFileExt( const std::tstring &s );

	// converts all '/' characters to '\'
	std::tstring  allDirSeperatorsToDos(const std::tstring filename);

	// converts all '\' characters to '/'
	std::tstring  allDirSeperatorsToUnix(const std::tstring filename);

	// pads string with zeros in front if length is smaller than numZeroes
	std::tstring  fillNumberStringWithZeros(const std::tstring number, unsigned numZeros);

	// converts time (in ms) into "[h hours] [m minutes] [s seconds] ms ms"
	std::tstring  convertTimeToString( unsigned int delta_time );

	char*  TextToAscii(const TCHAR *src);

	TCHAR* AsciiToText(const char  *src);
}

#endif
