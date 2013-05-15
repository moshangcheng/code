#if defined _WIN32 || defined _WINDOWS
#include <windows.h>
#endif 

//add UTF8 support
//otherwise we can't connect to UNICODE Apps
#ifndef AD_UTF8
#define AD_UTF8
#endif

#include <string.h>
#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

//memory alignment
//otherwise some values will be null
#if defined _WIN32 || defined _WINDOWS
#pragma pack(push,localid,1)
#endif
#include <essapi.h>
#include <essotl.h>
//restore memory alignment settings
#if defined _WIN32 || defined _WINDOWS
#pragma pack(pop,localid)
#endif

ESS_STS_T		sts = ESS_STS_NOERR;
ESS_HINST_T		hInst = NULL;              
ESS_HCTX_T		hCtx = NULL;
ESS_STR_T		AppName = "Sample";
ESS_STR_T		DbName = "Basic";

ESS_HOUTLINE_T	hOutline = NULL; 
ESS_OBJDEF_T	Object;
ESS_OBJNAME_T	szFileName;

static ESS_CHAR_T *axisnames[] =
{
	"COLUMNS", "ROWS", "PAGES", "CHAPTERS", "SECTIONS"
};

void GetDimMembers(ESS_STR_T iDimName)
{
	ESS_HMEMBER_T lhMember = NULL;
	ESS_PHMEMBER_T lphMember = NULL;
	ESS_MBRCOUNTS_T lCounts;
	ESS_PREDICATE_T lPredicate;
	memset(&lCounts, '\0', sizeof(lCounts));
	memset(&lPredicate, '\0', sizeof(lPredicate));

	lPredicate.ulQuery = ESS_DIMENSION;
	lPredicate.pszDimension = iDimName;
	lCounts.ulStart = 0;
	lCounts.ulMaxCount = 10000000;
	sts = EssOtlQueryMembers(hOutline, lhMember,  &lPredicate, &lCounts, &lphMember);
	for(ULONG i = 0; i < lCounts.ulReturnCount; i++)
	{
		ESS_PMBRINFO_T lpMemberInfo = NULL;
		sts = EssOtlGetMemberInfo(hOutline, lphMember[i], &lpMemberInfo);
		EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_MEMBERINFO, 1, lpMemberInfo);
	}

	EssOtlFreeMembers(hOutline, lCounts.ulReturnCount, lphMember);
}

void GetAllDims()
{
	ULONG lpDimCount;
	ESS_PDIMENSIONINFO_T lpDimInfo;
	sts = EssGetDimensionInfo(hCtx, NULL, &lpDimCount, &lpDimInfo);
	for(ULONG i = 0; i < lpDimCount; i++)
	{
		GetDimMembers(lpDimInfo[i].DimName);
	}
	EssFree(hInst, lpDimInfo);
}

int main()
{
	//initialize
	ESS_INIT_T InitStruct = {ESS_API_VERSION,
		NULL,
		0L,
		255,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		0L,
		ESS_API_UTF8
	};
	sts = EssInit(&InitStruct, &hInst);


	//login
	ESS_USHORT_T Items = 0;
	ESS_PAPPDB_T pAppsDbs = NULL;
	ESS_CHAR_T SvrName[ESS_SVRNAMELEN];
	ESS_CHAR_T UserName[ESS_USERNAMELEN];
	ESS_CHAR_T Password[ESS_PASSWORDLEN];

	strcpy(SvrName,"ts-essbase1111");
	strcpy(UserName,"admin");
	strcpy(Password,"password");

	sts = EssLogin(hInst, SvrName, UserName, Password, &Items, &pAppsDbs, &hCtx);
	
	//set active
	ESS_ACCESS_T Access;
	sts = EssSetActive(hCtx, AppName, DbName, &Access);

	//open outline
	memset(&Object, '\0', sizeof(Object));
	sts = EssOtlOpenOutlineQuery(hCtx, &Object, &hOutline);

	//get outline info
	ESS_POUTLINEINFO_T lpOutlineInfo = NULL;
	sts = EssOtlGetOutlineInfo(hOutline, &lpOutlineInfo);

	GetAllDims();

	//logout
	sts = EssLogout(hCtx);
	//term
	sts = EssTerm(hInst);

	return 0;
}