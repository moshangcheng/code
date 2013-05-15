#if defined _WIN32 || defined _WINDOWS
#include <windows.h>
#endif 

#ifndef AD_UTF8
#define AD_UTF8
#endif

#include <string.h>
#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#if defined _WIN32 || defined _WINDOWS
#pragma pack(push,localid,1)
#endif
#include <essapi.h>
#include <essotl.h>
#if defined _WIN32 || defined _WINDOWS
#pragma pack(pop,localid)
#endif

ESS_HINST_T  hInst;              
ESS_HCTX_T hCtx;
#define MAXQRYLEN 65536
ESS_CHAR_T qry[MAXQRYLEN];
ESS_STR_T AppName = "Sample";
ESS_STR_T DbName = "Basic";

ESS_HOUTLINE_T     hOutline; 
ESS_OBJDEF_T       Object;
ESS_OBJNAME_T      szFileName;

static ESS_CHAR_T *axisnames[] =
{
	"COLUMNS", "ROWS", "PAGES", "CHAPTERS", "SECTIONS"
};

ESS_FUNC_M CustomMessage(ESS_PVOID_T UserContext, /* user context pointer */
	ESS_LONG_T MessageNumber,   /* Essbase message number */
	ESS_USHORT_T Level,           /* message level */
	ESS_STR_T LogString,       /* message log string */
	ESS_STR_T MessageString    /* message string */
	)
{
	printf("hello");
	return 0;
}

#define AD_CHK_PRINTF_1(ARG1, ARG2) \
	do { printf(ARG1, (ARG2) ? (ARG2) : "NullValue"); } while (0)

