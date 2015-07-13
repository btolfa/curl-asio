#include <curl-asio.h>
#include <iostream>
#include <fstream>
#include <memory> // for std::auto_ptr

void handle_download_completed(const std::error_code& err, std::string url, std::shared_ptr<curl::easy> easy)
{
	if (!err)
	{
		std::cout << "Download of " << url << " completed" << std::endl;
	}
	else
	{
		std::cout << "Download of " << url << " failed: " << err.message() << std::endl;
	}
	
}

void start_download(curl::multi& multi, const std::string& url)
{
	auto easy = std::make_shared<curl::easy>(multi);
	
	// see 'Use server-provided file names' example for a more detailed implementation of this function which receives
	// the target file name from the server using libcurl's header callbacks
	std::string file_name = url.substr(url.find_last_of('/') + 1);
	
	easy->set_url(url);
	easy->set_sink(std::make_shared<std::ofstream>(file_name.c_str(), std::ios::binary));
	easy->async_perform([url, easy](const std::error_code& err){
		handle_download_completed(err, url, easy);
	});
}

int main(int argc, char* argv[])
{
	// expect one argument
	if (argc != 2)
	{
		std::cerr << "usage: " << argv[0] << " url-list-file" << std::endl;
		return 1;
	}

	// this example program downloads all urls in the text file argv[1] to the current directory
	char* url_file_name = argv[1];
	
	// start by creating an io_service object
	asio::io_service io_service;
	
	// construct an instance of curl::multi
	curl::multi manager(io_service);
	
	// treat each line in url_file_name as url and start a download from it
	std::ifstream url_file(url_file_name);
	while (!url_file.eof())
	{
		std::string url;
		std::getline(url_file, url);
		start_download(manager, url);
	}
	
	// let Boost.Asio do its magic
	io_service.run();
	
	std::cout << "All downloads completed" << std::endl;
	
	return 0;
}
