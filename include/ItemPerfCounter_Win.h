#ifndef MAGENT_ITEMPERFCOUNTER_H
#define MAGENT_ITEMPERFCOUNTER_H

#include <string>
#include "Item.h"


/** 
 *	ItemPerfCounter_Win
 *
 *	@author taekwonv@gmail.com
 */

class ItemPerfCounter_Win : public Item
{
public:
	virtual ~ItemPerfCounter_Win() {}

	virtual void Init(std::wstring &rawItemString);
	virtual void Acquire(); // Immediately returns. Acqusition must not block the progress.
	virtual std::wstring PullLastData(); // returns latest value and flush the latest data.		

	DECLARE_ITEM(ItemPerfCounter_Win);
};

#endif
