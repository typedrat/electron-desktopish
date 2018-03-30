#include <node_api.h>
#include <Windows.h>

napi_value desktopish(napi_env env, napi_callback_info info);

napi_value initialize_lib(napi_env env, napi_value exports)
{
    napi_status status;
    napi_value fn;

    status = napi_create_function(env, NULL, 0, desktopish, NULL, &fn);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Unable to wrap native function");
    }

    status = napi_set_named_property(env, exports, "desktopish", fn);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Unable to populate exports");
    }

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, initialize_lib);

LONG_PTR oldWndProc;

LRESULT CALLBACK DesktopishWndProc(HWND hwnd, UINT wm, WPARAM wParam, LPARAM lParam)
{
    if (wm == WM_WINDOWPOSCHANGING)
    {
        WINDOWPOS *pos = (WINDOWPOS *)lParam;
        pos->flags |= SWP_NOZORDER;
    }
    
    return CallWindowProc(oldWndProc, hwnd, wm, wParam, lParam);
}

napi_value desktopish(napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

    HWND hwnd;
    size_t len;
    status = napi_get_buffer_info(env, argv[0], (void **)&hwnd, &len);

    oldWndProc = SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)DesktopishWndProc);

    napi_value result;
    status = napi_get_boolean(env, true, &result);

    return result;
}
