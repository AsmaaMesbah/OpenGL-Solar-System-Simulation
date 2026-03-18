# OpenGL Solar System Simulation

![Solar System Demo](img/demo.gif)

## Project Overview 
A 3D simulation of the solar system using OpenGL, where each planet orbits the sun and rotates about its own axis. The motion is based on ratios derived from NASA data, with some simplifications applied for practicality and performance.

The simulation includes basic controls such as zoom in, zoom out, pause, and exit. 

## Technologies Used
- C
- OpenGL
- FreeGLUT

## Notes
- This project requires `freeglut.dll` to run.
- The executable is provided for convenience.

## How to Run 
1. Clone the repository 
```
git clone https://github.com/AsmaaMesbah/OpenGL-Solar-System-Simulation.git
```
2. Navigate to OpenGL-Solar-System-Simulation/build directory 
```
cd ./OpenGL-Solar-System-Simulation/build
```
3. Run the executable file: Double-click the solar.exe file
```
./solar.exe
```
## How to Build 
### MSYS2 MINGW64 Users
1. Install the freeglut package 
```
pacman -S mingw-w64-x86_64-freeglut
```
2. Navigate to your desired directory
3. Clone the repository
```
git clone https://github.com/AsmaaMesbah/OpenGL-Solar-System-Simulation.git
```
4. Navigate to OpenGL-Solar-System-Simulation/src directory
```
cd "OpenGL-Solar-System-Simulation/src"
```
5. Compile using GCC 
```
gcc solar.c -o solar.exe -lfreeglut -lopengl32 -lglu32
```

## Computations
Using real-life ratios to do this simulation would've been difficult; therefore, the calculations were simplified as follows: 
* **Radii of the sun and the planets**:  
  - The radius of the sun was set to 1.0
  - Earth's radius was set to half the radius of the sun.
  - Planets from Mercury to Mars: 
  real-life ratios to Earth were used.
  - Planets from Jupiter to Neptune:
  Using real-life ratios wasn't feasible. Therefore, taking into account their relative sizes, suitable values were assigned to each planet's radius.

* **Distance from the sun (orbit radius)**  
The real-life values were too big; therefore, values that are suitable for the simulation were assigned. Moreover, because of the asteroid belt, the distance between Mars and Jupiter was greater in real life than the average distance between other planets. This was accounted for in the simulation by assigning 3 units to the distance between Mars and Jupiter and 2 units elsewhere.

* **Orbiting (rotation around the sun)**  
The orbital speed of each planet was determined using NASA data relative to Earth's orbital speed.

* **Spinning (rotation about the planet's axis)**  
The spinning speed of each planet was determined using NASA data on rotation periods relative to Earth.

## Example Execution 
### Controls
- Zoom in: [+] or [=]
- Zoom out: [-] or [_]
- Pause: [space]
- Exit: [esc]

### Screenshots
<img width="1920" height="903" alt="Screenshot (14)" src="https://github.com/user-attachments/assets/cc601fbb-8bb5-4a17-8d16-5f8e57b6a214" />

<img width="1920" height="913" alt="Screenshot (16)" src="https://github.com/user-attachments/assets/d76f4a70-2e67-4a09-b677-5beeefbaaafb" />

<img width="1920" height="913" alt="Screenshot (17)" src="https://github.com/user-attachments/assets/a791df04-fb51-4790-8a32-4ad60f862a40" />

## References
- [Planetary Fact Sheet](https://faculty.kfupm.edu.sa/PHYS/alshukri/Planetary_Fact_Sheet_2pages.htm)
- [Solar Textures](https://www.solarsystemscope.com/textures/)
