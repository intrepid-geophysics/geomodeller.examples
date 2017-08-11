GeoModeller gravity and magnetic forward modelling and inversion
Batch Environment Command Reference
	Version:	4.0
	Date:	26 June 2017
Highlights
 - uses the Google Protobuf messaging libraries
 - now part of a whole of system ( Intrepid tools and Geomodeller Geology editing and modelling tools)
 - supports MPI and multi-threading
 Shipping with this release are examples of using this syntax.
 - tasks to create and then add extra steps for all of Tutorial A geology model building
 - simple slab scenario, where stochastic investigations of viable models, driven by geophysical observations
 - the original case study by Richard Lane, of BetBet Victoria, used to implement and validate the whole approach.
 - creating dyke swarms rapidly from automatic aeromagnetic line data, then testing the geometry and response
 of proposed 3D dyke networks with the original observed survey data.

Advatages of this new approach
1, all syntax errors are extensively trapped and reported by the parser, down to line and column number
2, each parameter is named in plainly, and constrained to "Data Type"
3, the full syntax for the language is made freely available with each installed version of the programs
	The language definition , in this case, is in the file "API/invtaskmodel.proto"
4, every example task that is shipped with the software is also part of the testing system for every build on all supported platforms.
5, the language is extensible, without in any way upsetting existing running versions. If there are new commands or messages that are
	not understood by older	versions, they are simply ignored.
6, many discrete parameters can be set, and actions undertaken, in the same session, so that if it makes sense to parallelise
   an operation, the whole context is available to the current session.

Parallelization Progress Report
Some aspects can take advantage of multiple cores ( multi-threading), and multiple computers (nodes) in a cluster.
The most time consuming tasks are "run", and making output movies of the probability results.
Formal specification of extra options to envoke these features are available on request.

STOCHASTIC simulations of 3D geology models
===========================================
All commands/messages are grouped here. Mostly the same keywords and options are used for both ways of running the task.
Also look at the shipping BetBet project for an actual full set of examples.

A. PROTOBUF Syntax:
	When using the protobuf syntax, the commands are in a standard text file. Execution is via a command line tool,
 		invbatch -batch batchfile.task
 	or the Intrepid Project manager, by clicking right on a task file and requesting a run.


The parent directory of the licensed GeoModeller
Installation must be on the path as well as  the server subdirectory (For 64bit Windows)


1. Case and Run management
============================
NewCase (Create a new case from a GeoModeller project)


PROTOBUF EXAMPLE
InversionTask {
	NewCase {
		filename: "InputGeology/CF83/CF83.xml";
		case: "C5";
		z_cell_size: 200;
		elevation_minimum_voxet: -28000;
		elevation_maximum_voxet: 0;

		ObservedGridList {
			ObservedGrid {
				type: Gravimetry;
				mean_elevation: 0;
				precision: 3.0; #  estimated accuracy of marine data
				Match_Trend: true;
				Match_Trend_Degree: 1;
				Match_Trend_Rate: 1;
				grid: "InputGrids/grv_CAP_BA2000_fully_corrected_mgal_3km_UTM57_20081118.ers";
				}
			}
	}
}
......................................................................................................
NewForwardCase (Create a new case for use in Forward modelling)


PROTOBUF EXAMPLE
InversionTask {
	NewForwardCase {
		filename: "KurtCase1/KurtCase1.xml";
		case: "Case_1";
		x_cell_size: 50.;
		y_cell_size: 50.;
		z_cell_size: 50.;
		east_minimum_voxet: -25;
		east_maximum_voxet: 975;
		north_minimum_voxet: -25;
		north_maximum_voxet: 975;
		elevation_minimum_voxet: -475;
		elevation_maximum_voxet: 25;
		mean_elevation: 25;
		product: Temperature;
	}
}
......................................................................................................
CreateCaseFromVoxet (Create a new case from an external voxet for use in Temperature Forward modelling)
	The new case is created with a dummy Observed grid with origins and cellsizes corresponding to that of the X,Y origins and cellsizes of the InputVoxet.
	This new case is intended for temperature forward modelling only.  See ForwardModelTemperatureForCreateCaseFromVoxet.

