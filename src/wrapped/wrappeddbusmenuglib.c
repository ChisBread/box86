#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "wrappedlibs.h"

#include "debug.h"
#include "wrapper.h"
#include "bridge.h"
#include "librarian/library_private.h"
#include "x86emu.h"
#include "emu/x86emu_private.h"
#include "callback.h"
#include "librarian.h"
#include "box86context.h"
#include "emu/x86emu_private.h"
#include "callback.h"

const char* dbusmenuglibName = "libdbusmenu-glib.so.4";
#define LIBNAME dbusmenuglib

#define ADDED_FUNCTIONS()                           \

#include "generated/wrappeddbusmenuglibtypes.h"

#include "wrappercallback.h"

#define SUPER() \
GO(0)   \
GO(1)   \
GO(2)   \
GO(3)

// DbusmenuClientTypeHandler
#define GO(A)   \
static uintptr_t my_DbusmenuClientTypeHandler_fct_##A = 0;                                  \
static int my_DbusmenuClientTypeHandler_##A(void* a, void* b, void* c, void* d)             \
{                                                                                           \
    return RunFunction(my_context, my_DbusmenuClientTypeHandler_fct_##A, 4, a, b, c, d);    \
}
SUPER()
#undef GO
static void* findDbusmenuClientTypeHandlerFct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my_DbusmenuClientTypeHandler_fct_##A == (uintptr_t)fct) return my_DbusmenuClientTypeHandler_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my_DbusmenuClientTypeHandler_fct_##A == 0) {my_DbusmenuClientTypeHandler_fct_##A = (uintptr_t)fct; return my_DbusmenuClientTypeHandler_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for dbusmenuglib DbusmenuClientTypeHandler callback\n");
    return NULL;
}

// DbusmenuMenuitem
#define GO(A)   \
static uintptr_t my_DbusmenuMenuitem_fct_##A = 0;                   \
static void my_DbusmenuMenuitem_##A(void* a, void* b)               \
{                                                                   \
    RunFunction(my_context, my_DbusmenuMenuitem_fct_##A, 2, a, b);  \
}
SUPER()
#undef GO
static void* findDbusmenuMenuitemFct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my_DbusmenuMenuitem_fct_##A == (uintptr_t)fct) return my_DbusmenuMenuitem_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my_DbusmenuMenuitem_fct_##A == 0) {my_DbusmenuMenuitem_fct_##A = (uintptr_t)fct; return my_DbusmenuMenuitem_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for dbusmenuglib DbusmenuMenuitem callback\n");
    return NULL;
}

#undef SUPER

EXPORT int my_dbusmenu_client_add_type_handler(x86emu_t* emu, void* client, void* type, void* f)
{
    return my->dbusmenu_client_add_type_handler(client, type, findDbusmenuClientTypeHandlerFct(f));
}

EXPORT void my_dbusmenu_menuitem_foreach(x86emu_t* emu, void* mi, void* f, void* data)
{
    my->dbusmenu_menuitem_foreach(mi, findDbusmenuMenuitemFct(f), data);
}

EXPORT void my_dbusmenu_menuitem_send_about_to_show(x86emu_t* emu, void* mi, void* f, void* data)
{
    my->dbusmenu_menuitem_send_about_to_show(mi, findDbusmenuMenuitemFct(f), data);
}

#define PRE_INIT    \
    if(box86_nogtk) \
        return -1;

#define CUSTOM_INIT \
    getMy(lib);     \

#define CUSTOM_FINI \
    freeMy();

#include "wrappedlib_init.h"

