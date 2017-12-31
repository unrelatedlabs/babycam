
#ifndef _VIDEO_PROCESSOR_H_
#define _VIDEO_PROCESSOR_H_

#include "rtc_base/logging.h"


#include "api/mediastreaminterface.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "modules/video_capture/video_capture_factory.h"
#include "media/engine/webrtcvideocapturerfactory.h"

#include "rtc_base/file.h"

class VideoProcessor : public rtc::VideoSinkInterface<webrtc::VideoFrame> 
{
  public:
    VideoProcessor();

    uint64_t prevTimestamp = 0;
    // VideoSinkInterface implementation
    virtual void OnFrame(const webrtc::VideoFrame &video_frame);

  protected:
    rtc::scoped_refptr<webrtc::VideoTrackInterface> m_track;
    rtc::File outputFile;
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
