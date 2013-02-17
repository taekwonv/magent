#include "Log.h"
#include "../lib/superstring.h"
#include <iostream>

using namespace std;


/**            
 *  __            
 * |  |   ___ ___ 
 * |  |__| . | . |
 * |_____|___|_  |
 *           |___|
 */


// Initialize statics
wstring Log::s_filepath;
wofstream Log::s_flog;
size_t Log::s_maxsize		= 10;	// in MB
Log::typeLevel Log::s_level = Log::LV_RECORD; // by default


// To close file before exit 
struct _FileCloser
{
	wofstream &sf;
	_FileCloser(wofstream &f) : sf(f) {}
	~_FileCloser() { if (sf.is_open()) { sf.close(); } 	}
};
static _FileCloser _fc(Log::s_flog);


void Log::SetPath(const wstring &logFilePath)
{
	s_filepath = logFilePath;
	s_flog.open(s_filepath, ios::out | ios::app);
}

void Log::Record(const wchar_t *fmt, ...)
{
	if (!s_flog.is_open() || s_level < int(LV_RECORD)) { return; }

	va_list(al);
	va_start(al, fmt);
	s_flog << sstr::format(fmt, al).c_str() << endl;
}

void Log::Detail(const wchar_t *fmt, ...)
{
	if (!s_flog.is_open() || s_level < int(LV_DETAIL)) { return; }

	va_list(al);
	va_start(al, fmt);
	s_flog << sstr::format(fmt, al).c_str() << endl;
}

void Log::Debug(const wchar_t *fmt, ...)
{
	if (!s_flog.is_open() || s_level < int(LV_DEBUG)) { return; }

	va_list(al);
	va_start(al, fmt);
	s_flog << sstr::format(fmt, al).c_str() << endl;
}
