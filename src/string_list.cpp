/**
	curl-asio: wrapper for integrating libcurl with boost.asio applications
	Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
	See COPYING for license information.

	C++ wrapper for libcurl's string list interface
*/

#include <curl-asio/string_list.h>

using namespace curl;

string_list::string_list():
	list_(0)
{
	initref_ = initialization::ensure_initialization();
}

string_list::~string_list()
{
	if (list_)
	{
		native::curl_slist_free_all(list_);
		list_ = 0;
	}
}

void string_list::add(const char* str)
{
	native::curl_slist* p = native::curl_slist_append(list_, str);

	if (!p)
	{
		throw std::bad_alloc();
	}

	list_ = p;
}

void string_list::add(const std::string& str)
{
	add(str.c_str());
}
