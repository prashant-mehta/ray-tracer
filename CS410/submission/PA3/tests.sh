#!/bin/bash
for i in $(seq 1 5); do
./PA3 tests/airplane_camera.txt tests/airplane_materials_1.txt tests/airplane.ply output/airplane_1_$i.pgm
./PA3 tests/airplane_camera.txt tests/airplane_materials_2.txt tests/airplane.ply output/airplane_2_$i.pgm
./PA3 tests/airplane_camera.txt tests/airplane_materials_3.txt tests/airplane.ply output/airplane_3_$i.pgm
./PA3 tests/apple_camera.txt tests/apple_materials_1.txt tests/scaled_apple.ply output/apple_1_$i.pgm
./PA3 tests/apple_camera.txt tests/apple_materials_2.txt tests/scaled_apple.ply output/apple_2_$i.pgm
done

