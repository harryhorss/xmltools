// Report.cpp: implementation of the Report class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PluginInterface.h"
#include "Report.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const int MAX_BUFFER = 4096;
std::wstring currentLog;

Report::Report() {
}

Report::~Report() {
}

void Report::_printf_err(const wchar_t* s, ...) {
  if (!s || !wcslen(s)) return;

  va_list msg;
  wchar_t buffer[MAX_BUFFER] = { '\0' };

  va_start(msg, s);
  _vsntprintf(buffer, MAX_BUFFER - 1, s, msg);
  va_end(msg);

  if (wcslen(buffer) <= 0) return;

  ::MessageBox(nppData._nppHandle, buffer, L"XML Tools plugin", MB_OK | MB_ICONEXCLAMATION);
}

void Report::_fprintf_err(void * ctx, const wchar_t* s, ...) {
  if (!s || !wcslen(s)) return;
  
  va_list msg;
  wchar_t buffer[MAX_BUFFER] = { '\0' };
  
  va_start(msg, s);
  _vsntprintf(buffer, MAX_BUFFER - 1, s, msg);
  va_end(msg);
  
  if (wcslen(buffer) <= 0) return;
  
  ::MessageBox(nppData._nppHandle, buffer, L"XML Tools plugin", MB_OK | MB_ICONEXCLAMATION);
}

void Report::_printf_inf(const wchar_t* s, ...) {
  if (!s || !wcslen(s)) return;

  va_list msg;
  wchar_t buffer[MAX_BUFFER] = { '\0' };

  va_start(msg, s);
  _vsntprintf(buffer, MAX_BUFFER - 1, s, msg);
  va_end(msg);

  if (wcslen(buffer) <= 0) return;

  ::MessageBox(nppData._nppHandle, buffer, L"XML Tools plugin", MB_OK | MB_ICONINFORMATION);
}

void Report::_printf_inf(const std::wstring& ws) {
  ::MessageBox(nppData._nppHandle, ws.c_str(), L"XML Tools plugin", MB_OK | MB_ICONINFORMATION);
}

void Report::_printf_inf(const std::string& s) {
  ::MessageBox(nppData._nppHandle, Report::widen(s).c_str(), L"XML Tools plugin", MB_OK | MB_ICONINFORMATION);
}

void Report::_fprintf_inf(void * ctx, const wchar_t* s, ...) {
  if (!s || !wcslen(s)) return;
  
  va_list msg;
  wchar_t buffer[MAX_BUFFER] = { '\0' };
  
  va_start(msg, s);
  _vsntprintf(buffer, MAX_BUFFER - 1, s, msg);
  va_end(msg);
  
  if (wcslen(buffer) <= 0) return;
  
  ::MessageBox(nppData._nppHandle, buffer, L"XML Tools plugin", MB_OK | MB_ICONINFORMATION);
}

std::wstring Report::str_format(const wchar_t* s, ...) {
  if (!s || !wcslen(s)) return L"";

  va_list msg;
  wchar_t buffer[MAX_BUFFER] = { '\0' };

  va_start(msg, s);
  _vsntprintf(buffer, MAX_BUFFER - 1, s, msg);
  va_end(msg);

  if (wcslen(buffer) <= 0) return L"";

  return std::wstring(buffer);
}

std::string Report::str_format(const char* s, ...) {
  if (!s || !strlen(s)) return "";
  
  int buffersize = 2*strlen(s);
  char * buffer = (char*) malloc(buffersize*sizeof(char));
  memset(buffer, '\0', buffersize);

  va_list msg;
  va_start(msg, s);
  //vsnprintf(buffer + strlen(buffer), s, msg);
  _vsnprintf(buffer, MAX_BUFFER - 1, s, msg);
  va_end(msg);

  if (strlen(buffer) <= 0) return "";

  return std::string(buffer);
}

CString Report::cstring(const wchar_t* s, ...) {
  if (!s || !wcslen(s)) return "";

  va_list msg;
  wchar_t buffer[MAX_BUFFER] = { '\0' };

  va_start(msg, s);
  _vsntprintf(buffer, MAX_BUFFER - 1, s, msg);
  va_end(msg);

  if (wcslen(buffer) <= 0) return "";

  return CString(buffer);
}

void Report::clearLog() {
  currentLog.clear();
}

