#include "streamer.h"

RTMP::Streamer::Streamer()
{
    format_ctx = nullptr;
    out_codec = nullptr;
    out_stream = nullptr;
    out_codec_ctx = nullptr;
    rtmp_server_conn = false;
    av_register_all();
    inv_stream_timebase = 30.0;
    network_init_ok = !avformat_network_init();
}

void RTMP::Streamer::cleanup()
{
    if (out_codec_ctx)
    {
        avcodec_close(out_codec_ctx);
        avcodec_free_context(&out_codec_ctx);
    }

    if (format_ctx)
    {
        if (format_ctx->pb)
        {
            avio_close(format_ctx->pb);
        }
        avformat_free_context(format_ctx);
        format_ctx = nullptr;
    }
}

RTMP::Streamer::~Streamer()
{
    cleanup();
    avformat_network_deinit();
}

// // void Streamer::stream_frame(const cv::Mat &image)
// // {
// //     if(can_stream()) {
// //         const int stride[] = {static_cast<int>(image.step[0])};
// //         sws_scale(scaler.ctx, &image.data, stride, 0, image.rows, picture.frame->data, picture.frame->linesize);
// //         picture.frame->pts += av_rescale_q(1, out_codec_ctx->time_base, out_stream->time_base);
// //         encode_and_write_frame(out_codec_ctx, format_ctx, picture.frame);
// //     }
// // }

// // void Streamer::stream_frame(const cv::Mat &image, int64_t frame_duration)
// // {
// //     if(can_stream()) {
// //         const int stride[] = {static_cast<int>(image.step[0])};
// //         sws_scale(scaler.ctx, &image.data, stride, 0, image.rows, picture.frame->data, picture.frame->linesize);
// //         picture.frame->pts += frame_duration; //time of frame in milliseconds
// //         encode_and_write_frame(out_codec_ctx, format_ctx, picture.frame);
// //     }
// // }

void RTMP::Streamer::enable_av_debug_log()
{
    av_log_set_level(AV_LOG_DEBUG);
}

int RTMP::Streamer::Init(const RTMP::Config &streamer_config)
{
    init_ok = false;
    cleanup();

    config = streamer_config;

    if (!network_init_ok)
    {
        return 1;
    }

    //initialize format context for output with flv and no filename
    avformat_alloc_output_context2(&format_ctx, nullptr, "flv", nullptr);
    if (!format_ctx)
    {
        return 1;
    }

    //AVIOContext for accessing the resource indicated by url
    if (!(format_ctx->oformat->flags & AVFMT_NOFILE))
    {
        int avopen_ret = avio_open2(&format_ctx->pb, config.server.c_str(),
                                    AVIO_FLAG_WRITE, nullptr, nullptr);
        if (avopen_ret < 0)
        {
            fprintf(stderr, "failed to open stream output context, stream will not work\n");
            return 1;
        }
        rtmp_server_conn = true;
    }

    //use selected codec
    AVCodecID codec_id = AV_CODEC_ID_H264;
    out_codec = avcodec_find_encoder(codec_id);
    if (!(out_codec))
    {
        fprintf(stderr, "Could not find encoder for '%s'\n",
                avcodec_get_name(codec_id));
        return 1;
    }

    out_stream = avformat_new_stream(format_ctx, out_codec);
    if (!out_stream)
    {
        fprintf(stderr, "Could not allocate stream\n");
        return 1;
    }

    out_codec_ctx = avcodec_alloc_context3(out_codec);

    if (RTMP::Encoder::set_options_and_open_encoder(format_ctx,
                                                   out_stream,
                                                   out_codec_ctx,
                                                   out_codec, 
                                                   config.profile,
                                                   config.dst_width,
                                                   config.dst_height,
                                                   config.fps,
                                                   config.bitrate,
                                                   codec_id))
    {
        return 1;
    }

    out_stream->codecpar->extradata_size = out_codec_ctx->extradata_size;
    out_stream->codecpar->extradata = static_cast<uint8_t *>(av_mallocz(out_codec_ctx->extradata_size));
    memcpy(out_stream->codecpar->extradata, out_codec_ctx->extradata, out_codec_ctx->extradata_size);

    av_dump_format(format_ctx, 0, config.server.c_str(), 1);

    picture.Init(out_codec_ctx->pix_fmt, config.dst_width, config.dst_height);
    scaler.Init(out_codec_ctx, config.src_width, config.src_height, config.dst_width, config.dst_height, SWS_BILINEAR);

    if (avformat_write_header(format_ctx, nullptr) < 0)
    {
        fprintf(stderr, "Could not write header!\n");
        return 1;
    }

    printf("stream time base = %d / %d \n", out_stream->time_base.num, out_stream->time_base.den);

    inv_stream_timebase = (double)out_stream->time_base.den / (double)out_stream->time_base.num;

    init_ok = true;
    return 0;
}