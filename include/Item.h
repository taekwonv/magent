/**
 *	Item 
 *
 *	@note	: Super class of all Item-derived class.
 *	@author : taekwonv@gmail.com
 *	@modified by
 *		[date name]
 */


#ifndef MAGENT_ITEM_H
#define MAGENT_ITEM_H

#include <string>
#include <vector>
#include "lock/SpinLock.h"

class Item
{
public:
	Item() {}	
	virtual ~Item() {}

	bool IsAvailable() const { return m_available; } // if false, it means something is not correct to acquire data. Call GetLastError() for detail reason.
	std::wstring GetLastError() const { return m_lastErr; }
	virtual void Init(std::wstring &rawItemString) = 0;	// Derived class must implement this. Parse rawItemString and setup itself as it's respective object.
	virtual void Acquire() = 0; // Immediately returns. Acqusition must not block the progress.
	virtual void PullLastDataSet(std::vector<std::wstring> &output); // returns latest value and flush the latest data.

protected:
	static bool ParseRawItemString(const std::wstring &itemRawString, std::wstring &funcName, std::vector<std::wstring> &params);

	std::wstring m_lastErr;
	std::vector<std::wstring>  m_lastDataSet;
	bool m_available;
	SpinLock	m_lock;
};


/**
 *	MACRO FUNCTIONS TO SIMPLIPY ItemBuilder AND Item DERIVED CLASSES
 *
 *	@note Please see ItemMatch<T> class to figure out how it works.
 *
 */
#define DECLARE_ITEM(class_name)	static Item *Creator(std::wstring &raw) { class_name *p = new (class_name); p->Init(raw); return p; }
#define IMPL_ITEM(class_name, itemfunctionname)	static ItemMatch<class_name> s_##class_name((itemfunctionname))

#endif