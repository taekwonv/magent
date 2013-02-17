#ifndef MAGENT_LOG_H
#define MAGENT_LOG_H

#include <string>
#include <fstream>


/**
 *	Log
 *
 *	@author : taekwonv@gmail.com
 */

class Log
{
public:
	typedef enum {LV_NOLOG=0, LV_RECORD=1, LV_DETAIL=2, LV_DEBUG=3} typeLevel;
	static void SetLevel(typeLevel lv) { s_level = lv; }
	static void SetSize(size_t maxsize) { s_maxsize = maxsize; }
	static void SetPath(const std::wstring &logFilePath);
	static void Record(const wchar_t *fmt, ...);
	static void Detail(const wchar_t *fmt, ...);
	static void Debug(const wchar_t *fmt, ...);

	static typeLevel s_level; // RECORD by default
	static size_t s_maxsize;	// in MB
	static std::wstring s_filepath;
	static std::wofstream s_flog;
};

#endif
