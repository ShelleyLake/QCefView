#ifndef QCEFVIEWBROWSERAPP_H_
#define QCEFVIEWBROWSERAPP_H_
#pragma once
#include <set>
#include <include/cef_app.h>

class CefViewBrowserApp : public CefApp, public CefBrowserProcessHandler {
public:
  CefViewBrowserApp();
  ~CefViewBrowserApp();

private:
#pragma region CefApp

  //////////////////////////////////////////////////////////////////////////
  // CefApp methods:
  virtual void OnBeforeCommandLineProcessing(const CefString &process_type,
                                             CefRefPtr<CefCommandLine> command_line) override;

  virtual void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) override;

  virtual CefRefPtr<CefResourceBundleHandler> GetResourceBundleHandler() override;

  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

  virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;

#pragma endregion CefApp

#pragma region CefBrowserProcessHandler

  // CefBrowserProcessHandler methods:
  virtual void OnContextInitialized() override;

  virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) override;

  virtual void OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info) override;

  virtual CefRefPtr<CefPrintHandler> GetPrintHandler() override;

  virtual void OnScheduleMessagePumpWork(int64 delay_ms) override;

#pragma endregion CefBrowserProcessHandler

private:
  std::vector<CefString> cookieable_schemes_;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(CefViewBrowserApp);
};

#endif //  QCEFVIEWBROWSERAPP_H_
