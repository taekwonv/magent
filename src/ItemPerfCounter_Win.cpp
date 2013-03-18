#include "ItemPerfCounter_Win.h"
#include "ItemBuilder.h"
#include "Log.h"
#include "win/PerfCounter.h"
#include "superstring/superstring.h"

using namespace std;

                                                                                       
/**
 *  _____ _             _____         ___ _____             _                 _ _ _ _     
 * |     | |_ ___ _____|  _  |___ ___|  _|     |___ _ _ ___| |_ ___ ___      | | | |_|___ 
 *  |- -|   _| -_|     |   __| -_|  _|  _|   --| . | | |   |  _| -_|  _|     | | | | |   |
 * |_____|_| |___|_|_|_|__|  |___|_| |_| |_____|___|___|_|_|_| |___|_|  _____|_____|_|_|_|
 *                                                                     |_____|            
 */

/**

	The follwoing is an example of raw item string of this item.
	"win.perfcounter("\System\File Write Bytes/sec")"

		Format : win.perfcounter( windows performance counter string )

 */

IMPL_ITEM(ItemPerfCounter_Win, L"win.perfcounter");

void ItemPerfCounter_Win::Init(std::wstring &rawItemString)
{
	wstring temp;
	vector<wstring> params;	

	if (!ParseRawItemString(rawItemString, temp, params))
	{
		Log::Record(L"The item [%s] does not have any paramter. Not support.", rawItemString.c_str());
		return;
	}

	m_counterPath = sstr::replace(params[0].c_str(), L"\"", L"");
}

void ItemPerfCounter_Win::Acquire()
{
	PerfCounter pc;
	if (!pc.Add(m_counterPath.c_str()))
	{
		Log::Record(L"%s failed. (%s)", m_counterPath.c_str(), pc.GetLastError().c_str());
		return;
	}

	wstring data;
	pc.Collect(data);
	m_lastDataSet.push_back(data);
}
