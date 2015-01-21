/***************************************************************************************
 *
 *  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
 *
 *  By downloading, copying, installing or using the software you agree to this license.
 *  If you do not agree to this license, do not download, install, 
 *  copy or use the software.
 *
 *  Copyright (C) 2010-2014, Happytimesoft Corporation, all rights reserved.
 *
 *  Redistribution and use in binary forms, with or without modification, are permitted.
 *
 *  Unless required by applicable law or agreed to in writing, software distributed 
 *  under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 *  CONDITIONS OF ANY KIND, either express or implied. See the License for the specific
 *  language governing permissions and limitations under the License.
 *
****************************************************************************************/

#ifndef _ONVIF_DEVICE_H_
#define _ONVIF_DEVICE_H_

/***************************************************************************************/
#define ONVIF_TOKEN_LEN   	100
#define ONVIF_NAME_LEN    	100
#define ONVIF_URI_LEN     	512


#define MAX_PTZ_PRESETS     100 
#define MAX_DNS_SERVER		2
#define MAX_SEARCHDOMAIN	4
#define MAX_NTP_SERVER		2
#define MAX_SERVER_PORT		4
#define MAX_GATEWAY			2
#define MAX_RES_NUMS		8
#define MAX_SCOPE_NUMS		100


// device type
#define ODT_UNKNOWN     	0
#define ODT_NVT         	1
#define ODT_NVD         	2
#define ODT_NVS         	3
#define ODT_NVA         	4

// device flag
#define FLAG_MANUAL			(1 << 0)	/* manual added device, other auto discovery devices */


/***************************************************************************************/
typedef enum 
{   
    VIDEO_ENCODING_JPEG = 0, 
    VIDEO_ENCODING_MPEG4 = 1, 
    VIDEO_ENCODING_H264 = 2
} E_VIDEO_ENCODING;

typedef enum 
{   
    AUDIO_ENCODING_G711 = 0,
    AUDIO_ENCODING_G726,
    AUDIO_ENCODING_AAC
} E_AUDIO_ENCODING;

typedef enum 
{
    H264_PROFILE_Baseline = 0, 
    H264_PROFILE_Main = 1, 
    H264_PROFILE_Extended = 2, 
    H264_PROFILE_High = 3
} E_H264_PROFILE;

typedef enum 
{
    MPEG4_PROFILE_SP = 0, 
    MPEG4_PROFILE_ASP = 1
} E_MPEG4_PROFILE;

typedef enum 
{
	CAP_CATEGORY_INVALID = -1,
	CAP_CATEGORY_MEDIA,
	CAP_CATEGORY_DEVICE,
	CAP_CATEGORY_ANALYTICS,
	CAP_CATEGORY_EVENTS,
	CAP_CATEGORY_IMAGE,
	CAP_CATEGORY_PTZ,
	CAP_CATEGORY_ALL
} E_CAP_CATEGORY;

typedef enum
{
	PTZ_STA_IDLE,
	PTZ_STA_MOVING,
	PTZ_STA_UNKNOWN
} E_PTZ_STATUS;


/***************************************************************************************/
typedef struct
{
    int     port;           // onvif port
    char    host[24];       // ip of xaddrs
    char    url[128];       // /onvif/device_service
} ONVIF_XADDR;

typedef struct
{
    unsigned int	ip;             // msg recv from
    int		type;           // device type
    
    ONVIF_XADDR xaddr;
} DEVICE_BINFO;

typedef struct
{
    char 	Manufacturer[32];
    char 	Model[32];
    char 	FirmwareVersion[32];
    char 	SerialNumber[32];
    char 	HardwareId[32];
} DEVICE_INFO;

/***************************************************************************************
 *
 * ONVIF capabilities structure
 *
****************************************************************************************/
typedef struct
{
    short  year;
    short  month;
    short  day;
    short  hour;
    short  minute;
    short  second;
} DATETIME;

typedef struct
{
	// network capabilities
    unsigned int	IPFilter 			: 1;
    unsigned int	ZeroConfiguration 	: 1;
    unsigned int	IPVersion6			: 1;
    unsigned int 	DynDNS 				: 1;

	// system capabilities
    unsigned int 	DiscoveryResolve 	: 1;
    unsigned int 	DiscoveryBye 		: 1;
    unsigned int 	RemoteDiscovery 	: 1;
    unsigned int 	SystemBackup 		: 1;
    unsigned int 	SystemLogging 		: 1;
    unsigned int 	FirmwareUpgrade 	: 1;

    unsigned int	reserved			: 22;
	
    ONVIF_XADDR xaddr;
} DEVICE_CAP;

typedef struct
{
    unsigned int	RTPMulticast 		: 1;
    unsigned int	RTP_TCP				: 1;
    unsigned int	RTP_RTSP_TCP		: 1;
    unsigned int  support				: 1;

    unsigned int	reserved			: 28;
	
    ONVIF_XADDR xaddr;
} MEDIA_CAP;

typedef struct
{
    unsigned int  support				: 1;
    unsigned int	reserved 			: 31;
	
    ONVIF_XADDR xaddr;
} PTZ_CAP;

typedef struct
{
    unsigned int	WSSubscriptionPolicySupport	: 1;
    unsigned int	WSPullPointSupport 	: 1;
    unsigned int	WSPausableSubscriptionManagerInterfaceSupport : 1;
    unsigned int  support				: 1;

    unsigned int	reserved 			: 28;
	
    ONVIF_XADDR xaddr;
} EVENT_CAP;

typedef struct
{
    unsigned int  support				: 1;
    unsigned int	reserved 			: 31;
	
    ONVIF_XADDR xaddr;
} IMAGE_CAP;

typedef struct
{
	DEVICE_CAP	device;
    MEDIA_CAP	media;
    PTZ_CAP		ptz;
	EVENT_CAP	events;
	IMAGE_CAP	image;
} ONVIF_CAP;

