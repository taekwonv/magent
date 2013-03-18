/** 
 *	ItemPerfCounter_Win
 *
 *	@author taekwonv@gmail.com
 */


#ifndef MAGENT_ITEMPERFCOUNTER_H
#define MAGENT_ITEMPERFCOUNTER_H

#include <string>
#include "Item.h"


class ItemPerfCounter_Win : public Item
{
public:
	virtual ~ItemPerfCounter_Win() {}

	virtual void Init(std::wstring &rawItemString);
	virtual void Acquire(); // Immediately returns. Acqusition must not block the progress.
	
	DECLARE_ITEM(ItemPerfCounter_Win);

private:
	std::wstring m_counterPath;
};

#endif
