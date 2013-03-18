#include "Item.h"
#include "superstring/superstring.h"
#include "lock\Lock.h"

using namespace std;

                     
/** 
 *  _____ _             
 * |     | |_ ___ _____ 
 *  |- -|   _| -_|     |
 * |_____|_| |___|_|_|_|
 *                      
 */


void Item::Acquire()
{
	AutoLock<SpinLock> lock(&m_lock);

	//m_lastDataSet.push_back();
}

void Item::PullLastDataSet(vector<wstring> &output) // returns lastest 
{
	AutoLock<SpinLock> lock(&m_lock);

	output = m_lastDataSet;
	m_lastDataSet.clear();
}

bool Item::ParseRawItemString(const std::wstring &itemRawString, wstring &funcName, vector<wstring> &params)
{
	// The following string is an example of itemRawString to understand this.
	// fs.size("/usr/")

	unsigned pos = itemRawString.find(L'(');
	if (wstring::npos == pos || pos > itemRawString.length() - 3 || itemRawString[itemRawString.length()-1] != L')')
		return false;

	funcName = itemRawString.substr(0, pos);
	wstring temp = itemRawString.substr(pos+1, itemRawString.length());
	*(--(temp.end())) = L'\0';
	params = sstr::split(temp.c_str(), L',');

	return true;
}