PROTOBUF EXAMPLE
InversionTask {
	CreateCaseFromLithologyVoxet {
		inputvoxet: "SA_GawCur_15km_4kmXY100mZ_thermal.vo";
		new_project: "SA_GawCur_15km_4kmXY100mZ_thermal_imported\SA_GawCur_15km_4kmXY100mZ_thermal_imported.xml";
		case: "Case_1";
		product: Temperature;
    	formation {
    		field: "Eucla_basin";
    		index: 1;
    		}
    	formation {
    		field: "Lake_eyre_basin";
    		index: 2;
    		}
	}
}
......................................................................................................

CaseControl

	SetLaw <Formation> <PROPERTY> <LAW>
	where LawChangeList = <LawChange1 ... LawChangeN>
	and LawChange = <Formation> <PROPERTY> <LAW>
	where <PROPERTY>=<Density | Susceptibility | Remanence | CommonalityVolume |
	Commonality | ShapeRatio | VolumeRatio | Movable | Index | ThermalConductivity | HeatProductionRate>

	eg. SetLaw F1 Density Normal(2.66,0.1,100)
	eg. SetLaw F1 Density "Normal(2.67,0.01,95) + Normal(3.67,0.01,5)"
	eg. SetLaw F1 Remanence Normal(0.3,0.1,100,45,89) where the inclination is 45 and the declination is 89eg. SetLaw F1 Density �Normal(2.67,0.0001,100,XYZ, F1_Densities.vo,Density)�
		where the field Density in the voxet F1_Densities.vo controls the mean of the distribution at every voxeleg. SetLaw F1 Density �Normal(2.67,0.0001,100,XY, F1_Densities.ers)�
		where the values in the ERMapper grid F1_Densities.ers provide 2D plan view control of the variable mean of the distribution.eg. SetLaw F1 CommonalityVolume LogNormal(0,5)
	where Commonality units are in percentages
	eg. SetLaw F1 Commonality Rayleigh(0.05)
	eg. SetLaw F1 Commonality Weibull(lambda,kappa)
	where lambda (>0) and kappa (>=0) define the PDF for the CommonalityMisfit function
	eg. SetLaw F1 Commonality Weibull(0.3,1.0)
	eg. SetLaw F1 Movable 1 (default 1)where Movable is either 0 (fixed) or 1 (movable)
	eg. SetLaw F1 Index 2
		where Index (2) is the index used in the voxet to represent formation F1
	eg. SetLaw F1 PreserveVerticalRelationship (0,1,1,1,1,1,1,1)
		where 1 means the vertical relationship between F1 and the n th formation is to be preserved
		and the n th formation means the n th formation as determined by age (1 as the youngest)

	The formation given by the "row name" cannot be allowed to occur below any formation that has a 1 in the PreserveVerticalRelationship array.
	A "normal" pile ordering is achieved with ones in the upper triangle (assuming the assignments are given as a sequence from youngest to oldest).
	An �overturned� structure may be maintained with a 1 in the lower triangle. It is not possible to maintain BOTH normal and overturned relationships
	in the same project! A one in both (i,j) and (j,i) means the two formations cannot exist in the same column.

	Example for PreserveVerticalRelationship
	Tertiary_Volcanic_and_Sedimentary_Rocks and Laramide_Unconformity are definitely above the basement series (Eg Chilitos_Formation_Sulphides_A).
	The middle formations prefixed by Chilitos (Chilitos_...) are all above the bottom two (Triassic...) but can have any vertical relationship within their series.


PROTOBUF EXAMPLE

