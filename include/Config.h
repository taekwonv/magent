#ifndef MAGENT_CONFIG_H
#define MAGENT_CONFIG_H

#include <string>
#include <map>


/** 
 *	Config
 *
 *	@author taekwonv@gmail.com
 */

class Config
{
public:
	static bool Load(const std::wstring &filepath);
	static std::wstring Get(const std::wstring &key);

private:
	Config() {}		
	~Config() {}
	void ByDefault();
	static std::map<std::wstring, std::wstring> s_mapValue;
};


#endif