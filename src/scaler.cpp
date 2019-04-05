#include "scaler.h"

RTMP::Scaler::Scaler()
{
    ctx = nullptr;
}

RTMP::Scaler::~Scaler()
{
    if (ctx)
    {
        sws_freeContext(ctx);
    }
}

int RTMP::Scaler::Init(AVCodecContext *codec_ctx, int src_width, int src_height, int dst_width, int dst_height, int flags)
{
    ctx = sws_getContext(src_width, 
                         src_height, 
                         AV_PIX_FMT_BGR24, 
                         dst_width, 
                         dst_height,
                         codec_ctx->pix_fmt, 
                         flags, 
                         nullptr, 
                         nullptr, 
                         nullptr);
    if (!ctx)
    {
        fprintf(stderr, "Could not initialize scaler!\n");
        return 1;
    }
    return 0;
}