InversionTask {
	CaseControl {
		filename: "InputGeology/CF83/CF83.xml";
		case: "C5";
	#	SetUseTopo: false;
		SetReferenceDensity: 2.00;
		IncludeBorderEffect: true;
		SetAboveTopoDensity: 2.0;
		SetReferenceMagneticField {	Magnitude:	50000;	Inclination: -65.0;	Declination: 25; }
SetLaw {
	LithologyProperty {	lithology: "Air";	property: Movable;	fixed: true;}
	LithologyProperty {	lithology: "Water"; property: Movable;	fixed: true;}
	LithologyProperty {	lithology: "SedUpper";property: Movable;fixed: true;}
	LithologyProperty {	lithology: "SedMiddle";	property: Movable;fixed: true;}
	LithologyProperty {	lithology: "SedLower";property: Movable;fixed: false;}
	LithologyProperty {	lithology: "Basement";property: Movable;fixed: false;}
	LithologyProperty {	lithology: "Mantle";property: Movable;	fixed: false;}

	LithologyProperty {	lithology: "Air";property: Density;	ProbabilityDistributionFunction {type: LogNormal;mean: 2.00;stddev: 0.0001;}}
	LithologyProperty {	lithology: "Water";property: Density;ProbabilityDistributionFunction {type: LogNormal;mean: 2.0;stddev: 0.0001;}}
	LithologyProperty {	lithology: "SedUpper";property: Density;ProbabilityDistributionFunction {type: LogNormal;mean: 1.85;stddev: 0.0001;}}
	LithologyProperty {	lithology: "SedMiddle";property: Density;ProbabilityDistributionFunction {type: LogNormal;mean: 2.13;stddev: 0.0001;}}
	LithologyProperty {lithology: "SedLower";property: Density;ProbabilityDistributionFunction {type: LogNormal;mean: 2.31;stddev: 0.0001;}}
	LithologyProperty {	lithology: "Basement";property: Density;ProbabilityDistributionFunction {type: LogNormal;mean: 2.70;stddev: 0.0001;}}
	LithologyProperty {lithology: "Mantle";property: Density;ProbabilityDistributionFunction {type: LogNormal;mean: 3.10;stddev: 0.0001;}}

	LithologyProperty {lithology: "Air";property: Commonality;ProbabilityDistributionFunction {type: Weibull;mean: 0.001;stddev: 1;}}
	LithologyProperty {lithology: "Water";property: Commonality;ProbabilityDistributionFunction {type: Weibull;mean: 0.001;stddev: 1;}}
	LithologyProperty {lithology: "SedUpper";property: Commonality;ProbabilityDistributionFunction {type: Weibull;mean: 0.001;stddev: 1;}}
	LithologyProperty {lithology: "SedMiddle";property: Commonality;ProbabilityDistributionFunction {type: Weibull;mean: 0.001;stddev: 1;}}
	LithologyProperty {lithology: "SedLower";property: Commonality;ProbabilityDistributionFunction {type: Weibull;mean: 0.001;stddev: 1;}}
	LithologyProperty {lithology: "Basement";property: Commonality;ProbabilityDistributionFunction {type: Weibull;mean: 0.001;stddev: 1;}}
	LithologyProperty {lithology: "Mantle";property: Commonality;ProbabilityDistributionFunction {type: Weibull;mean: 0.001;stddev: 1;}}


	LithologyProperty {lithology: "Air";property: ShapeRatio;ProbabilityDistributionFunction {type: LogNormal;mean: 0.0;stddev: 0.05;}}
	LithologyProperty {lithology: "Water";property: ShapeRatio;ProbabilityDistributionFunction {type: LogNormal;mean: 0.0;stddev: 0.05;}}
	LithologyProperty {lithology: "SedUpper";property: ShapeRatio;ProbabilityDistributionFunction {type: LogNormal;mean: 0.0;stddev: 0.05;}}
	LithologyProperty {lithology: "SedMiddle";property: ShapeRatio;ProbabilityDistributionFunction {type: LogNormal;mean: 0.0;stddev: 0.05;}}
	LithologyProperty {lithology: "SedLower";property: ShapeRatio;ProbabilityDistributionFunction {type: LogNormal;mean: 0.0;stddev: 0.05;}}
	LithologyProperty {lithology: "Basement";property: ShapeRatio;ProbabilityDistributionFunction {type: LogNormal;mean: 0.0;stddev: 0.05;}}
	LithologyProperty {lithology: "Mantle";property: ShapeRatio;ProbabilityDistributionFunction {type: LogNormal;mean: 0.0;stddev: 0.05;}}
			}
	}
}
......................................................................................................

NewRun

PROTOBUF EXAMPLE
InversionTask {
	NewRun {
		filename: "InputGeology/CF83/CF83.xml";
		run: "R1";
		case: "C5";
		NumberOfIterations:	10000;
	}
}

......................................................................................................
RunControl


	Note that the order of acceptance tests is geology first and geophysics second.
	Within geology tests the order is:
	1.	PreserveVerticalRelationship
	2.	Commonality
	3.	CommonalityVolume
	4.	VolumeRatio
	5.	ShapeRatio

	Within geophysics tests the order is the order in which they appear in the NewCase command

