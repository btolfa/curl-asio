/**
	curl-asio: wrapper for integrating libcurl with boost.asio applications
	Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
	See COPYING for license information.

	Constructs libcurl string lists
*/

#pragma once

#include "config.h"
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include "initialization.h"
#include "native.h"

namespace curl
{
	class CURLASIO_API string_list:
		public boost::enable_shared_from_this<string_list>
	{
	public:
		string_list();
		~string_list();

		string_list(const string_list&) = delete;
		string_list& operator= (const string_list&) = delete;

		inline native::curl_slist* native_handle() { return list_; }

		void add(const char* str);
		void add(const std::string& str);
		
	private:
		initialization::ptr initref_;
		native::curl_slist* list_;
	};
}
