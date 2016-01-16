curl-asio
=========

**Here be dragons. Although this library generally works quite well, it is still being developed and has not been extensively tested.** You will probably be fine, but don't look at me when things catch fire.

This library makes use of libcurl's multi interface in order to enable easy integration into standalone [Asio](http://think-async.com/) applications.

* **simple interface** - Download and upload anything, synchronously or asynchronously, with just a few lines of code.
* **familiar** - If you have used libcurl in a C application before, you will feel right at home.
* **exceptions** - Libcurl errors throw exceptions. Integrates nicely with std::error_code class.
* **useful wrappers** - C++ interfaces for libcurl's easy, multi, form, share and string list containers. All setopt calls are wrapped for type safety.
* **source/sink concept** - Works nicely with Boost.Iostreams

Installation
------------
1. If not already done, install cURL and its header files, Boost header files and Asio header
2. Clone this git repository. There are no tags or packages yet.
3. Run CMake and point it to cURL, Boost and Asio

```bash
mkdir build
cd build
cmake ..
make
```

Example
-------

```c++
#include <curl-asio.h>
#include <fstream>

int main(int argc, char* argv[])
{
	// expect two arguments
	if (argc != 3)
	{
		std::cerr << "usage: " << argv[0] << " url file" << std::endl;
		return 1;
	}

	// this example program downloads argv[1] to argv[2]
	char* url = argv[1];
	char* file_name = argv[2];
	
	// start by creating an io_service object
	asio::io_service io_service;
	
	// construct an instance of curl::easy
	curl::easy downloader(io_service);
	
	// set the object's properties
	downloader.set_url(url);
	downloader.set_sink(std::make_shared<std::ofstream>(file_name, std::ios::binary));
	
	// download the file
	std::error_code ec;
	downloader.perform(ec);

	// error handling
	if (!ec)
	{
		std::cerr << "Download succeeded" << std::endl;
	}
	else
	{
		std::cerr << "Download failed: " << ec.message() << std::endl;
	}
	
	return 0;
}
```

More examples, including one for curl-asio's [asynchronous interface](https://github.com/mologie/curl-asio/wiki/Asynchronous-interface), can be found in the [wiki](https://github.com/mologie/curl-asio/wiki) and the `examples` directory.

Todo
----

* Testing suite based on libcurl's tests
* API documentation, design documentation, more examples
* Support for transport schemes using UDP and incoming TCP sockets (active FTP)
* File upload streams
* string_list iterators

License
-------
Curl-asio is licensed under the same MIT/X derivate license used by libcurl.
