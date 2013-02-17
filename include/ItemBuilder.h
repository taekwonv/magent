#ifndef MAGENT_ITEMBUILDER_H
#define MAGENT_ITEMBUILDER_H

#include <string>
#include <map>
#include "Item.h"


/** 
 *	ItemBuilder
 *
 *	@author taekwonv@gmail.com
 */

class ItemBuilder
{
public:
	static Item *Build(std::wstring rawItemString);

	static std::map<std::wstring, Item *(*)()> s_table;
};


/** 
 *	ItemMatch<T>
 *
 *	@author taekwonv@gmail.com
 */

template <class T>
struct ItemMatch
{
	ItemMatch(const std::wstring &key)
	{
		ItemBuilder::s_table[key] = T::Creator;
	}
};

#endif