PROTOBUF EXAMPLE
InversionTask {
	RunControl {
		filename: "InputGeology/CF83/CF83.xml";
		case: "C5";
		run: "R1";
		NumberOfIterations:	10000;
		LithologyInitialiseStyle: FromVoxet;
		property_voxet: "InputGeology/CF83/C5/R1/modifiable.vo"
		DensityInitialiseStyle: FromLawMean;
		SusceptibilityInitialiseStyle: FromLawMean;
		RemenantMagnetizationInitialiseStyle: FromLawMean;
		PropertyChangeOnFixedCell: true;
		AllowNeighbourPropertyDifferentCheck: false;
		Seed:	1135314798;
		PriorOnly: false;
		ProbabilityOfPropertyChangeOnly: 0;
#		SetLargeMisfitRMSThresholdFactor:	1.0;
#		SetLargeMisfitTemperature:	1.0;
		SetDualTemperatureMode: true
		Mode1TemperatureFactor: 100;
		Mode1Duration: 500;
		Mode2TemperatureFactor: 1;
		Mode2Duration: 4500;
		PreserveTopology: false;
		CommonalityVolumeTest {	SetWeights: LocalAbundance;	}
		CommonalityTest {	SetWeights: none;	}
		ShapeRatioTest {SetWeights:	LocalAbundance;	IncludeAboveTopoFaces: true;IncludeOutsideFaces: true;}
		PreserveVerticalRelationshipTest: true;
		SetOutputMisfits: true;
		SetOutputCommonality: false;
		SetOutputTrendGrids: false;
	}
}

......................................................................................................
SetFixedCells

	If SetFixedCells is never called, the default is to set all the cells of the layer at the highest elevation to fixed.
	When the first call of SetFixedCells is made, this program default is cleared (i.e. equivalent to a call of SetFixedCells CLEAR)
	 and a voxet named <Case>_<Run>_modifiable.vo is established with all values of the �Modifiable� property initialised with 1.
	  All subsequent SetFixedCells calls are additive.

PROTOBUF EXAMPLE
InversionTask {
	SetFixedCells  {
		filename: "InputGeology/CF83/CF83.xml";
		case: "C5";
		run: "R1";
		CLEAR: true;
		SURFACE: true;
	}
}
......................................................................................................


Running Computation
===========================
Run

PROTOBUF EXAMPLE
InversionTask {
	Run {
		filename: "InputGeology/CF83/CF83.xml";
		run: "R1";
		case: "C5";
		Testing: true;
	}
}
......................................................................................................
ForwardModelFromCase

......................................................................................................
ForwardModelFromProject


	The easting will range from EastMIN_VOXET (the western edge of the most western voxels) to EastMIN_VOXET+NEAST*eCELLSIZE (the eastern edge of the most eastern voxels)
		    Where NEAST=Number of voxels in the easting direction such that
	                  EastMIN_VOXET+(NEAST-1)*eCELLSIZE < EastMAX_VOXET and
	                  EastMIN_VOXET+NEAST*eCELLSIZE >= EastMAX_VOXET

	The northing will range from NorthMIN_VOXET (the southern edge of the most southern voxels) to NorthMIN_VOXET+NNORTH*nCELLSIZE (the northern edge of the most northern voxels)
		    Where NNORTH=Number of voxels in the northing direction such that
	                  NorthMIN_VOXET +(NNORTH-1)* nCELLSIZE < NorthMAX_VOXET and
	                  NorthMIN_VOXET + NNORTH * nCELLSIZE >= NorthMAX_VOXET


	Where IGRF=<ReferenceMagneticFieldMagnitude> <ReferenceMagneticFieldInclination> <ReferenceMagneticFieldDeclination>
	in units of nT,decimal degrees, decimal degrees
	Where TEMPERATURECONTROL=<MeanSurfaceTemperature> <Base_Boundary_Style> <Base_Boundary_Value> <Max_Residual_Temperature>
	See ForwardModelTemperatureCreateCaseFromVoxet below for details on TEMPERATURECONTROL


......................................................................................................

ForwardModelFromVoxet

