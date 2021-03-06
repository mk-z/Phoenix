#pragma once
#include "HKLite.h"
#include "DVR/DVRStatementImpl.h"
#include "HK/Utility.h"

namespace DVR {
	namespace HKLite {

		class HKLite_API DVRStatementImpl : public DVR::DVRStatementImpl
{
public:
	DVRStatementImpl(DVR::DVRSessionImpl& rSession, Utility::HANDLE pDvr);
	~DVRStatementImpl();

	long donwloadByName(const RecordFile& rf, const std::string& filename);
	void downloadByTime(const Poco::DateTime& time);
	int getdownloadPos(const long handle);

	int playByName(const RecordFile& filename, HWND& hwnd);
	void playByTime(const Poco::DateTime& time);
	void stopPlayback(const int playhandle);
	void setplayPos(const int playhandle, const int proValue);
	int getplayPos(const int playhandle);


	void list(const Poco::DateTime& beginTime, const Poco::DateTime& endTime, const std::vector<int>& channels, std::vector<RecordFile>& files);

	bool canDownloadByName();
	bool canPlayByName();

	typedef void (*ProcessCallbackType)(long lPlayHandle, long lTotalSize, long lDownLoadSize, long dwUser);
private:
	Utility::HANDLE _handle;
	int _state;
};

inline bool DVRStatementImpl::canDownloadByName()
{
	return true;
}

inline bool DVRStatementImpl::canPlayByName()
{
	return true;
}

}}