void PrintResult(ESS_HOUTLINE_T  hOutline,
                 ESS_HMEMBER_T   hMbr)
{
   ESS_PMBRINFO_T pMbrInfo = NULL;
   ESS_STS_T      sts;
   int            size;
   ESS_STR_T      pszFormula = NULL;
   ESS_STR_T      pszLastFormula = NULL;
   ESS_STR_T      pszCommentEx = NULL;
   ESS_STR_T      pszAlias = NULL;
   ESS_STR_T      pszAliasCombo = NULL;
   ESS_PMBRNAME_T pUDAList = NULL;
   ESS_USHORT_T   iCount = 0;
   ESS_STR_T      pszPrev = NULL;
   ESS_USHORT_T   iIndex;

   ESS_ULONG_T* pMemNum;
   ESS_ULONG_T* pDimNum;
   ESS_STR_T    pDimName = NULL;
   ESS_STR_T    pAliasName = NULL;
   ESS_STR_T    pNextName = NULL;
   ESS_STR_T    pPrevName = NULL;
   ESS_STR_T    pParentName = NULL;
   ESS_STR_T    pChildName = NULL;
   ESS_BOOL_T*  pCurrConv = NULL;
   ESS_ULONG_T* pStatus = NULL;

   sts = EssOtlGetMemberInfo(hOutline, hMbr, &pMbrInfo);
   if (sts != 0) goto Error;

   size = sizeof(ESS_MBRINFO_T);

   printf("MbrInfo\n");
   AD_CHK_PRINTF_1("    szMember --------------->(%s)\n",  pMbrInfo->szMember);
   printf("    usLevel  --------------->(%hd)\n", pMbrInfo->usLevel);
   printf("    usGen  ----------------->(%hd)\n", pMbrInfo->usGen);
   printf("    usConsolidation  ------->(%hd)\n", pMbrInfo->usConsolidation);
   printf("    fTwoPass  -------------->(%hd)\n", pMbrInfo->fTwoPass);
   printf("    fExpense  -------------->(%hd)\n", pMbrInfo->fExpense);
   printf("    usConversion ----------->(%hd)\n", pMbrInfo->usConversion);
   AD_CHK_PRINTF_1("    szCurMember ------------>(%s)\n",  pMbrInfo->szCurMember);
   printf("    usTimeBalance ---------->(%hd)\n", pMbrInfo->usTimeBalance);
   printf("    usSkip ----------------->(%hd)\n", pMbrInfo->usSkip);
   printf("    usShare ---------------->(%hd)\n", pMbrInfo->usShare);
   printf("    usStorage -------------->(%hd)\n", pMbrInfo->usStorage);
   printf("    usCategory ------------->(%hd)\n", pMbrInfo->usCategory);
   printf("    usStorageCategory ------>(%hd)\n", pMbrInfo->usStorageCategory);
   AD_CHK_PRINTF_1("    szComment -------------->(%s)\n",  pMbrInfo->szComment);
   printf("    ulChildCount ----------->(%ld)\n", pMbrInfo->ulChildCount);

   sts = EssOtlGetMemberFormula(hOutline, hMbr, &pszFormula);
   if (sts) printf("sts=%d ", sts);
   AD_CHK_PRINTF_1("szFormula ------------------>(%s)\n", pszFormula);

   sts = EssOtlGetMemberLastFormula(hOutline, hMbr, &pszLastFormula);
   if (sts) printf("sts=%d ", sts);
   AD_CHK_PRINTF_1("szLastFormula -------------->(%s)\n", pszLastFormula);

   sts = EssOtlGetMemberCommentEx(hOutline, hMbr, &pszCommentEx);
   if (sts) printf("sts=%d ", sts);
   AD_CHK_PRINTF_1("szCommentEx ---------------->(%s)\n", pszCommentEx);

   sts = EssOtlGetMemberAlias(hOutline, hMbr, ESS_NULL, &pszAlias);
   if (sts) printf("sts=%d ", sts);
   AD_CHK_PRINTF_1("szAlias (Default)----------->(%s)\n", pszAlias);
      
   sts = EssOtlGetNextAliasCombination(hOutline, hMbr, ESS_NULL, "\0", &pszAliasCombo);
   if (sts) printf("sts=%d ", sts);
   
   printf("szAliasCombo ::\n" );
   pszPrev = pszAliasCombo;
   while (sts && pszAliasCombo)
   {
      AD_CHK_PRINTF_1("\t(%s)\n", pszAliasCombo);
      sts = EssOtlGetNextAliasCombination(hOutline, hMbr, ESS_NULL, pszPrev, &pszAliasCombo);
      EssFree(hInst, pszPrev);
      pszPrev = pszAliasCombo;
   }

   sts = EssOtlGetUserAttributes(hOutline, hMbr, &iCount, &pUDAList);
   if (sts) printf("sts=%d ", sts);

   printf("User Defined Attributes ::\n");
   for(iIndex = 0; iIndex < iCount; iIndex++)
      AD_CHK_PRINTF_1("\t(%s)\n", pUDAList[iIndex]);

   sts = EssOtlGetMemberField(hOutline, hMbr, ESS_OTLQRYMBR_NUMBER, (ESS_PPVOID_T) &pMemNum);
   if (sts) 
   { 
      printf("sts=%d ", sts); 
   }
   else 
   {
      printf("Member Number  ------------------>(%ld)\n", *pMemNum);
      EssFree(hInst, pMemNum);
   }
   
   sts = EssOtlGetMemberField(hOutline, hMbr, ESS_OTLQRYMBR_DIMNUMBER, (ESS_PPVOID_T) &pDimNum);
   if (sts) 
   { 
      printf("sts=%d ", sts); 
   }
   else
   {
      printf("Dimension Number ---------------->(%ld)\n", *pDimNum);
      EssFree(hInst, pDimNum);
   }   

   sts = EssOtlGetMemberField(hOutline, hMbr, ESS_OTLQRYMBR_DIMNAME, (ESS_PPVOID_T) &pDimName);
   if (sts) 
   {
      printf("sts=%d ", sts);
   }
   else
   {
      AD_CHK_PRINTF_1("Dimension Name ------------------>(%s)\n",  pDimName);
      EssFree(hInst, pDimName);
   }

   sts = EssOtlGetMemberField(hOutline, hMbr, ESS_OTLQRYMBR_ALIASNAME, (ESS_PPVOID_T) &pAliasName);
   if (sts) 
   {
      printf("sts=%d ", sts);
   }
   else
   {
      AD_CHK_PRINTF_1("Alias Name     ------------------>(%s)\n",  pAliasName);
      EssFree(hInst, pAliasName);
   }
   
   sts = EssOtlGetMemberField(hOutline, hMbr, ESS_OTLQRYMBR_NEXTNAME, (ESS_PPVOID_T) &pNextName);
   if (sts) 
   {
      printf("sts=%d ", sts);
   }
   else
   {
      AD_CHK_PRINTF_1("Next Mbr  Name ------------------>(%s)\n",  pNextName);
      EssFree(hInst, pNextName);
   }
   
   sts = EssOtlGetMemberField(hOutline, hMbr, ESS_OTLQRYMBR_PREVNAME, (ESS_PPVOID_T) &pPrevName);
   if (sts) 
   {
      printf("sts=%d ", sts);
   }
   else
   {
      AD_CHK_PRINTF_1("Prev Mbr  Name ------------------>(%s)\n",  pPrevName);
      EssFree(hInst, pPrevName);
   }

   sts = EssOtlGetMemberField(hOutline, hMbr, ESS_OTLQRYMBR_PARENTNAME, (ESS_PPVOID_T) &pParentName);
   if (sts) 
   {
      printf("sts=%d ", sts);
   }
   else
   {
      AD_CHK_PRINTF_1("Parent MbrName ------------------>(%s)\n",  pParentName);
      EssFree(hInst, pParentName);
   }   

   sts = EssOtlGetMemberField(hOutline, hMbr, ESS_OTLQRYMBR_CHILDNAME, (ESS_PPVOID_T) &pChildName);
   if (sts) 
   {
      printf("sts=%d ", sts);
   }
   else
   {
      AD_CHK_PRINTF_1("Child Mbr Name ------------------>(%s)\n",  pChildName);
      EssFree(hInst, pChildName);
   }
   
   sts = EssOtlGetMemberField(hOutline, hMbr, ESS_OTLQRYMBR_CURRENCYCONVDB, (ESS_PPVOID_T) &pCurrConv);
   if (sts)
   {
      printf("sts=%d ", sts); printf("Curr Conv Type ------------------>\n");
   }
   else
   {
      //AD_CHK_PRINTF_1("Curr Conv Type ------------------>(%ld)\n", *pCurrConv);
      EssFree(hInst, pCurrConv);
   }   

   sts = EssOtlGetMemberField(hOutline, hMbr, ESS_OTLQRYMBR_STATUS, (ESS_PPVOID_T) &pStatus);
   if (sts) 
      { printf("sts=%d ", sts); printf("Status    ------------------>\n"); }
   else
   {
      printf("Status       ------------------>(%hd)\n", *pStatus);
      EssFree(hInst, pStatus);
   }

   EssFree(hInst, pMbrInfo);
   EssFree(hInst, pszFormula);
   EssFree(hInst, pszLastFormula);
   EssFree(hInst, pszCommentEx);
   EssFree(hInst, pszAlias);
   EssFree(hInst, pszAliasCombo);
   return;

Error:
   printf("******************* Error *************************");
}


