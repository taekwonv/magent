#ifndef MAGENT_ITEM_H
#define MAGENT_ITEM_H

#include <string>


/**
 *	Item 
 *
 *	@note	: Super class of all Item-derived class.
 *	@author : taekwonv@gmail.com
 *	@modified by
 *		[date name]
 */

class Item
{
public:
	Item() {}	
	virtual ~Item() {}

	bool IsAvailable() const { return m_available; } // if false, it means something is not correct to acquire data. Call GetLastError() for detail reason.
	std::wstring GetLastError() const { return m_lastErr; }
	virtual void Acquire(); // Immediately returns. Acqusition must not block the progress.
	virtual std::wstring PullLastData(); // returns latest value and flush the latest data.

private:
	bool Parse(const std::wstring &itemRawString);
	std::wstring m_lastErr;
	bool m_available;
};


/**
 *	MACRO FUNCTIONS TO SIMPLIPY ItemBuilder AND Item DERIVED CLASSES
 *
 *	@note Please see ItemMatch<T> class to figure out how it works.
 *
 */
#define DECLARE_ITEM(class_name)	static Item *Creator() { return new (class_name); }
#define IMPL_ITEM(class_name, itemfunctionname)	static ItemMatch<class_name> s_##class_name((itemfunctionname))

#endif