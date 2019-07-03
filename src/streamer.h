#ifndef _STREAMER_H_
#define _STREAMER_H_

// Import STD
#include <iostream>
#include <chrono>

// Import LibAV
extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/mathematics.h>
#include <libavutil/time.h>
};

class Streamer
{
public:
  Streamer(const char *videoFileName,
           const char *rtmpServerAdress);
  ~Streamer();
  int Stream();

  AVOutputFormat *ofmt = NULL;
  AVFormatContext *ifmt_ctx = NULL;
  AVFormatContext *ofmt_ctx = NULL;
  AVPacket pkt;

private:
  int setupInput(const char *videoFileName);
  int setupOutput(const char *rtmpServerAdress);

  int ret;

  // Input file and RTMP server address
  const char *videoFileName;
  const char *rtmpServerAdress;

protected:
  int videoIndex = -1;
  int frameIndex = 0;
  int64_t startTime = 0;
};
#endif