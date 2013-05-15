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
#include <vector>
#include <iostream>

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


void PrintAppsAndDbs()
{
	ESS_PAPPNAME_T lpAppName = NULL;
	ESS_USHORT_T   lAppCount = 0;

	sts = EssListApplications(hCtx, &lAppCount, &lpAppName);

	std::cout << "There are " << lAppCount << " apps\n";
	for(ULONG i = 0; i < lAppCount; i++)
	{
		std::cout << "	" << lpAppName[i] << "\n";

		ESS_USHORT_T lDbCount = 0;
		ESS_PAPPDB_T pAppsDbs = NULL;
		sts = EssListDatabases(hCtx, lpAppName[i], &lDbCount, &pAppsDbs);

		std::cout << "	There are " << lDbCount << " dbs\n";
		for(ULONG j = 0; j < lDbCount; j++)
		{
			std::cout << "		" << pAppsDbs[j].DbName << "\n";
		}
	}
}

void QueryAttributesByHandle(ESS_HMEMBER_T ihMember)
{
	ESS_ATTRIBUTEQUERY_T  lAttributeQuery;
	ESS_ULONG_T           lAttributeCount = 0;
	ESS_PHMEMBER_T        phAttributes = ESS_NULL;

	memset(&lAttributeQuery, 0x00, sizeof(ESS_ATTRIBUTEQUERY_T));
	lAttributeQuery.bInputMemberIsHandle = ESS_TRUE;
	lAttributeQuery.uInputMember.hMember = ihMember;
	lAttributeQuery.usInputMemberType = ESS_BASE_MEMBER;
	lAttributeQuery.usOutputMemberType = ESS_ATTRIBUTE_DIMENSION;
	lAttributeQuery.usOperation = ESS_ALL;
	lAttributeQuery.Attribute.usDataType = ESS_ATTRMBRDT_NONE;


	sts = EssOtlQueryAttributes(hOutline, &lAttributeQuery, &lAttributeCount, &phAttributes);
	if(lAttributeCount > 0)
	{
		for(ULONG i = 0; i < lAttributeCount; i++)
		{
			ESS_PMBRINFO_T lpMemberInfo = NULL;
			sts = EssOtlGetMemberInfo(hOutline, phAttributes[i], &lpMemberInfo);
			EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_MBRINFO, 1, lpMemberInfo);
		}
		EssOtlFreeMembers(hOutline, lAttributeCount, phAttributes);
	}
}

void PrintDimensionsAndLevels()
{
	ULONG lDimCount;
	ESS_PDIMENSIONINFO_T lpDimInfo;
	//use EssGet
	sts = EssGetDimensionInfo(hCtx, NULL, &lDimCount, &lpDimInfo);
	std::cout << "There are " << lDimCount << " dimensions\n";
	for(ULONG i = 0; i < lDimCount; i++)
	{
		std::cout << "	" << lpDimInfo[i].DimName << "\n";

		ULONG lLevelCount = 0;
		ESS_PGENLEVELNAME_T lpLevelName;
		sts = EssOtlGetLevelNames(hOutline, lpDimInfo[i].DimName, ESS_GENLEV_ALL, &lLevelCount, &lpLevelName);

		std::cout << "		There are " << lLevelCount << " levels\n";
		for(ULONG j = 0; j < lLevelCount; j++)
		{
			std::cout << "			" << lpLevelName[j].szName << "\n";

			ESS_HMEMBER_T lhMember = NULL;
			ESS_PHMEMBER_T lphMember = NULL;
			ESS_MBRCOUNTS_T lCounts;
			ESS_PREDICATE_T lPredicate;
			memset(&lCounts, '\0', sizeof(lCounts));
			memset(&lPredicate, '\0', sizeof(lPredicate));

			lPredicate.ulQuery = ESS_NAMEDLEVEL;
			lPredicate.pszDimension = lpDimInfo[i].DimName;
			lPredicate.pszString1 = lpLevelName[j].szName;
			lCounts.ulStart = 0;
			lCounts.ulMaxCount = 10000000;
			sts = EssOtlQueryMembers(hOutline, lhMember,  &lPredicate, &lCounts, &lphMember);

			std::cout << "			There are " << lCounts.ulReturnCount << " members\n";
			for(ULONG k = 0; k < lCounts.ulReturnCount; k++)
			{
				ESS_PMBRINFO_T lpMemberInfo = NULL;
				sts = EssOtlGetMemberInfo(hOutline, lphMember[k], &lpMemberInfo);

				std::cout << "				" << lpMemberInfo->szMember << "\n";

				//if(lpDimInfo[i].DimTag != ESS_TTYPE_ATTRIBUTE)
				//{

				QueryAttributesByHandle(lphMember[k]);

				//}
				sts = EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_MBRINFO, 1, lpMemberInfo);
			}
			EssOtlFreeMembers(hOutline, lCounts.ulReturnCount, lphMember);
		}

		EssFree(hInst, lpLevelName);
	}
	EssFree(hInst, lpDimInfo);
}

