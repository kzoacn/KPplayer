# KPplayer

## Requirements

[ffmpeg](https://ffmpeg.org/)


[streamlink](https://github.com/streamlink/streamlink), plz use the latest version


## Compile

``` bash
sudo apt-get install libglib2.0-dev libfftw3-dev
sudo apt-get install git ffmpeg x264 mplayer


git clone https://github.com/kzoacn/KPplayer
cd KPplayer
make

#Encode

ffmpeg -i input.flv -f rawvideo - | ./kpenc -s 1000x562 -q 6 --qmin 1 --qmax 4 |x264 --input-res 1000x562 --profile high --level 5.1 --tune stillimage --crf 22 --colormatrix bt709 --me dia --merange 0 -o output.mkv -

#Decode

ffmpeg -i output.flv -f rawvideo - | ./kpdec -s 1000x562 -q 6 --qmin 1 --qmax 4 | mplayer - -demuxer rawvideo -rawvideo w=1000:h=562

#Push stream

ffmpeg  -re -i output.flv -c:v libx264  -f flv  "rtmp://0.0.0.0"

#Pull stream

streamlink <url> best -O | ffmpeg -i - -f rawvideo - | ./kpdec -s 1000x562 -q 6 --qmin 1 --qmax 4 | mplayer - -demuxer rawvideo -rawvideo w=1000:h=562

# choose your resolution !!!!
# choose your resolution !!!!
# choose your resolution !!!!

```

## Usage

## Acknowledgement

[lvdo](https://github.com/m13253/lvdo)