/***************************************************************************************/
typedef struct
{
	int w;
	int h;
} RESOLUTION;

typedef struct
{
	int frame_rate_min;
	int frame_rate_max;
	int encoding_interval_min;
	int encoding_interval_max;

	RESOLUTION	resolution[MAX_RES_NUMS];
} JPEG_CFG_OPT;

typedef struct
{
	int sp_profile 	: 1;
	int asp_profile : 1;
	int reserverd	: 30;
	
	int gov_length_min;
	int gov_length_max;
	int frame_rate_min;
	int frame_rate_max;
	int encoding_interval_min;
	int encoding_interval_max;

	RESOLUTION	resolution[MAX_RES_NUMS];
} MPEG4_CFG_OPT;

typedef struct
{
	int baseline_profile	: 1;
	int main_profile 		: 1;
	int extended_profile 	: 1;
	int high_profile 		: 1;
	int reserverd			: 28;
	
	int gov_length_min;
	int gov_length_max;
	int frame_rate_min;
	int frame_rate_max;
	int encoding_interval_min;
	int encoding_interval_max;

	RESOLUTION	resolution[MAX_RES_NUMS];	
} H264_CFG_OPT;

typedef struct 
{
	JPEG_CFG_OPT 	jpeg_opt;
	MPEG4_CFG_OPT	mpeg4_opt;
	H264_CFG_OPT	h264_opt;
	
	int				quality_min;
	int				quality_max;
} VIDEO_ENC_CFG;

typedef struct
{
	char	ip[32];
	int 	port;
	int 	ttl;
	int 	auto_start;
} MULTICAST_CFG;

typedef struct
{
	int	BacklightCompensation_Mode;	// 0-OFF, 1-ON//背光补偿
	int Brightness;					//亮度
	int ColorSaturation;			//色彩饱和度
	int Contrast;					//对比度
	int	Exposure_Mode;				// 0-AUTO, 1-MANUAL		//曝光	
	int MinExposureTime;		//曝光时间
	int MaxExposureTime;
	int MinGain;				//传感器增益范围
	int MaxGain;
	int IrCutFilter_Mode;			// 0-OFF, 1-ON, 2-AUTO//红外滤光片
	int Sharpness;					//清晰度
	int	WideDynamicRange_Mode;		// 0-OFF, 1-ON//宽动态范围
	int WideDynamicRange_Level;
	int	WhiteBalance_Mode;			// 0-AUTO, 1-MANUAL//白平衡
} IMAGE_CFG;

typedef struct
{
	unsigned int 	BacklightCompensation_ON	: 1;
	unsigned int 	BacklightCompensation_OFF	: 1;
	unsigned int    Exposure_AUTO				: 1;
	unsigned int    Exposure_MANUAL				: 1;
	unsigned int 	AutoFocus_AUTO				: 1;
	unsigned int 	AutoFocus_MANUAL			: 1;
	unsigned int 	IrCutFilter_ON				: 1;
	unsigned int 	IrCutFilter_OFF				: 1;
	unsigned int 	IrCutFilter_AUTO			: 1;
	unsigned int 	WideDynamicRange_ON			: 1;
	unsigned int 	WideDynamicRange_OFF		: 1;
	unsigned int 	WhiteBalance_AUTO			: 1;
	unsigned int 	WhiteBalance_MANUAL			: 1;
	
	unsigned int	reserved     				: 19;

	int				Brightness_min;
	int				Brightness_max;
	int				ColorSaturation_min;
	int				ColorSaturation_max;
	int				Contrast_min;
	int				Contrast_max;
	int				MinExposureTime_min;
	int				MinExposureTime_max;
	int				MaxExposureTime_min;
	int				MaxExposureTime_max;
	int				MinGain_min;
	int				MinGain_max;
	int				MaxGain_min;
	int				MaxGain_max;
	int				Sharpness_min;
	int				Sharpness_max;
	int				WideDynamicRange_Level_min;
	int				WideDynamicRange_Level_max;
} IMAGE_OPTIONS;

typedef struct _VIDEO_SRC
{
    struct _VIDEO_SRC * next;
	
    int     width;
    int     height;
    int     frame_rate;
    
    char    token[ONVIF_TOKEN_LEN];

    IMAGE_CFG img_cfg;
} VIDEO_SRC;

typedef struct _AUDIO_SRC
{
    struct _AUDIO_SRC * next;
	
    int     channels;
    
    char    token[ONVIF_TOKEN_LEN];
} AUDIO_SRC;

typedef struct _VIDEO_SRC_CFG
{
	struct _VIDEO_SRC_CFG * next;
	
    // Bounds   
    int  width;
    int  height;
    int  x;
    int  y;
    
    int  use_count;
    char token[ONVIF_TOKEN_LEN];
    char name[ONVIF_NAME_LEN];
    char source_token[ONVIF_TOKEN_LEN]; 
} VIDEO_SRC_CFG;

typedef struct _VIDEO_ENCODER
{    
	struct _VIDEO_ENCODER * next;	

	char name[ONVIF_NAME_LEN];
    char token[ONVIF_TOKEN_LEN];

	int  use_count;
	
    int  width;
    int  height;
    
	int  quality;
    int  session_timeout;
    int  framerate_limit;
	int  encoding_interval;
	int  bitrate_limit;
	
	E_VIDEO_ENCODING encoding;
	
	int  gov_len;
	int  profile;

	MULTICAST_CFG	 multicast;	
} VIDEO_ENCODER;

typedef struct _AUDIO_SRC_CFG
{    
	struct _AUDIO_SRC_CFG * next;
	
    int  use_count;
    char token[ONVIF_TOKEN_LEN];
	char name[ONVIF_NAME_LEN];
    char source_token[ONVIF_TOKEN_LEN]; 
} AUDIO_SRC_CFG;