int TestCode_EssOtlQueryMembersEx()
{
   ESS_STS_T sts = ESS_STS_NOERR;   
   ESS_HOUTLINE_T hOutline; 
   ESS_OBJDEF_T Object;
   ESS_HMEMBER_T hMember = 0;
   ESS_PHMEMBER_T phMemberArray = ESS_NULL;
   ESS_ULONG_T i;
   unsigned long MaxCount = -1;
   ESS_STR_T   member_fields;
   ESS_STR_T   member_selection;

   /* query string to get level numbers of all markets members */
   member_fields    = "<SelectMbrInfo ( MemberName, MemberLevel,Consolidation, MemberFormula ) ";
   member_selection = "@ichild(Product), @ichild(Market)";
   memset(&Object, '\0', sizeof(Object));
   strcpy(szFileName, DbName);
   Object.hCtx      = hCtx;
   Object.ObjType   = ESS_OBJTYPE_OUTLINE;
   Object.AppName   = AppName;
   Object.DbName    = DbName;
   Object.FileName  = szFileName;        
        
   sts = EssOtlOpenOutlineQuery(hCtx, &Object, &hOutline); 
   if (sts) goto exit;
        
   if(!sts)
   {
      ESS_POTLQUERYERRORLIST_T pqryErrorList;
	  ESS_HMEMBER_T lhMember = NULL;
	  ESS_PHMEMBER_T lphMember = NULL;
	  ESS_MBRCOUNTS_T lCounts;
	  ESS_PREDICATE_T lPredicate;
	  memset(&lCounts, '\0', sizeof(lCounts));
	  memset(&lPredicate, '\0', sizeof(lPredicate));

	  lPredicate.ulQuery = ESS_CHILDREN;
	  lPredicate.pszDimension = "Year";
	  lCounts.ulStart = 0;
	  lCounts.ulMaxCount = 10000000;

      //sts = EssOtlQueryMembersEx(hOutline, member_fields, member_selection, &MaxCount, &phMemberArray, &pqryErrorList);
	  sts = EssOtlQueryMembers(hOutline, lhMember, &lPredicate, &lCounts, &lphMember);
      if (sts) goto exit;

      //if (phMemberArray)
		  for (i = 0; i< lCounts.ulReturnCount; i++)
            PrintResult(hOutline, lphMember[i]);
   }                     

   if(MaxCount && phMemberArray)
   {
      sts = EssOtlFreeMembers(hOutline, MaxCount, phMemberArray);
      if (sts)
         printf("EssOtlFreeMembers   sts = %d\n",sts);
   }

   sts = EssOtlCloseOutline(hOutline);

exit:
   return sts;                          
}

