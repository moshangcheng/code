// SampleRS.h : Declaration of the CSampleRowset

#pragma once

#include "resource.h"       // main symbols
#include "OLEDBProviderSample_i.h"

using namespace ATL;

class CSampleWindowsFile: 
	public WIN32_FIND_DATA
{
public:

BEGIN_PROVIDER_COLUMN_MAP(CSampleWindowsFile)
	PROVIDER_COLUMN_ENTRY("FileAttributes", 1, dwFileAttributes)
	PROVIDER_COLUMN_ENTRY("FileSizeHigh", 2, nFileSizeHigh)
	PROVIDER_COLUMN_ENTRY("FileSizeLow", 3, nFileSizeLow)
	PROVIDER_COLUMN_ENTRY_STR("FileName", 4, cFileName)
	PROVIDER_COLUMN_ENTRY_STR("AltFileName", 5, cAlternateFileName)
END_PROVIDER_COLUMN_MAP()

};

// CSampleCommand
class ATL_NO_VTABLE CSampleCommand : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IAccessorImpl<CSampleCommand>,
	public ICommandTextImpl<CSampleCommand>,
	public ICommandPropertiesImpl<CSampleCommand>,
	public IObjectWithSiteImpl<CSampleCommand>,
	public IConvertTypeImpl<CSampleCommand>,
	public IColumnsInfoImpl<CSampleCommand>,
	public IInternalCommandConnectionImpl<CSampleCommand>

{
public:

BEGIN_COM_MAP(CSampleCommand)
	COM_INTERFACE_ENTRY(ICommand)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IAccessor)
	COM_INTERFACE_ENTRY(ICommandProperties)
	COM_INTERFACE_ENTRY2(ICommandText, ICommand)
	COM_INTERFACE_ENTRY(IColumnsInfo)
	COM_INTERFACE_ENTRY(IConvertType)
	COM_INTERFACE_ENTRY(IInternalConnection)
END_COM_MAP()

// ICommand
public:

	HRESULT FinalConstruct()
	{
		HRESULT hr = CConvertHelper::FinalConstruct();
		if (FAILED (hr))
			return hr;
		hr = IAccessorImpl<CSampleCommand>::FinalConstruct();
		if (FAILED(hr))
			return hr;
		return CUtlProps<CSampleCommand>::FInit();
	}
	void FinalRelease()
	{
		IAccessorImpl<CSampleCommand>::FinalRelease();
	}

	HRESULT WINAPI Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams, 
						  LONG * pcRowsAffected, IUnknown ** ppRowset);

	static ATLCOLUMNINFO* GetColumnInfo(CSampleCommand* pv, ULONG* pcInfo)
	{
		return CSampleWindowsFile::GetColumnInfo(pv,pcInfo);
	}

BEGIN_PROPSET_MAP(CSampleCommand)
	BEGIN_PROPERTY_SET(DBPROPSET_ROWSET)
		PROPERTY_INFO_ENTRY(IAccessor)
		PROPERTY_INFO_ENTRY(IColumnsInfo)
		PROPERTY_INFO_ENTRY(IConvertType)
		PROPERTY_INFO_ENTRY(IRowset)
		PROPERTY_INFO_ENTRY(IRowsetIdentity)
		PROPERTY_INFO_ENTRY(IRowsetInfo)
		PROPERTY_INFO_ENTRY(IRowsetLocate)
		PROPERTY_INFO_ENTRY(BOOKMARKS)
		PROPERTY_INFO_ENTRY(BOOKMARKSKIPPED)
		PROPERTY_INFO_ENTRY(BOOKMARKTYPE)
		PROPERTY_INFO_ENTRY(CANFETCHBACKWARDS)
		PROPERTY_INFO_ENTRY(CANHOLDROWS)
		PROPERTY_INFO_ENTRY(CANSCROLLBACKWARDS)
		PROPERTY_INFO_ENTRY(LITERALBOOKMARKS)
		PROPERTY_INFO_ENTRY(ORDEREDBOOKMARKS)
	END_PROPERTY_SET(DBPROPSET_ROWSET)
END_PROPSET_MAP()

};

class CSampleRowset : 
	public CRowsetImpl< CSampleRowset, CSampleWindowsFile, CSampleCommand>
{
public:

	HRESULT Execute(DBPARAMS * /*pParams*/, LONG* pcRowsAffected)
	{
		HANDLE hFile;

		CW2TEX<_MAX_PATH> szDir(m_strCommandText == L"" ? L"*.*" : m_strCommandText);

		CSampleWindowsFile wf;
		hFile = FindFirstFile(szDir, &wf);
		if (hFile == INVALID_HANDLE_VALUE)
			return DB_E_ERRORSINCOMMAND;
		LONG cFiles = 1;
		BOOL bMoreFiles = TRUE;
		while (bMoreFiles)
		{
			_ATLTRY
			{
				m_rgRowData.Add(wf);
			}
			_ATLCATCH( e )
			{
				_ATLDELETEEXCEPTION( e )
				return E_OUTOFMEMORY;
			}
			bMoreFiles = FindNextFile(hFile, &wf);
			cFiles++;
		}
		FindClose(hFile);
		if (pcRowsAffected != NULL)
			*pcRowsAffected = cFiles;
		return S_OK;
	}
};


