// SampleRS.cpp : Implementation of CSampleCommand

#include "stdafx.h"
#include "SampleRS.h"
#include "SampleDS.h"

// CSampleCommand

HRESULT CSampleCommand::Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams, 
								 LONG * pcRowsAffected, IUnknown ** ppRowset)
{
	CSampleRowset* pRowset;
	return CreateRowset(pUnkOuter, riid, pParams, pcRowsAffected, ppRowset, pRowset);
}

