
#include "VideoProcessor.h"

VideoProcessor::VideoProcessor(){
//	outputFile = rtc::File::Create("test.raw");
}


void VideoProcessor::OnFrame(const webrtc::VideoFrame &video_frame)
{
	rtc::scoped_refptr<webrtc::I420BufferInterface> buffer(video_frame.video_frame_buffer()->ToI420());
	double frameTime = video_frame.timestamp_us() - prevTimestamp;
	double fps = 1e6 / frameTime;
//	RTC_LOG(LS_INFO) << __PRETTY_FUNCTION__ << " frame:" << buffer->width() << "x" << buffer->height() << " " << video_frame.timestamp_us() << " " << fps
//			<< " " << buffer->ChromaWidth() << "x" << buffer->ChromaHeight()
//			<< " StrideY " << buffer->StrideY()
//			<< " StrideU " << buffer->StrideU()
//			<< " StrideV " << buffer->StrideV();

	prevTimestamp = video_frame.timestamp_us();

//	outputFile.Write( buffer->DataY(), buffer->StrideY() * buffer->height() );
//	outputFile.Write( buffer->DataU(), buffer->StrideU() * buffer->ChromaHeight() );
//	outputFile.Write( buffer->DataV(), buffer->StrideV() * buffer->ChromaHeight() );

}