void ESS_Init()
{
	ESS_STS_T    sts;
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
	//InitStruct.MessageFunc = (ESS_PFUNC_T)MakeProcInstance((FARPROC)CustomMessage, hInst);

	if ((sts = EssInit(&InitStruct, &hInst)) != ESS_STS_NOERR)
	{
		printf("EssInit failure: %ld\n", sts);
		exit ((int) sts);
	}
	//printf("EssInit sts: %ld\n", sts);  
}    

void ESS_Login ()
{
	ESS_STS_T sts = ESS_STS_NOERR;                                    
	ESS_USHORT_T Items;
	ESS_PAPPDB_T pAppsDbs = NULL;
	ESS_CHAR_T SvrName[ESS_SVRNAMELEN];
	ESS_CHAR_T UserName[ESS_USERNAMELEN];
	ESS_CHAR_T Password[ESS_PASSWORDLEN];

	/* Initialize parameters */
	strcpy(SvrName,"ts-essbase1111");
	strcpy(UserName,"admin");
	strcpy(Password,"password");

	sts = EssLogin(hInst, SvrName, UserName, Password, &Items, &pAppsDbs, &hCtx);

	ESS_ACCESS_T lAccess;
	//sts = EssAutoLogin(hInst, SvrName, UserName, Password, AppName, NULL, AUTO_NODIALOG | AUTO_NOSELECT, &lAccess, &hCtx);

	/*if ( (sts != 0) && (sts != 1051093L) && (sts != 1051090L) )
	{
		printf("EssLogin failure: %ld\n", sts);
		exit ((int) sts);
	}*/
	//printf("EssLogin sts: %ld\n", sts);
}

