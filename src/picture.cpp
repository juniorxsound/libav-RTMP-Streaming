#include "picture.h"

RTMP::Picture::Picture()
{
    frame = nullptr;
    data = nullptr;
}

RTMP::Picture::~Picture()
{
    if (data)
    {
        free(data);
        data = nullptr;
    }

    if (frame)
    {
        av_frame_free(&frame);
    }
}

int RTMP::Picture::Init(enum AVPixelFormat pix_fmt,
                        int width, 
                        int height)
{
    frame = nullptr;
    data = nullptr;
    frame = av_frame_alloc();

    int sz =  av_image_get_buffer_size(pix_fmt, width, height, align_frame_buffer);
    int ret = posix_memalign(reinterpret_cast<void**>(&data), align_frame_buffer, sz);

    av_image_fill_arrays(frame->data, frame->linesize, data, pix_fmt, width, height, align_frame_buffer);
    frame->format = pix_fmt;
    frame->width  = width;
    frame->height = height;

    return ret;
}