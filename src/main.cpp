
#include <iostream>
#include <chrono>

#include "streamer.h"
#include "scaler.h"
#include "picture.h"
#include "config.h"
#include "encoder.h"

using namespace std;
using namespace RTMP;

int main()
{
    cout << endl << "Welcome to RTMP streamer 📽" << endl << "Written by @juniorxsound <https://orfleisher.com>" << endl << endl;
    
    Streamer streamer;
    streamer.enable_av_debug_log();

    return 0;
}