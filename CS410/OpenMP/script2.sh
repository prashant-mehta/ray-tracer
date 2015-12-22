#!/bin/bash
set -o verbose
for i in `seq 1 8`;
do
export OMP_NUM_THREADS=$i;
time ./Debug/OpenMP ../camera/spheres_better_camera.txt ../material/red_sphere_material.txt ../ply/sphere.ply output/red_spheres_output.ppm
done

