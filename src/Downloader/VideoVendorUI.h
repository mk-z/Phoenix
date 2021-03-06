
#pragma once
#include <DuiLib/UIlib.h>
#include <vector>
#include <sstream>

#define BT_CloseVwnd			(_T("close_btn"))

enum Select
{
	GetDeviceName,
	GetNothing
};

class CVideoVendorUI :
	public WindowImplBase
{
public:
	CVideoVendorUI();
	~CVideoVendorUI();
	CDuiString GetVendorName();

	virtual void OnFinalMessage(HWND /*hWnd*/);
	virtual void Notify(TNotifyUI& msg);
	DUI_DECLARE_MESSAGE_MAP();

	void OnCloseWnd(TNotifyUI& msg);

protected:
	virtual LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();

private:
	CDuiString		_vendor_name;
	Select			_is_select;
};
