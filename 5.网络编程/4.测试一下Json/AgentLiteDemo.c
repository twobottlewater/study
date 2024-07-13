#include "stdio.h"
#include "signal.h"

#if defined(WIN32) || defined(WIN64)
#include "windows.h"
#endif

#include "pthread.h"

#include <math.h>
#include "hw_type.h"
#include "iota_init.h"
#include "iota_cfg.h"

#include "LogUtil.h"
#include "JsonUtil.h"
#include "StringUtil.h"
#include "iota_login.h"
#include "iota_datatrans.h"
#include "string.h"
#include "cJSON.h"
#include "sys/types.h"
#include "unistd.h"
#include "iota_error_type.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

/* if you want to use syslog,you should do this:
 *
 * #include "syslog.h"
 * #define _SYS_LOG
 *
 * */
#define SERVER_IP "192.168.1.48"
#define SERVER_PORT 13000

struct sockaddr_in serveraddr;

char *workPath = ".";
char *gatewayId = NULL;

int alarmValue = 0;

char *serverIp_ = "";
int port_ = 1883;

char *username_ = "6670f88a6bc31504f06f55d0_gec6818"; // deviceId
char *password_ = "12345678";

int disconnected_ = 0;

char *subDeviceId = "f6cd4bbb1a8ab53acbb595efd0e90199_ABC123456789";

int sleepTime = 3000;

int socketfd;

void timeSleep(int ms)
{
#if defined(WIN32) || defined(WIN64)
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif
}

//------------------------------------------------------Test  data report---------------------------------------------------------------------

void Test_messageReport()
{
	int messageId = IOTA_MessageReport(NULL, "data123", "123", "hello");
	if (messageId != 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: Test_messageReport() failed, messageId %d\n", messageId);
	}
}

void Test_propertiesReport()
{
	int serviceNum = 1; // ����Ҫ�ϱ���service����
	ST_IOTA_SERVICE_DATA_INFO services[serviceNum];

	// 使用TCP协议 或者 UDP协议 接收开发板的设备信息，然后使用json的形式封装起来
	// 通过这里的代码 ubuntu转发 华为云物联网平台
	int value;
	struct sockaddr_in addr;
	int addrlen = sizeof(addr);

	int ret = recvfrom(socketfd, &value, sizeof(value), 0, (struct sockaddr *)&addr, &addrlen);
	if (ret == -1)
	{
		perror("recvfrom error");
		return;
	}

	printf("IP:[%s] Port:[%d]recvfrom:%d ret:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), value, ret);

	cJSON *root;
	root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "温度值", rand() % 1000);
	cJSON_AddNumberToObject(root, "湿度值", (double)(rand() % 900 + 100) / 10);
	cJSON_AddNumberToObject(root, "Temp", value);

	char *payload;
	payload = cJSON_Print(root);
	cJSON_Delete(root);

	services[0].event_time = getEventTimeStamp(); // if event_time is set to NULL, the time will be the iot-platform's time.
	services[0].service_id = "smokeDetector";
	services[0].properties = payload;

	int messageId = IOTA_PropertiesReport(services, serviceNum);
	if (messageId != 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: Test_batchPropertiesReport() failed, messageId %d\n", messageId);
	}
	free(payload);
}

