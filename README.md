# GeoModeller Examples (BETA)

Lots of simple examples of using the batch interface to GeoModeller.

## Getting Started

Once you have installed geomodeller, there are several ways to access the scripting language to run a repeatable process as captured in the "task" files from within an executing GeoModeller GUI session -
    
### Run Tasks From The GUI

In the Navigator view of GeoModeller, locate a task file you wish to launch, choose the right most green icon, with a white arrow, choose Run Configurations, choose the plus (+), add Name, choose a task, set the working directory, choose Apply. Or click right, and the Run Asoption is available. 

This is the standard toolkit support for launching processes from within GeoModeller, that is also used behind the scenes for long running tasks.

Interactive GUI Execution of any of the batch tasks is now also supported in the Navigator/ view of your projects. Once tasks are executing OK, check the output, by running geomodeller and opening the created project.
	
### Run Tasks In Batch

Alternatively, a CMD window can be opened, by navigating to geophysics>3DInversion>Create Command Window. This command window inherits all the path and environment variables required to execute the "geomodellerbatch" and "invbatch" etc tools. The PATH environment variable can be examined, and will show an entry something like

	C:\GeoModeller\GeoModeller4.0_x64_b8244e77c6a1\bin

You can also set up a reference to the same bin directory, by modifying your system parameters, so that you can launch a command window from your windows start menu you also need to run "geomodellerbatch" in this command shell, and verify that the executable and jvm.dll is in the "path"

Geology Run Instruction:  anything with geology modelling with the following command:
	
	geomodellerbatch name_ofprocess.task
	
Geophysics Run Instruction: anything to with geophysics modelling with the following command:

	invbatch name_ofprocess.task
	
There is cross over to the geophysics processing available within Intrepid using the same philosophy and approach

A lot more access to processing and auto-generating interpretions from geophysical datasets are accessible via this same protbuf messaging system.

## Create Task Files From An Existing Project

With V4.0, you can now convert any GeoModeller geology model back to its original sparse observations and the creation steps for defining the formations, faults and the geological pile.
File>Save batch script Options for refactoring your model, to eliminate any sections are also supported.

## API

The "GeoModeller" geology language is defined using GOOGLE protobuf formats  - see "gmtaskmodel.proto" - go to the bottom of this file for a summary of all function points in this API.
 
Some of the geophysics modelling language is defined using GOOGLE protobuf formats  - see "invtaskmodel.proto"

Any syntax errors will be reported down to line, column position by the GOOGLE parser depending upon the source of the required input data, as referenced in your task. The older C API has header files and some sample stub programs here.
GOOGLE publish tools for Python/Ruby/C++/Java bindings-


## Create Geology

Tutorial A is given again as a scripted set of processes for you to learn from. Other non-tutorial datasets/3D models that have featured over the years, such as a Salt Dome, Swiss alps "Zermat" and BetBet are given in the knocked down task file format form.

The folded geology example features hinge-lines, axial surfaces etc.

## Geology From Geophysics

The examples here include one to take the Bouguer, terrain corrected gravity grid of Australia, and find the 900 most important crustal faults, and have these importable into GeoModeller, to create a 3D fault network.

The second example is from the Anisotropic clustering tool, being applied to the Landers 3D seismic locations dataset, to find the best fitting 40 flat planes or fault surfaces and have these beconme a starting model in geomodeller.

The Ellipsoid test, is from Roger Clifton's random dipole for magnetic responses, to demonstrate a forward model that a massive ellipsoid body, buried and tilted might exhibit AEM, Airborne ElectroMagnetic support, is also a big part of GeoModeller V4. All of the processing tools for AEM are driven by batch processes, and the first update to use the GOOGLE protobuf interface is still emerging. Like many of the other aspects in the Intrepid/GeoModeller API, AEM has a large set of options and parameters that are needed to capture all the nuances and complexities.

The Bevereley project ( HydroGeology) was modelled for tops of 3 of the formations, from the 2.5D inversion of Tempest data. As this data is public domain, Intrepid can supply the full geophysical datasets plus the inversion, upon request, otherwise, consult GSSA.

## Geology Uncertainty

This follows from the UWA Target work, of modifying the structural foliation data in a GeoModeller project, and by sampling from a VonMies/Fisher distribution, generate a family of equally likely Geological models. The sample here is for Mansfield, Victoria, and has 10 variations all equally likely. The speed is enhanced by removing all 2D observatiuons tied to a section and treating all observations as 3D points.

The other example is from Saudi Arabia, and concerns reservoir simulations for uncertainty in oil recovery opertaions, and how effective a downhole well monitoring scheme might prove, depending upon the design of the monitoring bores, vs the stimulation wells, the thickness of the oil bearing strata, and the sensitivity of the geophysics signal that might be sensed.

## GeoStatistics

Access to the geostatsitics capability inside geomodeller via the batch language is also demostrated with these tasks.

There are two examples of having a variogram calculated.
The first is just from an external geophysics points database. (Point cloud - Landers) The second is for down hole drilling data, but inside a geomodeller project.

Similarly, the Lady Lorreta examples are for grade assay estimations, going from the drill data to the 3D volumes, that are formation based.

