#include "PluginStdAfx.h"
#include "PluginUtil.h"

static CString sDllDir()
{
  TCHAR filePath[MAX_PATH + 1];
  filePath[0] = L'\0';

  if (GetModuleFileName(_AtlBaseModule.GetModuleInstance(), filePath, countof(filePath) - 1))
  {
    TCHAR* pLastBackslash = wcsrchr(filePath, L'\\');
    if (pLastBackslash)
    {
      *(pLastBackslash + 1) = L'\0';
    }
  }

  return filePath;
}

const CString& DllDir()
{
  static CString s_dllDir = sDllDir();
  return s_dllDir;
}

const CString& HtmlDir()
{
  static CString s_htmlDir = DllDir().GetLength()?  (DllDir() + L"html\\") : L"";
  return s_htmlDir;
}

const CString& UserSettingsFileUrl()
{
  static CString s_url = HtmlDir().GetLength()? (FileUrl(HtmlDir() + USERS_LOCAL_USER_SETTINGS_HTML)) : L"";
  return s_url;
}

CString FileUrl(const CString& url)
{
  CString tmpUrl = url;
  tmpUrl.Replace(L'\\', L'/');

  return CString("file:///") + tmpUrl;
}
