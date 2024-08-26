/*  Havok Tool for 3ds Max
    Copyright(C) 2019-2020 Lukas Cone

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.

    Havok Tool uses HavokLib 2016-2020 Lukas Cone
*/

#include "HavokMax.h"
#include "datas/master_printer.hpp"
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#include <gdiplus.h>

#if VERSION_3DSMAX_B == VERSION_3DSMAX_E(2010)
#include <maxscrpt/maxscrpt.h>
#else
#include <maxscript/maxscript.h>
#endif

extern ClassDesc2 *GetHavokImportDesc();
extern ClassDesc2 *GetHavokExportDesc();

HINSTANCE hInstance;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

// This function is called by Windows when the DLL is loaded.  This
// function may also be called many times during time critical operations
// like rendering.  Therefore developers need to be careful what they
// do inside this function.  In the code below, note how after the DLL is
// loaded the first time only a few statements are executed.

BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason,
                    LPVOID /*lpvReserved*/) {
  if (fdwReason == DLL_PROCESS_ATTACH) {
    hInstance = hinstDLL;
    DisableThreadLibraryCalls(hInstance);
    // DO NOT do any initialization here. Use LibInitialize() instead.
  }
  return (TRUE);
}

void PrintLog(const char *msg) {
  if (!IsWindowVisible(the_listener_window) || IsIconic(the_listener_window))
    show_listener();

  const auto cvted = ToTSTRING(msg);

  mprintf(cvted.data());
  mflush();
}

extern "C" {
// This function returns a string that describes the DLL and where the user
// could purchase the DLL if they don't have it.
__declspec(dllexport) const TCHAR *LibDescription() {
  return _T(HavokMax_DESC);
}

// This function returns the number of plug-in classes this DLL
// TODO: Must change this number when adding a new class
__declspec(dllexport) int LibNumberClasses() { return 2; }

// This function returns the number of plug-in classes this DLL
__declspec(dllexport) ClassDesc *LibClassDesc(int i) {
  switch (i) {
  case 0:
    return GetHavokImportDesc();
  case 1:
    return GetHavokExportDesc();
  default:
    return 0;
  }
}

// This function returns a pre-defined constant indicating the version of
// the system under which it was compiled.  It is used to allow the system
// to catch obsolete DLLs.
__declspec(dllexport) ULONG LibVersion() { return VERSION_3DSMAX; }

// This function is called once, right after your plugin has been loaded by 3ds
// Max. Perform one-time plugin initialization in this method. Return TRUE if
// you deem your plugin successfully loaded, or FALSE otherwise. If the function
// returns FALSE, the system will NOT load the plugin, it will then call
// FreeLibrary on your DLL, and send you a message.
__declspec(dllexport) int LibInitialize(void) {
  printer.AddPrinterFunction(PrintLog);
  Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
  BuildHavokResources();
  return TRUE;
}

// This function is called once, just before the plugin is unloaded.
// Perform one-time plugin un-initialization in this method."
// The system doesn't pay attention to a return value.
__declspec(dllexport) int LibShutdown(void) {
  Gdiplus::GdiplusShutdown(gdiplusToken);
  DestroyHavokResources();
  return TRUE;
}
}
