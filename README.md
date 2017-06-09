# VGA API for the ARM STM32F4

This API allows the user to post the following items on a VGA display:

### shapes
* Line
* Rectangle
* Triangle
* Ellipse

### Other features
* Display text      
*[multiple fonts, bold, italic, full ASCI]*
* Display bitmaps   
*[basic bitmaps are included in API]*
* Clear screen

### Demo
The API comes with a demo code. The code will execute all the function of the API through commands over the UART. Commands of the UART are build by the following way:

* Line ```[x1, y1, x2, y2, weight, color]```
* Ellipse ```[x-mp, y-mp, radius-x, radius-y, color]```
* Rechthoek  ```[x-lo, y-lo, x-rb, y-rb, color]```
* Tekst  ```[x, y, text, font name, color, style <italic/bold/normal>]```
* Bitmap ```[<arrow<left/right/up/down>>, smiley<happy/angry>]```
* Clearscherm ```[color]```

__!Commands are in Dutch__

### More Info
For more information see the [doxygen](https://gruifin.github.io/SD_HU_3/) documentation.

### afterword
This code was developed by Ludo Teirlinck, Wilmar van Dijk and Jasper de Zoete commissioned by the University of Applied Sciences of Utrecht. The code is published under the GNU license. You can use this code as you like. But we do not bear any responsibility for it.
