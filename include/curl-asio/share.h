/**
	curl-asio: wrapper for integrating libcurl with boost.asio applications
	Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
	See COPYING for license information.

	C++ wrapper for libcurl's share interface
*/

#pragma once

#include "config.h"
#include <mutex>
#include "initialization.h"
#include "native.h"

namespace curl
{
	class CURLASIO_API share:
		public std::enable_shared_from_this<share>
	{
	public:
		share();
		~share();

		share(const share&) = delete;
		share& operator=(const share&) = delete;

		inline native::CURLSH* native_handle() { return handle_; }
		void set_share_cookies(bool enabled);
		void set_share_dns(bool enabled);
		void set_share_ssl_session(bool enabled);

		typedef void (*lock_function_t)(native::CURL* handle, native::curl_lock_data data, native::curl_lock_access access, void* userptr);
		void set_lock_function(lock_function_t lock_function);

		typedef void (*unlock_function_t)(native::CURL* handle, native::curl_lock_data data, void* userptr);
		void set_unlock_function(unlock_function_t unlock_function);

		void set_user_data(void* user_data);

	private:
		static void lock(native::CURL* handle, native::curl_lock_data data, native::curl_lock_access access, void* userptr);
		static void unlock(native::CURL* handle, native::curl_lock_data data, void* userptr);

		initialization::ptr initref_;
		native::CURLSH* handle_;
		std::mutex mutex_;
	};
}
