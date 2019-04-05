#include "encoder.h"

int RTMP::Encoder::set_options_and_open_encoder(AVFormatContext *fctx,
                                                AVStream *stream,
                                                AVCodecContext *codec_ctx,
                                                AVCodec *codec,
                                                std::string codec_profile,
                                                double width,
                                                double height,
                                                int fps,
                                                int bitrate,
                                                AVCodecID codec_id)
{
    const AVRational dst_fps = {fps, 1};

    codec_ctx->codec_tag = 0;
    codec_ctx->codec_id = codec_id;
    codec_ctx->codec_type = AVMEDIA_TYPE_VIDEO;
    codec_ctx->width = width;
    codec_ctx->height = height;
    codec_ctx->gop_size = 12;
    codec_ctx->pix_fmt = STREAM_PIX_FMT;
    codec_ctx->framerate = dst_fps;
    codec_ctx->time_base = av_inv_q(dst_fps);
    codec_ctx->bit_rate = bitrate;
    if (fctx->oformat->flags & AVFMT_GLOBALHEADER)
    {
        codec_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }

    stream->time_base = codec_ctx->time_base; //will be set afterwards by avformat_write_header to 1/1000

    int ret = avcodec_parameters_from_context(stream->codecpar, codec_ctx);
    if (ret < 0)
    {
        fprintf(stderr, "Could not initialize stream codec parameters!\n");
        return 1;
    }

    AVDictionary *codec_options = nullptr;
    av_dict_set(&codec_options, "profile", codec_profile.c_str(), 0);
    av_dict_set(&codec_options, "preset", "fast", 0);
    av_dict_set(&codec_options, "tune", "zerolatency", 0);

    // open video encoder
    ret = avcodec_open2(codec_ctx, codec, &codec_options);
    if (ret < 0)
    {
        fprintf(stderr, "Could not open video encoder!\n");
        return 1;
    }
    av_dict_free(&codec_options);
    return 0;
}

int RTMP::Encoder::encode_and_write_frame(AVCodecContext *codec_ctx,
                                          AVFormatContext *fmt_ctx,
                                          AVFrame *frame)
{
    AVPacket pkt = {0};
    av_init_packet(&pkt);

    int ret = avcodec_send_frame(codec_ctx, frame);
    if (ret < 0)
    {
        fprintf(stderr, "Error sending frame to codec context!\n");
        return ret;
    }

    ret = avcodec_receive_packet(codec_ctx, &pkt);
    if (ret < 0)
    {
        fprintf(stderr, "Error receiving packet from codec context!\n");
        return ret;
    }

    av_interleaved_write_frame(fmt_ctx, &pkt);
    av_packet_unref(&pkt);

    return 0;
}