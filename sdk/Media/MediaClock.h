#ifndef _MediaClock_h_
#define _MediaClock_h_

#include "Media/media_define.h"

#include <boost/shared_ptr.hpp>

typedef unsigned __int64 MediaTime;
typedef __int64 MediaTimeDiff;

#define MSECS_PER_SECOND 1000
#define USECS_PER_SECOND MSECS_PER_SECOND*1000
#define NSECS_PER_SECOND USECS_PER_SECOND*1000

class MEDIA_EXPORT MediaClock
{
public:
	MediaClock();
	virtual ~MediaClock();

	boost::shared_ptr<MediaClock> masterClock();
	void setMasterClock(boost::shared_ptr<MediaClock> masterClock);
	
	MediaTime time();

	virtual MediaTime internalTime(){return 0;};
	virtual MediaTime resolution(){return 0;};

	MediaTime convertToMasterTime(MediaTime internalTime);
	MediaTime convertToInternalTime(MediaTime masterTime);

	void addMarker();
	void addMarker(MediaTime masterTime);
	void addMarker(MediaTime internalTime, MediaTime masterTime);

	void setMasterCalibration(const MediaTime &localOffset, const MediaTime &scaleNum, const MediaTime &scaleDen, const MediaTime &masterOffset);
private:
	double leastSquaresFit(MediaTime &localOffset, MediaTime &scaleNum, MediaTime &scaleDen, MediaTime &masterOffset);

	boost::shared_ptr<MediaClock> m_master;

	MediaTime m_localOffset;
	MediaTime m_scaleNum;
	MediaTime m_scaleDen;
	MediaTime m_masterOffset;

	int m_markerSize;
	int m_markerNext;
	int m_markerCalibrateCount;
	int m_markerWindowSize;
	MediaTime *m_timeMarkers;
};

typedef boost::shared_ptr<MediaClock> SharedMediaClock;
#endif// _MediaClock_h_