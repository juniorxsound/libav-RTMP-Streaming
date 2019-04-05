#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

namespace RTMP
{
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
} // namespace RTMP

#endif