void ESS_Term()
{
	ESS_STS_T sts = ESS_STS_NOERR;
	if ((sts = EssTerm(hInst)) != ESS_STS_NOERR)
	{
		/* error terminating API */
		exit((ESS_USHORT_T) sts);
	}
	//   printf("EssTerm sts: %ld\n", sts);
}

void ESS_Logout()
{
	ESS_STS_T sts = ESS_STS_NOERR;
	sts = EssLogout(hCtx);
	//  printf("\n\nEssLogout sts: %ld\n",sts);
}

void ESS_SetActive()
{
	/*ESS_USHORT_T  Release;
	ESS_USHORT_T  Version;
	ESS_USHORT_T  Revision;
	EssGetVersion (hCtx, &Release, &Version, &Revision);*/

	ESS_STS_T sts = ESS_STS_NOERR;
	ESS_ACCESS_T Access;
	sts = EssSetActive(hCtx, AppName, DbName, &Access);

	ESS_PAPPINFO_T lAppInfo;
	EssGetApplicationInfo(hCtx, AppName, &lAppInfo);

	memset(&Object, '\0', sizeof(Object));
	EssOtlOpenOutlineQuery(hCtx, &Object, &hOutline);

	//ESS_PAPPINFO_T lAppInfo1;
	//EssGetApplicationInfo(hCtx, "Sample_U", &lAppInfo1);
	//EssFree (hInst, lAppInfo1);

	//ESS_PAPPINFO_T lAppInfo2;
	//EssGetApplicationInfo(hCtx, "Demo", &lAppInfo2);
	//EssFree (hInst, lAppInfo2);
	
	//ESS_PDBINFO_T lpDbInfo1, lpDbInfo2;
	//EssGetDatabaseInfo(hCtx, AppName, "Basic", &lpDbInfo1);
	//EssFree(hInst, lpDbInfo);
	//EssGetDatabaseInfo(hCtx, AppName, "ng", &lpDbInfo2);
	//EssFree(hInst, lpDbInfo);
	/*sts = EssSetActive(hCtx, AppName, "ng", &Access);
	ESS_STR_T lActiveAppName;
	ESS_STR_T lActiveDbName;
	EssAlloc(hInst, 80, (ESS_PPVOID_T)&lActiveAppName);
	EssAlloc(hInst, 80, (ESS_PPVOID_T)&lActiveDbName);
	EssGetActive(hCtx, &lActiveAppName, &lActiveDbName, &Access);
	EssFree (hInst, lActiveAppName);
	EssFree (hInst, lActiveDbName);*/
	//   printf("EssSetActive sts: %ld\n",sts);

	/*memset(&Object, '\0', sizeof(Object));
	Object.hCtx = hCtx;
	Object.ObjType = ESS_OBJTYPE_OUTLINE;
	strcpy(szFileName, DbName);
	Object.AppName = AppName;
	Object.DbName = DbName;
	Object.FileName = szFileName;
	sts = EssOtlOpenOutline(hCtx, &Object, ESS_TRUE, ESS_TRUE, &hOutline);*/
	//for unicode app
	//sts = EssOtlOpenOutlineEx(hCtx, &Object, ESS_TRUE, ESS_TRUE, lAppInfo->AppLocale, &hOutline);
}

ESS_FUNC_M ESS_GetMbrInfo()
{
   ESS_FUNC_M sts = ESS_STS_NOERR;
   ESS_MEMBERINFO_T  *pMbrInfo = NULL;
   sts = EssGetMemberInfo(hCtx, "East", &pMbrInfo);
   if (!sts)
   {      
      if (pMbrInfo)
      {
         EssFreeStructure(hCtx, ESS_DT_STRUCT_MEMBERINFO, 1, (ESS_PVOID_T)pMbrInfo);
      }
   }
   return (sts);
}