void PrintMeasures()
{
	std::vector<ESS_PMBRINFO_T> lppMeasureInfo;
	ESS_HMEMBER_T lhMember = NULL;
	ESS_PHMEMBER_T lphMember = NULL;

	ESS_MBRCOUNTS_T lCounts;
	ESS_PREDICATE_T lPredicate;
	memset(&lCounts, '\0', sizeof(lCounts));
	memset(&lPredicate, '\0', sizeof(lPredicate));
	lPredicate.ulQuery = ESS_CHILDREN;
	lCounts.ulStart = 0;
	lCounts.ulMaxCount = ~0;
	//Get all dimension handles
	sts = EssOtlQueryMembers(hOutline, lhMember,  &lPredicate, &lCounts, &lphMember);
	for(ULONG i = 0; i < lCounts.ulReturnCount; i++)
	{
		ESS_PMBRINFO_T lpMemberInfo = NULL;
		//Get dimension info
		sts = EssOtlGetMemberInfo(hOutline, lphMember[i], &lpMemberInfo);
		//Find measure dimension
		if(lpMemberInfo->usCategory == ESS_CAT_ACCOUNTS)
		{
			ESS_PHMEMBER_T lphMeasureMember = NULL;

			ESS_MBRCOUNTS_T lMeasureCounts;
			ESS_PREDICATE_T lMeasurePredicate;
			memset(&lMeasureCounts, '\0', sizeof(lMeasureCounts));
			memset(&lMeasurePredicate, '\0', sizeof(lMeasurePredicate));
			lMeasurePredicate.ulQuery = ESS_DESCENDANTS;//Get all descendants of measure dimension
			lMeasureCounts.ulStart = 0;
			lMeasureCounts.ulMaxCount = ~0;

			//Get all measure handles
			sts = EssOtlQueryMembers(hOutline, lphMember[i], &lMeasurePredicate, &lMeasureCounts, &lphMeasureMember);
 			for(ULONG j = 0; j < lMeasureCounts.ulReturnCount; j++)
			{
				ESS_PMBRINFO_T lpMeasureInfo = NULL;
				sts = EssOtlGetMemberInfo(hOutline, lphMeasureMember[j], &lpMeasureInfo);
				//EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_MBRINFO, 1, lpMeasureInfo);
				lppMeasureInfo.push_back(lpMeasureInfo);
			}
			sts = EssOtlFreeMembers(hOutline, lMeasureCounts.ulReturnCount, lphMeasureMember);
		}
		EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_MBRINFO, 1, lpMemberInfo);
	}
	EssOtlFreeMembers(hOutline, lCounts.ulReturnCount, lphMember);
	for(ULONG i = 0; i < lppMeasureInfo.size(); i++)
	{
		sts = EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_MBRINFO, 1, lppMeasureInfo[i]);
	}
}

