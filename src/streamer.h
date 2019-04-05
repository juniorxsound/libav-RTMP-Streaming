#ifndef _STREAMER_H_
#define _STREAMER_H_

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include "config.h"
#include "picture.h"
#include "scaler.h"
#include "encoder.h"

namespace RTMP
{
class Streamer
{
    bool network_init_ok;
    bool rtmp_server_conn;
    bool init_ok;

    AVFormatContext *format_ctx;
    AVCodec *out_codec;
    AVStream *out_stream;
    AVCodecContext *out_codec_ctx;

    Scaler scaler;
    Picture picture;

    void cleanup();
    bool can_stream()
    {
        return network_init_ok && rtmp_server_conn && init_ok;
    }

  public:
    double inv_stream_timebase;
    Config config;
    Streamer();
    ~Streamer();
    void enable_av_debug_log();
    int Init(const Config &streamer_config);
    // void stream_frame(const cv::Mat &frame);
    // void stream_frame(const cv::Mat &image, int64_t frame_duration);
};

} // namespace RTMP
#endif