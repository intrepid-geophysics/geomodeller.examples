Reflective Seismic examples Geomodeller -Readme
The examples presented in this directory represent preliminary
methods to take ship track 2D seismic tracks, that have both navigation
and depth converted picks, exported in ASCII, from a tool such as GeoFrame.
The "ddf" files are the data description files, that help our parsers
assign the correct field names and types to all the channels.
The navigation import process creates Intrepid databases, that are also
used to support long sections within the Geomodeller project.
The second stage import of all the seicmic picks, appends extra fields
at each shot-point, to create the layers.
For intersecting seimic lines, a true 3D foliation for the formations
can be calculated from the seimic data. Otherwise, an apparent dip,
which represents the in-section gradients, can be used by the co-krigging engine
to constrain the 3D model interpoation.
As the ASCII pick files are huge, we do not routinely ship these with the examples.
However, this Capel Faust project is Open File, with compliments of Geoscience Australia,
and can be down-loaded from the GA site, or via Intrepid Geophysics.

Marine gravity data was also used in this project to identify the new basins,
and to also estimate the basin thicknesses.