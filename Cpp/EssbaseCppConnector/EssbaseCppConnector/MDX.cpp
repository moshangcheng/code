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
#include <iostream>

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


void ESS_MdxAxis(ESS_MDX_QRYHDL_T hQry, ESS_MDX_AXISHDL_T hAxis, ESS_STR_T pszAxisName)
{
	ESS_STS_T    sts;
	ESS_ULONG_T ulNAxisDims, ulAxisSize;
	ESS_ULONG_T ulNClusters, ulClusterSize, ulNClusterDims;
	ESS_ULONG_T ulAxisDimCnt, ulIndex, ulPropCnt;
	ESS_ULONG_T ulClusterCnt, ulClusterDimCnt;
	ESS_PULONG_T ulaDimSizes;
	ESS_MDX_PCLUSTERHDL_T haClusters;
	ESS_MDX_CLUSTERHDL_T hCluster;
	ESS_MDX_PDIMHDL_T haDims;
	ESS_STR_T pszDimName, pszMbrIdentifier, pszPropName;
	ESS_MDX_PMBRHDL_T haMbrs;
	ESS_PULONG_T ulaNProps = NULL;
	ESS_MDX_PPPROPHDL_T haaProps = NULL;
	ESS_MDX_PPROPHDL_T haProps;
	ESS_MDX_PROPHDL_T hProp;
	ESS_MDX_PROPTYPE_T propType;
	ESS_MDX_PROPVALUE_T propval;

	if ((sts = EssMdxGetAxisInfo(hAxis, &ulAxisSize, &ulNAxisDims, &haDims)) != ESS_STS_NOERR)
	{
		printf("EssMdxGetAxisInfo failure: %ld\n", sts);
		exit ((int) sts);
	}
	//printf("EssMdxGetAxisInfo sts: %ld\n", sts);
	printf("%s Size %ld Num dims %ld\n", pszAxisName, ulAxisSize, ulNAxisDims);
	if (ulAxisSize == 0)
	{
		return;
	}
	if ((sts = EssAlloc(hInst, ulNAxisDims * sizeof(ESS_ULONG_T), (ESS_PPVOID_T) &ulaNProps)) != ESS_STS_NOERR)
	{
		printf("EssAlloc failure: %ld\n", sts);
		exit ((int) sts);
	}
	//printf("EssAlloc sts: %ld\n", sts);
	if ((sts = EssAlloc(hInst, ulNAxisDims * sizeof(ESS_MDX_PPROPHDL_T), (ESS_PPVOID_T) &haaProps)) != ESS_STS_NOERR)
	{
		printf("EssAlloc failure: %ld\n", sts);
		exit ((int) sts);
	}
	//printf("EssAlloc sts: %ld\n", sts);
	for (ulAxisDimCnt = 0; ulAxisDimCnt < ulNAxisDims; ulAxisDimCnt++)
	{
		if ((sts = EssMdxGetDimInfo(haDims[ulAxisDimCnt], &pszDimName, &ulaNProps[ulAxisDimCnt], &haaProps[ulAxisDimCnt])) != ESS_STS_NOERR)
		{
			printf("EssMdxGetDimInfo failure: %ld\n", sts);
			exit ((int) sts);
		}
		// printf("EssMdxGetDimInfo sts: %ld\n", sts);
		printf("Dim %ld name %s #props %ld\n", ulAxisDimCnt, pszDimName, ulaNProps[ulAxisDimCnt]);
		haProps = haaProps[ulAxisDimCnt];
		for (ulPropCnt = 0; ulPropCnt < ulaNProps[ulAxisDimCnt]; ulPropCnt++)
		{
			hProp = haProps[ulPropCnt];
			if ((sts = EssMdxGetPropertyInfo(hProp, &pszPropName, &propType)) != ESS_STS_NOERR)
			{
				printf("EssMdxGetPropertyInfo failure: %ld\n", sts);
				exit ((int) sts);
			}
			// printf("EssMdxGetPropertyInfo sts: %ld\n", sts);
			printf("Property %ld type %ld name %s\n", ulPropCnt, propType, pszPropName);
		}
	}
	if ((sts = EssMdxGetClusters(hAxis, &ulNClusters, &haClusters)) != ESS_STS_NOERR)
	{
		printf("EssMdxGetClusters failure: %ld\n", sts);
		exit ((int) sts);
	}
	//printf("EssMdxGetClusters sts: %ld\n", sts);
	printf("Num clusters %ld\n", ulNClusters);
	for (ulClusterCnt = 0; ulClusterCnt < ulNClusters; ulClusterCnt++)
	{
		hCluster = haClusters[ulClusterCnt];
		if ((sts = EssMdxGetClusterInfo(hCluster, &ulClusterSize, &ulNClusterDims, &ulaDimSizes)) != ESS_STS_NOERR)
		{
			printf("EssMdxGetClusterInfo failure: %ld\n", sts);
			exit ((int) sts);
		}
		// printf("EssMdxGetClusterInfo sts: %ld\n", sts);
		printf("Cluster %ld Size %ld\n", ulClusterCnt, ulClusterSize);
		for (ulClusterDimCnt = 0; ulClusterDimCnt < ulNClusterDims; ulClusterDimCnt++)
		{
			printf("Cluster Dim %ld Size %ld\n", ulClusterDimCnt, ulaDimSizes[ulClusterDimCnt]);
		}
		for (ulIndex = 0; ulIndex < ulClusterSize; ulIndex++)
		{
			if ((sts = EssMdxGetClusterMembers(hCluster, ulIndex, &haMbrs)) != ESS_STS_NOERR)
			{
				printf("EssMdxGetClusterMembers failure: %ld\n", sts);
				exit ((int) sts);
			}
			//  printf("EssMdxGetClusterMembers sts: %ld\n", sts);
			for (ulClusterDimCnt = 0; ulClusterDimCnt < ulNClusterDims; ulClusterDimCnt++)
			{
				if ((sts = EssMdxGetMbrIdentifier(haMbrs[ulClusterDimCnt], &pszMbrIdentifier)) != ESS_STS_NOERR)
				{
					printf("EssMdxGetMbrIdentifier failure: %ld\n", sts);
					exit ((int) sts);
				}
				// printf("EssMdxGetMbrIdentifier sts: %ld\n", sts);
				printf("Mbr %ld identifier %s\n", ulClusterDimCnt, pszMbrIdentifier);
				haProps = haaProps[ulClusterDimCnt];
				for (ulPropCnt = 0;	ulPropCnt < ulaNProps[ulClusterDimCnt]; ulPropCnt++)
				{
					if ((sts = EssMdxGetMbrProperty(haMbrs[ulClusterDimCnt], haProps[ulPropCnt], &propval)) != ESS_STS_NOERR)
					{
						printf("EssMdxGetMbrProperty failure: %ld\n", sts);
						exit ((int) sts);
					}
					//  printf("EssMdxGetMbrProperty sts: %ld\n", sts);
					printf("Property %ld Type ", ulPropCnt);
					switch (propval.ulPropType)
					{
					case ESS_MDX_PROPTYPE_ULONG:
						{
							printf("Ulong Value: %ld\n", propval.value.ulData);
							break;
						}
					case ESS_MDX_PROPTYPE_STRING:
						{
							printf("String Value: %s\n", propval.value.strData);
							break;
						}
					case ESS_MDX_PROPTYPE_BOOL:
						{
							printf("Bool Value: %s\n", propval.value.bData ? "TRUE" : "FALSE");
							break;
						}
					case ESS_MDX_PROPTYPE_DOUBLE:
						{
							printf("Double Value: %lf\n", propval.value.dblData);
							break;
						}
					case ESS_MDX_PROPTYPE_DATETIME:
						{
							ESS_CHAR_T tmpbuf[80];
							struct tm* pTime;
							pTime =  gmtime((time_t*)&(propval.value.dtData));
							sprintf(tmpbuf, "%02i-%02i-%04i", pTime->tm_mon+1, pTime->tm_mday,pTime->tm_year+1900);
							printf("DateTime Value: %s\n", tmpbuf);
							break;
						}
					case ESS_MDX_PROPTYPE_NONE:
						{
							printf("NULL Value\n");
							break;
						}
					}
				}
			}
			if ((sts = EssFree(hInst, (ESS_PVOID_T) haMbrs)) != ESS_STS_NOERR)
			{
				printf("EssFree failure: %ld\n", sts);
				exit ((int) sts);
			}
			// printf("EssFree sts: %ld\n", sts);
		}
		for (ulClusterDimCnt = 0; ulClusterDimCnt < ulNClusterDims; ulClusterDimCnt++)
		{
			if ((sts = EssMdxGetClusterDimMembers(hCluster, ulClusterDimCnt, &haMbrs)) != ESS_STS_NOERR)
			{
				printf("EssMdxGetClusterDimMembers failure: %ld\n", sts);
				exit ((int) sts);
			}
			// printf("EssMdxGetClusterDimMembers sts: %ld\n", sts);
			for (ulIndex = 0; ulIndex < ulaDimSizes[ulClusterDimCnt]; ulIndex++)
			{
				if ((sts = EssMdxGetMbrIdentifier(haMbrs[ulIndex], &pszMbrIdentifier)) != ESS_STS_NOERR)
				{
					printf("EssMdxGetMbrIdentifier failure: %ld\n", sts);
					exit ((int) sts);
				}
				//  printf("EssMdxGetMbrIdentifier sts: %ld\n", sts);
				printf("Dim %ld Mbr %ld identifier %s\n", ulClusterDimCnt, ulIndex, pszMbrIdentifier);
			}
		}
	}
	for (ulIndex = 0; ulIndex < ulAxisSize; ulIndex++)
	{
		if ((sts = EssMdxGetAxisMembers(hAxis, ulIndex, &haMbrs)) != ESS_STS_NOERR)
		{
			printf("EssMdxGetAxisMembers failure: %ld\n", sts);
			exit ((int) sts);
		}
		// printf("EssMdxGetAxisMembers sts: %ld\n", sts);
		for (ulAxisDimCnt = 0; ulAxisDimCnt < ulNAxisDims; ulAxisDimCnt++)
		{
			if ((sts = EssMdxGetMbrIdentifier(haMbrs[ulAxisDimCnt], &pszMbrIdentifier)) != ESS_STS_NOERR)
			{
				printf("EssMdxGetMbrIdentifier failure: %ld\n", sts);
				exit ((int) sts);
			}
			//    printf("EssMdxGetMbrIdentifier sts: %ld\n", sts);
			printf("Mbr %ld identifier %s\n", ulAxisDimCnt, pszMbrIdentifier);
			haProps = haaProps[ulAxisDimCnt];
			for (ulPropCnt = 0; ulPropCnt < ulaNProps[ulAxisDimCnt]; ulPropCnt++)
			{
				hProp = haProps[ulPropCnt];
				if ((sts = EssMdxGetPropertyInfo(hProp, &pszPropName, &propType)) != ESS_STS_NOERR)
				{
					printf("EssMdxGetPropertyInfo failure: %ld\n", sts);
					exit ((int) sts);
				}
				if ((sts = EssMdxGetMbrProperty(haMbrs[ulAxisDimCnt], hProp, &propval)) != ESS_STS_NOERR)
				{
					printf("EssMdxGetMbrProperty failure: %ld\n", sts);
					exit ((int) sts);
				}
				//  printf("EssMdxGetMbrProperty sts: %ld\n", sts);
				printf("Property %ld Type ", ulPropCnt);
				switch (propval.ulPropType)
				{
				case ESS_MDX_PROPTYPE_ULONG:
					{
						printf("Ulong Value: %ld\n", propval.value.ulData);
						break;
					}
				case ESS_MDX_PROPTYPE_STRING:
					{
						printf("String Value: %s\n", propval.value.strData);
						break;
					}
				case ESS_MDX_PROPTYPE_BOOL:
					{
						printf("Bool Value: %s\n", propval.value.bData ? "TRUE" : "FALSE");
						break;
					}
				case ESS_MDX_PROPTYPE_DOUBLE:
					{
						printf("Double Value: %lf\n", propval.value.dblData);
						break;
					}
				case ESS_MDX_PROPTYPE_DATETIME:
					{
						ESS_CHAR_T tmpbuf[80];
						struct tm* pTime;
						pTime =  gmtime((time_t*)&(propval.value.dtData));
						sprintf(tmpbuf, "%02i-%02i-%04i", pTime->tm_mon+1, pTime->tm_mday,pTime->tm_year+1900);
						printf("DateTime Value: %s\n", tmpbuf);
						break;
					}
				case ESS_MDX_PROPTYPE_NONE:
					{
						printf("NULL Value\n");
						break;
					}
				}
			}
		}
		if ((sts = EssFree(hInst, (ESS_PVOID_T) haMbrs)) != ESS_STS_NOERR)
		{
			printf("EssFree failure: %ld\n", sts);
			exit ((int) sts);
		}
		//  printf("EssFree sts: %ld\n", sts);
	}
	if ((sts = EssFree(hInst, (ESS_PVOID_T) ulaNProps)) != ESS_STS_NOERR)
	{
		printf("EssFree failure: %ld\n", sts);
		exit ((int) sts);
	}
	// printf("EssFree sts: %ld\n", sts);
	if ((sts = EssFree(hInst, (ESS_PVOID_T) haaProps)) != ESS_STS_NOERR)
	{
		printf("EssFree failure: %ld\n", sts);
		exit ((int) sts);
	}
	//printf("EssFree sts: %ld\n", sts);
}

