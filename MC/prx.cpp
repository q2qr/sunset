#pragma once
#pragma comment(lib, "libhttp_stub.a")
#pragma comment(lib, "libhttp_util_stub.a")
#pragma comment(lib, "libnet_stub.a")
#pragma comment(lib, "netctl_stub")
#pragma comment(lib, "libsysutil_stub.a")
#pragma comment(lib, "libc.a")
#pragma comment(lib, "libstdc++.a")
#pragma comment(lib, "libstdc++_stub.a")
#pragma comment(lib, "libsn.a")
#pragma comment(lib, "libm.a")
#pragma comment(lib, "libio_stub.a")
#pragma comment(lib, "liblv2_stub.a")
#pragma comment(lib, "libfs_stub.a")

#pragma region "includes"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cellstatus.h>
#include <sys/prx.h>
#include <cell/sysmodule.h>
#include <sys/process.h>
#include <sys/ppu_thread.h>
#include <sys/syscall.h>
#include <sys/tty.h>
#include <ppu_intrinsics.h>
#include <ctype.h>
#include <sys/timer.h>
#include <fastmath.h>
#include <cell/pad.h>
#include <sysutil\sysutil_msgdialog.h>
#include <sys\sys_time.h>
#include <time.h>
#include <cell/cell_fs.h>
#include <cell/http.h>
#include <sysutil/sysutil_oskdialog.h>
#include <sys\socket.h>
#include <netinet\in.h>
#include <arpa\inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <netex/net.h>
#include <netex/errno.h>
#include <inttypes.h>  
#include <sys/memory.h>
#include <stdarg.h>
#include <cstdlib>
#include <sys/time_util.h>
#include <assert.h>
#include <sys/return_code.h>
#include <stddef.h>
#include <math.h>
#include <typeinfo>
#include <vector>
#include <locale.h>
#include <cell/error.h>
#include <sys/paths.h>
#include <net\if_dl.h>
#include <cell/fs/cell_fs_errno.h>
#include <cell/fs/cell_fs_file_api.h>
#include <sys/fs.h>
#include <sys/ss_get_open_psid.h>
#include <netex\libnetctl.h>
#pragma comment(lib, "net_stub")
#include <cstddef>

#include "dialog.h"
#include "sunset_loader/include/ModLoader.h"

#include <sys/stat.h>
#include <sys/fs_external.h>
#include <pthread.h>
#pragma endregion


SYS_MODULE_INFO(sunset_loader, 0, 1, 0);
SYS_MODULE_START(_sunset_loader_prx_entry);
SYS_MODULE_STOP(_sunset_loader_prx_stop);

SYS_LIB_DECLARE_WITH_STUB(LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME);
SYS_LIB_EXPORT(_sunset_loader_export, LIBNAME);

extern "C" int _sunset_loader_export(void)
{
    return CELL_OK;
}


extern "C" int _sunset_loader_prx_entry(void)
{
    Dialog::msgdialog_mode = Dialog::MODE_RUNNING;
    Dialog::ProgressBar("Sunset", "Initializing Sunset...", 20);
    Dialog::End();

    ModLoader_Init();

    return SYS_PRX_RESIDENT;
}

extern "C" int _sunset_loader_prx_stop(void)
{
    ModLoader_Shutdown();
    return SYS_PRX_STOP_OK;
}