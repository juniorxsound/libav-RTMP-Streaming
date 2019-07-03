clean:
	rm -rf ./build/*

build: clean
	docker run -w /files --rm -it  -v `pwd`:/files leandromoreira/ffmpeg-devel \
	  g++ -std=c++11 -L/files/src -L/opt/ffmpeg/lib -I/opt/ffmpeg/include/ /files/src/streamer.cpp /files/src/main.cpp \
	  -lavcodec -lavformat -lavfilter -lavdevice -lswresample -lswscale -lavutil \
	  -o /files/build/streamer

run: build
	docker run -w /files --rm -it -v `pwd`:/files leandromoreira/ffmpeg-devel /files/build/streamer 