#include "config.h"

RTMP::Config::Config()
{
    dst_width = 0;
    dst_height = 0;
    src_width = 0;
    src_height = 0;
    fps = 0;
    bitrate = 0;
}

RTMP::Config::Config(int source_width,
                     int source_height,
                     int stream_width,
                     int stream_height,
                     int stream_fps,
                     int stream_bitrate,
                     const std::string &stream_profile,
                     const std::string &stream_server)
{
    src_width = source_width;
    src_height = source_height;
    dst_width = stream_width;
    dst_height = stream_height;
    fps = stream_fps;
    bitrate = stream_bitrate;
    profile = stream_profile;
    server = stream_server;
}