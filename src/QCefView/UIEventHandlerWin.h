#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#include <include/cef_client.h>
#include <windowsx.h>
#include "CefViewBrowserApp/CefViewBrowserHandler.h"
#include "IMEHandlerWin.h"

class UIEventHandlerWin {
public:
  UIEventHandlerWin(HWND h, float deviceScaleFactor, CefRefPtr<CefBrowser> pCefBrowser);
  ~UIEventHandlerWin();

  void OnSize(UINT message, WPARAM wParam, LPARAM lParam);
  void OnKeyboardEvent(UINT message, WPARAM wParam, LPARAM lParam);
  void OnMouseEvent(UINT message, WPARAM wParam, LPARAM lParam);
  void OnTouchEvent(UINT message, WPARAM wParam, LPARAM lParam);
  void OnFocusEvent(UINT message, WPARAM wParam, LPARAM lParam);
  void OnIMEEvent(UINT message, WPARAM wParam, LPARAM lParam);

  void OnImeCompositionRangeChanged(CefRefPtr<CefBrowser> browser, const CefRange &selection_range,
                                    const CefRenderHandler::RectList &character_bounds);

private:
  bool IsKeyDown(WPARAM wParam);
  int GetCefMouseModifiers(WPARAM wParam);
  int GetCefKeyboardModifiers(WPARAM wParam, LPARAM lParam);
  void OnIMEComposition(UINT message, WPARAM wParam, LPARAM lParam);
  void OnIMECancelCompositionEvent();

  CefRefPtr<CefBrowserHost> GetBrowserHost();

private:
  HWND hwnd_;
  CefRefPtr<CefBrowser> pCefBrowser_;
  float deviceScaleFactor_;

  // Mouse state tracking.
  POINT last_mouse_pos_;
  POINT current_mouse_pos_;
  bool mouse_rotation_;
  bool mouse_tracking_;
  int last_click_x_;
  int last_click_y_;
  CefBrowserHost::MouseButtonType last_click_button_;
  int last_click_count_;
  double last_click_time_;
  bool last_mouse_down_on_view_;

  std::unique_ptr<IMEHandlerWin> ime_handler_;
};

#endif