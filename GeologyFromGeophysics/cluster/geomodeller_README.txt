The task files below are intended for the demonstration of the Intrepid Cluster, vfilt and cfilter Tools.

	landers_earthquake_clustering.task
	tensor_2D_region_clustering.task
	ForwardModelFFT_GravityTensors.task

The first example reduces the 3D seismic location point cloud to around 40 fault planes
that best fit the data. The anisotrophy of the local point cloud clusters,
is used to find best fit planes. The Planes are then described by an extent, a mid-point 
and the stike/dip vector. 
The point cloud data has been previously imported to the "datasets\landers..." database.
Note, this example is tuned to work in geodetic spatial coordinates and depth expressed in kilometers.

The demonstrations can be run in the following ways
.............................................................
A.  For any GeomodellerBatch task
In the navigator view, find the task file you wish to run.
Highlight it.
Find the Run process icon ( green circle with an white arrow)
Choose run configuration, with task still highlighted.
Find the Top left hand Icon, with a blank piece of paper and a plus sign
Name your task
Confirm the task file path
choose the directory you wnat to run the process in.
Apply - this saves the run configuration for repeats.
Run - observe the console window for progress reports.
...............................................................
B.
1.  Launch GeoModeller and open any GeoModeller project
2.  Open a shell window using the Geophysics/3D geophysics/Shell Window
3.  Navigate to the directory containing the task files
4.  Run cluster -batch <taskfile>

Graphical feedback is provided when running these demonstrations.  The user needs to close the graphical window repeatedly
to step through the results.

The outputs directory contains a sample GOCAD format sgrid, after a stoichastic inversion. This is a usefull resource
to demonstrate Forward modelling for Gravity and other geophysics signals