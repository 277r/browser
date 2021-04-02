
#include "requests.hpp"

namespace request
{
	char *getByUrl(std::string &url, unsigned int port)
	{
		switch (port){
			case 80: {
				getraw(url, port);
				break;
			}
			case 443: {
				return getrawS(url, port);
				break;
			}
		}
		return getraw(url, port);
	}

	char *getraw(std::string &url, unsigned int port)
	{

		// create socket, and hostent
		int sock;
		sockaddr_in hint;
		hostent *h;
		sock = socket(AF_INET, SOCK_STREAM, 0);

		// WARNING: WON'T WORK WITH IPV6
		// this turns the url into an ip
		h = gethostbyname(url.c_str());

		if (h == nullptr)
		{

			return nullptr;
		}

		// copy ip, set internet type (ipv4 now), set port
		memcpy(&hint.sin_addr, h->h_addr_list[0], h->h_length);
		hint.sin_family = AF_INET;
		// if port == 0, set port to 80, else set port to port
		hint.sin_port = htons(port == 0 ? 80 : port);

		// connect to server on port using sock
		int connectSock = connect(sock, (sockaddr *)&hint, sizeof(hint));
		if (connectSock == -1)
		{

			return nullptr;
		}

		// buffer containing the response
		char *buf = new char[41943040];
		int bytesReceived;

		// content length
		int conlength;
		// sub buffer containing content
		char *subbuf;

		// string containing the request, look in httpget.txt how this is structured
		std::string sendData;
		sendData += "GET / HTTP/1.1\r\n";
		sendData += "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:88.0) Gecko/20100101 Firefox/88.0\r\n";
		sendData += "Host: " + url + "\r\n";
		sendData += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n";
		sendData += "Accept-Language: en-us\r\n";
		sendData += "Accept-Encoding: gzip\r\n";
		sendData += "Connection: keep-alive\r\n";

		sendData += "\r\n";
		//std::cout << sendData.c_str();

		do
		{
			// send data
			int sendres = send(sock, sendData.c_str(), sendData.size() + 1, 0);

			// get data
			if (sendres == -1)
			{
				// error happened, could not connect
				return nullptr;
			}
			usleep(50000);

			bytesReceived = recv(sock, buf, 41943040, 0);

			// byte size out of range, resize buffer and request again
			if (bytesReceived > 41943040)
			{
				delete[] buf;
				buf = new char[bytesReceived];
				// retry
				bytesReceived = 0;
			}

			// possibly return
			// do not return
			//return buf;

		} while (bytesReceived == 0);

		// close socket
		close(sock);

		// check http headers
		int enctype = 0;
		int i = 0;
		while (i + 16 < bytesReceived)
		{
			// check for contentEncoding
			if (startsWith(&buf[i], "Content-Encoding"))
			{
				// skip `Content-Encoding: `
				i += 18;
				if (startsWith(&buf[i], "gzip"))
				{
					enctype = 1;
				}
			}

			// get content length
			else if (startsWith(&buf[i], "Content-Length"))
			{
				// skip `Content-Length: `
				i += 16;
				std::string sizeS;
				// all lines end with \r\n so we wait until there
				while (buf[i] != '\r' && i < bytesReceived)
				{
					sizeS += buf[i];
					i++;
				}
				conlength = std::stoi(sizeS);
			}

			// skip to next line
			while (buf[i] != '\n' && i < bytesReceived)
			{
				i++;
			}
			i++;

			// check for empty line \r\n
			if (startsWith(&buf[i], "\r\n"))
			{
				// get pointer of end of HTTP header
				subbuf = buf + i + 2;
				// stop loop
				i = bytesReceived;
			}
		}

		// if gzip, ungzip
		if (enctype == 1)
		{

			char *oldData = buf;
			// this segfaults
			buf = compression::ungzip(subbuf, conlength, conlength);
			// ungzip doesn't delete[] the old pointer because it can't
			delete[] oldData;
			// set 0 character
			buf[conlength] = 0;
		}

		//output to see length and encryption type, not used anymore
		//std::cout << "len: " << conlength << '\n' << "enc: " << enctype;

		return buf;
	}
	
	// needed for openSSL
	SSL_CTX *ssl_ctx;
	int initSSL()
	{
		OpenSSL_add_all_algorithms();
		SSL_load_error_strings();
		SSL_library_init();
		ssl_ctx = SSL_CTX_new(SSLv23_client_method());
		return 0;
	}

