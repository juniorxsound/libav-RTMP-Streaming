#ifndef _ENCODER_H_
#define _ENCODER_H_

#define STREAM_PIX_FMT AV_PIX_FMT_YUV420P

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

}

#include <string>

namespace RTMP
{
class Encoder
{
public:
    static int set_options_and_open_encoder(AVFormatContext *fctx,
                                            AVStream *stream,
                                            AVCodecContext *codec_ctx,
                                            AVCodec *codec,
                                            std::string codec_profile,
                                            double width,
                                            double height,
                                            int fps,
                                            int bitrate,
                                            AVCodecID codec_id);

    static int encode_and_write_frame(AVCodecContext *codec_ctx,
                                      AVFormatContext *fmt_ctx,
                                      AVFrame *frame);
};
} // namespace RTMP

#endif