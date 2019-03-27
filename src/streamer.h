
#ifndef _RTMP_CPP_STREAMER_
#define _RTMP_CPP_STREAMER_

// Include all the needed libav components
extern "C" {
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

namespace RTMP_Streamer 
{
    class Scaler 
    {
    public:
        SwsContext *ctx;
        Scaler();
        ~Scaler();
        bool Init(AVCodecContext *codec_ctx, 
                  int src_width, 
                  int src_height, 
                  int dst_width, 
                  int dst_height, 
                  int flags);

    };
    
    class Streamer 
    {
    public:
        Streamer();
        ~Streamer();
    };
}

#endif