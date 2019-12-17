#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <tchar.h>
#include <windows.h>
#endif

#include <include/cef_app.h>
#include "CefViewRenderApp/QCefViewRenderApp.h"
#include "QCefWing.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CefEnableHighDPISupport();

    CefRefPtr<QCefViewRenderApp> app(new QCefViewRenderApp);
    CefMainArgs main_args(hInstance);
    void* sandboxInfo = nullptr;
    return CefExecuteProcess(main_args, app, sandboxInfo);
}
#else  // _WIN32
int main(int argc, char* argv[]) {
    CefEnableHighDPISupport();

    CefRefPtr<QCefViewRenderApp> app(new QCefViewRenderApp);
    CefMainArgs main_args();
    void* sandboxInfo = nullptr;
    return CefExecuteProcess(main_args, app.get(), sandboxInfo);
}
#endif // _WIN32