void Test_batchPropertiesReport()
{
	int deviceNum = 1;							 // Ҫ�ϱ������豸�ĸ���
	ST_IOTA_DEVICE_DATA_INFO devices[deviceNum]; // ���豸Ҫ�ϱ��Ľṹ������
	int serviceList[deviceNum];					 // ��Ӧ�洢ÿ�����豸Ҫ�ϱ��ķ������
	serviceList[0] = 2;							 // ���豸һҪ�ϱ���������
	//	serviceList[1] = 1;		  //���豸��Ҫ�ϱ�һ������

	char *device1_service1 = "{\"Load\":\"1\",\"ImbA_strVal\":\"3\"}"; // service1Ҫ�ϱ����������ݣ�������json��ʽ

	char *device1_service2 = "{\"PhV_phsA\":\"2\",\"PhV_phsB\":\"4\"}"; // service2Ҫ�ϱ����������ݣ�������json��ʽ

	devices[0].device_id = subDeviceId;
	devices[0].services[0].event_time = getEventTimeStamp();
	devices[0].services[0].service_id = "parameter";
	devices[0].services[0].properties = device1_service1;

	devices[0].services[1].event_time = getEventTimeStamp();
	devices[0].services[1].service_id = "analog";
	devices[0].services[1].properties = device1_service2;

	//	char *device2_service1 = "{\"AA\":\"2\",\"BB\":\"4\"}";
	//	devices[1].device_id = "subDevices22222";
	//	devices[1].services[0].event_time = "d2s1";
	//	devices[1].services[0].service_id = "device2_service11111111";
	//	devices[1].services[0].properties = device2_service1;

	int messageId = IOTA_BatchPropertiesReport(devices, deviceNum, serviceList);
	if (messageId != 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: Test_batchPropertiesReport() failed, messageId %d\n", messageId);
	}
}

void Test_commandResponse(char *requestId)
{
	char *pcCommandRespense = "{\"cmdRsp\":\"success\"}"; // just test response

	int result_code = 0;
	char *response_name = NULL;

	int messageId = IOTA_CommandResponse(requestId, result_code, response_name, pcCommandRespense);
	if (messageId != 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: Test_commandResponse() failed, messageId %d\n", messageId);
	}
}

void Test_propSetResponse(char *requestId)
{
	int messageId = IOTA_PropertiesSetResponse(requestId, 0, "success");
	if (messageId != 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: Test_propSetResponse() failed, messageId %d\n", messageId);
	}
}

