#ifndef _FFMPEG_ENCODER_H
#define _FFMPEG_ENCODER_H

#include "Media/MediaPluginFactory.h"
#include "Media/IMediaFilter.h"
#include "codecDescription.h"
#include "ffmpegMediaFilter.h"


extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libswscale/swscale.h>
}

//class CodecOption
//{
//public:
//	CodecOption(const AVOption *option);
//	~CodecOption(){};
//
//	const AVOption *option;
//};
//typedef std::vector<CodecOption> CodecOptions;
//
//class CodecDescription
//{
//public:
//	CodecDescription(AVCodec *avCodec);
//	~CodecDescription(){}
//
//	std::string name;
//	std::string fullName;
//	AVCodecID id;
//
//	AVCodec *avCodec;
//};

class FfmpegDecoder:public MediaAutoRegister<FfmpegDecoder, FfmpegMediaFilter>
{
public:
	FfmpegDecoder(std::string name, SharedMediaFilter parent);
	~FfmpegDecoder();

	virtual bool initialize(const Attributes &attributes);
	virtual bool shutdown(){return true;}

	virtual SharedPluginView getView();

	virtual bool processSample(SharedMediaPad sinkPad, SharedMediaSample sample);

protected:
	//IMediaFilter
	virtual StateChange onReady();
	virtual StateChange onPaused();
	virtual StateChange onPlaying();

	virtual bool FfmpegDecoder::onAcceptMediaFormat(SharedMediaPad pad, SharedMediaFormat format);
	virtual void onLinkFormatChanged(SharedMediaPad mediaPad, SharedMediaFormat format);
	//PluginObject
	virtual void onAttributeChanged(std::string name, SharedAttribute attribute);

private:
	void queryCodecs();
//	void queryFormats();
//	void setupFormat();

	int getVideoCodecIndex(std::string name);
	int getVideoCodecIndexFromId(AVCodecID id);
	int getAudioCodecIndex(std::string name);
	void updateVideoCodecAttributes();

	SharedPluginView m_view;
	size_t m_imageSampleId;
	size_t m_bufferSampleId;

//	typedef std::vector<CodecDetail> CodecDetails;
//	CodecDetails m_accessibleCodecs;
//	typedef std::vector<AVCodecID> AVCodecIDs;
//	AVCodecIDs m_accessibleCodecs;

	CodecDescriptions m_videoCodecs;
	CodecDescriptions m_audioCodecs;

	int m_currentVideoCodec;
	AVCodecContext *m_videoCodec;
	CodecOptions m_videoOptions;
	int m_currentAudioCodec;
	AVCodecContext *m_audioCodec;

	AVFrame *m_frame;
	int m_avFrameSize;
	AVPicture m_picture;
	AVPacket m_pkt;
	SwsContext *m_swsContext;
};

#endif // _FFMPEG_ENCODER_H