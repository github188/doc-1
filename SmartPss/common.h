#ifndef COMMON_H
#define COMMON_H

#define SHADOW_WIDTH            5
#define WINDOW_WIDTH            680
#define WINDOW_HEIGHT           372
#define WINDOW_START_X          0
#define WINDOW_START_Y          0
#define WINDOW_PAGE_COUNT       4
#define WINDOW_BUTTON_COUNT     4
#define WINDOW_PAGE_MOVE        20
#define WINDOW_ONEBUTTON_WIDTH  170
#define DEFAULT_SKIN            ":/skin/17_big"

typedef enum{
	UI_EN,
	UI_ZH
}LANGUAGE;

typedef enum{
	SAFE,
	SINA,
	RENREN
}LOGIN;

typedef enum{
	HELP_ONLINE,
	PLATFORM_HELP,
	LOGIN_HOME,
	PROTECT
}ACTION;

//枚举按钮的几种状态
typedef enum{
	NORMAL,
	ENTER,
	PRESS,
	NOSTATUS
}ButtonStatus;

typedef struct DeviceInfo
{
    char ip[20];
    char szName[30];
    char username[30];
    char password[30];
    char Mainrtspurl[100];
    char SubrtspUrl[100];
}*PDeviceInfo;

#endif // COMMON_H