PROTOBUF EXAMPLE
InversionTask {
	ForwardModelFromVoxet {  #  uses vfilt to run, via FFTW, also compatible with the Geomodeller spatial as well
        input_voxet:				"./data/Model-5d_v2a/Case1/run1/initial.vo";
        fields {        			node: "Lithology";   }
        POSC_CoordinateSystem: 		"WGS84/NUTM22";
        drape_elevation_grid:		"./data/Avaanna_GDB_G_Alt_SplineRot61_DC_RotBck.ers";
        output_gridname:			"ComputedFTGGrid.ers"
        PropertyValuesVoxelName:	"./data/outputdensity.vo"
        ExpandedVoxelName:			"./data/expandedPaddedVoxet.vo"
        OutputVoxelName:			"./data/FTG.vo"
        InputVoxetAlreadyProperty: 	false;	#  is the voxet a litho model, or a density model
        LanczosTaper:  				true;
        product:  					GravityTensor;
        coordsys: 					END;
        mean_elevation:				670;		# height to calculate forward model at
        maximum_elevation:			1000;		# continue up the 3D model to accommodate the padding
        IGRF {						Date: "10/11/2006";	}
        method: 					FastFourierTransform;
#BIF1,BIF2,BIF3,BIF4,BIF4b,BIF4c,BIF5,BIF5b,BIF6,BIF6b,BIF6c,BIF6d,BIF7,BIF7b,BIF8,BIF8b,BIF9,BIF9b,BIF10,BIF10b,BIF10c,BIF11,BIF12,BIF13,BIF13b,BIF14,BIF15,BIF16,Geology
        Density  {  # idea here is that each lithology has a corresponding density starts from litho = 0,1,2 etc.
        node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0;
        node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0;
         node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 3.0; node: 2.6; node: 2.6
         }
    }
}
......................................................................................................
ForwardModelTemperatureForCreateCaseFromVoxet
	Forward calculation of temperature from a case created using CreateCaseFromVoxet on <ImportedVoxet>

	
PROTOBUF EXAMPLE
InversionTask {
	ForwardModelTemperatureForCreateCaseFromVoxet {
		filename: "SA_GawCur_15km_4kmXY100mZ_thermal_imported\SA_GawCur_15km_4kmXY100mZ_thermal_imported.xml";
		mycase: "Case_1";
		input_voxet: "SA_GawCur_15km_4kmXY100mZ_thermal.vo";
		field_alias {
			alias: "Lithology";
			field: "Lithology";
		}
		Advanced: true;
		Surface_Temperature_Law {
			type: Log_normal;
			mean: 22;
			stddev: 0;
			percentage: 100;
		}
		Base_Heatflow_Law {
			type: Log_normal;
			mean: 0.036;
			stddev: 0;
			percentage: 100;
		}
		Max_Residual_Temperature: 0.000001;
		NumberOfIterations: 100000;
	}
}
......................................................................................................

ForwardModelFromDykes
No support for this on a command line, except via the mtdyke tool

PROTOBUF EXAMPLE
#  example of tensor dyke response forward modelling
IntrepidTask {
	ForwardModelFromDykes {
		InputDykesName: 	"bifdatadyke_imported..DIR";
		InputField:  		"Susceptibility";
		POSC_CoordinateSystem: 		"AGD84/AUSTRALIAN_MAP_GRID_ZONE_53";
		ComputedGridName:	"teisa_dyketest.ers"
		product: 			MagneticTensors
# 		DrapeSurfaceGridName =
#		OutputPrecision =  IEEE4ByteReal
		OutputGridCoordSysType: END;
		ObservationHeight: 	0.0;
		Grid_Size:         	10.0;
#		Average_Dyke_Length: 140.;
#		Susceptibility 	{  node: 0.01; node: 0.01; };
		IGRF {	Date: "01/01/2005";	};
		method: 			Dyke_Skeletons;
	}
}

Post Run Reporting
===========================
RunState
	syntax: <CaseXML> RunState <RUN> <Iteration> <Existing Output Directory>

	The output voxet will be <Existing Output Directory>\<CASE>_<RUN>_<Iteration>.vo

PROTOBUF EXAMPLE
InversionTask {
	RunState {
		filename: "slab_inversion/InputGeology/slab_vertical_20070420c/slab_vertical_20070420c.xml";
		run: "Run_1";
		number_of_iterations: 70000;
	}
}

Post Run Reporting (Multi Run Interval)
===========================
MakeSummaryStats

	RunIntervalList=<RunIntervalList(1)> ... <RunIntervalList(N)>
	and RunInterval=<RUN> <StartIteration> <EndIteration>

