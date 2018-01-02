
#ifndef _VIDEO_PROCESSOR_H_
#define _VIDEO_PROCESSOR_H_

#include "rtc_base/logging.h"


#include "api/mediastreaminterface.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "modules/video_capture/video_capture_factory.h"
#include "media/engine/webrtcvideocapturerfactory.h"

#include "rtc_base/file.h"
#include "rtc_base/thread.h"

class VideoProcessor : public rtc::VideoSinkInterface<webrtc::VideoFrame>, public webrtc::AudioTrackSinkInterface, public rtc::Runnable
{
  public:
    VideoProcessor();
    virtual ~VideoProcessor();

    virtual void Run(rtc::Thread* thread);

    uint64_t prevTimestamp = 0;
    // VideoSinkInterface implementation
    virtual void OnFrame(const webrtc::VideoFrame &video_frame);
    virtual void OnData(const void* audio_data,
                          int bits_per_sample,
                          int sample_rate,
                          size_t number_of_channels,
                          size_t number_of_frames) ;
  protected:
    rtc::scoped_refptr<webrtc::VideoTrackInterface> m_track;
    rtc::File outputFile;
    int fifo_fd;
    std::unique_ptr<rtc::Thread> thread;
};

// class VideoSink : public rtc::VideoSinkInterface<webrtc::VideoFrame>
// {
//   public:
//     VideoSink(webrtc::VideoTrackInterface *track) : m_track(track)
//     {
//         RTC_LOG(LS_ERROR) << __PRETTY_FUNCTION__ << " track:" << m_track->id();
//         m_track->AddOrUpdateSink(this, rtc::VideoSinkWants());
//     }
//     virtual ~VideoSink()
//     {
//         RTC_LOG(LS_ERROR) << __PRETTY_FUNCTION__ << " track:" << m_track->id();
//         m_track->RemoveSink(this);
//     }


// };

#endif //_VIDEO_PROCESSOR_H_
