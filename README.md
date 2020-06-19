# Imager

A simple program to calculate the projective cover of grass or foliage projective cover by a photo.

## How to use

Take a photo of the ground (or the sky), positioning your camera parallel to the ground, so that it would see the ground (or the sky) at a 90 degrees angle.

Supply the image to the program. You can either use the intercative mode or pass it as a command line argument. To pass the photo as a command line argument run the program as following:

```
imager image1.jpg image2.jpg image3.jpg ...
```

where imageN is a path to your photo.

To start the program in intercative mode pass no arguments:

```
imager
```

## How to compile

1. Run cmake:

```
cmake -S [path to source] -B [path to build directory]
```

2. Go to the build directory you specified in the previous step and run:

```
make
```

3. You should now have an executable `imager` in the build directory