Lastly, we also give a Domain Kriging example, where the 3D geology model is used to estiamte the distance between samples, rather than the more traditional Cartesian coordiante distance methods. The trend of the geology, and how it has been deformed and folded, is taken straight from the geology model and used directly in the geostats calculations.
 
## Geotechnical

The examples presented in this directory represent preliminary geological investigation work done, when the choice of a tunnel transit is under investigation.

The example is loosly based upon a realistic scenario around Paris. Project extent is around 4.2 * 1.6 km. The engineering geology observations are reduced to a bare minimum, to still enable an approximation of realistic workflows. The project is geolocated to the NTF projected co-ordinate reference system, and the ERMapper format DTM grid is at 10 metre cell size.

The shallow tunnel, is to proceed through many faulted compartment blocks, and the predicted geology that the tunnel is to go through, can be easily perturbed for uncertainty. The tunnel transit can also easily be changed. Typically, a tunnel design can be given to GeoModeller project, via a dxf file, and the meshing is redone in GeoModeller, to make sure all the geological important transitions are honoured in the DXF meshing, that can then be recovered and viewed in the CAD design tool.

In this case, there are many faulted zones, with varying throws. To successfully create a 3D geology model each fault compartment must have at least one set of observations of the contigous pile units. The 40+ short boreholes give this control.

Workflow steps:
		
	a. Build the 3D geology model from its raw observations and the pile - Run "TunnelExample_France.task"
	b. Open the newly built 3D model in geomodeller - verify the boreholes were all used to build the model.
	c. Inspect the long section, note the series of fault throws.
	d. Import a design dxf file as a mesh grid.
	e. Add the geology to this mesh  grid
	f. export the meshGrid to a DXF, now with the newly added lithology field, and the re-triangulaed mesh walls.

## GeoThermal

The examples come from South Australia, and concern estimating the thernal gradients and temepratures, given a 3D model with the thermal properties.
 
## HydroGeology

New to V4, is the formal support for CGAL meshing, leading to the ability to produce manifold and water-tight physical admissable meshing. This means simulation software such as MODFLOW and FEFLOW can take GeoModeller geology models and have structured layered and unstructured tetrahedral meshes that reflect best efforts at creating a satifactory 3D geology model and not just the topography. We retain infinetly thin fault planes as our way of showing the conformal mesh for any number of cross-cutting fault or hydraulic barriers.
 
The examples include the original Robin DuFour Swiss Alpes model (Zermat).
From the North Flinders Ranges, South Australia, we have a regional thin body Beverley model. So 30 * 30km, but just 500m thick. 6 formations, with pinch-outs are part of this together with a few faults, picked from the AEM, and the GSSA interpretation.

We also recycle Tutorial A for demostration of meshing. The outputs sub-director shows samples of coarely meshed versions of these models. The *.vtu version can be viewed in the free viewer PARAVIEW, and has  fully attributed fields including geology gradient estimates.
 
## Meshing

The link between implicit co-krigging modelling of geology and 3D meshes is shown here for more generic example situations. The Mansfield model is used to create a mesh, a simple Dyke intrusion and a simple 3 formation, with a cutting fault etc. Importing older technology meshes into a GeoModeller environment (MeshGrid) is also featured (Petrel).

## Mining

The links between geology, geostatistics, and mining engineering are many and varied.

An example that represent preliminary geological investigation work when another mining package is also being used in conjunction for planning stope shapes and development work.

A second example from bulk mining, is based upon the Brockman Syncline, Western Australia. The region where a huge amount of Iron Ore mining occurs.  Very simple methods are shown to demostrate how easy it is to create a regional setting for the geology, then add the detail of faults and further geology refienments. We give some rock properties, that are derived from back analysis of the observed geophysics. Determining the geology from AEM 2.5D inversion, can also be tied into parts of this region.
 
## Seismic Passive

The geothermal projects often involve the observation of FRACCING, or other passive seismic event records

There are a couple of tasks to show how to bring these datasets into the GeoModeller MeshGrid structures, within your project.

## Seismic Reflective

Some preliminary setup for the Capel Faust cross-over from marine 2D seismic acquisition, integrated with co-incident marine gravity. The aim was to create a frontier basin identification and analysis method and to also study the Law of the Sea implcations for remote continetal shelf studies.

## Rock Properties

The often neglected job of working on ways to best estimate bulk physical properties for your formations is shown by some workflow examples for gravity and magnetics. This is also described in the GeoModeller reference manual, via the GUI workflows. But here we have task files that do the same job, so enabling easier repeatable testing, as the models might be changed.

## Stochastic Inversion

From the original 2007 development work, by Richard Lane, we present the BetBet study from central Victoria. The whole process encompasses taking your best effort 3D geology model, and then using both Gravty and magnetic data to drive constrained stochastic inversion processes and genertate millions of equally likely but with small differences. The method for generating Histogram Stats, Movies and Liklihood plots are also captured in the task files.
 
## Tasks

An audit trail (including potential return values) is written to "geomodeller-batch.audit". And any errors are reported in "geomodeller-batch.rpt". Both files are located in the current working directory. Make sure to check these files since non-fatal errors do not result in a termination of the batch processing.

Quite a lot of the sub-tasks used in GeoModeller uses this message passing scheme so you may spot automatically generated *.task files appearing in your work directories.

(c) 2017 Intrepid Geophysics
