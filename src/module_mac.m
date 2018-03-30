#include <node_api.h>
#include <cocoa/Cocoa.h>

napi_value desktopish(napi_env env, napi_callback_info info);

napi_value initialize_lib(napi_env env, napi_value exports) {
    napi_status status;
    napi_value fn;

    status = napi_create_function(env, NULL, 0, desktopish, NULL, &fn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Unable to wrap native function");
    }

    status = napi_set_named_property(env, exports, "desktopish", fn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Unable to populate exports");
    }

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, initialize_lib);

napi_value desktopish(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

    NSWindow *windowPtr;
    size_t len;
    status = napi_get_buffer_info(env, argv[0], (void **)&windowPtr, &len);

    [windowPtr setLevel:kCGDesktopIconWindowLevelKey];

    napi_value result;
    status = napi_get_boolean(env, true, &result);

    return result;
}