void PrintProperties()
{
	ULONG lDimCount;
	ESS_PDIMENSIONINFO_T lpDimInfo;
	//use EssGet
	sts = EssGetDimensionInfo(hCtx, NULL, &lDimCount, &lpDimInfo);
	std::cout << "There are " << lDimCount << " dimensions\n";
	for(ULONG i = 0; i < lDimCount; i++)
	{
		std::cout << "	" << lpDimInfo[i].DimName << "\n";

		ESS_ATTRIBUTEQUERY_T  lAttributeQuery;
		ESS_ULONG_T           lAttributeCount = 0;
		ESS_PHMEMBER_T        phAttributes = ESS_NULL;

		memset(&lAttributeQuery, 0x00, sizeof(ESS_ATTRIBUTEQUERY_T));
		lAttributeQuery.bInputMemberIsHandle = ESS_FALSE;
		lAttributeQuery.uInputMember.szMember = lpDimInfo[i].DimName;
		lAttributeQuery.usInputMemberType = ESS_BASE_DIMENSION;
		lAttributeQuery.usOutputMemberType = ESS_ATTRIBUTE_DIMENSION;
		lAttributeQuery.usOperation = ESS_ALL;
		lAttributeQuery.Attribute.usDataType = lpDimInfo[i].DimDataType;

		//Get dimension attributes
		sts = EssOtlQueryAttributes(hOutline, &lAttributeQuery, &lAttributeCount, &phAttributes);
		if(lAttributeCount > 0)
		{
			for(ULONG j = 0; j < lAttributeCount; j++)
			{
				ESS_PATTRIBUTEINFO_T lpAttributeInfo = NULL;
				sts = EssOtlGetAttributeInfo(hOutline, phAttributes[j], &lpAttributeInfo);
				EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_ATTRIBUTEINFO, 1, lpAttributeInfo);
			}

			EssOtlFreeMembers(hOutline, lAttributeCount, phAttributes);
		}

		//Get UDA
		ESS_MBRCOUNTS_T lCounts;
		ESS_PREDICATE_T lPredicate;
		memset(&lPredicate, '\0', sizeof(lPredicate));  
		lPredicate.ulQuery       = ESS_DIMUSERATTRIBUTES;
		lPredicate.pszDimension  = lpDimInfo[i].DimName;
		memset(&lCounts, '\0', sizeof(lCounts));  
		lCounts.ulStart    = 0;
		lCounts.ulMaxCount = ~0;

		ESS_PMBRNAME_T lphUDAName = NULL;

		sts = EssOtlGetDimensionUserAttributes(hOutline, &lPredicate, &lCounts, &lphUDAName);
		if (!sts && lCounts.ulReturnCount)
		{
			/*for(ULONG j = 0; j < lCounts.ulReturnCount; j++)
			{
				ESS_PATTRIBUTEINFO_T lpAttributeInfo = NULL;
				sts = EssGetAttributeInfo(hCtx, lphUDAName[j], &lpAttributeInfo);
				EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_ATTRIBUTEINFO, 1, lpAttributeInfo);
			}*/
			sts = EssFree(hInst, lphUDAName);
		}

		//Get Alias
		/*ESS_STR_T lAliasName = NULL;
		ESS_HMEMBER_T lhMemberAlias = NULL;
		sts = EssOtlFindMember(hOutline, lpDimInfo[i].DimName, &lhMemberAlias);
		sts = EssOtlGetMemberAlias(hOutline, lhMemberAlias, ESS_NULL, &lAliasName);
		if (lAliasName)
		{
			EssFree(hInst, lAliasName);
		}*/
	}
	EssFree(hInst, lpDimInfo);
}

