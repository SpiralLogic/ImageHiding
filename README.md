---------------------------------------------------------------------
 <p align="center">
                                Hide/Unhide<br>
                          	 Image Steganography
     </p>            <p align="center">             
                             by Solomon Jennings
</p>

---------------------------------------------------------------------

### INTRODUCTION:

This following set of tools written in C for linux that allows for the hiding of
a message within images.

Currently supported images are:
* Standard Binary PPM
* 24 bit BMPs

To try for yourself after compiling:

<pre>
printf "This is a hidden message!" | ./hide images/cross.pbm output.ppm
./unhide output.ppm
</pre>

### COMPILING:
GCC is used to compile and compilation should be supported up until C99
The program can be complied in the following ways:

Requires the SDL2 Library to compile

make clean			  	- cleans any previous compilation and removes any output files<br>

make all  				- makes both hide and unhide<br>
make hide 				- makes hide only<br>
make unhide 			- makes unhide only<br>

make alldebug 			- makes both hide and unhide with debug output<br>
make hidedebug  		- makes hide with debug output<br>
make unhidedebug 		- makes unhide with debug output<br>

## HIDING:

#### To hide a message within a image:

<code>./hide imagename outputfilename</code>

Example:
<code>./hide example.ppm output.ppm</code>

The end of the message is marked up a EOF character. This can be enter into the terminal by pressing ctrl+D
sometimes it takes a couple of ctrl+Ds to work.

#### To hide a message and show the before and after image:
<code>./hide -s imagename outputfilename</code>

Example:
<code>./hide -s example.ppm output.ppm</code>

To close the image when complete either click the X or push any key on the display window

#### To hide a message in multiple images:
<code>./hide -m numimages basename outputbase</code>

Example:
<code>./hide -m 5 images/example output/output</code>

This will hide the message across 5 ppm images from the input directory starting from images/example-000.ppm to
images/example-004.ppm

#### To hide a message in parallel:
<code>./hide -p infofile</code>

Example:
<code>./hide -p multiimage.txt</code>

This will hide multi messages in parallel across multiple files
format for the txt file is :
text.txt image1.ppm output1.ppm
text2.txt image2.ppm output2.ppm

#### To hide a message in a directory of files
<code>./hide -d inputdirectory outputdirectory</code>

Example:
<code>./hide -d inputimages/ outputimages/</code>

This will hide a message in a directory of images. **WARNING** If an unsupported file is in the directory
it will cause an unsupported image error.
Both BMP and PPM are supported in this mode

## UNHIDING:

#### To unhide a message from an image:
<code>./unhide filename</code>

Example:
<code>./unhide output.ppm</code>

#### To unhide a message from multiple images:
<code>./unhide -m numfiles basename</code>

Example:
<code>./unhide -m 5 outputbase</code>

Note: If the message cannot fit in all of the images, it will store as much as it can into the images provided

#### To unhide a message into a directory of images
<code>./unhide -d directory</code>

Example:
<code>./unhide -d output/</code>


If the image does not contain a message then the output message may be garbled or not exist at all.

The output of the message will be start and end with a line of '########################'

SUPPORTED FUNCTIONALITY:
--

noswitch: Hide in one image<br>
-m: Hide in multiple images<br>
-s: Show before and after images<br>
-p: hide in images in parallel<br>
-d: hide message in a directory of images<br>


Both hiding and unhiding a message within both a 24Bit (255 depth) standard PPM image and 24 Bit BMP images.<br>
A BMP with an alpha channel or compression is not supported.

Any non malformed header for both image types is supported. This includes any number of
comments within the PPM format.

Implementation is file extension agnostic. Image types are dependent on the magic number of the file header.

Error detection is supported and should detect any incomplete image pixel map, incorrect headers, malformed headers and
message lengths which are too long.

Piping is supported. Example<br>
<code>printf "Test" | ./hide input.ppm output.ppm</code>

Example
--
<code>printf "This is a message\nhidden in a doge" | ./hide -s images/doge.ppm output.ppm
</code>
<pre>
Input secret message press ctrl+D 1-3 times when finished

Successfully hid message in output.ppm!
</pre>

<code>./unhide output.ppm</code>
<pre>
##################
This is a message
hidden in a doge
##################
</pre>


![image of comparison](https://github.com/srjen3/ImageHiding/raw/master/comparescreenshot.png)
