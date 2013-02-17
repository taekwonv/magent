#include "Config.h"
#include <fstream>
#include <iostream>
#include "..\lib\superstring.h"

using namespace std;

                         
/**
 *  _____         ___ _     
 * |     |___ ___|  _|_|___ 
 * |   --| . |   |  _| | . |
 * |_____|___|_|_|_| |_|_  |
 *                     |___|
 */


map<wstring, wstring> Config::s_mapValue;


bool Config::Load(const wstring &filepath)
{
	// read and parse conf file
	wifstream fconf;
	wstring line;
	fconf.open(filepath.c_str());
	if (!fconf.is_open()) { return false; }

	while (!fconf.eof())
	{
		getline(fconf, line);
		if (line.size() > 0 && line[0] == L'#') { continue; } // in comment case
		vector<wstring> src = sstr::split(line.c_str(), L'=');		
		if (src.size() < 2) { continue; }
		s_mapValue[src[0]] = src[1];
	}
	
	return true;
}

wstring Config::Get(const wstring &key)
{
	return s_mapValue[key];
}

void Config::ByDefault()
{
	s_mapValue[L"LogFile"] = L"magent.log";
	s_mapValue[L"LogFileSize"] = L"10";
	s_mapValue[L"LogLevel"] = L"1";	// 0 ~ 4 : 0 - nothing, 1 - normal, 2 - debug
	s_mapValue[L"Server"] = L"magent.log";
	s_mapValue[L"ServerPort"] = L"13300";
	s_mapValue[L"ReportFreq"] = L"1";	// times per a minute.
	s_mapValue[L"Timeout"] = L"30";		// timeout in sec for running an item
}