typedef struct _AUDIO_ENCODER
{
	struct _AUDIO_ENCODER * next;
	
    int  use_count;
    int  session_timeout;
    
    char name[ONVIF_NAME_LEN];
    char token[ONVIF_TOKEN_LEN];
    
	int  sample_rate;
	int  bitrate;    
	
	E_AUDIO_ENCODING encoding;

	MULTICAST_CFG	 multicast;
} AUDIO_ENCODER;

typedef struct
{
	float min;
	float max;
} ONVIF_FRANGE;

typedef struct
{
    int    used_flag;
    
    char	name[ONVIF_NAME_LEN];
    char	token[ONVIF_TOKEN_LEN];

    float 	pantilt_pos_x;
	float 	pantilt_pos_y;
	float   zoom_pos;
} PTZ_PRESET;

typedef struct
{
	ONVIF_FRANGE abs_pantilt_x;
	ONVIF_FRANGE abs_pantilt_y;
	ONVIF_FRANGE abs_zoom;
	ONVIF_FRANGE rel_pantilt_x;
	ONVIF_FRANGE rel_pantilt_y;
	ONVIF_FRANGE rel_zoom;
	ONVIF_FRANGE con_pantilt_x;
	ONVIF_FRANGE con_pantilt_y;
	ONVIF_FRANGE con_zoom;
	ONVIF_FRANGE pantile_speed;
	ONVIF_FRANGE zoom_speed;
	ONVIF_FRANGE timeout_range;
} PTZ_CFG_OPT;

typedef struct _PTZ_CFG
{
	struct _PTZ_CFG * next;

	int 	use_count;
	
	char	name[ONVIF_NAME_LEN];
    char	token[ONVIF_TOKEN_LEN];
	char	node_token[ONVIF_TOKEN_LEN];
	
	float 	def_pantilt_speed_x;
	float 	def_pantilt_speed_y;
	float 	def_zoom_speed;
    unsigned int 	def_timeout;

	ONVIF_FRANGE pantilt_limits_x;
	ONVIF_FRANGE pantilt_limits_y;
	ONVIF_FRANGE zoom_limits;	

	PTZ_CFG_OPT	 ptz_cfg_opt;
} PTZ_CFG;

typedef struct _PTZ_NODE
{
	struct _PTZ_NODE * next;

	unsigned int fixed_home_pos 		: 1;
	unsigned int abs_pantilt_space 		: 1;
	unsigned int abs_zoom_space 		: 1;
	unsigned int rel_pantilt_space 		: 1;
	unsigned int rel_zoom_space 		: 1;	
	unsigned int con_pantilt_space 		: 1;
	unsigned int con_zoom_space 		: 1;
	unsigned int pantile_speed_space	: 1;
	unsigned int zoom_speed_space		: 1;
	unsigned int home_support			: 1;

	unsigned int reserved				: 23;

	char 		 name[ONVIF_NAME_LEN];
    char         token[ONVIF_TOKEN_LEN];

	ONVIF_FRANGE abs_pantilt_x;
	ONVIF_FRANGE abs_pantilt_y;
	ONVIF_FRANGE abs_zoom;
	ONVIF_FRANGE rel_pantilt_x;
	ONVIF_FRANGE rel_pantilt_y;
	ONVIF_FRANGE rel_zoom;
	ONVIF_FRANGE con_pantilt_x;
	ONVIF_FRANGE con_pantilt_y;
	ONVIF_FRANGE con_zoom;
	ONVIF_FRANGE pantile_speed;
	ONVIF_FRANGE zoom_speed;	
} PTZ_NODE;

typedef struct
{
	float pantilt_pos_x;
	float pantilt_pos_y;
	float zoom_pos;
	
	E_PTZ_STATUS move_sta;
	E_PTZ_STATUS zoom_sta;

	char  error[200];
	char  utc_time[64];
} PTZ_STATUS;


typedef struct _ONVIF_PROFILE
{
    struct _ONVIF_PROFILE * next;
    
    VIDEO_SRC_CFG * video_src_cfg;
    VIDEO_ENCODER * video_enc;
	AUDIO_SRC_CFG * audio_src_cfg;
	AUDIO_ENCODER * audio_enc;
	PTZ_NODE      * ptz_node;
	PTZ_CFG	      * ptz_cfg;

	PTZ_PRESET 	  presets[MAX_PTZ_PRESETS];
	
	char 	name[ONVIF_NAME_LEN];
    char 	token[ONVIF_TOKEN_LEN];
    char 	stream_uri[ONVIF_URI_LEN];
    int 	fixed;
    
} ONVIF_PROFILE;

typedef struct _ONVIF_NET_INF
{	
	struct _ONVIF_NET_INF * next;

    unsigned int	enabled 		: 1;
    unsigned int	ipv4_enabled 	: 1;
    unsigned int	fromdhcp		: 1;
    unsigned int  reserved		: 29;
	
	char 	name[ONVIF_NAME_LEN];
    char 	token[ONVIF_TOKEN_LEN];
	char 	hwaddr[32];
	char 	ipv4_addr[32];

	int	 	mtu;	
	int	 	prefix_len;
} ONVIF_NET_INF;

typedef struct
{
	int		type;	// 0 - NoUpdate, 1 - ClientUpdates, 2 - ServerUpdates
	int		ttl;
	char	name[ONVIF_NAME_LEN];
} DDNS_INFO;

typedef struct
{
    int	fromdhcp;
	char	server[MAX_NTP_SERVER][32];
} NTP_INFO;

typedef struct
{
    int	fromdhcp;
	char	searchdomain[MAX_SEARCHDOMAIN][64];
	char	server[MAX_DNS_SERVER][32];
} DNS_INFO;

typedef struct
{
    int	fromdhcp;
	char    name[ONVIF_NAME_LEN];
} HOSTNAME;

