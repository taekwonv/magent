#include "superstring.h"


/**
 *  _____                 _____ _       _         
 * |   __|_ _ ___ ___ ___|   __| |_ ___|_|___ ___ 
 * |__   | | | . | -_|  _|__   |  _|  _| |   | . |
 * |_____|___|  _|___|_| |_____|_| |_| |_|_|_|_  |
 *           |_|                             |___|
 */


template<class T>
std::basic_string<T> slice_impl(const T *src, int start, int end, T endc)
{
	std::basic_string<T> ret = src + start;
	ret[end] = endc;
	return ret;
}

std::string sstr::slice(const char *src, int start, int end)
{
	return slice_impl<char>(src, start, end, '\0');
}

std::wstring sstr::slice(const wchar_t *src, int start, int end)
{
	return slice_impl<wchar_t>(src, start, end, L'\0');
}



template<class T, class SplitterT>
std::vector<std::basic_string<T>> split_impl(const T*src, const T splitter, const T* (*schr)(const T*, SplitterT), T endc)
{
	std::vector<std::basic_string<T>> ret;
	int start = 0, end = 0;
	const T* p = src;

	while ((p = schr(p, splitter)) != NULL)
	{
		end = (int)(p - src);
		ret.push_back(slice_impl<T>(src, start, end, endc));
		start = end + 1;
		p++;
	}	
	ret.push_back((T*)(src + start));
	return ret;
}

std::vector<std::string> sstr::split(const char *src, char splitter)
{
	return split_impl<char, int>(src, splitter, &strchr, '\0');
}

std::vector<std::wstring> sstr::split(const wchar_t *src, const wchar_t splitter)
{
	return split_impl<wchar_t, wchar_t>(src, splitter, &wcschr, L'\0');
}



template<class T>
std::basic_string<T> join_impl(const std::vector<std::basic_string<T>> &strings)
{
	std::basic_string<T> ret;
	for (auto it = strings.begin(); it != strings.end(); ++it)
		ret = ret + it->c_str();
	return ret;
}

std::string sstr::join(const std::vector<std::string> &strings)
{
	return join_impl<char>(strings);
}

std::wstring sstr::join(const std::vector<std::wstring> &strings)
{
	return join_impl<wchar_t>(strings);
}



template<class T>
std::basic_string<T> format_impl(int (*func_snprintf)(T*, size_t, const T*, va_list), const T *fmt, va_list ap) 
{
	int size = 100;
	std::basic_string<T> str;
	
	while (1) 
	{
		str.resize(size);
		int n = func_snprintf((T *)str.c_str(), size, fmt, ap);
		va_end(ap);
		if (n > -1 && n < size) 
		{
			str.resize(n);
			return str;
		}
		if (n > -1)
			size = n + 1;
		else
			size *= 2;

		va_start(ap, fmt);
	}
	return str;
}

std::string sstr::format(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	return format_impl(vsnprintf, fmt, ap);
}

std::string sstr::format(const char *fmt, va_list al)
{	
	va_start(al, fmt);
	return format_impl(vsnprintf, fmt, al);
}

std::wstring sstr::format(const wchar_t *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	return format_impl(_vsnwprintf, fmt, ap);	
}

std::wstring sstr::format(const wchar_t *fmt, va_list al)
{	
	va_start(al, fmt);
	return format_impl(_vsnwprintf, fmt, al);
}

int sstr::toInt(const char *src)
{
	return atoi(src);
}

int sstr::toInt(const wchar_t *src)
{
	return _wtoi(src);
}
