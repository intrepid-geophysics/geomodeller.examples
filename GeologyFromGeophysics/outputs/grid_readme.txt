Mesh Grid examples Geomodeller -Readme
The examples presented in this directory represent small
examples of some not so common Mesh Grid formats.

a. final.sg and the other files, are all associated with an sGrid,
or SemiRegular grid. It was genertated by the BetBet project, with the aim
of having a variable depth increment with depth.
b. Fully Unstructured meshes or tetrahedra, are over under the Meshing/outputs
and *.gmod,  an ASCII version for FEFLOW
 *.vtu, a VTK binary format ( Note basically all VTK data formats are now supported 
 as part of this upgrade).
 c. The internal MeshGrid format has a design closely modelled on VTK, but
 it uses the underlying Intrepid IO binary database drivers.