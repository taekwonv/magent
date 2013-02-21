#ifndef MAGENT_WINSERVICE_H
#define MAGENT_WINSERVICE_H

#include <string>


/**
 *	Functionality to manipulate Windows Service
 *
 *	@author : taekwonv@gmail.com
 *	@modified by
 *		[date name]
 *		...
 */

class WinService
{
public:
	static bool CreateService(const std::wstring &binPath, const std::wstring &cfgPath);
	static bool StartService();
	static bool StopService();	
	static bool RemoveService();
	static std::wstring GetLastError() { return s_lastError; }

private:
	static std::wstring s_lastError;
};

#endif
