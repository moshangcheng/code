#include <iostream>
#include <stdio.h>
#include "curl/curl.h"

#ifdef WIN32
#define SECURITY_WIN32
#include <Windows.h>
#include <Winbase.h>
#include <Winerror.h>
#include <security.h>
#include <sspi.h>
#include <lmcons.h>
#endif

int ConnectIIS()
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {
		char nline[256];

		//curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1");
		//curl_easy_setopt(curl, CURLOPT_PROXYPORT, 8888);

		//for local server, evev if using hostname, NTLM authentication is still used
		//for remote server, use hostname to authenticate using kerberos authentication
		curl_easy_setopt(curl, CURLOPT_URL, "http://shu-0864-imdb.labs.microstrategy.com/kerberos/");
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, ""); /* just to start the cookie engine */
		curl_easy_setopt(curl, CURLOPT_USERPWD, "Kerberos" );
		curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_GSSNEGOTIATE );
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "Curl perform failed: %s\n", curl_easy_strerror(res));
			return 1;
		}
	}
}

int main()
{
	ConnectIIS();
	return 0;
}
