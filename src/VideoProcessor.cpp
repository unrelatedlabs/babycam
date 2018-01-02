
#include "VideoProcessor.h"
#include <stdio.h>
#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static const char *myFIFO = "fifo";
VideoProcessor::VideoProcessor(){
//	outputFile = rtc::File::Create("test.raw");
	int status = 0;
	 if ( (status = mkfifo(myFIFO, 0666)) < 0 ) {
	     printf("\n %s \n", strerror(errno));
	 }
//	 printf("will open\n");
//     if ((fifo_fd = open(myFIFO, O_WRONLY)) < 0) {
//	     printf("\n %s \n", strerror(errno));
//     }
//	 printf("did open\n");

	 thread = rtc::Thread::Create();
	 thread->Start(this);
}
VideoProcessor::~VideoProcessor(){

}

void VideoProcessor::Run(rtc::Thread* thread){
	 printf("will open\n");
	 if ((fifo_fd = open(myFIFO, O_WRONLY)) < 0) {
		 printf("\n %s \n", strerror(errno));
	 }
	 printf("did open\n");
	 sleep(1000*10);
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
	if( fifo_fd){
		write(fifo_fd, buffer->DataY(), buffer->StrideY() * buffer->height() );
		write(fifo_fd, buffer->DataU(), buffer->StrideU() * buffer->ChromaHeight() );
		write(fifo_fd, buffer->DataV(), buffer->StrideV() * buffer->ChromaHeight() );
	}
}

void VideoProcessor::OnData(const void* audio_data,
                         int bits_per_sample,
                         int sample_rate,
                         size_t number_of_channels,
                         size_t number_of_frames){

}