typedef struct
{
    unsigned int 	http_support	: 1;
    unsigned int 	http_enable		: 1;
    unsigned int 	https_support	: 1;
    unsigned int 	https_enable	: 1;
    unsigned int 	rtsp_support	: 1;
    unsigned int 	rtsp_enable		: 1;
    unsigned int  reserved		: 26;
	
	int		http_port[MAX_SERVER_PORT];
	int		https_port[MAX_SERVER_PORT];
	int		rtsp_port[MAX_SERVER_PORT];
} NETPROTOCOL;

typedef struct 
{
    int            discoverable;
	char			gateway[MAX_GATEWAY][32];
	
	DDNS_INFO	 	ddns;
	NTP_INFO	 	ntp;
	DNS_INFO	 	dns;
	HOSTNAME	 	hostname;
	NETPROTOCOL	 	protocols;

	ONVIF_NET_INF * interfaces;
} ONVIF_NET;

typedef struct _SIMPLE_ITEM
{
    struct _SIMPLE_ITEM * next;

    char    name[64];
    char    value[64];
} SIMPLE_ITEM;

typedef struct _ONVIF_NOTIFY
{
    struct _ONVIF_NOTIFY * next;
    
    char	reference_addr[256];
    char    producter_addr[256];
    char    topic[256];
    char    operation[100];
    char    utctime[64];
    time_t  arrival_time;
    
    SIMPLE_ITEM * source;
    SIMPLE_ITEM * key;
    SIMPLE_ITEM * data;
} ONVIF_NOTIFY;


typedef struct PPSN	//ppstack_node
{
    unsigned long		prev_node;
    unsigned long		next_node;
    unsigned long		node_flag;	//0:idle；1:in FreeList 2:in UsedList
}PPSN;

typedef struct PPSN_CTX
{
    unsigned long		fl_base;
    unsigned int		head_node;
    unsigned int		tail_node;
    unsigned int		node_num;
    unsigned int		low_offset;
    unsigned int		high_offset;
    unsigned int		unit_size;
    void	*			ctx_mutex;
    unsigned int		pop_cnt;
    unsigned int		push_cnt;
}PPSN_CTX;

typedef struct http_srv_s
{
    int				r_flag;

    int				sfd;

    int				sport;
    unsigned int	saddr;

    unsigned int	guid;

    PPSN_CTX *		cln_fl;
    PPSN_CTX *		cln_ul;

    unsigned int		rx_tid;
} HTTPSRV;

typedef struct
{
    int            subscribe;              // event subscribed flag
    
    HTTPSRV         http_srv;
    char            reference_addr[256];    // event comsumer address
    char            producter_addr[256];    // event producter address

    int             init_term_time;
    unsigned int 	   		timer_id;

    unsigned int    notify_nums;
    ONVIF_NOTIFY  * notify;
} ONVIF_EVENT;

typedef struct
{
	int				flags;      // FLAG_MANUAL mean added manual, other auto discovery device
	int				state;      // 0 -- offline; 1 -- online
	int				no_res_nums;// probe not response numbers, when > 2 means offline
	unsigned int    local_ip;   // local ip address to connect to server, network byte order
	
    DEVICE_BINFO    binfo;
    DEVICE_INFO  	dev_info;

    ONVIF_CAP   	capablity;

	VIDEO_ENC_CFG	video_enc_cfg;

	VIDEO_SRC       * video_src;
	AUDIO_SRC       * audio_src;
    ONVIF_PROFILE   * profiles;
	VIDEO_SRC_CFG   * video_src_cfg;
	AUDIO_SRC_CFG   * audio_src_cfg;
	VIDEO_ENCODER   * video_enc;
	AUDIO_ENCODER   * audio_enc;
	PTZ_NODE        * ptznodes;
	PTZ_CFG		    * ptz_cfg;
	
	ONVIF_NET       network;
	ONVIF_EVENT     events;
	
	// request
	char 			username[32];
	char 			password[32];
    
    ONVIF_PROFILE * curProfile;
    void          * p_user;
} ONVIF_DEVICE;

/*************************************************************************/
typedef enum onvif_action_e
{
	eActionNull = 0,
		
	eGetCapabilities,
	eGetDeviceInformation,
	eGetNetworkInterfaces,
	eSetNetworkInterfaces,
	eGetNTP,
	eSetNTP,
	eGetHostname,
	eSetHostname,
	eSetHostnameFromDHCP,
	eGetDNS,
	eSetDNS,
	eGetDynamicDNS,
	eSetDynamicDNS,
	eGetNetworkProtocols,
	eSetNetworkProtocols,
	eGetDiscoveryMode,
	eSetDiscoveryMode,
	eGetNetworkDefaultGateway,
	eSetNetworkDefaultGateway,	
	eGetSystemDateAndTime,
	eSetSystemDateAndTime,
	eSystemReboot,
	eSetSystemFactoryDefault,
	eGetSystemLog,
	eGetScopes,
	eSetScopes,
	eAddScopes,
	eRemoveScopes,

	eGetVideoSources,
	eGetAudioSources,
	eCreateProfile,
	eGetProfile,
	eGetProfiles,
	eAddVideoEncoderConfiguration,
	eAddVideoSourceConfiguration,
	eAddAudioEncoderConfiguration,
	eAddAudioSourceConfiguration,
	eAddPTZConfiguration,
	eRemoveVideoEncoderConfiguration,
	eRemoveVideoSourceConfiguration,
	eRemoveAudioEncoderConfiguration,
	eRemoveAudioSourceConfiguration,
	eRemovePTZConfiguration,
	eDeleteProfile,
	eGetVideoSourceConfigurations,
	eGetVideoEncoderConfigurations,
	eGetAudioSourceConfigurations,
	eGetAudioEncoderConfigurations,
	eGetVideoSourceConfiguration,
	eGetVideoEncoderConfiguration,
	eGetAudioSourceConfiguration,
	eGetAudioEncoderConfiguration,
	eSetVideoSourceConfiguration,
	eSetVideoEncoderConfiguration,
	eSetAudioSourceConfiguration,
	eSetAudioEncoderConfiguration,
	eGetVideoSourceConfigurationOptions,
	eGetVideoEncoderConfigurationOptions,
	eGetAudioSourceConfigurationOptions,
	eGetAudioEncoderConfigurationOptions,	
	eGetStreamUri,	
	eSetSynchronizationPoint,
	eGetSnapshotUri,

	eGetNodes,
	eGetNode,
	eGetPresets,
	eSetPreset,
	eRemovePreset,
	eGotoPreset,
	eGotoHomePosition,
	eSetHomePosition,
	eGetStatus,
	eContinuousMove,
	eRelativeMove,
	eAbsoluteMove,
	ePTZStop,
	eGetConfigurations,
	eGetConfiguration,
	eSetConfiguration,	
	eGetConfigurationOptions,	

	eGetEventProperties,
	eRenew,
	eUnsubscribe,
	eSubscribe,
	
	eGetImagingSettings,
	eSetImagingSettings,
	eGetOptions,
	
	eActionMax
}eOnvifAction;