std::wstring Report::getLog() {
  return currentLog;
}

void Report::registerError(const char* s) {
  currentLog += L"ERROR: ";
  currentLog += Report::widen(s).c_str();
  currentLog = currentLog.substr(0, currentLog.length()-1);
  currentLog += L"\r\n";
}

void Report::registerError(void * ctx, const char* s, ...) {
  if (!s || !strlen(s)) return;
  
  va_list args;
  va_start(args, s);
  char *buffer = va_arg(args,char*);
  va_end(args);
  
  if (strlen(buffer) <= 0) return;
  
  Report::registerError(buffer);
}

void Report::registerWarn(const char* s) {
  currentLog += L"WARN: ";
  currentLog += Report::widen(s).c_str();
  currentLog = currentLog.substr(0, currentLog.length()-1);
  currentLog += L"\r\n";
}

void Report::registerWarn(void * ctx, const char* s, ...) {
  if (!s || !strlen(s)) return;
  
  va_list args;
  va_start(args, s);
  char *buffer = va_arg(args,char*);
  va_end(args);
  
  if (strlen(buffer) <= 0) return;
  
  Report::registerWarn(buffer);
}

void Report::registerMessage(const char* s) {
  currentLog += Report::widen(s).c_str();
  currentLog = currentLog.substr(0, currentLog.length()-1);
  currentLog += L"\r\n";
}
void Report::registerMessage(void * ctx, const char* s, ...) {
  if (!s || !strlen(s)) return;
  
  va_list args;
  va_start(args, s);
  char *buffer = va_arg(args,char*);
  va_end(args);
  
  Report::registerMessage(buffer);
}

void Report::strcpy(char* dest, const wchar_t* src) {
  std::wstring s = std::wstring(src);
  std::copy(s.c_str(), s.c_str()+s.length()+1, dest);
}

void Report::strcpy(char* dest, std::wstring src) {
  //strcpy(params[nbparams], key.c_str());
	std::copy(src.c_str(), src.c_str()+src.length()+1, dest);
}

void Report::strcpy(wchar_t* dest, std::wstring src) {
    //strcpy(params[nbparams], key.c_str());
  wcscpy(dest, src.c_str());
}

std::string Report::narrow(const std::wstring& ws) {
  std::string res(ws.length(), ' '); // Make room for characters
  std::copy(ws.begin(), ws.end(), res.begin());

  return res;
}

std::wstring Report::widen(const char* s) {
  int len = strlen(s);
  std::wstring res(len, L' '); // Make room for characters
  std::copy(s, s+len, res.begin());
  return res;
}

std::wstring Report::widen(const xmlChar* s) {
  int len = _mbslen(s);
  std::wstring res(len, L' '); // Make room for characters
  std::copy(s, s+len, res.begin());
  return res;
}

std::wstring Report::widen(const std::string& s) {
  std::wstring res(s.length(), L' '); // Make room for characters
  std::copy(s.begin(), s.end(), res.begin());
  return res;
}

// TODO: Optimiser les fonctions suivantes
std::string Report::trimleft(const std::string& s) {
  if (s.empty()) return s;
  int i = 0, l = s.length();
  while (i < l && isspace(s.at(i))) ++i;
  if (i >= l) return "";
  else return s.substr(i);
}

std::string Report::trimright(const std::string& s) {
  if (s.empty()) return s;
  int i = s.length()-1;
  while (i >= 0 && isspace(s.at(i))) --i;
  if (i < 0) return "";
  else return s.substr(0, i+1);
}

std::string Report::trim(const std::string& s) {
   return Report::trimleft(Report::trimright(s));
}

// TODO: Optimiser les fonctions suivantes
std::wstring Report::wtrimleft(const std::wstring& s) {
  if (s.empty()) return s;
  int i = 0, l = s.length();
  while (i < l && isspace(s.at(i))) ++i;
  if (i >= l) return L"";
  else return s.substr(i);
}

std::wstring Report::wtrimright(const std::wstring& s) {
  if (s.empty()) return s;
  int i = s.length()-1;
  while (i >= 0 && isspace(s.at(i))) --i;
  if (i < 0) return L"";
  else return s.substr(0, i+1);
}

std::wstring Report::wtrim(const std::wstring& s) {
  return Report::wtrimleft(Report::wtrimright(s));
}