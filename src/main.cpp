
#include <iostream>
#include <chrono>

#include "streamer.h"
#include "scaler.h"
#include "picture.h"
#include "config.h"
#include "encoder.h"

using namespace std;
using namespace RTMP;

#define VIMEO_LIVE_RTMP_ENDPOINT "rtmp://rtmp-global.cloud.vimeo.com/live"

int main()
{
    cout << endl
         << "Welcome to RTMP streamer 📽" << endl
         << "Written by @juniorxsound <https://orfleisher.com>" << endl
         << endl;

    Streamer streamer;
    // streamer.enable_av_debug_log();

    Config stream_config(640, 360,
                         640, 360,
                         30, 50000, "high444", (string)VIMEO_LIVE_RTMP_ENDPOINT + "/stream-key");

    streamer.Init(stream_config);

    return 0;
}