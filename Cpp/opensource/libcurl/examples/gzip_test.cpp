/* Don't debug directly in VS2010
 * Because Z:\Bin is added to PATH env
 * Z:\Bin\libcurl.dll is used when debugging
 */

#include <stdio.h>
#include "curl/curl.h"

//The size of the data pointed to by ptr is size multiplied with nmemb
//it will not be zero terminated. Return the number of bytes actually taken care of.
size_t fn( char *ptr, size_t size, size_t nmemb, void *userdata)
{
	printf("hello\n");
	return size * nmemb;
}


int main(void)
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl) {
		//set proxy
		curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:8888");

		//set accept-encoding
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");

		//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fn);

		curl_easy_setopt(curl, CURLOPT_URL, "localhost:8080");

		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	return 0;
}
