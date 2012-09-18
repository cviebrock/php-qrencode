# php-qrencode

PHP qrencode extension, binding to [libqrencode](https://github.com/fukuchi/libqrencode).

This PHP extension is essentially the work found at http://hirokawa.netflowers.jp/entry/4900/ (I can not find the author's name).

That site doesn't seem to exist anymore, so I am putting the code here for the benefit of everyone. I've also made some improvements (see CHANGELOG.md for details).

C programming is not my forté, so if you have any suggested improvements, please fork and send a pull request.


## Building

First, you need to compile and install [libqrencode](https://github.com/fukuchi/libqrencode).
Please see that package's README for instructions.

Then, compile php-qrencode:

```
cd ../php-qrencode
phpize
./configure
make
sudo make install
```

Finally, add the following to the end of your `php.ini` file:

```
extension=qrencode.so
```

## Usage

```php
array qrencode( string $data, int $ecc, int $version, int $mode );
```

`$data` is the information to encode in the QR Code (e.g. URL, vCard, phone number, etc.).

`$ecc` is one of the error correction level constants defined below.

`$version` (integer in the range 1-40) defines the overall block size of the generated image (block size = (version * 4) + 17).  If you pass in more data than can fit in the requested size, the function will increase the size as required so this, in effect, defines the _minimum_ size of the resulting QR Code.

`$mode` is one of the storage modes defined below.

The returned two-dimensional array defines the on/off state for each pixel "block" in the resulting QR code.

To turn this data into an image, you will need to use GD functions, and loop through the array, building the image as you go.  e.g.:

```php
$data = qrencode( 'Hello world!', QR_ECLEVEL_L, 1, QR_MODE_8 );

$size = count( $data );
$im = imagecreate( $size, $size );

$color_bg = imagecolorallocate( $im, 255, 255, 255 );
$color_fg = imagecolorallocate( $im, 0, 0, 0 );

imagefill( $im, 0, 0, $color_bg );

for( $y = 0; $y < $size; $y++ ) {
	for( $x = 0; $x < $size; $x++ ) {
		if ( $data[$y][$x] ) {
			imagesetpixel( $im, $x, $y, $color_fg );
		}
	}
}

imagepng( $im );
```


## PHP Constants

### Storage Modes

- `QR_MODE_NUM` - numeric only, max. 7,089 characters, 0-9

- `QR_MODE_AN` - alphanumeric, max. 4,296 characters, 0-9, A-Z (uppercase only), space, $, %, *, +, -, ., /, :

- `QR_MODE_8` - binary/byte, max. 2,953 characters (8-bit bytes) or 23624 bits

- `QR_MODE_KANJI` - Kanji/Kana, max. 1,817 characters

### Error Correction Levels

- `QR_ECLEVEL_L` - Low (approximately 7% of codewords can be restored)

- `QR_ECLEVEL_M` - Medium (15%)

- `QR_ECLEVEL_Q` - Quartile (25%)

- `QR_ECLEVEL_H` - High (30%)


-----

"QR Code" is a registered trademark of Denso Wave Incorporated.