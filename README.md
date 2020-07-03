# Imager

A simple program to work with images


## How to compile

You would need git, cmake, g++(gcc).

1. Clone the repo to get source code

```
git clone https://github.com/VMaksimN/imager.git
```

2. Run cmake

```
cmake -S [path to source] -B [path to build directory]
```

3. Go to the build directory you specified in the previous step and run

```
make
```

3. You should now have an executable `imager` in the build directory


## How to use

You can run the program in two ways:

1. TO do it with command line arguments run:

```
imager image1.ext image2.ext image3.ext ...
```

where imageN is a path to your photo, .ext means .jpg or .png 

2. To start the program without arguments:

```
imager
```

	