......................................................................................................
MakeSuperSummaryStats
	<Threshold> is the percentage value to use for the MostProbableThresholded output
	where only those voxels for which the MostProbable formation had a probability greater than <Threshold> are retained


PROTOBUF EXAMPLE
InversionTask {
	MakeSuperSummaryStats {
		filename: "InputGeology/CF83/CF83.xml";
		statistical_voxet: "InputGeology/CF83/R1/super_stats.vo";
		RunInterval {
			run: "R1";
			case: "C5";
			start_iterations: 10000000;
			end_iterations: 20000000;
		}
		threshold_percentage: 90;
	}
}
......................................................................................................
MakeEvolutionMovie

	MovieControl=<MaxCols> <MaxRows> <VerticalExaggeration> <FramesPerSecond> <QualityPercentage>
	ScaleOption=<LogOrLinear> <minClip> <maxClip>

	Where
			LogOrLinear=0 for Linear and 1 for Log
			MinClip=minimum value or use minClip=Auto to have the software automatically calculate this
			MaxClip=maximum value or use maxClip=Auto to have the software automatically calculate this
	           EvolutionField=<Lithology | Density | Susceptibility | RemanenceEast | RemanenceNorth | RemanenceDown>
	           ColourStyle = <LithologyColours | Colours | Greyscale>

	AboveTopo cells are shown in red if the ColourStyle is Greyscale and
	in black if the ColourStyle is LithologyColours or Colours.


PROTOBUF EXAMPLE
InversionTask {
	MakeEvolutionMovie  {
		filename: "InputGeology/CF83/CF83.xml";
		RunInterval {
			run: "R1";
			case: "C5";
			start_iterations: 10000000;
			end_iterations: 20000000;
			}
		IterationIncrement: 40000;
		show: Geology;
		MaxPixelCols: 900;
		MaxPixelRows: 900;
		VerticalExaggeration: 3;
		FramesPerSecond: 6;
		QualityPercentage: 100;
		lut: LithologyColours;
		Scaling {
			doLog: false;  # linear
		}
		Section: "302-17";
		movie: "Results/EvolutionMovie_C5_R1_Lithology_302-17_VE3"
	}
}

Run Reporting (Multi Voxet)
===========================
MakeHistogram
	Information on the requested property distributions is read from the definitions in the specified Case.
At this point, a Student's t- test can be perfomed to verify the required Probablity distribution function, as specified, has been honoured
at the end of all the stochastic perturbations for properties etc.

PROTOBUF EXAMPLE
InversionTask {
	MakeHistogram {
		filename: "slab_inversion/InputGeology/slab_vertical_20070420c/slab_vertical_20070420c.xml";
		voxet: "slab_inversion/InputGeology/slab_vertical_20070420c/Case_1/Run_1/initial.vo";
		run: "Run_1";
		lithology_field: "Lithology";
		property_field: "Density";
		number_of_bins: 51;
		Scaling {
			doLog: false;
		}
		report: "Histogram_Density_initial.rpt";
	}
}

Reporting (DerivedVoxet processing)
===========================
MakeSectionImage

PROTOBUF EXAMPLE
InversionTask {
	MakeSectionImage   {
		filename: "InputGeology/CF83/CF83.xml";
		run: "R1";
		case: "C5";
		get_function {
			existing_voxet: "Results/StatsReports/SuperSummaryStats_C5_R1_90_super.vo";
			statistical_field: MeanDensity;
			transform: GetField;
			threshold: 90;
		}
		Section: "302-17";
		MaxPixelCols: 900;
		MaxPixelRows: 900;
		VerticalExaggeration: 3;
		QualityPercentage: 100;
		lut: Colours;
		Scaling {
			doLog: false;  # linear
		}
		image: "Results/SectionImage_C5_R1_VE3_MeanDensity_302-17_VE3"
	}
}
......................................................................................................
MakeAllSectionImages

	Runs MakeSectionImage for all Sections in the project

	GetField(<DerivedVoxet>,<FieldWithinDerivedVoxet>) extracts data for a specified Field from a specified Voxet.
	There must be no spaces within the braces.
	<DerivedVoxet> is any voxet which is derived from the GeoModeller Project
	<FieldWithinDerivedVoxet>) is a Keyword as used in the voxet header file such as Lithology, MostProbable, MostProbableThresholded, MeanDensity, StdDevDensity,
			Probablity0, Probablity1, etc.

