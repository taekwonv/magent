#include "Item.h"
#include "superstring/superstring.h"

using namespace std;

                     
/** 
 *  _____ _             
 * |     | |_ ___ _____ 
 *  |- -|   _| -_|     |
 * |_____|_| |___|_|_|_|
 *                      
 * 
 */

void Item::Acquire()
{

}

wstring Item::PullLastData() // returns lastest 
{
	return L"";
}

void Item::ParseRawItemString(const std::wstring &itemRawString, wstring &funcName, vector<wstring> &params)
{
	// The following string is an example of itemRawString to understand this.
	// fs.size("/usr/")

	vector<wstring> vec = sstr::split(itemRawString.c_str(), L'(');
	if (vec.size() < 2) { return; }

	funcName= vec[0];
	*(--(vec[1].end())) = L'\0';
	params = sstr::split(vec[1].c_str(), L',');	
}
