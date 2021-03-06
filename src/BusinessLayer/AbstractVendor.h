#pragma once
#include <string>
#include <ctime>
#include <list>
#include <vector>
#include <Windows.h>

#ifndef _TIME_RANGE
#define _TIME_RANGE
typedef struct _time_range
{
	std::time_t start;
	std::time_t end;
} time_range, *ptime_range;
#endif 


#define  MAX_IPADDR_LEN				16       //ip address length    
#define  MAX_MACADDR_LEN			32		 //mac address length

typedef enum tagSDK_TYPE
{
	NONE_SDK = 0,
	JXJ_SDK,
	DZP_SDK,
	DH_SDK,
	HK_SDK,
}NET_SDK_TYPE;

typedef enum
{
	Notification_Type_None = 0,
	Notification_Type_Network_status_Connect,
	Notification_Type_Network_status_Disconnect,
	Notification_Type_Search_Device_Finish,
	Notification_Type_Search_Device_Cancel,
	Notification_Type_Device_Manager_Online,
	Notification_Type_Device_Manager_Dropped,
	Notification_Type_Device_Manager_Cancel,
	Notification_Type_Search_File_Process,
	Notification_Type_Search_File_TotalSize,
	Notification_Type_Search_File_Failure,
	Notification_Type_Search_File_Finish,
	Notification_Type_Search_File_Cancel,
	Notification_Type_Download_File_Process,
	Notification_Type_Download_File_Finish,
	Notification_Type_Download_File_Cancel,
	Notification_Type_Play_Video_Play,
	Notification_Type_Play_Video_Pos,
	Notification_Type_Play_Video_Stop,
	Notification_Type_Play_Video_Replay,
	Notification_Type_Port_Scan_Finish,
	Notification_Type_Exception_Login,

}NOTIFICATION_TYPE;

class AbstractVendor;

struct NET_DEVICE_INFO
{
	int					nSDKType;							//device type 
	char				szIp[MAX_IPADDR_LEN];				//ip address
	int					nPort;								//port
	char				szSubmask[MAX_IPADDR_LEN];			//subnet mask
	char				szMac[MAX_MACADDR_LEN];				//mac address
	//int                 iIPVersion;							//ip version 4:ipv4 ; 6:ipv6

	AbstractVendor*		pVendor;
};

struct NET_DEVICE_INFO_SIMPLE
{
	char				szIP[MAX_IPADDR_LEN];
	int					nPort;
};

struct RecordFile
{
	RecordFile()
	{
		channel = 0;
		size = 0;
		pPrivateData = nullptr;
		PrivateDataDataSize = 0;
	}
	~RecordFile()
	{
		if (nullptr != pPrivateData)
		{
			delete pPrivateData;
			pPrivateData = nullptr;
			PrivateDataDataSize = 0;
		}
	}
	RecordFile(const RecordFile& other)
	{
		channel = other.channel;
		size = other.size;
		name = other.name;
		beginTime = other.beginTime;
		endTime = other.endTime;
		pPrivateData = nullptr;
		PrivateDataDataSize = 0;
		setPrivateData(other.pPrivateData, other.PrivateDataDataSize);
	}

	RecordFile& operator= (const RecordFile& other)
	{
		if (&other == this)
		{
			return *this;
		}
		channel = other.channel;
		size = other.size;
		name = other.name;
		beginTime = other.beginTime;
		endTime = other.endTime;
		setPrivateData(other.pPrivateData, other.PrivateDataDataSize);
		return *this;
	}
	// Set Private Data
	void setPrivateData(void* pData, int size)
	{
		if (nullptr != pPrivateData)
		{
			delete pPrivateData;
			pPrivateData = nullptr;
			PrivateDataDataSize = 0;
		}
		if (size > 0)
		{
			pPrivateData = new char[size];
			PrivateDataDataSize = size;
			memcpy(pPrivateData, pData, size);
		}
	}
	// Get Private Data
	void* getPrivateData() const
	{
		return pPrivateData;
	}
	// Get Private Data Size
	__int32 getPrivateDataSize() const
	{
		return PrivateDataDataSize;
	}
	void deletePrivateData()
	{
		delete pPrivateData;
		pPrivateData = nullptr;
	}

	int channel;
	int size;
	std::string name;
	std::time_t beginTime;
	std::time_t endTime;
	char* pPrivateData;   //Private Data
	__int32 PrivateDataDataSize;//Private Data Size
};

typedef std::vector<NET_DEVICE_INFO*> DEVICE_INFO_LIST;
typedef std::vector<NET_DEVICE_INFO_SIMPLE*> DEVICE_INFO_SIMPLE_LIST;
typedef std::vector<AbstractVendor*> VENDOR_LIST;
typedef std::vector<RecordFile> RECORD_FILE_LIST;