typedef struct onvif_action_s
{
	eOnvifAction	type;
	char			action_url[256];
} OVFACTS;

/*************************************************************************
 *
 * onvif request structure
 *
**************************************************************************/ 
typedef struct
{
	E_CAP_CATEGORY	cap_category;
} GetCapabilities_REQ;

typedef struct
{
} GetDeviceInformation_REQ;

typedef struct
{
} GetNetworkInterfaces_REQ;

typedef struct
{
    ONVIF_NET_INF net_inf;
} SetNetworkInterfaces_REQ;

typedef struct
{
} GetNTP_REQ;

typedef struct 
{
	NTP_INFO	ntp;
} SetNTP_REQ;

typedef struct
{
} GetHostname_REQ;

typedef struct
{
	char	name[128];
} SetHostname_REQ;

typedef struct
{
    int    fromdhcp;
} SetHostnameFromDHCP_REQ;

typedef struct
{
} GetDNS_REQ;

typedef struct 
{
	DNS_INFO	dns;
} SetDNS_REQ;

typedef struct
{
	DDNS_INFO	ddns;
} GetDynamicDNS_REQ;

typedef struct
{
    DDNS_INFO	ddns;
} SetDynamicDNS_REQ;

typedef struct
{
} GetNetworkProtocols_REQ;

typedef struct
{
	NETPROTOCOL	protocols;
} SetNetworkProtocols_REQ;

typedef struct
{
} GetDiscoveryMode_REQ;

typedef struct
{
	int 	discoverable;
} SetDiscoveryMode_REQ;

typedef struct
{
} GetNetworkDefaultGateway_REQ;

typedef struct
{
	char 	gateway[MAX_GATEWAY][32];
} SetNetworkDefaultGateway_REQ;

typedef struct
{
} GetSystemDateAndTime_REQ;

typedef struct
{
	int    type;   /* 0 : Manual, 1 : NTP*/
    int   DaylightSavings;
    char   TZ[32];

    /*UTC Time*/
    DATETIME    datetime;
} SetSystemDateAndTime_REQ;

typedef struct
{
} SystemReboot_REQ;

typedef struct
{
	int		type;		// 0 -- soft reset; 1 -- hard reset
} SetSystemFactoryDefault_REQ;

typedef struct
{
    int     logtype;    // 0 - System, 1 - Access
} GetSystemLog_REQ;

typedef struct
{
} GetScopes_REQ;

typedef struct
{
} SetScopes_REQ;

typedef struct
{
} AddScopes_REQ;

typedef struct
{
} RemoveScopes_REQ;


typedef struct
{
} GetVideoSources_REQ;

typedef struct
{
} GetAudioSources_REQ;

typedef struct
{
    char    name[ONVIF_NAME_LEN];
    char    token[ONVIF_TOKEN_LEN];
} CreateProfile_REQ;

typedef struct
{
    char    token[ONVIF_TOKEN_LEN];
} GetProfile_REQ;

typedef struct
{
} GetProfiles_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
    char    config_token[ONVIF_TOKEN_LEN];
} AddVideoEncoderConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
    char    config_token[ONVIF_TOKEN_LEN];
} AddVideoSourceConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
    char    config_token[ONVIF_TOKEN_LEN];
} AddAudioEncoderConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
    char    config_token[ONVIF_TOKEN_LEN];
} AddAudioSourceConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
    char    config_token[ONVIF_TOKEN_LEN];
} AddPTZConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
} RemoveVideoEncoderConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
} RemoveVideoSourceConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
} RemoveAudioEncoderConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
} RemoveAudioSourceConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
} RemovePTZConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
} DeleteProfile_REQ;

typedef struct
{
} GetVideoSourceConfigurations_REQ;

typedef struct
{
} GetVideoEncoderConfigurations_REQ;

typedef struct
{
} GetAudioSourceConfigurations_REQ;

typedef struct
{
} GetAudioEncoderConfigurations_REQ;

typedef struct
{
    char    config_token[ONVIF_TOKEN_LEN];
} GetVideoSourceConfiguration_REQ;

typedef struct
{
    char    config_token[ONVIF_TOKEN_LEN];
} GetVideoEncoderConfiguration_REQ;

typedef struct
{
    char    config_token[ONVIF_TOKEN_LEN];
} GetAudioSourceConfiguration_REQ;

typedef struct
{
    char    config_token[ONVIF_TOKEN_LEN];
} GetAudioEncoderConfiguration_REQ;

typedef struct
{
	VIDEO_SRC_CFG	video_src_cfg;

	int	persistence;
} SetVideoSourceConfiguration_REQ;

typedef struct
{
	VIDEO_ENCODER	video_enc;
	
	int	persistence;
} SetVideoEncoderConfiguration_REQ;

typedef struct
{
	AUDIO_SRC_CFG	audio_src_cfg;

	int	persistence;
} SetAudioSourceConfiguration_REQ;

