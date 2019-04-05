#ifndef _SCALER_H_
#define _SCALER_H_

extern "C"
{
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
}

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

  private:
    SwsContext *ctx;
};
} // namespace RTMP
#endif