ffmpeg.exe -i input.flv -f rawvideo - | kpenc.exe 1280x720   |  x264.exe --input-res 1280x720 --fps 30  --preset ultrafast -o tmp.mkv -

ffmpeg.exe -i input.flv -f mp3 tmp.mp3

ffmpeg.exe -i tmp.mp3 -i tmp.mkv output.flv