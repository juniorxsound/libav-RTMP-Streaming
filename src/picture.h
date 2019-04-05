#ifndef _PICTURE_H_
#define _PICTURE_H_

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
}

namespace RTMP
{
class Picture
{
  public:
    static const int align_frame_buffer = 32;
    
    Picture();
    ~Picture();

    int Init(enum AVPixelFormat pix_fmt,
             int width, 
             int height);
    

  private:
    AVFrame *frame;
    uint8_t *data;
};
} // namespace RTMP

#endif