#ifndef MAGENT_ITEM_H
#define MAGENT_ITEM_H

#include <string>
#include <vector>


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
	virtual void Init(std::wstring &rawItemString) = 0;	// Derived class must implement this. Parse rawItemString and setup itself as it's respective object.
	virtual void Acquire(); // Immediately returns. Acqusition must not block the progress.
	virtual std::wstring PullLastData(); // returns latest value and flush the latest data.

protected:
	static void ParseRawItemString(const std::wstring &itemRawString, std::wstring &funcName, std::vector<std::wstring> &params);

private:	
	std::wstring m_lastErr;
	bool m_available;
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