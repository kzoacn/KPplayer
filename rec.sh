streamlink https://live.bilibili.com/705722 soualt2 -O | ffmpeg -i - -r 30 -f rawvideo - | ./kpdec -s 640x480 -q 6 --qmin 1 --qmax 4

