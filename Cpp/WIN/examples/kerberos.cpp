/*
For detail information, check "security and identity -> authentication"
http://msdn.microsoft.com/en-us/library/aa374735(v=vs.85).aspx

For status code, check SSPI Status Codes("http://msdn.microsoft.com/en-us/library/aa380499(v=vs.85).aspx")
For value of status code, check WinError.h

Todo: send AP_REQ
*/


#include <iostream>
#include <stdio.h>

#ifdef WIN32
#define SECURITY_WIN32
#include <Windows.h>
#include <Winbase.h>
#include <Winerror.h>
#include <security.h>
#include <sspi.h>
#include <lmcons.h>
#endif

int main()
{
	CredHandle lCredHandle;

	//AS_REQ
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

	//TGS_REQ
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

	return 0;
}