void Test_propGetResponse(char *requestId)
{
	int serviceNum = 2;
	ST_IOTA_SERVICE_DATA_INFO serviceProp[serviceNum];

	char *property = "{\"Load\":\"5\",\"ImbA_strVal\":\"6\"}";

	serviceProp[0].event_time = getEventTimeStamp();
	serviceProp[0].service_id = "parameter";
	serviceProp[0].properties = property;

	char *property2 = "{\"PhV_phsA\":\"2\",\"PhV_phsB\":\"4\"}";

	serviceProp[1].event_time = getEventTimeStamp();
	serviceProp[1].service_id = "analog";
	serviceProp[1].properties = property2;

	int messageId = IOTA_PropertiesGetResponse(requestId, serviceProp, serviceNum);
	if (messageId != 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: Test_propGetResponse() failed, messageId %d\n", messageId);
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void handleAuthSuccess(void *context, int messageId, int code, char *message)
{
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleConnectSuccess(), login success\n");
	disconnected_ = 0;
}

void handleAuthFailure(void *context, int messageId, int code, char *message)
{
	printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: handleConnectFailure() error, messageId %d, code %d, messsage %s\n", messageId, code, message);
	// judge if the network is available etc. and login again
	//...
	printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: handleConnectFailure() login again\n");
	int ret = IOTA_Connect();
	if (ret != 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: handleConnectionLost() error, login again failed, result %d\n", ret);
	}
}

void handleConnectionLost(void *context, int messageId, int code, char *message)
{
	printfLog(EN_LOG_LEVEL_WARNING, "AgentLiteDemo: handleConnectionLost() warning, messageId, code %d, messsage %s\n", messageId, code, message);
	// judge if the network is available etc. and login again
	//...
	int ret = IOTA_Connect();
	if (ret != 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: handleConnectionLost() error, login again failed, result %d\n", ret);
	}
}

void handleDisAuthSuccess(void *context, int messageId, int code, char *message)
{
	disconnected_ = 1;

	printf("AgentLiteDemo: handleLogoutSuccess, login again\n");
	printf("AgentLiteDemo: handleDisAuthSuccess(), messageId %d, code %d, messsage %s\n", messageId, code, message);
}

void handleDisAuthFailure(void *context, int messageId, int code, char *message)
{
	printf("AgentLiteDemo: handleLogoutFailure, login again\n");
	int ret = IOTA_Connect();
	if (ret != 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: handleConnectionLost() error, login again failed, result %d\n", ret);
	}
	printf("AgentLiteDemo: handleDisAuthFailure(), messageId %d, code %d, messsage %s\n", messageId, code, message);
}

void handleSubscribesuccess(void *context, int messageId, int code, char *message)
{
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleSubscribesuccess() messageId %d\n", messageId);
}

void handleSubscribeFailure(void *context, int messageId, int code, char *message)
{
	printfLog(EN_LOG_LEVEL_WARNING, "AgentLiteDemo: handleSubscribeFailure() warning, messageId %d, code %d, messsage %s\n", messageId, code, message);
}

void handlePublishSuccess(void *context, int messageId, int code, char *message)
{
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handlePublishSuccess() messageId %d\n", messageId);
}

void handlePublishFailure(void *context, int messageId, int code, char *message)
{
	printfLog(EN_LOG_LEVEL_WARNING, "AgentLiteDemo: handlePublishFailure() warning, messageId %d, code %d, messsage %s\n", messageId, code, message);
}

//-------------------------------------------handle  message   arrived------------------------------------------------------------------------------

void handleMessageDown(void *context, int messageId, int code, char *message)
{
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleMessageDown(), messageId %d, code %d, messsage %s\n", messageId, code, message);

	JSON *root = JSON_Parse(message); // Convert string to JSON

	char *content = JSON_GetStringFromObject(root, "content", "-1"); // get value of content
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleMessageDown(), content %s\n", content);

	char *object_device_id = JSON_GetStringFromObject(root, "object_device_id", "-1"); // get value of object_device_id
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleMessageDown(), object_device_id %s\n", object_device_id);

	char *name = JSON_GetStringFromObject(root, "name", "-1"); // get value of name
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleMessageDown(), name %s\n", name);

	char *id = JSON_GetStringFromObject(root, "id", "-1"); // get value of id
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleMessageDown(), id %s\n", id);

	JSON_Delete(root);
}

void handleCommandRequest(void *context, int messageId, int code, char *message, char *requestId)
{
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleCommandRequest(), messageId %d, code %d, messsage %s, requestId %s\n", messageId, code, message, requestId);

	printf("------------------------------------\n");
	printf("message:%s\n", message);
	/*
	{
		"paras": {
			"温度值": 90 
		},
		"service_id": "smokeDetector",
		"command_name": "温度传感器"
	}

	 */
	int size = 0;
	for (int i = 0; *(message + size) != '\0'; i++)
	{
		size++;
	}
	printf("%d\n", size);

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVER_PORT);
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	char buf[2024];
	int ret = sendto(socketfd, message, size, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	printf("ret =%d\n", ret);
	
	if (ret == -1)
	{
		perror("sendto error");
		return -1;
	}
  


	JSON * root =  JSON_Parse(message);  //Convert string to JSON

	char* object_device_id = JSON_GetStringFromObject(root, "object_device_id", "-1");     //get value of object_device_id
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleCommandRequest(), object_device_id %s\n", object_device_id);

	char* service_id = JSON_GetStringFromObject(root, "service_id", "-1");     //get value of service_id
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleCommandRequest(), content %s\n", service_id);

	char* command_name = JSON_GetStringFromObject(root, "command_name", "-1");     //get value of command_name
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleCommandRequest(), name %s\n", command_name);

	JSON* paras = JSON_GetObjectFromObject(root, "paras");       //get value of data
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleCommandRequest(), id %s\n", paras);

	if (paras)
	{
		sleepTime = JSON_GetIntFromObject(paras, "value", 1) * 1000;

		printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleCommandRequest(), sleepTime %d\n", sleepTime);
	}

	Test_commandResponse(requestId); // command reponse

	JSON_Delete(root);
}

void handlePropertiesSet(void *context, int messageId, int code, char *message, char *requestId)
{
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handlePropertiesSet(), messageId %d, code %d, messsage %s, requestId %s\n", messageId, code, message, requestId);

	JSON *root = JSON_Parse(message); // Convert string to JSON

	char *object_device_id = JSON_GetStringFromObject(root, "object_device_id", "-1"); // get value of object_device_id
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handlePropertiesSet(), object_device_id %s\n", object_device_id);

	JSON *services = JSON_GetObjectFromObject(root, "services"); // get  services array
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handlePropertiesSet(), services %s\n", services);

	int dataSize = JSON_GetArraySize(services); // get length of services array
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handlePropertiesSet(), dataSize %d\n", dataSize);

	if (dataSize > 0)
	{
		JSON *service = JSON_GetObjectFromArray(services, 0); // only get the first one to demonstrate
		printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleSubDeviceMessageDown(), service %s\n", service);
		if (service)
		{
			char *service_id = JSON_GetStringFromObject(service, "service_id", NULL);

			printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handlePropertiesSet(), service_id %s\n", service_id);

			JSON *properties = JSON_GetObjectFromObject(service, "properties");

			alarmValue = JSON_GetIntFromObject(properties, "alarm", NULL);
			printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handlePropertiesSet(), alarmValue %d\n", alarmValue);
		}
	}

	Test_propSetResponse(requestId); // command response

	JSON_Delete(root);
}

void handlePropertiesGet(void *context, int messageId, int code, char *message, char *requestId)
{
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handlePropertiesGet(), messageId %d, code %d, messsage %s, requestId %s\n", messageId, code, message, requestId);

	JSON *root = JSON_Parse(message);

	char *object_device_id = JSON_GetStringFromObject(root, "object_device_id", "-1"); // get value of object_device_id
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handlePropertiesGet(), object_device_id %s\n", object_device_id);

	char *service_id = JSON_GetStringFromObject(root, "service_id", "-1"); // get value of service_id
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handlePropertiesGet(), service_id %s\n", service_id);

	Test_propGetResponse(requestId); // command response

	JSON_Delete(root);
}

void handleDeviceProGetResp(void *context, int messageId, int code, char *message, char *requestId)
{
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleDeviceProGetResp(), messageId %d, code %d, messsage %s, requestId %s\n", messageId, code, message, requestId);
	// start to reponse  command  by the topic  of $oc/devices/{device_id}/sys/commands/response/request_id={request_id}
}

void handleEventsDown(void *context, int messageId, int code, char *message)
{
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleSubDeviceMessageDown(), messageId %d, code %d, messsage %s\n", messageId, code, message);

	// the demo of how to get the parameter
	JSON *root = JSON_Parse(message);

	char *object_device_id = JSON_GetStringFromObject(root, "object_device_id", "-1"); // get value of object_device_id
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), object_device_id %s\n", object_device_id);

	JSON *service = JSON_GetObjectFromObject(root, "services"); // get object of services
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), services %s\n", service);

	int dataSize = JSON_GetArraySize(service); // get size of services
	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), dataSize %d\n", dataSize);

	if (dataSize > 0)
	{
		JSON *serviceEvent = JSON_GetObjectFromArray(service, 0); // get object of ServiceEvent
		printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), serviceEvent %s\n", serviceEvent);
		if (serviceEvent)
		{
			char *service_id = JSON_GetStringFromObject(serviceEvent, "service_id", NULL); // get value of service_id
			printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), service_id %s\n", service_id);

			char *event_type = NULL;												 // To determine whether to add or delete a sub device
			event_type = JSON_GetStringFromObject(serviceEvent, "event_type", NULL); // get value of event_type
			printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), event_type %s\n", event_type);

			char *event_time = JSON_GetStringFromObject(serviceEvent, "event_time", NULL); // get value of event_time
			printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), event_time %s\n", event_time);

			JSON *paras = JSON_GetObjectFromObject(serviceEvent, "paras"); // get object of paras
			printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), paras %s\n", paras);

			JSON *devices = JSON_GetObjectFromObject(paras, "devices"); // get object of devices
			printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), devices %s\n", devices);

			int version = JSON_GetIntFromObject(paras, "version", -1); // get value of version
			printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), version %d\n", version);

			int devicesSize = JSON_GetArraySize(devices); // get size of devicesSize
			printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), devicesSize %d\n", devicesSize);

			if (devicesSize > 0)
			{
				JSON *deviceInfo = JSON_GetObjectFromArray(devices, 0); // get object of deviceInfo
				printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), deviceInfo %s\n", deviceInfo);

				char *parent_device_id = JSON_GetStringFromObject(serviceEvent, "parent_device_id", NULL); // get value of parent_device_id
				printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), parent_device_id %s\n", parent_device_id);

				char *node_id = JSON_GetStringFromObject(serviceEvent, "node_id", NULL); // get value of node_id
				printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), node_id %s\n", node_id);

				subDeviceId = JSON_GetStringFromObject(serviceEvent, "device_id", NULL); // get value of device_id
				printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), device_id %s\n", subDeviceId);

				if (!strcmp(event_type, "add_sub_device_notify")) // add a sub device
				{
					char *name = JSON_GetStringFromObject(serviceEvent, "name", NULL); // get value of name
					printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), name %s\n", name);

					char *description = JSON_GetStringFromObject(serviceEvent, "description", NULL); // get value of description
					printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), description %s\n", description);

					char *manufacturer_id = JSON_GetStringFromObject(serviceEvent, "manufacturer_id", NULL); // get value of manufacturer_id
					printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), manufacturer_id %s\n", manufacturer_id);

					char *model = JSON_GetStringFromObject(serviceEvent, "model", NULL); // get value of model
					printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), model %s\n", model);

					char *product_id = JSON_GetStringFromObject(serviceEvent, "product_id", NULL); // get value of product_id
					printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), product_id %s\n", product_id);

					char *fw_version = JSON_GetStringFromObject(serviceEvent, "fw_version", NULL); // get value of fw_version
					printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), fw_version %s\n", fw_version);

					char *sw_version = JSON_GetStringFromObject(serviceEvent, "sw_version", NULL); // get value of sw_version
					printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), sw_version %s\n", sw_version);

					char *status = JSON_GetStringFromObject(serviceEvent, "status", NULL); // get value of status
					printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), status %s\n", status);

					Test_batchPropertiesReport(); // command response
				}
				else if (!strcmp(event_type, "delete_sub_device_notify")) // delete a sub device
				{
					printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), delete a sub device.\n");
				}
				else
				{
					printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: handleEventsDown(), default.\n");
				}
			}
		}
	}

	JSON_Delete(root);
}