void PrintAllProperties()
{
	ESS_HMEMBER_T lhMember = NULL;
	ESS_PHMEMBER_T lphMember = NULL;

	ESS_MBRCOUNTS_T lCounts;
	ESS_PREDICATE_T lPredicate;
	memset(&lCounts, '\0', sizeof(lCounts));
	memset(&lPredicate, '\0', sizeof(lPredicate));
	lPredicate.ulQuery = ESS_CHILDREN;
	lPredicate.pszDimension = NULL;
	lCounts.ulStart = 0;
	lCounts.ulMaxCount = ~0;
	//Get all dimension handles
	sts = EssOtlQueryMembers(hOutline, lhMember,  &lPredicate, &lCounts, &lphMember);
	for(ULONG i = 0; i < lCounts.ulReturnCount; i++)
	{
		ESS_PMBRINFO_T lpMemberInfo = NULL;
		//Get dimension info
		sts = EssOtlGetMemberInfo(hOutline, lphMember[i], &lpMemberInfo);

		ESS_ATTRIBUTEQUERY_T  lAttributeQuery;
		ESS_ULONG_T           lAttributeCount = 0;
		ESS_PHMEMBER_T        phAttributes = ESS_NULL;

		memset(&lAttributeQuery, 0x00, sizeof(ESS_ATTRIBUTEQUERY_T));
		lAttributeQuery.bInputMemberIsHandle = ESS_FALSE;
		lAttributeQuery.uInputMember.szMember = lpMemberInfo->szDimName;
		lAttributeQuery.usInputMemberType = ESS_BASE_DIMENSION;
		lAttributeQuery.usOutputMemberType = ESS_ATTRIBUTE_DIMENSION;
		lAttributeQuery.usOperation = ESS_ALL;
		//lAttributeQuery.Attribute.usDataType = lpDimInfo[i].DimDataType;

		//Get dimension attributes
		sts = EssOtlQueryAttributes(hOutline, &lAttributeQuery, &lAttributeCount, &phAttributes);
		if(lAttributeCount > 0)
		{
			for(ULONG j = 0; j < lAttributeCount; j++)
			{
				ESS_PATTRIBUTEINFO_T lpAttributeInfo = NULL;
				sts = EssOtlGetAttributeInfo(hOutline, phAttributes[j], &lpAttributeInfo);
				EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_ATTRIBUTEINFO, 1, lpAttributeInfo);
			}

			EssOtlFreeMembers(hOutline, lAttributeCount, phAttributes);
		}

		//Get UDA
		ESS_MBRCOUNTS_T lUDACounts;
		ESS_PREDICATE_T lUDAPredicate;
		memset(&lUDAPredicate, '\0', sizeof(lUDAPredicate));  
		lUDAPredicate.ulQuery       = ESS_DIMUSERATTRIBUTES;
		lUDAPredicate.pszDimension  = lpMemberInfo->szDimName;
		memset(&lUDACounts, '\0', sizeof(lUDACounts));  
		lUDACounts.ulStart    = 0;
		lUDACounts.ulMaxCount = ~0;

		ESS_PMBRNAME_T lphUDAName = NULL;

		sts = EssOtlGetDimensionUserAttributes(hOutline, &lUDAPredicate, &lUDACounts, &lphUDAName);
		if (!sts && lUDACounts.ulReturnCount)
		{
			sts = EssFree(hInst, lphUDAName);
		}

		//Get Alias
		ESS_STR_T lAliasName = NULL;
		sts = EssOtlGetMemberAlias(hOutline, lphMember[i], ESS_NULL, &lAliasName);
		if (lAliasName)
		{
			EssFree(hInst, lAliasName);
		}

		EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_MBRINFO, 1, lpMemberInfo);
		
	}
	EssOtlFreeMembers(hOutline, lCounts.ulReturnCount, lphMember);
}


void TraverseTreeRecurse(ESS_HMEMBER_T hMember)
{
	ESS_PMBRINFO_T MbrInfo;
	ESS_HMEMBER_T hChild;
	ESS_STS_T  sts = 0;

	while (!sts && hMember)
	{
		sts = EssOtlGetMemberInfo (hOutline, hMember, &MbrInfo);

		ESS_USHORT_T lAssociatedAttributesCount = 0;
		ESS_PHMEMBER_T lphAssociatedAttributes = NULL;
		sts = EssOtlGetAssociatedAttributes(hOutline, hMember, &lAssociatedAttributesCount, &lphAssociatedAttributes);
		EssFree(hInst, lphAssociatedAttributes);

		ESS_USHORT_T lUserAttributeCount = 0;
		ESS_PMBRNAME_T lUserAttributeList = NULL;
		sts = EssOtlGetUserAttributes(hOutline, hMember, &lUserAttributeCount, &lUserAttributeList);
		EssFree(hInst, lUserAttributeList);

		/* ADD THE PROCESSING FOR EACH MEMBER HERE. */

		if (!sts)
		{
			sts = EssOtlGetChild(hOutline, hMember, &hChild);
			if (!sts && hChild)
			{
				TraverseTreeRecurse(hChild);
			}
		}
		sts = EssOtlGetNextSibling(hOutline, hMember, &hMember);
	}
}

void TraverseTree ()
{
	ESS_HMEMBER_T hMember;
	ESS_STS_T  sts = 0;

	sts = EssOtlGetFirstMember(hOutline, &hMember);
	TraverseTreeRecurse(hMember);
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

	/*Object.hCtx = hCtx;
	Object.ObjType = ESS_OBJTYPE_OUTLINE;
	strcpy(szFileName, DbName);
	Object.AppName = AppName;
	Object.DbName = DbName;
	Object.FileName = szFileName;
	sts = EssOtlOpenOutline(hCtx, &Object, ESS_FALSE, ESS_FALSE, &hOutline);*/


	//get outline info
	ESS_POUTLINEINFO_T lpOutlineInfo = NULL;
	sts = EssOtlGetOutlineInfo(hOutline, &lpOutlineInfo);

	//PrintAppsAndDbs();
	//PrintDimensionsAndLevels();
	PrintProperties();
	//PrintAllProperties();
	//TraverseTree();
	//PrintMeasures();

	//logout
	sts = EssLogout(hCtx);
	//term
	sts = EssTerm(hInst);

	return 0;
}