......................................................................................................
MakeDerivedVoxet

......................................................................................................
MakeSectionMovie

	LINE_COORDS=<EastingForCentreLineStart> <NorthingForCentreLineStart> <EastingForCentreLineEnd> <NorthingForCentreLineEnd>
	MAX_SECTION_WIDTH=the maximum horizontal length of section, limited by the extent of the project/inversion model

	Sections entirely outside the project extent are omitted from the movie.


Utility Functions
===========================

MakeSurfaceShells (From Single Voxet)
	syntax: MakeSurfaceShells <Input Voxet> <Input Field> <OPERATOR> <ISO VALUE> <OUTPUT_PREFIX>

	OPERATOR is one of EQ, LE, or GE)

......................................................................................................
MakeMovie (From a list of JPG image files)
	syntax: MakeMovie <FramesPerSecond> <MaxCols> <MaxRows> <Input jpg List> <Output MPG>

......................................................................................................
DumpVoxet (From Single Voxet)
	syntax: DumpVoxet <Input Voxet> <Output CSV>
......................................................................................................
CreateDepthFunction
	syntax: <CaseXML> CreateDepthFunction F(d1,v1,�,di,v2i,�) <Output Voxet> <Output Field>

	Where (di,vi) are the points of a spline used to calculate the value of the function at depth.
	The di represents the depth of the ith point and vi represents the value (eg. Density) at the ith point.
	The depth is measured relative to the topographic surface.
......................................................................................................
Horizons

	Where OutputVoxet will contain for each formation the probability that any given cell is the top of that formation.
	Treating each column in the OutputVoxet as a probability distribution for each formation a csv file is created that gives the upper
	and lower depths for the nominated <Threshold> (defaults to 90).
	That is, the depths for which the cumulative probability is (100-<Threshold>)/2 and (100-((100-<Threshold>)/2).
	The names of the csv files will be of the form Prob_<Formation>_bounds.csv
......................................................................................................
StatsVoxet

......................................................................................................
Threshold

	Where <InputStatsVoxet> is an <OutputVoxet> from the StatsVoxet process.
	And where <OutputVoxet> will contain the value <ThresholdValue> if the value at a cell is within the <ConfidenceBounds> of the <ThesholdValue>.
	 For cells below the <ThresholdValue> and outside the confidence bound the value will be zero.
	 For cells above the <ThresholdValue> and outside the confidence bound the value will be 2 times the <ThresholdValue>.
	ConfidenceBounds = a positive number denoting the number of standard deviations of the confidence bounds
	or
	ConfidenceBounds = <ConfidencePercentage>%
	where
	<ConfidencePercentage> = a positive number denoting the confidence bounds as a percentage.



Extra syntax definitions for old style command line syntax, deprecated
===========================================

DerivedVoxet=MostProbableField(<SummaryStats Voxet Prefix>,<Field>,<Threshold>)
                which means: Create a voxet where each cell is assigned as follows:
                             1. Look at the set of voxets beginning with the string with <SummaryStats Voxet Prefix>
                             2. Pick the one with the highest probability >= Threshold
                             3. Lookup the value of <Field> for that voxet at that cell
                             4. This becomes the value of the new voxet at that cell
          or WeightedField(<SummaryStats Voxet Prefix>,<Field>)
                which means: Create a voxet where each cell is assigned as follows:
                             1. Look at the set of voxets beginning with the string with <SummaryStats Voxet Prefix>
                             2. Calculate a weighted average of <Field> based on the probablity
                             3. This becomes the value of the new voxet at that cell
          or MostProbableLithology(<SummaryStats Voxet>,<Threshold>)
                which means: Create a voxet where each cell is assigned as follows:
                             1. Look at the set of voxets beginning with the string with <SummaryStats Voxet Prefix>
                             2. Pick the one with the highest probability >= Threshold
                             3. The lithology index of this picked one becomes the value of the new voxet at that cell
          or GetField(<Input Voxet>,<Field>)
                which means: Create a voxet where each cell is assigned as follows:
                             1. Retrieve the value of <Field> for the <Input Voxet> at that cell
                             2. This becomes the value of the new voxet at that cell

Threshold=Threshold probability as a percentage

Document formatting notes: The document uses the following styles Plain text, Command, Syntax, Command_comment, Command_example.

