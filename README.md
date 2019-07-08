<div align="center">
<h1>libav RTMP streaming 📽</h1>
<img src="https://i.imgur.com/W1TmWTM.gif" /><br>
 A C++ app that streams a video to an RTMP endpoint using libav<br>
 <a href="#getting-started">Getting Started</a> • <a href="#shoutouts">Shoutouts</a>
</div>

# Getting Started
> To run the app you would need Docker and make - [Docker installation guide](https://docs.docker.com/v17.12/install/)
1. Clone or download the repo `git clone https://github.com/juniorxsound/libav-RTMP-Streaming.git`
2. Place an mp4 file you would like to stream in `samples/` folder
3. Create a `build` folder inside the root directory
4. From within the root directory run `make build` to create the Docker container
5. Open `main.cpp` and change the video file name and RTMP server address in line 12
```cpp
Streamer streamer("samples/your_video_test_file.mp4", "rtmp://your_rtmp_streaming_endpoint");
```
6. Run `make run` and if everything goes smooth, you should be live streaming your video file to the RTMP server ✨

# Shoutouts
Thank you [@kodabb](https://github.com/kodabb) for helping me get started with using *libav* and to [@leandromoreira](https://github.com/leandromoreira/) for posting helpful getting started tutorials and a Docker image (used in this repo).
