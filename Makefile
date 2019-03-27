clean:
	rm -rf ./build/*

build: clean
	docker run -w /files --rm -it  -v `pwd`:/files leandromoreira/ffmpeg-devel \
	  g++ -L/opt/ffmpeg/lib -I/opt/ffmpeg/include/ /files/src/main.cpp \
	  -lavcodec -lavformat -lavfilter -lavdevice -lswresample -lswscale -lavutil \
	  -o /files/build/hello

run_hello: make_hello
	docker run -w /files --rm -it -v `pwd`:/files leandromoreira/ffmpeg-devel /files/build/hello /files/small_bunny_1080p_60fps.mp4

make_remuxing: clean
	docker run -w /files --rm -it  -v `pwd`:/files leandromoreira/ffmpeg-devel \
	  gcc -L/opt/ffmpeg/lib -I/opt/ffmpeg/include/ /files/2_remuxing.c \
	  -lavcodec -lavformat -lavfilter -lavdevice -lswresample -lswscale -lavutil \
	  -o /files/build/remuxing