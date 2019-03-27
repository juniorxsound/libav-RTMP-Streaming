
#ifndef _RTMP_CPP_STREAMER_
#define _RTMP_CPP_STREAMER_

// Include all the needed libav components
extern "C"
{
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

#include <string>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace RTMP
{
class Scaler
{
public:
  Scaler();
  ~Scaler();

  int Init(AVCodecContext *codec_ctx,
           int src_width,
           int src_height,
           int dst_width,
           int dst_height,
           int flags);

protected:
  SwsContext *ctx;
};

class Picture
{
  static const int align_frame_buffer = 32;

public:
  AVFrame *frame;
  uint8_t *data;

  Picture();
  ~Picture();

  int Init(enum AVPixelFormat pix_fmt, int width, int height);
};

struct Config
{
  int src_width;
  int src_height;
  int dst_width;
  int dst_height;
  int fps;
  int bitrate;
  std::string profile;
  std::string server;

  Config();
  Config(int source_width,
         int source_height,
         int stream_width,
         int stream_height,
         int stream_fps,
         int stream_bitrate,
         const std::string &stream_profile,
         const std::string &stream_server);
};

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

public:
  Streamer();
  ~Streamer();

  void cleanup();
  bool can_stream();

  void enable_av_debug_log();
  int Init(const Config &streamer_config);
  // void stream_frame(const cv::Mat &frame);
  // void stream_frame(const cv::Mat &image, int64_t frame_duration);
};
} // namespace RTMP

#endif