void ESS_MdxQry()
{
	ESS_STS_T    sts;
	ESS_MDX_QRYHDL_T hQry;
	ESS_ULONG_T ulNAxes, ulNAxisDims, ulAxisSize, ulResultSize;
	ESS_ULONG_T ulNClusters, ulClusterSize, ulNClusterDims;
	ESS_ULONG_T ulAxisCnt, ulAxisDimCnt, ulIndex, ulPropCnt;
	ESS_ULONG_T ulCellOffset, ulClusterCnt, ulClusterDimCnt;
	ESS_MDX_CELLSTATUS_T ulCellStatus;
	ESS_PULONG_T ulaDimSizes;
	ESS_MDX_PCLUSTERHDL_T haClusters;
	ESS_MDX_CLUSTERHDL_T hCluster;
	ESS_MDX_PAXISHDL_T haAxes;
	ESS_MDX_PDIMHDL_T haDims;
	ESS_STR_T pszDimName, pszMbrIdentifier, pszPropName;
	ESS_MDX_AXISHDL_T hAxis, hSlicerAxis;
	ESS_MDX_PMBRHDL_T haMbrs;
	ESS_MDX_CELLHDL_T hCell;
	ESS_DOUBLE_T dValue;
	ESS_BOOL_T bIsMissing, bNoAccess;
	ESS_PULONG_T ulaNProps;
	ESS_MDX_PPPROPHDL_T haaProps;
	ESS_MDX_PPROPHDL_T haProps;
	ESS_MDX_PROPHDL_T hProp;
	ESS_MDX_PROPTYPE_T propType;
	ESS_MDX_PROPVALUE_T propval;

	//shu;
	if ((sts = EssMdxNewQuery(hCtx, qry, &hQry)) != ESS_STS_NOERR)
	{
		printf("EssMdxNewQuery failure: %ld\n", sts);
		exit ((int) sts);
	}
	// printf("EssMdxNewQuery sts: %ld\n", sts);


	if ((sts = EssMdxSetXmlaMode(hQry)) != ESS_STS_NOERR)
	{
		printf("EssMdxSetXmlaMode failure: %ld\n", sts);
		exit ((int) sts);
	}

	//shu;
	if ((sts = EssMdxSetMbrIdType(hQry, ESS_MDX_MEMBERIDTYPE_NAME)) !=	ESS_STS_NOERR)
	{
		printf("EssMdxSetMbrIdType failure: %ld\n", sts);
		exit ((int) sts);
	}
	//  printf("EssMdxSetMbrIdType sts: %ld\n", sts);

	if ((sts = EssMdxSetNeedCellStatus(hQry)) != ESS_STS_NOERR)
	{
		printf("EssMdxSetNeedCellStatus failure: %ld\n", sts);
		exit ((int) sts);
	}
	//   printf("EssMdxSetNeedCellStatus sts: %ld\n", sts);
	if ((sts = EssMdxSetQueryCellProperties (hQry, ESS_MDX_CELLPROP_FORMATTED_VALUE | ESS_MDX_CELLPROP_FORMAT_STRING)) != ESS_STS_NOERR)
	{
		printf("EssMdxSetQueryCellProperties failure: %ld\n", sts);
		exit ((int) sts);
	}



	//shu;
	if ((sts = EssMdxExecuteQuery(hQry)) != ESS_STS_NOERR)
	{
		printf("EssMdxExecuteQuery failure: %ld\n", sts);
		exit ((int) sts);
	}
	// printf("EssMdxExecuteQuery sts: %ld\n", sts);

	//shu;
	if ((sts = EssMdxGetAxes(hQry, &ulNAxes, &haAxes, &hSlicerAxis)) != ESS_STS_NOERR)
	{
		printf("EssMdxGetAxes failure: %ld\n", sts);
		exit ((int) sts);
	}
	//  printf("EssMdxGetAxes sts: %ld\n", sts);
	printf("Number of axes: %ld\n", ulNAxes);

	ulResultSize = 1;
	for (ulAxisCnt = 0; ulAxisCnt < ulNAxes; ulAxisCnt++)
	{
		hAxis = haAxes[ulAxisCnt];
		if ((sts = EssMdxGetAxisInfo(hAxis, &ulAxisSize, &ulNAxisDims, &haDims)) != ESS_STS_NOERR)
		{
			printf("EssMdxGetAxisInfo failure: %ld\n", sts);
			exit ((int) sts);
		}
		//    printf("EssMdxGetAxisInfo sts: %ld\n", sts);
		printf("Axis %ld Size %ld Num dims %ld\n", ulAxisCnt, ulAxisSize, ulNAxisDims);
		ulResultSize *= ulAxisSize;
	}

	if (hSlicerAxis)
	{
		ESS_MdxAxis(hQry, hSlicerAxis, "SLICER");
	}
	else
	{
		printf("Slicer Axis is empty\n");
	}

	for (ulAxisCnt = 0; ulAxisCnt < ulNAxes; ulAxisCnt++)
	{
		hAxis = haAxes[ulAxisCnt];
		ESS_MdxAxis(hQry, hAxis, axisnames[ulAxisCnt]);
	}
	for (ulCellOffset = 0; ulCellOffset < ulResultSize; ulCellOffset++)
	{
		if ((sts = EssMdxGetCellAtOffset(hQry, ulCellOffset, &hCell)) != ESS_STS_NOERR)
		//if ((sts = EssMdxGetCellAtIndices(hQry, ulCellOffset, &hCell)) != ESS_STS_NOERR)
		{
			printf("EssMdxGetCellAtOffset failure: %ld\n", sts);
			exit ((int) sts);
		}
		/*ESS_ULONG_T dataType, cellInfo, cellStatus;
		if ((sts = EssMdxGetCellInfo (hCell, &dataType, &cellInfo, &cellStatus) != ESS_STS_NOERR))
		{
			printf("EssMdxGetValue failure: %ld\n", sts);
			exit ((int) sts);
		}*/
		//    printf("EssMdxGetCellAtOffset sts: %ld\n", sts);
		ULONG lCellType = 0;
		ESS_MDX_CELLINFO_T lCellInfo = 0;
		ESS_MDX_CELLSTATUS_T lCellStatus = 0;
		sts = EssMdxGetCellInfo(hCell, &lCellType, &lCellInfo, &lCellStatus);
		if ((sts = EssMdxGetValue(hCell, &bIsMissing, &bNoAccess, &dValue)) != ESS_STS_NOERR)
		{
			printf("EssMdxGetValue failure: %ld\n", sts);
			exit ((int) sts);
		}
		ESS_STR_T lFormattedValue;
		if((sts = EssMdxGetFormattedValue(hQry, hCell, &lFormattedValue)) != ESS_STS_NOERR)
		{
			printf("EssMdxGetFormattedValue failure: %ld\n", sts);
			exit ((int) sts);
		}
		//     printf("EssMdxGetValue sts: %ld\n", sts);
		if (bIsMissing)
		{
			printf("CellOffset %ld Value #Missing\n", ulCellOffset);
		}
		else if (bNoAccess)
		{
			printf("CellOffset %ld Value #NoAccess\n", ulCellOffset);
		}
		else
		{
			printf("CellOffset %ld Value %lf\n", ulCellOffset, dValue);
		}
		if (!bNoAccess)
		{
			if ((sts = EssMdxGetCellStatus(hQry, hCell, &ulCellStatus)) != ESS_STS_NOERR)
			{
				printf("EssMdxGetCellStatus failure: %ld\n", sts);
				exit ((int) sts);
			}
			//     printf("EssMdxGetCellStatus sts: %ld\n", sts);
			if (ulCellStatus & ESS_MDX_CELLSTATUS_LINKEDOBJS)
			{
				printf("Cell status: LINKEDOBJS\n");
			}
			if (ulCellStatus & ESS_MDX_CELLSTATUS_DYNCALC)
			{
				printf("Cell status: DYNCALC\n");
			}
			if (ulCellStatus & ESS_MDX_CELLSTATUS_CALCEDMBR)
			{
				printf("Cell status: CALCEDMBR\n");
			}
			if (ulCellStatus & ESS_MDX_CELLSTATUS_READONLY)
			{
				printf("Cell status: READONLY\n");
			}
		}
	}

	if ((sts = EssMdxFreeQuery(hQry)) != ESS_STS_NOERR)
	{
		printf("EssMdxFreeQuery failure: %ld\n", sts);
		exit ((int) sts);
	}
	//   printf("EssMdxFreeQuery sts: %ld\n", sts);

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
	ESS_USHORT_T  Release;
	ESS_USHORT_T  Version;
	ESS_USHORT_T  Revision;
	EssGetVersion (hCtx, &Release, &Version, &Revision);

	ULONG lAPIVersion;
	EssGetAPIVersion(&lAPIVersion);
	//std::cout << std::oct << lAPIVersion << std::endl;
	printf("API Version %x\n", lAPIVersion);

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

	lPredicate.ulQuery = ESS_DIMENSION;
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

	//Ess_GetAllDims();

	//ESS_GetMbrInfo();
	//Ess_GetLevelName();

	ESS_MdxQry();

	ESS_Logout();
	ESS_Term();

	return 0;
} 
