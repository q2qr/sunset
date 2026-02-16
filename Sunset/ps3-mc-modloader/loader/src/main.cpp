#include <cellstatus.h>
#include <sys/prx.h>
#include <libpsutil.h>

#include "../../framework/include/ModLoader.h"
#include "../include/EBOOTHook.h"
#include "../include/TickHook.h"

SYS_MODULE_INFO(ps3_mc_modloader_loader, 0, 1, 0);
SYS_MODULE_START(_ps3_mc_modloader_loader_prx_entry);
SYS_MODULE_STOP(_ps3_mc_modloader_loader_prx_stop);

SYS_LIB_DECLARE_WITH_STUB(LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME);
SYS_LIB_EXPORT(_ps3_mc_modloader_loader_export, LIBNAME);

extern "C" int _ps3_mc_modloader_loader_export(void)
{
    return CELL_OK;
}

extern "C" int _ps3_mc_modloader_loader_prx_entry(void)
{
    ModLoader_Init();
    EBOOTHook_Install();
    TickHook_Install(ModLoader_Tick);
    return SYS_PRX_RESIDENT;
}

extern "C" int _ps3_mc_modloader_loader_prx_stop(void)
{
    TickHook_Remove();
    EBOOTHook_Remove();
    ModLoader_Shutdown();
    return SYS_PRX_STOP_OK;
}
