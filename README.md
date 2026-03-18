# OpenGL-Solar-System-Simulation

## Project Overview 
A 3d simulation of the solar system using OpenGL, where each planet orbits around the sun and rotates about its axis, with ratios calculated based on the NASA statistics - some modifications were applied for simplicity and limitations. The simulation also includes basic controls: zoom in, zoom out, pause, and exit. 

## How to Run 
1. Clone the repository 
```
git clone https://github.com/AsmaaMesbah/OpenGL-Solar-System-Simulation.git
```
2. Navigate to OpenGL-Solar-System-Simulation/build directory 
```
cd "OpenGL-Solar-System-Simulation/build"
```
3. Run the executable file 
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
2. Navigate to OpenGL-Solar-System-Simulation/src directory
```
cd "OpenGL-Solar-System-Simulation/src"
```
3. Compile using GCC 
```
gcc solar.c -o solar.exe -lfreeglut -lopengl32 -lglu32
```

## Computations
Using real-life ratios to do this simulation would've been difficult; therefore, the calculations were simplified as follows: 
* **Radii of the sun and the planets**:  
  - The radius of the sun was set to 1.0
  - Earth's radius was set to $\frac{1}{2} \times radius$ of the sun
  - Planets from Mercury to Mars: 
  real-life ratios to Earth were used.
  - Planets from Jupiter to Neptune:
  using real-life ratios wasn't possible. Therefore, taking into account their relative sizes, suitable values were assigned to each planet's radius.

* **Distance from the sun (orbit radius)**  
The real-life values were too big; therefore, values that are suitable for the simulation were assigned. Moreover, because of the asteroid belt, the distance between Mars and Jupiter was greater in real life than the average distance between other planets. This was accounted for in the simulation by assigning 3 units to the distance between Mars and Jupiter and 2 units elsewhere.

* **Orbiting (rotation around the sun)**  
The speed of each planet's orbiting was set based on data obtained from NASA about the orbital speed ratio relative to that of the Earth.

* **Spinning (rotation about the planet's axis)**  
Data from NASA on the rotation period of each planet relative to Earth was used to determine the spinning speed of each planet.

## Example Execution 
<img width="1479" height="227" alt="Screenshot 2026-03-18 221236" src="https://github.com/user-attachments/assets/3488edb2-07d5-4bad-bd09-4d6286a527c5" />

<img width="1920" height="903" alt="Screenshot (14)" src="https://github.com/user-attachments/assets/cc601fbb-8bb5-4a17-8d16-5f8e57b6a214" />

<img width="1920" height="913" alt="Screenshot (16)" src="https://github.com/user-attachments/assets/d76f4a70-2e67-4a09-b677-5beeefbaaafb" />

<img width="1920" height="913" alt="Screenshot (17)" src="https://github.com/user-attachments/assets/a791df04-fb51-4790-8a32-4ad60f862a40" />

## References
- [Planetary Fact Sheet](https://faculty.kfupm.edu.sa/PHYS/alshukri/Planetary_Fact_Sheet_2pages.htm)
- [Solar Textures](https://www.solarsystemscope.com/textures/)