void setConnectConfig()
{

	FILE *file;
	long length;
	char *content;
	cJSON *json;

	file = fopen("./ClientConf.json", "rb");
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	content = (char *)malloc(length + 1);
	fread(content, 1, length, file);
	fclose(file);

	json = cJSON_Parse(content);

	username_ = JSON_GetStringFromObject(json, "deviceId", NULL);
	password_ = JSON_GetStringFromObject(json, "secret", NULL);
	char *url = JSON_GetStringFromObject(json, "serverUri", NULL);

	deleteSubStr(url, "ssl://");
	deleteSubStr(url, ":8883");

	serverIp_ = url;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void setAuthConfig()
{
	IOTA_ConfigSetStr(EN_IOTA_CFG_MQTT_ADDR, serverIp_);
	IOTA_ConfigSetUint(EN_IOTA_CFG_MQTT_PORT, port_);
	IOTA_ConfigSetStr(EN_IOTA_CFG_DEVICEID, username_);
	IOTA_ConfigSetStr(EN_IOTA_CFG_DEVICESECRET, password_);

#ifdef _SYS_LOG
	IOTA_ConfigSetUint(EN_IOTA_CFG_LOG_LOCAL_NUMBER, LOG_LOCAL7);
	IOTA_ConfigSetUint(EN_IOTA_CFG_LOG_LEVEL, LOG_INFO);
#endif
}

void setMyCallbacks()
{
	IOTA_SetCallback(EN_IOTA_CALLBACK_CONNECT_SUCCESS, handleAuthSuccess);
	IOTA_SetCallback(EN_IOTA_CALLBACK_CONNECT_FAILURE, handleAuthFailure);
	IOTA_SetCallback(EN_IOTA_CALLBACK_CONNECTION_LOST, handleConnectionLost);

	IOTA_SetCallback(EN_IOTA_CALLBACK_DISCONNECT_SUCCESS, handleDisAuthSuccess);
	IOTA_SetCallback(EN_IOTA_CALLBACK_DISCONNECT_FAILURE, handleDisAuthFailure);

	IOTA_SetCallback(EN_IOTA_CALLBACK_SUBSCRIBE_SUCCESS, handleSubscribesuccess);
	IOTA_SetCallback(EN_IOTA_CALLBACK_SUBSCRIBE_FAILURE, handleSubscribeFailure);

	IOTA_SetCallback(EN_IOTA_CALLBACK_PUBLISH_SUCCESS, handlePublishSuccess);
	IOTA_SetCallback(EN_IOTA_CALLBACK_PUBLISH_FAILURE, handlePublishFailure);

	IOTA_SetCallback(EN_IOTA_CALLBACK_MESSAGE_DOWN, handleMessageDown);
	IOTA_SetCallbackWithTopic(EN_IOTA_CALLBACK_COMMAND_REQUEST, handleCommandRequest);
	IOTA_SetCallbackWithTopic(EN_IOTA_CALLBACK_PROPERTIES_SET, handlePropertiesSet);
	IOTA_SetCallbackWithTopic(EN_IOTA_CALLBACK_PROPERTIES_GET, handlePropertiesGet);
	IOTA_SetCallback(EN_IOTA_CALLBACK_SUB_DEVICE_MESSAGE_DOWN, handleEventsDown);
}

void myPrintLog(int level, char *format, va_list args)
{
	vprintf(format, args); // ��־��ӡ�ڿ���̨
						   /*if you want to printf log in system log files,you can do this:
							*
							* vsyslog(level, format, args);
							* */
}

void socket_init()
{
	// 1.创建套接字
	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketfd == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(12000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// 2 绑定
	int ret = bind(socketfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if (ret == -1)
	{
		perror("bind error");
		return -1;
	}
}

int main(int argc, char **argv)
{

#if defined(_DEBUG)
	setvbuf(stdout, NULL, _IONBF, 0); // in order to make the console log printed immediately at debug mode
#endif

	// 网络初始化
	socket_init();

	IOTA_SetPrintLogCallback(myPrintLog);

	setConnectConfig();

	printfLog(EN_LOG_LEVEL_INFO, "AgentLiteDemo: start test ===================>\n");

	if (IOTA_Init(workPath) > 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: IOTA_Init() error, init failed\n");
		return 1;
	}

	setAuthConfig();
	setMyCallbacks();

	// see handleLoginSuccess and handleLoginFailure for login result
	int ret = IOTA_Connect();
	if (ret != 0)
	{
		printfLog(EN_LOG_LEVEL_ERROR, "AgentLiteDemo: IOTA_Auth() error, Auth failed, result %d\n", ret);
	}

	timeSleep(1500);
	int count = 0;
	while (1)
	{

		//        //message up
		//        Test_messageReport();

		// properties report
		Test_propertiesReport();

		//        //batchProperties report
		//        Test_batchPropertiesReport();
		//
		//        //command response
		//        Test_commandResponse("1005");
		//
		//        timeSleep(1500);
		//
		//        //propSetResponse
		//        Test_propSetResponse("1006");
		//
		//        timeSleep(1500);
		//
		//        //propSetResponse
		//        Test_propGetResponse("1007");

		timeSleep(sleepTime);

		count++;
	}

	while (1)
	{
		timeSleep(50);
	}

	return 0;
}