typedef struct
{
	AUDIO_ENCODER	audio_enc;

	int	persistence;
} SetAudioEncoderConfiguration_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
    char    config_token[ONVIF_TOKEN_LEN];
} GetVideoSourceConfigurationOptions_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
    char    config_token[ONVIF_TOKEN_LEN];
} GetVideoEncoderConfigurationOptions_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
    char    config_token[ONVIF_TOKEN_LEN];
} GetAudioSourceConfigurationOptions_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
    char    config_token[ONVIF_TOKEN_LEN];
} GetAudioEncoderConfigurationOptions_REQ;

typedef struct
{
	char 	profile_token[ONVIF_TOKEN_LEN];
	int  	stream_type;	/* 0: RTP-Unicast, 1: RTP-Multicast */
	int  	protocol;		/* 0: UDP 1: TCP 2: RTSP 3: HTTP */
} GetStreamUri_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
} SetSynchronizationPoint_REQ;

typedef struct
{
    char    profile_token[ONVIF_TOKEN_LEN];
} GetSnapshotUri_REQ;


typedef struct
{
} GetNodes_REQ;

typedef struct
{
	char	node_token[ONVIF_TOKEN_LEN];
} GetNode_REQ;

typedef struct
{
	char 	profile_token[ONVIF_TOKEN_LEN];
} GetPresets_REQ;

typedef struct
{
    char	profile_token[ONVIF_TOKEN_LEN];
    char	preset_token[ONVIF_TOKEN_LEN];
    char    name[ONVIF_NAME_LEN];
} SetPreset_REQ;

typedef struct
{
	char	profile_token[ONVIF_TOKEN_LEN];
    char	preset_token[ONVIF_TOKEN_LEN];
} RemovePreset_REQ;

typedef struct
{
	char	profile_token[ONVIF_TOKEN_LEN];
	char	preset_token[ONVIF_TOKEN_LEN];

	float   pantilt_speed_x;
    float   pantilt_speed_y;
    float   zoom_speed;
} GotoPreset_REQ;

typedef struct
{
    char	profile_token[ONVIF_TOKEN_LEN];

    float   pantilt_speed_x;
    float   pantilt_speed_y;
    float   zoom_speed;
} GotoHomePosition_REQ;

typedef struct
{
    char	profile_token[ONVIF_TOKEN_LEN];
} SetHomePosition_REQ;

typedef struct
{
	char	profile_token[ONVIF_TOKEN_LEN];
} GetStatus_REQ;

typedef struct
{
	char	profile_token[ONVIF_TOKEN_LEN];
	
	float	pantilt_velocity_x;
	float	pantilt_velocity_y;
	float   zoom_velocity;
	
	int		timeout;	
} ContinuousMove_REQ;

typedef struct
{
	char	profile_token[ONVIF_TOKEN_LEN];

	float	pantilt_translation_x;
	float	pantilt_translation_y;
	float   zoom_translation;
	
	float	pantilt_speed_x;
	float	pantilt_speed_y;
	float   zoom_speed;
} RelativeMove_REQ;

typedef struct
{
	char	profile_token[ONVIF_TOKEN_LEN];

	float	pantilt_position_x;
	float	pantilt_position_y;
	float   zoom_position;
	
	float	pantilt_speed_x;
	float	pantilt_speed_y;
	float   zoom_speed;
} AbsoluteMove_REQ;

typedef struct
{
	char	profile_token[ONVIF_TOKEN_LEN];

	int	stop_pantile;
	int	stop_zoom;
} PTZStop_REQ;

typedef struct
{
} GetConfigurations_REQ;

typedef struct
{
	char	config_token[ONVIF_TOKEN_LEN];
} GetConfiguration_REQ;

typedef struct
{
} SetConfiguration_REQ;

typedef struct
{
	char	config_token[ONVIF_TOKEN_LEN];
} GetConfigurationOptions_REQ;

typedef struct
{
} GetEventProperties_REQ;

typedef struct
{
	int		term_time;
} Renew_REQ;

typedef struct
{
} Unsubscribe_REQ;

typedef struct
{
	char	reference_addr[256];
	int		init_term_time;
} Subscribe_REQ;

typedef struct
{
	char	source_token[ONVIF_TOKEN_LEN];
} GetImagingSettings_REQ;

typedef struct
{
	IMAGE_CFG	img_cfg;
	
	char	source_token[ONVIF_TOKEN_LEN];	
	int	persistence;
} SetImagingSettings_REQ;

typedef struct
{
	char	source_token[ONVIF_TOKEN_LEN];
} GetOptions_REQ;



/*************************************************************************
 *
 * onvif response structure
 *
**************************************************************************/
typedef struct
{
	ONVIF_CAP 	capablity;
} GetCapabilities_RES;

typedef struct
{
	DEVICE_INFO	dev_info;
} GetDeviceInformation_RES;


typedef struct
{
	ONVIF_NET_INF * p_net_inf;
} GetNetworkInterfaces_RES;

typedef struct
{
	int	need_reboot;
} SetNetworkInterfaces_RES;

typedef struct
{
	NTP_INFO	ntp;
} GetNTP_RES;

typedef struct 
{	
} SetNTP_RES;

typedef struct
{
	HOSTNAME	hostname;
} GetHostname_RES;

typedef struct
{
} SetHostname_RES;

typedef struct
{
	int	need_reboot;
} SetHostnameFromDHCP_RES;

typedef struct
{
	DNS_INFO	dns;
} GetDNS_RES;

typedef struct 
{
} SetDNS_RES;

typedef struct
{
	DDNS_INFO	ddns;
} GetDynamicDNS_RES;

typedef struct
{
} SetDynamicDNS_RES;

typedef struct
{
	NETPROTOCOL	protocols;
} GetNetworkProtocols_RES;

typedef struct
{
} SetNetworkProtocols_RES;

typedef struct
{
	int 	discoverable;
} GetDiscoveryMode_RES;

typedef struct
{
} SetDiscoveryMode_RES;