ESS_FUNC_M ESS_QueryMember(ESS_STR_T iDimName)
{
	ESS_FUNC_M sts = ESS_STS_NOERR;

	ESS_HMEMBER_T lhMember = NULL;
	ESS_PHMEMBER_T lphMember = NULL;
	ESS_MBRCOUNTS_T lCounts;
	ESS_PREDICATE_T lPredicate;
	memset(&lCounts, '\0', sizeof(lCounts));
	memset(&lPredicate, '\0', sizeof(lPredicate));

	lPredicate.ulQuery = ESS_DESCENDANTS;
	lPredicate.pszDimension = iDimName;
	lCounts.ulStart = 0;
	lCounts.ulMaxCount = 10000000;
	sts = EssOtlQueryMembers(hOutline, lhMember,  &lPredicate, &lCounts, &lphMember);
	//ESS_HMEMBER_T lhPrevMember, lhCurMember = lphMember[0];
	for(ULONG i = 0; i < lCounts.ulReturnCount; i++)
	{
		ESS_STR_T lMemberAlias = NULL;
		ESS_PMBRINFO_T lpMemberInfo = NULL;
		EssOtlGetMemberAlias(hOutline, lphMember[i], ESS_NULL, &lMemberAlias);
		sts = EssOtlGetMemberInfo(hOutline, lphMember[i], &lpMemberInfo);
		EssOtlFreeStructure(hOutline, ESS_DT_STRUCT_MEMBERINFO, 1, lpMemberInfo);
		//lhPrevMember = lhCurMember;
		//EssOtlGetNextSibling(hOutline, lhPrevMember, &lhCurMember);
	}

	EssOtlFreeMembers(hOutline, lCounts.ulReturnCount, lphMember);

	return sts;
}

ESS_FUNC_M Ess_GetAllDims()
{
	ESS_FUNC_M sts = ESS_STS_NOERR;
	ULONG lpDimCount;
	ESS_PDIMENSIONINFO_T lpDimInfo;
	sts = EssGetDimensionInfo(hCtx, NULL, &lpDimCount, &lpDimInfo);
	for(ULONG i = 0; i < lpDimCount; i++)
	{
		ESS_QueryMember(lpDimInfo[i].DimName);
	}
	EssFree(hInst, lpDimInfo);
	return sts;
}

ESS_FUNC_M Ess_GetLevelName()
{
	ESS_STS_T          sts = 0;
	ESS_STR_T          Dimension;
	ESS_USHORT_T       LevelNum;
	ESS_STR_T          LevelName;

	Dimension = "Year";
	LevelNum = 0;   

	if (!sts)
	{
	   sts = EssOtlGetLevelName(hOutline, Dimension,  
			 LevelNum, &LevelName);
	}

	if (!sts && LevelName)
	{
	   printf("Level Name: %s\n",LevelName);
			 EssFree(hInst, LevelName);
	}
	return (sts);
}


int main(int argc, char *argv[])
{
	FILE *f, *file_out;
	char *s, *sout;
	int n, l, e;

	assert(argc > 1);
	f = fopen(argv[1], "r");
	assert(f != NULL);
	s = qry;
	n = MAXQRYLEN;
	while (n > 0 && !feof(f) && fgets(s, n, f) != NULL)
	{
		l = strlen(s);
		s += l;
		n -= l;
	}
	if ((e = ferror(f)) != 0)
	{
		printf("fgets error %d\n", e);
		exit((int) e);
	}
	fclose(f);
	printf("The query is\n%s\n", qry);
	if (argc > 2)
	{
		AppName = argv[2];
	}
	if (argc > 3)
	{
		DbName = argv[3];
	}

	//file_out = freopen("C:\\Users\\shu\\Desktop\\out.txt", "w", stdout);

	ESS_Init();
	ESS_Login();
	ESS_SetActive();

	//TestCode_EssOtlQueryMembersEx();
	//Ess_GetAllDims();

	//ESS_GetMbrInfo();
	//Ess_GetLevelName();

	ESS_Logout();
	ESS_Term();

	return 0;
} 

