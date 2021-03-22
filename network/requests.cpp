
#include "requests.h"


namespace request
{
	char *getraw(std::string url, unsigned int port)
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
		hint.sin_port = htons(port);

		// connect to server on port using sock
		int connectSock = connect(sock, (sockaddr *)&hint, sizeof(hint));
		if (connectSock == -1)
		{

			return nullptr;
		}

		// buffer containing the response
		char *buf = new char[4096];
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
		sendData += "Accept-Encoding: gzip,deflate\r\n";
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

			bytesReceived = recv(sock, buf, 4096, 0);

			// byte size out of range, resize buffer and request again
			if (bytesReceived > 4096)
			{
				delete[] buf;
				buf = new char[bytesReceived];
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
			if (startsWith(&buf[i], "Content-Length"))
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
			/*
			char *oldData = buf;
			// this segfaults
			buf = ungzip(subbuf, conlength, conlength);
			// ungzip doesn't delete[] the old pointer because it can't
			delete[] oldData;
			*/
		}

		//std::cout << "len: " << conlength << '\n' << "enc: " << enctype;
		return buf;
	}

	// will probably be the same on every platform
	void urlDecoder(std::string &url, unsigned int &port, std::string headers)
	{
	}

};
