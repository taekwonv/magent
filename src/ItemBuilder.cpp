#include "ItemBuilder.h"
#include "..\lib\superstring.h"
#include <map>
#include "Log.h"

using namespace std;

map<wstring, Item *(*)()> ItemBuilder::s_table;


/**
 *  _____ _             _____     _ _   _         
 * |     | |_ ___ _____| __  |_ _|_| |_| |___ ___ 
 *  |- -|   _| -_|     | __ -| | | | | . | -_|  _|
 * |_____|_| |___|_|_|_|_____|___|_|_|___|___|_|  
 */


Item *ItemBuilder::Build(std::wstring rawItemString)
{
	// parse rawstring
	vector<wstring> vec = sstr::split(rawItemString.c_str(), L'(');
	Log::Detail(L"Building item for [%s]", vec[0]/*item function name*/.c_str()); 

	auto it = s_table.find(vec[0]);
	if (it == s_table.end())
	{
		Log::Detail(L"No respective class found for the item function name [%s]", vec[0].c_str());
		return NULL;
	}
		
	return s_table[vec[0]](); // create an respective instance
}
