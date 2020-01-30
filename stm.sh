streamlink https://live.bilibili.com/705722 best -O | ffmpeg -i - -f rawvideo - | ./kpdec -s 1000x562 -q 6 --qmin 1 --qmax 4 | mplayer - -demuxer rawvideo -rawvideo w=1000:h=562