class AbstractVendor
{
public:

	///     Init SDK
	///     @param		None
	///		@return		None
	///		@see
	///		@note		None
	virtual void Init() = 0;

	///     SDK vendor's login
	///     @param		const std::string& ip -- The IP address of the manufacturer's server connected
	///		@param		size_t port -- Connect the manufacturer server port number
	///		@param		const std::string& user -- Login user name
	///		@return		const std::string& password -- The login password
	///     @see		None
	///     @note		Must be initialized before login
	virtual long Login(const std::string& ip, size_t port, const std::string& user, const std::string& password) = 0;

	///     SDK vendor's logout
	///     @param		const long loginHandle -- Login the returned  value
	///     @return		Login handle
	///     @see		
	///		@note		After Login
	virtual void Logout(const long loginHandle) = 0;

	virtual void SearchAll(const long loginHandle) = 0;

	///     Query video file
	///     @param		const long loginHandle -- Login the returned  value
	///		@param		const size_t channel -- Query the channel
	///		@param		const time_range& range -- Query the time range
	///     @return		None
	///     @see	 
	///		@note		After Login
	virtual void Search(const long loginHandle, const size_t channel, const time_range& range) = 0;

	///     Clean up the local video query file
	///     @param		None		   
	///     @return		None
	///     @see		
	///		@note		After Login
	virtual void ClearLocalRecordFiles() = 0;

	///     Through the file information to download video files
	///     @param		const long loginHandle -- Login the returned  value	
	///		@param	    const RecordFile& file -- File information structure
	///     @return	    None
	///     @see	   
	///		@note		After Login
	virtual void Download(const long loginHandle, const RecordFile& file) = 0;	

	///     Stop the file download
	///     @param		None
	///     @return		None
	///     @see		
	///		@note		After Login
	virtual bool StopDownload() = 0;

	///     Through the file information to download video files
	///     @param		const long loginHandle -- Login the returned  value	
	///		@param		const RecordFile& file -- File information structure
	///     @return		Stop download success return true, otherwise return false
	///     @see	 
	//		@note		After download
	virtual void PlayVideo(const long loginHandle, const RecordFile& file) = 0;

	///     Set the progress of the video
	///     @param		int pos -- 100
	///     @return		None
	///     @see		None
	///		@note	
	virtual void SetPlayVideoPos(int pos) = 0;

	///     Stop play video 
	///     @param	 None
	///     @return	 None
	///     @see	 
	///		@note	After play video
	virtual void StopPlayVideo() = 0;


	///     Get the progress of the video
	///     @param		None
	///     @return		None
	///     @see		None
	///		@note	
	virtual int GetPlayVideoPos() = 0;

	///     Get the window's play handle 
	///     @param		const HWND& hWnd -- play handle 
	///     @return		Get progress
	///     @see		
	//		@note		None
	virtual void SetHWnd(const HWND& hWnd) = 0;

	///     Set the download path
	///     @param		const std::string& Root -- The root directory
	///     @return		None
	///     @see	
	///     @note		None
	virtual void SetDownloadPath(const std::string& Root) = 0;
	virtual void throwException() = 0;

	///     Get the user name
	///     @param		None
	///     @return		None
	///     @see	
	///     @note		None
	virtual std::string GetDefUsearName() = 0;

	///      Get the password
	///      @param		None
	///      @return	None
	///      @see	
	///      @note		None
	virtual std::string GetDefPassword() = 0;

	///      Access to the SDK manufacturer's type
	///      @param		None
	///      @return	None
	///      @see	
	///      @note		None
	virtual NET_SDK_TYPE GetSDKType() = 0;

	///      Judge whether the interface of the SDK support equipment
	///      @param		None
	///      @return	An enumeration of the object, get the SDK manufacturers
	///      @see	
	///      @note		None
	virtual bool IsSearchDeviceAPIExist() = 0;

	///      The equipment query
	///      @param		None
	///      @return	The SDK presence of equipment found in the interface
	///      @see	
	///      @note		None
	virtual void StartSearchDevice() = 0;

	///      Get equipment Information
	///      @param		None
	///      @return	Get device information
	///      @see	
	///      @note		None
	virtual DEVICE_INFO_LIST& GetDeviceInfoList() = 0;

	///      Stop device query
	///      @param		None
	///      @return	List for equipment information
	///      @see	
	///      @note		None
	virtual void StopSearchDevice() = 0;

	///      The channel maximum number
	///      @param		None
	///      @return	None
	///      @see	
	///      @note		None
	virtual size_t GetMaxChannel() = 0;

	//virtual RECORD_FILE_LIST GetRecordFileList() = 0;

};