	// http, but with SSL
	char *getrawS(std::string &url, unsigned int port)
	{ // create socket, and hostent
		int sock;
		sockaddr_in hint;
		hostent *h;
		sock = socket(AF_INET, SOCK_STREAM, 0);

		// WARNING: WON'T WORK WITH IPV6
		// this turns the url into an ip
		h = gethostbyname(url.c_str());

		if (h == nullptr)
		{

			return nullptr;
		}

		// copy ip, set internet type (ipv4 now), set port
		memcpy(&hint.sin_addr, h->h_addr_list[0], h->h_length);
		hint.sin_family = AF_INET;
		// if port == 0, set port to 80, else set port to port
		hint.sin_port = htons(port == 0 ? 443 : port);

		// connect to server on port using sock
		int connectSock = connect(sock, (sockaddr *)&hint, sizeof(hint));
		if (connectSock == -1)
		{

			return 0;
		}

		SSL *conn = SSL_new(ssl_ctx);
		SSL_set_fd(conn, sock);

		int err = SSL_connect(conn);
		// if not 1, abort
		if (err != 1){
			SSL_free(conn);
			return 0;
		}

		// buffer containing the response
		char *buf = new char[41943040];
		int bytesReceived;

		// content length
		int conlength;
		// sub buffer containing content
		char *subbuf;

		// string containing the request, look in httpget.txt how this is structured
		std::string sendData;
		sendData += "GET / HTTP/1.1\r\n";
		sendData += "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:88.0) Gecko/20100101 Firefox/88.0\r\n";
		sendData += "Host: " + url + "\r\n";
		sendData += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n";
		sendData += "Accept-Language: en-US\r\n";
		sendData += "Accept-Encoding: gzip\r\n";
		sendData += "Connection: Keep-Alive\r\n";

		sendData += "\r\n";
		//std::cout << sendData.c_str();

		do
		{
			// send data
			int sendres = SSL_write(conn, sendData.c_str(), sendData.size() + 1);

			// get data
			if (sendres == -1)
			{
				// error happened, could not connect
				SSL_free(conn);
				return nullptr;
			}
			usleep(50000);

			bytesReceived = SSL_read(conn, buf, 41943040);

			// byte size out of range, resize buffer and request again
			if (bytesReceived > 41943040)
			{
				delete[] buf;
				buf = new char[bytesReceived];
				// retry
				bytesReceived = 0;
			}

			// possibly return
			// do not return
			//return buf;

		} while (bytesReceived == 0);

		// close socket
		SSL_shutdown(conn);
		SSL_free(conn);
		close(sock);

		// check http headers
		int enctype = 0;
		int i = 0;
		while (i + 16 < bytesReceived)
		{
			// check for contentEncoding
			if (startsWith(&buf[i], "Content-Encoding"))
			{
				// skip `Content-Encoding: `
				i += 18;
				if (startsWith(&buf[i], "gzip"))
				{
					enctype = 1;
				}
			}

			// get content length
			else if (startsWith(&buf[i], "Content-Length"))
			{
				// skip `Content-Length: `
				i += 16;
				std::string sizeS;
				// all lines end with \r\n so we wait until there
				while (buf[i] != '\r' && i < bytesReceived)
				{
					sizeS += buf[i];
					i++;
				}
				conlength = std::stoi(sizeS);
			}

			// skip to next line
			while (buf[i] != '\n' && i < bytesReceived)
			{
				i++;
			}
			i++;

			// check for empty line \r\n
			if (startsWith(&buf[i], "\r\n"))
			{
				// get pointer of end of HTTP header
				subbuf = buf + i + 2;
				// stop loop
				i = bytesReceived;
			}
		}

		// if gzip, ungzip
		if (enctype == 1)
		{

			char *oldData = buf;
			// this segfaults
			buf = compression::ungzip(subbuf, conlength, conlength);
			// ungzip doesn't delete[] the old pointer because it can't
			delete[] oldData;
			// set 0 character
			buf[conlength] = 0;
		}

		//output to see length and encryption type, not used anymore
		//std::cout << "len: " << conlength << '\n' << "enc: " << enctype;

		return buf;
		
	}

	// deletes all headers of the url, be careful
	void urlDecoder(std::string &url, unsigned int &port)
	{
		int index = 0;
		std::string portString;

		// if someone enters https://google.com:80, it will use port 80 and no https

		// delete https
		if (startsWith(url.c_str(), "https://"))
		{
			port = 443;
			// cut part of url of
			url.erase(0, 8);
		}
		// delete http
		else if (startsWith(url.c_str(), "http://"))
		{
			port = 80;
			url.erase(0, 7);
		}

		// delete headers (deletes whole thing now if we use anything other than https or http)
		while (url[index] != '/' && index < url.size())
		{
			index++;
		}
		url.erase(index, url.size() - 1);

		// get port
		index = 0;
		while (url[index] != ':' && index < url.size())
		{
			index++;
		}
		// if index == url.size() -1, there was no : found in the url
		if (index != url.size())
		{
			index++;
			// port is at the end of the string so we can go on until we're there
			while (index < url.size())
			{
				// add chars to portstring
				portString += url[index];
				index++;
			}
			port = std::stoul(portString);
			// remove port from string
			url.erase(url.size() - portString.size() - 1, portString.size() + 1);
		}

	}

};
