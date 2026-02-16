#include <cellstatus.h>
#include <sys/prx.h>
#include <libpsutil.h>
#include "deps/syscalls.h"

SYS_MODULE_INFO(ps3_mc_modloader_legacy, 0, 1, 1);
SYS_MODULE_START(_ps3_mc_modloader_legacy_prx_entry);

SYS_LIB_DECLARE_WITH_STUB(LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME);
SYS_LIB_EXPORT(_ps3_mc_modloader_legacy_export_function, LIBNAME);

extern "C" int _ps3_mc_modloader_legacy_export_function(void)
{
    return CELL_OK;
}

extern "C" int _ps3_mc_modloader_legacy_prx_entry(void)
{
    return SYS_PRX_RESIDENT;
}
