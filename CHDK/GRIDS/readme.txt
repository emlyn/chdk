Format of grid file for CHDK:

@title <text to show in menu>
@line   x0, y0, x1, y1, lineColor
@rect   x0, y0, x1, y1, borderColor
@rectf  x0, y0, x1, y1, borderColor, fillColor
@elps   x0, y0, rx, ry, borderColor
@elpsf  x0, y0, rx, ry, fillColor

All numbers can be either decimal or hex.

Find more grids here: http://chdk.wikia.com/wiki/Grids


Included are some sample Grid files, these are:

3to2grid.grd
  Match your EVF/LCD display to a 3:2 crop-ratio for prints matching that ratio, 6" x 4" prints.
  
3to8grid.grd
  <i>(Usage Unknown, I'm not sure why this one was included, perhaps someone else can clarify?)</i>
  
golden1.grd
  Compose your subject placement in accordance with the "Golden Ratio". A composition ratio deemed most pleasing to the human-eye. This version is based on "golden-triangles". Place your subject where the two lines meet or aligned along their axes. (This grid may be used in reflections and flips, affording 3 more locations, do it mentally, or edit the grid file to reflect all 4 golden-triangle intersections.)
  
golden2.grd
  Same as above, but showing you one more of the 4 total intersection/alignment possibilities.
  
id.grd
  This grid is based on ISO/IEC 19794-5:2005 values required for administrative identity photo (passports, identity cards, driving licence...). A large red face shape represent the maximum size accepted, whereas the smaller green shape is the minimal size allowed. A grey area represent where eyes have to be. A vertical axis and two horizontal rulers should help for positioning the subject. The picture afterwards has to be resized to 35 x 45 mm before being printed. The best is to make a composition of 6 (2 lines, 3 rows) photo on a 10 x 13 cm format or 8 (2 lines, 4 rows) photo on a 10x15 format. The reprint should be done by a professional, not by your personnal printer...otherwise it might be refused by the administration staff.
  
rulecross.grd
  Fashioned after some aerial-photography and photomicrography grids. Horizontal and vertical rulers bisecting your FOV. Divided horizontally in 4 units of measure and vertically in 3 units of measure. With half and 1/10th unit tic-marks. Small crosshairs in the open areas at 1/2 and 1-unit intervals. May be extremely handy for macro-photography when trying to keep the subject size the same in landscape or portrait orientations. Or when comparing subject size to one another when reframing or refocusing.
  
rulers.grd
  As above, but without the crosshairs in the clear areas.
  
sports.grd
  A "Sports Finder" grid. This grid was designed around the available image sizes of an "S3 IS" camera. When shooting in highest resolution of "L", 2816 x 2112 pixels, this grid displays the cropping areas as if you were using the "M1" - 2271 x 1704 pixels, the "M2" - 1600 x 1200 pixels, and the "S" - 640 x 480 pixel image sizes. This way you can view the full-frame in the viewfinder, but plan ahead for cropping to one of the other available resolutions. You can then watch for any activity outside of those image-resolution boundaries and be better able to follow any fast action in your viewfinder that might be entering or leaving the final-crop image area. One more pair of lines was included to show the "W" - 2816 x 1584 wide-angle FOV so when planning to crop for that resolution you can still watch for activity above and below your final image area, instead of just blacking out those areas as the camera normally does. It is worth noting, that even a 1600 x 1200 resolution image will still print quite nicely even at 7"x5" print size. For that little-league game this might be just the thing you need for following the action and still having photos to print out for relatives and friends.
  
stolen.grd
  Load this grid before putting your camera down and you don't want anyone else to use it. When turning on your camera only the words "STOLEN CAMERA!" will show in the display. The view blacked-out, making subject viewing/framing useless. Unless they know how to turn off CHDK features. :) This is part of an experiment on using CHDK as a theft-deterent. Using this grid combined with an auto-running script file which flashes all your LED lights and triggers all the warning-beep sound-events in your camera, it might be a quite effective way to see/hear if someone is picking up your camera and turning it on without your permission, as well as rendering the camera useless to anyone without CHDK knowledge.
  
third_h.grd
  Divides your FOV into 3rds horizontally. Based on the "Rule of Thirds" composition concept. (A simplified version of the "Golden Ratio" concept.)
  
third_v.grd
  As above but dividing your FOV into 3rds vertically.