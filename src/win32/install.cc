#include "../../include/fx/install.h"

#include <windows.h>

extern "C" int
fx_install (void) {
  STARTUPINFO startup_info;

  ZeroMemory(&startup_info, sizeof(startup_info));

  startup_info.cb = sizeof(startup_info);

  PROCESS_INFORMATION process_info;

  ZeroMemory(&process_info, sizeof(process_info));

  BOOL success;

  success = CreateProcess(
    "Microsoft.WindowsAppRuntime.Install.exe",
    NULL,
    NULL,
    NULL,
    FALSE,
    CREATE_NO_WINDOW,
    NULL,
    NULL,
    &startup_info,
    &process_info
  );

  if (!success) return -1;

  WaitForSingleObject(process_info.hProcess, 30 * 1000);

  DWORD status;

  success = GetExitCodeProcess(process_info.hProcess, &status);

  if (!success) return -1;

  return status;
}
