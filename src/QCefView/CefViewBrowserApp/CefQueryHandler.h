#pragma once
#include <map>
#include <mutex>
#include <include/cef_base.h>
#include <include/wrapper/cef_stream_resource_handler.h>
#include <include/wrapper/cef_message_router.h>

class QCefViewImplement;

class CefQueryHandler : public CefBaseRefCounted, public CefMessageRouterBrowserSide::Handler {
public:
  CefQueryHandler(QCefViewImplement *pCefViewImpl);
  ~CefQueryHandler();

  virtual bool OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id,
                       const CefString &request, bool persistent,
                       CefRefPtr<Callback> callback) override;

  virtual void OnQueryCanceled(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                               int64 query_id) override;

  bool Response(int64_t query, bool success, const CefString &response, int error);

private:
  QCefViewImplement *pCefViewImpl_;
  std::map<int64, CefRefPtr<Callback>> mapCallback_;
  std::mutex mtxCallbackMap_;

private:
  IMPLEMENT_REFCOUNTING(CefQueryHandler);
};
