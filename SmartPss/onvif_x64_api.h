#ifndef ONVIF_API_X64
#define ONVIF_API_X64
#include "onvif.h"

#define ONVIF_API  extern "C" __declspec(dllexport)

 ONVIF_API int __stdcall ONVIF_Init(ONVIF_DEVICE * pDev);
 ONVIF_API int __stdcall ONVIF_DeviceSearch(onvif_probe_cb pSearchCallback,void* pContext);
 ONVIF_API int __stdcall ONVIF_SendProbe();
 ONVIF_API int __stdcall ONVIF_StopSearch();
 ONVIF_API int __stdcall ONVIF_GetDevInfo(ONVIF_DEVICE * pDev,GetCmd nGetCommand);
 ONVIF_API int __stdcall ONVIF_SetDevInfo(ONVIF_DEVICE * pDev,SetCmd nSetCommand);
 ONVIF_API int __stdcall ONVIF_EventCmd(ONVIF_DEVICE * pDev,EventCmd nEventCommand,onvif_event_notify_cb pEventCallback=NULL,void* pContext=NULL);
 ONVIF_API int __stdcall ONVIF_PTZCmd(ONVIF_DEVICE * pDev,PTZCmd nPtzCommand,int nSpeed = 50,char* name = NULL);
 ONVIF_API int __stdcall ONVIF_Clear(ONVIF_DEVICE * pDev);
#endif
