#include "ItemPerfCounter_Win.h"
#include "ItemBuilder.h"

using namespace std;

                                                                                       
/**
 *  _____ _             _____         ___ _____             _                 _ _ _ _     
 * |     | |_ ___ _____|  _  |___ ___|  _|     |___ _ _ ___| |_ ___ ___      | | | |_|___ 
 * |-   -|  _| -_|     |   __| -_|  _|  _|   --| . | | |   |  _| -_|  _|     | | | | |   |
 * |_____|_| |___|_|_|_|__|  |___|_| |_| |_____|___|___|_|_|_| |___|_|  _____|_____|_|_|_|
 *                                                                     |_____|            
 */


IMPL_ITEM(ItemPerfCounter_Win, L"PerfCounter");

void ItemPerfCounter_Win::Acquire()
{
}

wstring ItemPerfCounter_Win::PullLastData()
{
	return L"";
}
