Meshing from Geomodeller -Readme
The examples presented in this directory represent preliminary
meshing products, done quickly, at a coarse resolution.
The reason this is done is to keep the size of the meshes down, and also ensure that
the automatic testing system, which produces these examples, can continue to do so routinely.
The meshes produced here take less than 5 minutes to produce on standard/generic hardware.
If your requirement is for much high accuracy and precision, you can expect to take longer
and to also produce a much bigger mesh file. Please see the notes on all the tuning paramaters
as to how to achieve this other outcome. 
Water-tight, unstructured and manifold should always be achieved with this technology.
mesh formats are interchangeable.
The VTK format is the most complete, as it is extensible and well documtnted, and a binary format.
The seperate file produced for faults, is also part of the deliverables in that case.
The "medit" format allows a free viewer to test/show the meshes.
the "gmod" format is a special for FEFLOW interchangeability.
