*This project has been created as part of the 42 curriculum by dthoo*  

## FdF

### Description  
  
This project takes a bitmap and displays it as a 3d wireframe in isometric projection.  
  
Bonus features include:  
- rotation  
- zoom  
- translation  
- changing to perspective projection  
- using multiple inputs at once (subject to user hardware)  
- changing colour where no colour is specified  
  
### Instructions  

A copy of minilibx is included in this folder.
It runs on linux. A different version is available for mac.
It does not run on windows, sadly.
  
Compilation:  
```
make
```
Bonus compilation:
```
make bonus
```

To run:
```
./fdf [.fdf file]
./fdf_bonus [.fdf file] [-p (optional bonus flag)]
```
  
Rotation controls (bonus feature):  
- q/e: yaw  
- w/s: pitch  
- a/d: roll  
- mouse wheel: zoom  
- arrow keys: translate  
- r, g, b: toggle colour bits  
  
### Overview of the project

The .fdf files are bitmaps represented by points.
Their values denote their elevation level, their longitude and latitude are as appears in the file.

My program parses this and uses the xiaolin wu algorithm to draw lines between said points.
A colour argument taking the form of:
```
[elevation],[colour in hex]
```
is accepted for each point.
The bresenham algorithm is used for these points.
  
### Resources  
  
[An introductory perspective on 3d graphics for those trying out this project](https://youtu.be/qjWkNZ0SXfo)  
This shows that trigonometry is all that stands between 2d and 3d projection. Of course, as the project demands an  
orthographic projection, we will not be dividing by z just yet.  
  
[The formulas for said trigonometry](https://en.wikipedia.org/wiki/Euler_angles)  
...but I dont understand math-  
[really good explanation pt1](https://medium.com/@sepideh.92sh/part-i-how-robots-understand-space-kinematics-and-the-power-of-rotation-matrices-6b2ba5bc07be)  
[really good explanation pt2](https://medium.com/@sepideh.92sh/part-ii-inside-rotation-matrices-axes-frames-and-coordinate-transformations-f6d0810a804a)  
[really good explanation pt3](https://medium.com/@sepideh.92sh/part-iii-composing-rotations-euler-angles-and-roll-pitch-yaw-38aa816a5bcd)  
[even simpler matrix usage](https://youtu.be/XkY2DOUCWMU) << this shows what order to apply the matrix: in the opposite order I had imagined.  
  
The above showcases how to use matrix formulas, from plugging them in to deriving them yourself. I personally wanted to go for zyx, but ended up with  
xyz due to my code implementation. That works well enough.  
  
[xiaolin wu anti aliasing](https://youtu.be/f3Rs20k-hcI)  
[bresenham algo](https://youtu.be/CceepU1vIKo)  
[mlx usage guide](https://www.canva.com/design/DAGT6G8aJHY/fqork5u1hxZONk8a4WQtdQ/view#1)  
  
The above mlx guide leaves out a few details:  
- function prototypes for other hook handlers  
- there needing to be only one handler per unique mask and/or event  
- configuration for keyrelease hook handler  
- the fact that I needed a loop hook handler  
- if first two digits in 0x00RRGGBB are not empty, I will be bitten in the rear end  
- using mlx-clear-img  
  
Perplexity got me those details and my perspective formula: apparently anything can be a perspective scalar if you scale it with the right component.
