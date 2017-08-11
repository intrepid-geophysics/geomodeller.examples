Geotechnical examples Geomodeller -Readme
The examples presented in this directory represent preliminary
geological investigation work done, when the choice of a tunnel transit is under investigation.

The example is loosly based upon a realistic scenario around Paris.
Project extent is around 4.2 * 1.6 km
The engineering geology observations are reduced to a bare minimum, to still enable an approximation 
of realistic workflows. The project is geolocated to the NTF projected co-ordinate reference system,
and the ERMapper format DTM grid is at 10 metre cell size.

The shallow tunnel, is to proceed through many faulted compartment blocks, and the
predicted geology that the tunnel is to go through, can be easily perturbed for uncertainty.
The tunnel transit can also easily be changed. Typically, a tunnel design can be given to
Geomodeller project, via a dxf file, and the meshing is redone in Geomodeller, to make sure
all the geological important transitions are honoured in the DXF meshing, that can then be recovered
and viewed in the CAD design tool.
In this case, there are many faulted zones, with varying throws. To successfully create a 3D geology model
each fault compartment must have at least one set of observations of the contigous pile units.
The 40+ short boreholes give this control.
Workflow steps.
a. Build the 3D geology model from its raw observations and the pile - Run "TunnelExample_France.task"
b. Open the newly built 3D model in geomodeller - verify the boreholes were all used to build the model.
c. Inspect the long section, note the series of fault throws.
d. Import a design dxf file as a mesh grid.
e. Add the geology to this mesh  grid
f. export the meshGrid to a DXF, now with the newly added lithology field, and the re-triangulaed mesh walls.

**********************************
The second example is a Dolerite Dyke Intrusive, with a tunnel crossing through, and a large chamber planned to
co-incide with parts of the stronger rock type.