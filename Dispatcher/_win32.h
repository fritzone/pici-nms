#pragma once

#ifdef WIN32

#include <windows.h>
#include <commctrl.h>
#include <sql.h>
#include <sqlext.h>

#define StringCchCopy(strDest,nDest,strSrc) strncpy(strDest, strSrc, nDest);

#define IFCRM_DO(wparam,appmsg,fn)  if ( wparam == appmsg) return fn
#define IFNMIDFROM_DO(nm,msg,fn)    if (((NMHDR*)nm)->idFrom == msg) return fn
#define IFNMCODE_DO(nm,msg,fn)      if (((NMHDR*)nm)->code == msg) return fn
#define NEWDIALOG(id,hParent,controller) CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(id),hParent,controller)
#define NEWTHREADSUSPENDED(ThreadFunc, dwThrdParam) CreateThread( NULL, 0, ThreadFunc, dwThrdParam, CREATE_SUSPENDED, NULL)
#define NEWTHREADRUNNING(ThreadFunc, dwThrdParam) CreateThread( NULL, 0, ThreadFunc, dwThrdParam, 0, NULL)
#define POSTDLGRESULT(dlg,result) SetWindowLong(dlg, DWL_MSGRESULT, (LONG)result);
#define SETICON(dlg, icontype, iconid) SendMessage(dlg, WM_SETICON, icontype,(LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(iconid) ) );
#define MSGBOX(x) MessageBox(NULL, x, "System", MB_OK)
#define MSGBOXERROR(x) MessageBox(NULL, x, "System", MB_OK)

#endif