typedef struct
{
	char	gateway[MAX_GATEWAY][32];
} GetNetworkDefaultGateway_RES;

typedef struct
{
} SetNetworkDefaultGateway_RES;

typedef struct
{
    int     DaylightSavings : 1;
    int     utc_valid   : 1;    /* utc_datetime valid flag */
    int     local_valid : 1;    /* local_datetime valid flag */
    int     reserved    : 29;
    
    int     type;   /* 0 : Manual, 1 : NTP*/
    
    char    TZ[32];

    /*UTC Time*/
    DATETIME    utc_datetime;
    DATETIME    local_datetime;
} GetSystemDateAndTime_RES;

typedef struct
{
} SetSystemDateAndTime_RES;

typedef struct
{
} SystemReboot_RES;

typedef struct
{
} SetSystemFactoryDefault_RES;

typedef struct
{
} GetSystemLog_RES;

typedef struct
{
} GetScopes_RES;

typedef struct
{
} SetScopes_RES;

typedef struct
{
} AddScopes_RES;

typedef struct
{
} RemoveScopes_RES;


typedef struct
{
	VIDEO_SRC * p_v_src;
} GetVideoSources_RES;

typedef struct
{
    AUDIO_SRC * p_a_src;
} GetAudioSources_RES;

typedef struct
{
	ONVIF_PROFILE profile;
} CreateProfile_RES;

typedef struct
{
	ONVIF_PROFILE profile;
} GetProfile_RES;

typedef struct
{
	ONVIF_PROFILE * p_profile;
} GetProfiles_RES;

typedef struct
{
} AddVideoEncoderConfiguration_RES;

typedef struct
{
} AddVideoSourceConfiguration_RES;

typedef struct
{
} AddAudioEncoderConfiguration_RES;

typedef struct
{
} AddAudioSourceConfiguration_RES;

typedef struct
{
} AddPTZConfiguration_RES;

typedef struct
{
} RemoveVideoEncoderConfiguration_RES;

typedef struct
{
} RemoveVideoSourceConfiguration_RES;

typedef struct
{
} RemoveAudioEncoderConfiguration_RES;

typedef struct
{
} RemoveAudioSourceConfiguration_RES;

typedef struct
{
} RemovePTZConfiguration_RES;

typedef struct
{
} DeleteProfile_RES;

typedef struct
{
	VIDEO_SRC_CFG * p_v_src_cfg;
} GetVideoSourceConfigurations_RES;

typedef struct
{
	VIDEO_ENCODER * p_v_enc;
} GetVideoEncoderConfigurations_RES;

typedef struct
{
	AUDIO_SRC_CFG * p_a_src_cfg;
} GetAudioSourceConfigurations_RES;

typedef struct
{
	AUDIO_ENCODER * p_a_enc;
} GetAudioEncoderConfigurations_RES;

typedef struct
{
	VIDEO_SRC_CFG	video_src_cfg;
} GetVideoSourceConfiguration_RES;

typedef struct
{
	VIDEO_ENCODER video_enc;
} GetVideoEncoderConfiguration_RES;

typedef struct
{
	AUDIO_SRC_CFG audio_src_cfg;
} GetAudioSourceConfiguration_RES;

typedef struct
{
	AUDIO_ENCODER audio_enc;
} GetAudioEncoderConfiguration_RES;

typedef struct
{
} SetVideoSourceConfiguration_RES;

typedef struct
{
} SetVideoEncoderConfiguration_RES;

typedef struct
{
} SetAudioSourceConfiguration_RES;

typedef struct
{
} SetAudioEncoderConfiguration_RES;

typedef struct
{
} GetVideoSourceConfigurationOptions_RES;

typedef struct
{
	VIDEO_ENC_CFG video_enc_cfg;
} GetVideoEncoderConfigurationOptions_RES;

typedef struct
{
} GetAudioSourceConfigurationOptions_RES;

typedef struct
{
} GetAudioEncoderConfigurationOptions_RES;

typedef struct
{
	char	Uri[ONVIF_URI_LEN];

	int 	Timeout;
	
	int	InvalidAfterConnect;
	int	InvalidAfterReboot;	
} GetStreamUri_RES;

typedef struct
{
} SetSynchronizationPoint_RES;

typedef struct
{
	char	Uri[ONVIF_URI_LEN];

	int 	Timeout;
	
	int	InvalidAfterConnect;
	int	InvalidAfterReboot;
} GetSnapshotUri_RES;


typedef struct
{
	PTZ_NODE * p_ptz_node;
} GetNodes_RES;

typedef struct
{
	PTZ_NODE ptz_node;
} GetNode_RES;

typedef struct
{
	PTZ_PRESET 	presets[MAX_PTZ_PRESETS];
} GetPresets_RES;

typedef struct
{
	char	preset_token[ONVIF_TOKEN_LEN];
} SetPreset_RES;

typedef struct
{
} RemovePreset_RES;

typedef struct
{
} GotoPreset_RES;

typedef struct
{
} GotoHomePosition_RES;

typedef struct
{
} SetHomePosition_RES;

typedef struct
{
	PTZ_STATUS	status;
} GetStatus_RES;

typedef struct
{
} ContinuousMove_RES;

typedef struct
{
} RelativeMove_RES;

typedef struct
{
} AbsoluteMove_RES;

typedef struct
{
} PTZStop_RES;

typedef struct
{
    PTZ_CFG * p_ptz_cfg;
} GetConfigurations_RES;

typedef struct
{
    PTZ_CFG ptz_cfg;
} GetConfiguration_RES;

typedef struct
{
} SetConfiguration_RES;

typedef struct
{
	PTZ_CFG_OPT ptz_cfg_opt;
} GetConfigurationOptions_RES;

typedef struct
{
} GetEventProperties_RES;

typedef struct
{
} Renew_RES;

typedef struct
{
} Unsubscribe_RES;

