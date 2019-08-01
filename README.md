# Bat BSP

A solution to the Base Station Positioning problem using the Bat Optimization Algorithm

## How to run the code
- run `g++ make.cpp -o make.exe`
- run `make.exe`
- run `bat-bsp.exe`

In case files are added, adjust the system command in make.cpp and run the above commands again

## Changing the map
Changes to the map should be made in the /src/main.cpp file
- To change the starting map, modify the hexagons added to the region map in the initMap function
- To change the map's size, modify the T_MAX constant
- To change the coverage area of each station, modify the STATION_RADIUS constant
- To change the area of the city's districts, modify the HEXAGON_RADIUS constant
- To change the amount of base stations to be put on the map, modify the STATION_COUNT constant

## Results
- The current best result will be printed on screen with its Iteration count, the best bat's solution and its fitness
- Plots will be created in the /plots/ folder
- An example of the initial situation of the given map will be created in /plots/example.txt
- An option to convert the generated .txt plots to .bmp is [this site](https://www.dcode.fr/binary-image)