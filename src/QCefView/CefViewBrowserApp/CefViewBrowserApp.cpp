#include "CefViewBrowserApp.h"
#include "CefGlobalSetting.h"
#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#include <include/wrapper/cef_helpers.h>
#include <string>

CefViewBrowserApp::CefViewBrowserApp() {}

CefViewBrowserApp::~CefViewBrowserApp() {
  LOG(INFO) << "Exit Trace: ~CefViewBrowserApp enter";
  LOG(INFO) << "Exit Trace: ~CefViewBrowserApp leave";
}

void CefViewBrowserApp::OnBeforeCommandLineProcessing(const CefString &process_type,
                                                      CefRefPtr<CefCommandLine> command_line) {
  // Chromium has removed --disable-surfaces as per
  // https://codereview.chromium.org/1603133003 so the workaround specified
  // here is no longer applicable
  // command_line->AppendSwitch("disable-surfaces");

  command_line->AppendSwitch("no-proxy-server");
  command_line->AppendSwitch("disable-extensions");
  command_line->AppendSwitch("allow-file-access-from-files");
  command_line->AppendSwitchWithValue("disable-features", "NetworkService");

  if (CefGlobalSetting::enable_gpu) {
    // command_line->AppendSwitch("in-process-gpu");
  }
  else {
    // D3D11ģʽ���ܽ���GPU���٣�2623�汾����ʹ��D3D11ģʽ
    // command_line->AppendSwitch("disable-gpu");
    // command_line->AppendSwitch("disable-gpu-compositing");
  }
}

void CefViewBrowserApp::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) {}

CefRefPtr<CefResourceBundleHandler> CefViewBrowserApp::GetResourceBundleHandler() {
  return nullptr;
}

CefRefPtr<CefBrowserProcessHandler> CefViewBrowserApp::GetBrowserProcessHandler() { return this; }

CefRefPtr<CefRenderProcessHandler> CefViewBrowserApp::GetRenderProcessHandler() { return nullptr; }

//////////////////////////////////////////////////////////////////////////
void CefViewBrowserApp::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();

  // Register cookieable schemes with the global cookie manager.
  CefRefPtr<CefCookieManager> manager = CefCookieManager::GetGlobalManager(nullptr);
  DCHECK(manager.get());
  manager->SetSupportedSchemes(cookieable_schemes_, true, nullptr);
}

void CefViewBrowserApp::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) {}

void CefViewBrowserApp::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info) {
  CEF_REQUIRE_IO_THREAD();
}

CefRefPtr<CefPrintHandler> CefViewBrowserApp::GetPrintHandler() { return nullptr; }

void CefViewBrowserApp::OnScheduleMessagePumpWork(int64 delay_ms) {}