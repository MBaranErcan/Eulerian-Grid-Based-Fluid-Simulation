# Eulerian Grid-Based Fluid Simulation

This project implements a 2D Eulerian grid-based fluid simulation using Computational Fluid Dynamics (CFD) techniques.

The simulation includes key components such as diffusion, advection, and projection to solve the Navier-Stokes equations for incompressible fluid flow.


![demo](https://github.com/user-attachments/assets/fbd215e9-9994-4f12-89e9-bfddd53d346c)


---

## Features

### Right Mouse Button + Drag:

Adds fluid (density) to the simulation.

While holding down the right mouse button and dragging across the window, you increase the fluid density at the cursor's position. This simulates introducing more fluid into the simulation, affecting how the fluid behaves.


### Left Mouse Button + Drag:

Adds velocity to the fluid.

Holding down the left mouse button and dragging across the window applies a velocity to the fluid at the cursor's position. This changes the direction and speed of the fluid, affecting how it moves through the simulation.


### Middle Mouse Button: Adds a density source.

Clicking the middle mouse button places a density source in the simulation. This acts as a point where fluid density is continuously added, creating localized regions of high density.


### 'R' Key:

Resets velocity, fluid density, and sources.

Pressing the 'R' key resets the simulation by clearing the velocity field, fluid density, and any density sources. This returns the simulation to its initial state, allowing you to start fresh.


---
•	Boundary Conditions: Handles boundary conditions for velocity and scalar fields.

•	Diffusion: Simulates the spreading of substances within the fluid using Gauss-Seidel relaxation.

•	Advection: Transports quantities like velocity and density through the fluid.

•	Projection: Ensures the velocity field is divergence-free, maintaining incompressibility.
