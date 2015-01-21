#ifndef RTSP_CLIENT_X64
#define RTSP_CLIENT_X64

typedef enum RTSPCMD
{
	PLAY = 0,
	PAUSE,
	STOP
};

typedef enum LinkType
{
	RTSPOVERTCP = 0,
	RTSPOVERUDP,
	RTSPOVERHTTP
};
typedef int (*video_cb)(char*, int, unsigned int, unsigned short, void *);
typedef int (*audio_cb)(char*, int, void *);
#define RTSPAPI extern "C" __declspec(dllexport)
RTSPAPI int __stdcall  RtspInit(video_cb pVideoCallback, audio_cb pAudioCallback,void** pRtsp,void* pContext);
RTSPAPI int __stdcall  RtspStart(void* pRtsp,char* url,char* Username,char* Password,LinkType nLinktype);
RTSPAPI int __stdcall  RtspCmd(void* pRtsp,RTSPCMD nRtspCmd);
RTSPAPI int __stdcall  RtspClear(void* pRtsp);
#endif
