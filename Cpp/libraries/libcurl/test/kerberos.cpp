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

		curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1");
		curl_easy_setopt(curl, CURLOPT_PROXYPORT, 8888);

		//for local server, evev if using hostname, NTLM authentication is still used
		//for remote server, use hostname to authenticate using kerberos authentication
		curl_easy_setopt(curl, CURLOPT_URL, "http://shu-0864-imdb/kerberos/");
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
	CredHandle lCredHandle;

	SECURITY_STATUS lStatus = AcquireCredentialsHandle( 
		NULL,					// [in] principal : current user's credential 
		"Kerberos",			// [in] package : Kerberos
		SECPKG_CRED_BOTH,		// [in] Allow credential to prepare an outgoing token as well as accept an incoming token 
		NULL,					// [in] Login ID : current user
		NULL,
		NULL,
		NULL,
		&lCredHandle,			// [out] credential handle
		NULL );

	CtxtHandle lContextHandle;
	SecBuffer lTokenBuffer[1];
	lTokenBuffer[0].BufferType = SECBUFFER_TOKEN;
	lTokenBuffer[0].cbBuffer = 0;
	lTokenBuffer[0].pvBuffer = NULL;

	
	SecBufferDesc lTokenBufferDesc;
	lTokenBufferDesc.ulVersion  = SECBUFFER_VERSION;
	lTokenBufferDesc.cBuffers = 1;
	lTokenBufferDesc.pBuffers = lTokenBuffer;
	unsigned long lContextReq = ISC_REQ_DELEGATE | ISC_REQ_ALLOCATE_MEMORY | ISC_REQ_MUTUAL_AUTH;
	unsigned long lInitSecContextRet = 0;
	char* lpSPN = "HTTP/SHU-0864-IMDB";

	lStatus = InitializeSecurityContext( 
		&lCredHandle,			// [in] credential handle acquire above
		NULL,					// [in] null CtxtHandle pointer for the first call
		lpSPN,					// [in] service principal name
		lContextReq,			// [in] Bit flags to request context
		0,						// reserved
		SECURITY_NETWORK_DREP,	// [in] Byte ordering : SECURITY_NATIVE_DREP/SECURITY_NETWORK_DREP
		NULL,					// [in,out] NULL SecBufferDesc for first call.
		0,						// reserved
		&lContextHandle,		// [in, out] receive the handle for second call
		&lTokenBufferDesc,		// [out] Buffer for kerberos token
		&lInitSecContextRet,	// [out] Bit flags for returned context
		NULL);

	if(lInitSecContextRet & ISC_RET_ALLOCATED_MEMORY)
	{
		FreeContextBuffer(lTokenBuffer[0].pvBuffer);
		lTokenBuffer[0].pvBuffer = NULL;
		lInitSecContextRet = 0;
	}
	DeleteSecurityContext(&lContextHandle);
	FreeCredentialsHandle(&lCredHandle);

	ConnectIIS();
	return 0;
}
