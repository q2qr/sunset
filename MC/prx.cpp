#include <cellstatus.h>
#include <sys/prx.h>
#include <libpsutil.h>
#include <sysutil/sysutil_msgdialog.h>

#include "sunset_loader/include/ModLoader.h"

SYS_MODULE_INFO(sunset_loader, 0, 1, 0);
SYS_MODULE_START(_sunset_loader_prx_entry);
SYS_MODULE_STOP(_sunset_loader_prx_stop);

SYS_LIB_DECLARE_WITH_STUB(LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME);
SYS_LIB_EXPORT(_sunset_loader_export, LIBNAME);

extern "C" int _sunset_loader_export(void)
{
    return CELL_OK;
}

static bool g_startupProgressOpen = false;
static int g_startupProgressValue = 0;

static void StartupProgressOpen(void)
{
    if (g_startupProgressOpen) {
        return;
    }

    unsigned int type = CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL |
                        CELL_MSGDIALOG_TYPE_BUTTON_TYPE_NONE |
                        CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON |
                        CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_NONE |
                        CELL_MSGDIALOG_TYPE_PROGRESSBAR_SINGLE;

    int rc = cellMsgDialogOpen2(type, "Sunset\nMod Loader Startup", 0, 0, 0);
    if (rc != CELL_OK) {
        return;
    }

    g_startupProgressOpen = true;
    g_startupProgressValue = 0;
}

static void StartupProgressStep(const char* phase, int targetPercent)
{
    if (!g_startupProgressOpen) {
        return;
    }

    if (phase && phase[0]) {
        cellMsgDialogProgressBarSetMsg(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, phase);
    }

    if (targetPercent < g_startupProgressValue) {
        targetPercent = g_startupProgressValue;
    }
    if (targetPercent > 100) {
        targetPercent = 100;
    }

    int delta = targetPercent - g_startupProgressValue;
    if (delta > 0) {
        cellMsgDialogProgressBarInc(CELL_MSGDIALOG_PROGRESSBAR_INDEX_SINGLE, (uint32_t)delta);
        g_startupProgressValue = targetPercent;
    }
}

static void StartupProgressClose(void)
{
    if (!g_startupProgressOpen) {
        return;
    }

    StartupProgressStep("Startup complete", 100);
    cellMsgDialogClose(500);
    g_startupProgressOpen = false;
    g_startupProgressValue = 0;
}

extern "C" int _sunset_loader_prx_entry(void)
{
    StartupProgressOpen();
    StartupProgressStep("Initializing Sunset...", 50);

    ModLoader_Init();

    StartupProgressClose();
    return SYS_PRX_RESIDENT;
}

extern "C" int _sunset_loader_prx_stop(void)
{
    ModLoader_Shutdown();
    return SYS_PRX_STOP_OK;
}