/**
	curl-asio: wrapper for integrating libcurl with boost.asio applications
	Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
	See COPYING for license information.

	C++ wrapper for constructing libcurl forms
*/

#pragma once

#include "config.h"
#include <string>
#include "initialization.h"
#include "native.h"

namespace curl
{
	class CURLASIO_API form:
		public std::enable_shared_from_this<form>
	{
	public:
		form();
		~form();

		form(const form&) = delete;
		form& operator=(const form&) = delete;

		inline native::curl_httppost* native_handle() { return post_; };

		void add_content(const std::string& key, const std::string& content);
		void add_content(const std::string& key, const std::string& content, std::error_code& ec);
		void add_content(const std::string& key, const std::string& content, const std::string& content_type);
		void add_content(const std::string& key, const std::string& content, const std::string& content_type, std::error_code& ec);
		void add_file(const std::string& key, const std::string& file_path);
		void add_file(const std::string& key, const std::string& file_path, std::error_code& ec);
		void add_file(const std::string& key, const std::string& file_path, const std::string& content_type);
		void add_file(const std::string& key, const std::string& file_path, const std::string& content_type, std::error_code& ec);
		void add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name);
		void add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name, std::error_code& ec);
		void add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name, const std::string& content_type);
		void add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name, const std::string& content_type, std::error_code& ec);
		void add_file_content(const std::string& key, const std::string& file_path);
		void add_file_content(const std::string& key, const std::string& file_path, std::error_code& ec);
		void add_file_content(const std::string& key, const std::string& file_path, const std::string& content_type);
		void add_file_content(const std::string& key, const std::string& file_path, const std::string& content_type, std::error_code& ec);

	private:
		initialization::ptr initref_;
		native::curl_httppost* post_;
		native::curl_httppost* last_;
	};
}
