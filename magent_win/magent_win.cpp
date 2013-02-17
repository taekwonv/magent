// magent_win.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Config.h"
#include <iostream>
#include "Log.h"
#include "..\lib\superstring.h"

#define VERSIONSTRING L"0.1.2013"

static void Help()
{
	std::cout << \
		L"magent" \
		<< std::endl;
}


static void Version()
{
	std::cout << VERSIONSTRING << std::endl;
}


static void Install()
{
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*if (argc < 2)
		goto HELPEXIT;*/

	bool conf = Config::Load(L"magent.conf");

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == L'-')
		{
			if (wcslen(argv[i]) < 2) { goto HELPEXIT; }

			switch (argv[i][1])
			{
			case L'i': // install agent as a service
				Install();
				break;

			case L'c': // read a config file from the specified file
				if (i+1 == argc) { goto HELPEXIT; }
				conf = Config::Load(argv[++i]);
				break;

			case L'-':
				if (wcscmp(argv[i]+2, L"version") == 0) { goto HELPEXIT; }
				if (wcscmp(argv[i]+2, L"help") == 0) {Help(); exit(0); }
				Help();
				exit(1);
			}
		}
	}

	if (!conf) { goto HELPEXIT; }
	Log::SetLevel((Log::typeLevel)sstr::toInt(Config::Get(L"LogLevel").c_str()));
	Log::SetPath(Config::Get(L"LogPath"));
	Log::Record(L"Starting magent verion %s", VERSIONSTRING);

	/**	 Order
		1. Get rules of items from a server
		2. Run each items and acqure data
		3. Report acqured data to the server
		4. return to #1 and repeat
	*/

	// Part. Rule(Item) Update
	//		- rule data format (json)
	//		- active / passive

	// Part. Agent Distribution (Probing)
	//		- for Windows (psexec, smb, winrm ...)
	//		- for Linux

	// Part. Report
	//		- data structure (json)
	
	// Part. Data Acqusition
	//		- Linux
	//		- Windows

	// Part. Install

	// Part. Socket

	return 0;

HELPEXIT:
	Help();
	exit(1);
}

