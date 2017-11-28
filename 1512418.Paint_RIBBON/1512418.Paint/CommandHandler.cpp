// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
#include "stdafx.h"
#include <UIRibbon.h>

#include "CommandHandler.h"
#include "RibbonIDs.h"
#include "RibbonFramework.h"
#include "Application.h"
#include "resource.h"
#include <UIRibbonPropertyHelpers.h>
#include <commdlg.h> 
#pragma comment(lib, "ComCtl32.lib")

extern int isChosen;
// Static method to create an instance of the object.
HRESULT CCommandHandler::CreateInstance(IUICommandHandler **ppCommandHandler)
{
	if (!ppCommandHandler)
	{
		return E_POINTER;
	}

	*ppCommandHandler = NULL;

	HRESULT hr = S_OK;

	CCommandHandler* pCommandHandler = new CCommandHandler();

	if (pCommandHandler != NULL)
	{
		*ppCommandHandler = static_cast<IUICommandHandler *>(pCommandHandler);
	}
	else
	{
		hr = E_OUTOFMEMORY;
	}

	return hr;
}

// IUnknown method implementations.
STDMETHODIMP_(ULONG) CCommandHandler::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CCommandHandler::Release()
{
	LONG cRef = InterlockedDecrement(&m_cRef);
	if (cRef == 0)
	{
		delete this;
	}

	return cRef;
}

STDMETHODIMP CCommandHandler::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == __uuidof(IUnknown))
	{
		*ppv = static_cast<IUnknown*>(this);
	}
	else if (iid == __uuidof(IUICommandHandler))
	{
		*ppv = static_cast<IUICommandHandler*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	return S_OK;
}

//
//  FUNCTION: UpdateProperty()
//
//  PURPOSE: Called by the Ribbon framework when a command property (PKEY) needs to be updated.
//
//  COMMENTS:
//
//    This function is used to provide new command property values, such as labels, icons, or
//    tooltip information, when requested by the Ribbon framework.  
//    
//    In this SimpleRibbon sample, the method is not implemented.  
//

int GetContextMapIDFromCommandID(int iCmdID)
{
	int iRet = 0;

	switch (iCmdID)
	{
	case ID_BTN_LINE:
		iRet = ID_BTN_LINE;
		break;
	case ID_BTN_ELLIPSE:
		iRet = ID_BTN_ELLIPSE;
		break;
	case ID_BTN_RECT:
		iRet = ID_BTN_RECT;
		break;

	default:
		;
	}

	return iRet;
}


STDMETHODIMP CCommandHandler::UpdateProperty(
	UINT nCmdID,
	REFPROPERTYKEY key,
	const PROPVARIANT* ppropvarCurrentValue,
	PROPVARIANT* ppropvarNewValue)
{
	UNREFERENCED_PARAMETER(nCmdID);
	UNREFERENCED_PARAMETER(key);
	UNREFERENCED_PARAMETER(ppropvarCurrentValue);
	UNREFERENCED_PARAMETER(ppropvarNewValue);
	//HRESULT hr;
	
	//if (key == UI_PKEY_BooleanValue)
	//{

	//	hr = UIInitPropertyFromBoolean(UI_PKEY_BooleanValue, g_pApplication->GetCurrentContext() == GetContextMapIDFromCommandID(nCmdID), ppropvarNewValue);

	//}

	return E_NOTIMPL;
}

//
//  FUNCTION: Execute()
//
//  PURPOSE: Called by the Ribbon framework when a command is executed by the user.  For example, when
//           a button is pressed.
//
STDMETHODIMP CCommandHandler::Execute(
	UINT nCmdID,
	UI_EXECUTIONVERB verb,
	const PROPERTYKEY* key,
	const PROPVARIANT* ppropvarValue,
	IUISimplePropertySet* pCommandExecutionProperties)
{
	UNREFERENCED_PARAMETER(pCommandExecutionProperties);
	UNREFERENCED_PARAMETER(ppropvarValue);
	UNREFERENCED_PARAMETER(key);
	UNREFERENCED_PARAMETER(verb);
	UNREFERENCED_PARAMETER(nCmdID);
	//HRESULT hr;
	//if (key != NULL && *key == UI_PKEY_BooleanValue)
	//{
	//	g_pApplication->SetCurrentContext(GetContextMapIDFromCommandID(nCmdID));

	//	// We need to update the toggle state (boolean value) of the toggle buttons,
	//	// But we just invalidate all things to keep it simple.
	//	hr = g_pFramework->InvalidateUICommand(UI_ALL_COMMANDS, UI_INVALIDATIONS_VALUE, NULL);

	//}
	if (nCmdID == ID_BTN_LINE)
	{
		isChosen = LINE;
	
		//MessageBox(0, 0, 0, 0);
	}
	if (nCmdID == ID_BTN_ELLIPSE)
	{
		isChosen = ELLIPSE;

		//MessageBox(0, 0, 0, 0);
	}
	if (nCmdID == ID_BTN_RECT)
	{
		isChosen = RECTANGLE;

//		MessageBox(0, 0, 0, 0);
	}
	return S_OK;
}