typedef struct
{
    char    producter_addr[256];
} Subscribe_RES;

typedef struct
{
    ONVIF_NOTIFY * notify;
} Notify_REQ;

typedef struct
{
    IMAGE_CFG img_cfg;
} GetImagingSettings_RES;

typedef struct
{
} SetImagingSettings_RES;

typedef struct
{
	IMAGE_OPTIONS img_opt;
} GetOptions_RES;

typedef enum GetCmd
{
	cmdGetdevInformation = 0,
	cmdGetNetworkInfo,
	cmdGetStreamUri,
	cmdGetVideoEncodeInfo,
	cmdGetVideoSourceInfo,
	cmdGetAudioEncodeInfo,
	cmdGetAudioSourceInfo,
	cmdGetImageSetting
};

typedef enum SetCmd
{
	cmdSetNetworkInfo = 0,
	cmdSetVideoEncodeInfo,
	cmdSetImageSetting
};

typedef enum EventCmd
{
	cmdSubscribe = 0,
	cmdUnsubscribe
};

typedef enum PTZCmd
{
	cmdGetPreset =0,
	cmdSetPreset,
	cmdRemovePreset,
	cmdGotoPreset,
	cmdSetHomePos,
	cmdGotoHomePos,
	cmdMoveLeft,
	cmdMoveUp,
	cmdMoveRight,
	cmdMoveDown,
	cmdMoveLeftup,
	cmdMoveLeftdown,
	cmdMoveRightup,
	cmdMoveRightdown
};


typedef void (* onvif_probe_cb)(DEVICE_BINFO * p_res, void * pdata);
typedef void (* onvif_event_notify_cb)(Notify_REQ * p_req, void * pdata);
#ifdef __cplusplus
extern "C" {
#endif

OVFACTS 	  * onvif_find_action_by_type(eOnvifAction type);
ONVIF_NET_INF * onvif_add_network_interface(ONVIF_NET_INF ** p_net_inf);
void			onvif_free_network_interface(ONVIF_NET_INF ** p_net_inf);
ONVIF_NET_INF * onvif_find_network_interface(ONVIF_DEVICE * p_dev, const char * token);
VIDEO_SRC     * onvif_add_video_source(VIDEO_SRC ** p_v_src);
void 		    onvif_free_video_source(VIDEO_SRC ** p_v_src);
VIDEO_SRC     * onvif_find_video_source(ONVIF_DEVICE * p_dev, const char * token);
AUDIO_SRC     * onvif_add_audio_source(AUDIO_SRC ** p_a_src);
void 		    onvif_free_audio_source(AUDIO_SRC ** p_a_src);
AUDIO_SRC     * onvif_find_audio_source(ONVIF_DEVICE * p_dev, const char * token);
VIDEO_SRC_CFG * onvif_add_video_source_cfg(VIDEO_SRC_CFG ** p_v_src_cfg);
void 		    onvif_free_video_source_cfg(VIDEO_SRC_CFG ** p_v_src_cfg);
VIDEO_SRC_CFG * onvif_find_video_source_cfg(ONVIF_DEVICE * p_dev, const char * token);
AUDIO_SRC_CFG * onvif_add_audio_source_cfg(AUDIO_SRC_CFG ** p_a_src_cfg);
void 		    onvif_free_audio_source_cfg(AUDIO_SRC_CFG ** p_a_src_cfg);
AUDIO_SRC_CFG * onvif_find_audio_source_cfg(ONVIF_DEVICE * p_dev, const char * token);
VIDEO_ENCODER * onvif_add_video_encoder(VIDEO_ENCODER ** p_v_enc);
void 		    onvif_free_video_encoder(VIDEO_ENCODER ** p_v_enc);
VIDEO_ENCODER * onvif_find_video_encoder(ONVIF_DEVICE * p_dev, const char * token);
AUDIO_ENCODER * onvif_add_audio_encoder(AUDIO_ENCODER ** p_a_enc);
void 		    onvif_free_audio_encoder(AUDIO_ENCODER ** p_a_enc);
AUDIO_ENCODER * onvif_find_audio_encoder(ONVIF_DEVICE * p_dev, const char * token);
ONVIF_PROFILE * onvif_add_profile(ONVIF_PROFILE ** p_profile);
void            onvif_free_profile(ONVIF_PROFILE ** p_profile);
ONVIF_PROFILE * onvif_find_profile(ONVIF_DEVICE * p_dev, const char * token);
PTZ_NODE      * onvif_add_ptz_node(PTZ_NODE ** p_ptz_node);
void 			onvif_free_ptz_node(PTZ_NODE ** p_ptz_node);
PTZ_NODE      * onvif_find_ptz_node(ONVIF_DEVICE * p_dev, const char * token);
PTZ_CFG       * onvif_add_ptz_cfg(PTZ_CFG ** p_ptz_cfg);
void 			onvif_free_ptz_cfg(PTZ_CFG ** p_ptz_cfg);
PTZ_CFG       * onvif_find_ptz_cfg(ONVIF_DEVICE * p_dev, const char * token);

VIDEO_SRC     * onvif_get_cur_video_src(ONVIF_DEVICE * p_dev);

ONVIF_NOTIFY  * onvif_add_notify(ONVIF_NOTIFY ** p_notify);
void            onvif_free_notify(ONVIF_NOTIFY ** p_notify);
SIMPLE_ITEM   * onvif_add_simple_item(SIMPLE_ITEM ** p_item);
void            onvif_free_simple_item(SIMPLE_ITEM ** p_item);

int             onvif_get_notify_nums(ONVIF_NOTIFY * p_notify);
void            onvif_device_add_notify(ONVIF_DEVICE * p_dev, ONVIF_NOTIFY * p_notify);
int             onvif_device_free_notify(ONVIF_DEVICE * p_dev, int nums);
const char *    onvif_format_simple_item(SIMPLE_ITEM * p_item);

#ifdef __cplusplus
}
#endif

#endif


