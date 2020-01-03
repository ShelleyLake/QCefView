#pragma once
#include "CefViewBrowserApp/CefViewBrowserHandler.h"
#include "Include/QCefEvent.h"
#include "Include/QCefQuery.h"
#include "Include/QCefView.h"
#include "UIEventHandlerWin.h"
#include <QString>
#include <QWidget>

class QCefView;
class QCefViewImplement {
public:
  explicit QCefViewImplement(QCefView *pCefView);
  ~QCefViewImplement();

public:
  void navigateToUrl(const QString &url);
  bool browserCanGoBack();
  bool browserCanGoForward();
  void browserGoBack();
  void browserGoForward();
  bool browserIsLoading();
  void browserReload();
  void browserStopLoad();
  bool triggerEvent(const QString &name, const QCefEvent &event,
                    int frameId = CefViewBrowserHandler::MAIN_FRAME);
  bool responseQCefQuery(const QCefQuery &query);

  void createBrowser();
  void closeAllBrowsers();

  void browserCreatedNotify(CefRefPtr<CefBrowser> browser);

  void OnImeCompositionRangeChanged(CefRefPtr<CefBrowser> browser, const CefRange &selection_range,
                                    const CefRenderHandler::RectList &character_bounds);

  QCefView *getCefView();
  bool nativeEvent(const QByteArray &eventType, void *message, long *result);
  void paintEvent(QPaintEvent *event);
  float deviceScaleFactor();
  void setFPS(int fps);
  int fps() const;

  void updateView();

protected:
  bool sendEventNotifyMessage(int frameId, const QString &name, const QCefEvent &event);
  CefRefPtr<CefBrowserHost> getCefBrowserHost();

private:
  QCefView *pCefView_;
  CefRefPtr<CefViewBrowserHandler> pQCefViewHandler_;
  std::shared_ptr<UIEventHandlerWin> pCefUIEventWin_;

  // Cached url will be navigated
  CefString cachedNavigateUrl_;

  std::atomic<float> deviceScaleFactor_;
  HWND hwnd_;
  bool browserCreated_;

  int fps_;
};