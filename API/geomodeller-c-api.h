/// @file geomodeller-c-api.h
/// @group GeomodellerAPI Geomodeller API
/// @{
///  the user's programmable application interface specification for GEOMODELLER
///  this is designed for simple, standard programs created by the users to
/// create and or modify 3d geology models via programming.
///
///  shipped library is
///        geomodellerapi.dll
///
/// see also the GOOGLE/Protobuf interface
///
/// note,  you must have a valid license for Geomodeller to gain access to most function in this API

#ifndef dfa_geomodeller_c_api
#define dfa_geomodeller_c_api
#ifdef   WIN32
#ifndef  PUBLISH
#define  PUBLISH  __declspec(dllexport)
#endif
#else
#ifndef PUBLISH
#define PUBLISH
#endif
#endif
#ifndef NULL
#define NULL 0
#endif
extern "C" {


/// @struct GMAPI_Polyline2d
/// Structure to hold a poly line points, the iso value and the formation name when
/// methods return the rendered model as poly lines on sections.
struct PUBLISH GMAPI_Polyline2d {
	double *m_X; ///< Array of X coordinates for each point
	double *m_Y; ///< Array of Y coordinates for each point
	int m_NumPnts; ///< Number of points (number of elements in the X and Y arrays)
	char *m_Name; ///< Name of this poly line. @note Limited to 256 characters
	double m_IsoValue; ///< Iso-value for this poly line. THis will be the Formation iso value.
};
/// @struct GMAPI_ArrayOfPolylines2d
/// Holds an array of GMAPI_Polyline2d objects and the number of elements in the array
/// via the call to ReleasePolyline2dArray()
struct PUBLISH GMAPI_ArrayOfPolylines2d {
	struct GMAPI_Polyline2d *m_Lines; ///< Array of poly lines
	int m_NumLines; ///< Number of elements in the array.
};

enum GMAPI_FileType3D
{
    GMAPI_TSURF = 0,
    GMAPI_VULCAN = 1,
    GMAPI_IGES = 2,
    GMAPI_STEP = 3,

    GMAPI_DXF12 = 4,
    GMAPI_DXF13 = 5,
    GMAPI_VTP = 6,
    GMAPI_STL = 7,
    GMAPI_VTU = 8,  // unstructured mesh, VTK
	GMAPI_FEFLOW = 9,  // gmod file
	GMAPI_MEDIT = 10,
	GMAPI_C3T3 = 11,
    GMAPI_NUM_3D_TYPES = 12,
    GMAPI_MAX_3D_TYPE_INDEX = 7,

};

enum GMAPI_MeshType
{
    GMAPI_SURFACE = 0,
    GMAPI_SHELL = 1,
    GMAPI_VOLUME = 2  // tetrahedra for instance
};

// ####
/// Release a polyline array and the XY point arrays held in a GMAPI_ArrayOfPolylines2d object.
///
/// @param  Reference to the GMAPI_ArrayOfPolylines2d object
PUBLISH void gmapi_releaseArrayOfPolylines2d(GMAPI_ArrayOfPolylines2d &theArray);


// ####
/// Given a GMAPI_ArrayOfPolylines2d object, allocate the specified number of polyline2d
/// elements and initialise to empty lines.
///
/// @param  array       Reference to the array object to fill.
/// @param  nElem       Number of lines to allocate (default = 0)
PUBLISH void gmapi_allocateArrayOfPolylines2d(GMAPI_ArrayOfPolylines2d &theArray, int nElem = 1);

// ####
/// Initialise the read API.
///
/// @return 0 on success
/// @return -1 if no read license found
PUBLISH int gmapi_initialiseReadAPI();

// ####
/// Initialise the write API.
/// The license manager requires command line args (argc, argv and envp)
/// This version of the write initialise routines uses default
/// args.
/// @return 0 on success

PUBLISH int gmapi_initialiseWriteAPINoArgs();

// ####
/// Initialise the write API.
///
/// @param  argc            Number of the command line arguments
/// @param  argv            Command line arguments.
/// @param  envp            Current environment variables.
/// @return 0 on success

PUBLISH int gmapi_initialiseWriteAPI(int argc, char **argv, char **envp);

// ####
/// Create a new GeoModeller project
/// @param theName          Name of the project
/// @param xmin             X minimum of the extents
/// @param ymin             Y minimum of the extents
/// @param zmin             Z minimum of the extents
/// @param xmax             X maximum of the extents
/// @param ymax             Y maximum of the extents
/// @param zmax             Z maximum of the extents
/// @param thePrecision     Precision for the model [default = "1.0"]
/// @param theAuthor        Name of the author [default = ""]
/// @param theDate          Date string of the form DD/MM/YYYY [default = TODAY]
/// @param theDesc          Project description string [default = ""]
/// @param theProjection    Projection string of the form: "NTF / LambertIIet" [default = "Raw/Raw"]
/// @param theVersion       Version of the project [default = "1.0"]
/// @param lengthUnit       Length unit string (m or ft) [default = "M"]
/// @param deflection2d     Deflection 2d [default=0.001]
/// @param deflection3d     Deflection 3d [default=0.001]
/// @param discretisation   Discretisation level for the project [GUI default = 10.0]
/// @param dynamicSelection Dynamic selection is on or off [default = false]
/// @return 0 on success, -1 on error
PUBLISH int gmapi_createProject(const char *theName, double aXmin, double aYmin,
		double aZmin, double aXmax, double aYmax, double aZmax,
		double aPrecision = 1.0, const char *theAuthor = NULL,
		const char *theDate = NULL, const char *theDesc = NULL,
		const char *theProjection = NULL, const char *theVersion = NULL,
		const char *theLengthUnit = NULL, double aDeflexion2d = 0.001,
		double aDeflexion3d = 0.001, double aDiscretisation = 10.0);
// ####
/// Opens a Geomodeller project to operate on.
///
/// @param  geomodellerXML      Geomodeller project file.
/// @return 0 on success
/// @return -1 if no read license found
/// @return -2 on error
PUBLISH int gmapi_openProject(const char *geomodellerXML);

// ####
/// Opens a Geomodeller project without a GUI to operate on.
///
/// @param  geomodellerXML      Geomodeller project file.
/// @return 0 on success
/// @return -1 if no read license found
/// @return -2 on error
PUBLISH int gmapi_openProjectWithoutDisplay(const char *geomodellerXML);

// ####
/// Return the current model bounds in the reference parameters.
///
/// @param  xmin        [OUT] Minimum X extents of the project
/// @param  ymin        [OUT] Minimum Y extents of the project
/// @param  zmin        [OUT] Minimum Z extents of the project
/// @param  xmax        [OUT] Maximum X extents of the project
/// @param  ymax        [OUT] Maximum Y extents of the project
/// @param  zmax        [OUT] Maximum Z extents of the project
/// @return 0 on success
/// @return -1 if no read license found
PUBLISH int gmapi_getModelBounds(double &xmin, double &ymin, double &zmin,
		double &xmax, double &ymax, double &zmax);
// ####
/// Set the model extents.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  xmin         Minimum X extents of the project
/// @param  ymin         Minimum Y extents of the project
/// @param  zmin         Minimum Z extents of the project
/// @param  xmax         Maximum X extents of the project
/// @param  ymax         Maximum Y extents of the project
/// @param  zmax         Maximum Z extents of the project
/// @return 0 on success
PUBLISH int gmapi_setModelBounds(double xmin, double ymin, double zmin, double xmax,
		double ymax, double zmax);
// ####
/// Returns the computed lithology index at the given XYZ in the output reference
/// parameter.
///
/// @param	x, y, z		XYZ coordinates to return the computed lithology
/// @return 0 on success
/// @return -1 if read license is not initialised.
PUBLISH int gmapi_getComputedLithologyXYZ(double x, double y, double z,
		int &lithologyIndex);
// ####
/// Returns the computed gradient of the iso potential function at the given XYZ in the output reference
/// parameter.
///
/// @param	x, y, z		XYZ coordinates to return the computed lithology
/// @return 0 on success
/// @return -1 if no read license found
PUBLISH int gmapi_getComputedGradientXYZ(double x, double y, double z,
		double &xgradient, double &ygradient, double &zgradient);
// ####
/// Returns the computed gradients of the iso potential function of all the faults in the fault network at the given
/// XYZ in the output reference
/// parameter.
///
/// @param	x, y, z		XYZ coordinates to return the computed lithology
/// @param	max_faults		length of xgradients,ygradients,zgradients array
/// @return 0 on success
/// @return -1 if no read license found
PUBLISH int gmapi_getComputedGradientForFaultXYZ(double x, double y, double z,
		int max_faults, double *xgradient, double *ygradient,
		double *zgradient);

// ####
/// Save the current project using the existing project folder.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @return 0 on success
PUBLISH int gmapi_saveProject();
// ####
/// Save the current project using the given path to the XML and project files.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param	pathtoxml		Folder to write the project to.
/// @return	0 on success
PUBLISH int gmapi_saveProjectAs(const char *geomodellerXML);
// ####
/// Creates a formation or a fault with the given parameters
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param	isFormation		Flag indicating if this is a formation or a fault
///							(fault if 0, formation otherwise)
/// @param	dataName		Name for the formation or fault.
/// @param	red				Red component of the RGB formation/fault colour (0 <= R <= 1.0)
/// @param 	green			Green component of the RGB formation/fault colour (0 <= G <= 1.0)
/// @param 	blue 			Blue component of the RGB formation/fault colour (0 <= B <= 1.0)
/// @return 0 on success
PUBLISH int gmapi_createFormationOrFault(int isFormation, const char *dataName,
		double red, double green, double blue, double thickness = 0.0);
// ####
/// Creates a dyke with the given parameters
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param	dataName		Name for the formation or fault.
/// @param	red				Red component of the RGB formation/fault colour (0 <= R <= 1.0)
/// @param 	green			Green component of the RGB formation/fault colour (0 <= G <= 1.0)
/// @param 	blue 			Blue component of the RGB formation/fault colour (0 <= B <= 1.0)
/// @return 0 on success
PUBLISH int gmapi_createDyke(const char *dataName, double red, double green,
		double blue);
// ####
/// Delete the formation with the specified name.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param	dataName		Name of the formation to delete.
/// @return	0 on success.
PUBLISH int gmapi_deleteAFormation(const char *dataName);
// ####
/// Delete the fault with the given name.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param	dataName		Name of the fault to delete.
/// @return	0 on success
PUBLISH int gmapi_deleteAFault(const char *dataName);
// ####
/// Delete the dyke with the given name.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param	dataName		Name of the fault to delete.
/// @return	0 on success
PUBLISH int gmapi_deleteADyke(const char *dataName);
// ####
/// Set the series at the given position in the pile and its relation which can
/// be one of:\n
/// <pre>
/// 0, default    - Any\n
/// 1             - Onlap\n
/// 2             - Erode\n
/// 3             - Channel\n
/// 4             - Intrusion\n
/// </pre>
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param	aName		Name of the series to set
/// @param	aPosition	Position (index) in the pile to set the series
/// @param	aRelation	Relationship for the series.
/// @return	0 on success
PUBLISH int gmapi_setSeriesAtPosition(const char *aName, int aPosition,
		int aRelation);
// ####
/// Add a formation to the given series
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param	nameOfSeries		Name of the series to add the formation to
/// @param	nameOfFormation		Name of the formation being added to the series
/// @return	0 on success
PUBLISH int gmapi_addFormationToSeries(const char *nameOfSeries,
		const char *nameOfFormation);
// ####
/// Clear the 3D point trace list.
///
/// The geomodeller API uses  a trace of points
/// which is added to with calls to <tt>createPoint3dOfTrace(x, y, z)</tt>. This list is
/// then used by all functions which require an array of points such as
/// <tt>CreateSectionWithPoints()</tt>
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @return	0 on success
PUBLISH int gmapi_cleanPoint3dOfTrace();
// ####
/// Add a 3D point to the trace list.
///
/// The geomodeller API uses  a trace of points
/// which is added to with calls to <tt>createPoint3dOfTrace(x, y, z)</tt>. This list is
/// then used by all functions which require an array of points such as
/// <tt>CreateSectionWithPoints()</tt>
///

///
/// @param	aX, aY, aZ		3D X, Y, Z coordinates
/// @return 0 on success
PUBLISH int gmapi_createPoint3dOfTrace(double aX, double aY, double aZ);
// ####
/// Create a section with points from the 3D trace clipped to the given X, Y, Z bounds. The
/// orientation of the section is defined by the degrees, direction and dip parameters.
/// @note This function uses the list of 3D trace points as set by calls to <tt>createPoint3dOfTrace(x, y, z)</tt>
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param	aName				Name of the section
///	@param	Xmin, Ymin, Zmin	Minimum of the section rectangle
///	@parma	Xmax, Ymax, Zmax	Maximum of the section rectangle
/// @param	Degrees        Angle of the section rectangle
/// @param	Direction			Direction of the section
/// @param	Dip					Dip for the section
/// @return	0 on success
PUBLISH int gmapi_createSectionWithPoints(const char *aName, double aXmin,
		double aYmin, double aZmin, double aXmax, double aYmax, double aZmax,
		int aDegrees, double aDirection, double aDip);
// ####
/// Create a section with points from the 3D trace clipped to the project extents. The
/// orientation of the section is defined by the degrees, direction and dip parameters.
/// @note This function uses the list of 3D trace points as set by calls to <tt>createPoint3dOfTrace(x, y, z)</tt>
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param	aName				Name of the section
/// @param	Degrees        Angle of the section rectangle
/// @param	Direction			Direction of the section
/// @param	Dip					Dip for the section
/// @return	0 on success
PUBLISH int gmapi_createOrientedSectionWithPoints(const char *aName, int aDegrees, double aDirection, double aDip);
// ####
/// Clear the 2D trace array
///
/// The geomodeller API uses a trace of points
/// which is added to with calls to <tt>createPoint2dOfTrace(x, y, z)</tt>. This list is
/// then used by all functions which require an array of points such as
/// <tt>addInterfaceToSection(...)</tt>
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @return	0 on success
PUBLISH int gmapi_cleanPoint2dOfTrace();
// ####
/// Add a 2D point to the trace list.
///
/// The geomodeller API uses  a trace of points
/// which is added to with calls to <tt>createPoint2dOfTrace(x, y, z)</tt>. This list is
/// then used by all functions which require an array of points such as
/// <tt>addInterfaceToSection(...)</tt>
///
///
/// @param	aX, aY, aZ		3D X, Y, Z coordinates
/// @return 0 on success
int createPoint2dOfTrace(double aU, double aV);

// ####
/// Add an interface which splits the top and bottom formations to the given section.
/// The interface will be orthogonal to the section.
/// @note This will use the list of 2d trace points set via <tt>addPoint2dOfTrace(u, v)</tt>
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  aSectionName            Name of the section
/// @param  aTopFormationName       Name of the top formation
/// @param  aBottomFormationName    Name of the bottom formation
/// @return 0 on success
PUBLISH int gmapi_addInterfaceToSection(const char *aSectionName, const char *aTopFormationName, const char *aBottomFormationName);
// ####
/// Add an orthogonal interface to a section specifying the polarity.
/// @note This will use the list of 2d trace points set via <tt>addPoint2dOfTrace(u, v)</tt>
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  aSectionName            Name of the section
/// @param  aTopFormationName       Name of the top formation
/// @param  aBottomFormationName    Name of the bottom formation
/// @param  aPolarity               Polarity of the assoicated intersection
/// @param  aLocation               Location of the intersection.
/// @return 0 on success
PUBLISH int gmapi_addInterfaceToSectionWithPolarity(const char *aSectionName,
		const char *aTopFormationName, const char *aBottomFormationName,
		int aPolarity, int aLocation);
// ####
/// Add an interface to a section with polarity and location as well as an associated orientation.
/// @note This will use the list of 2d trace points set via <tt>addPoint2dOfTrace(u, v)</tt>
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  aSectionName            Name of the section
/// @param  aTopFormationName       Name of the top formation
/// @param  aBottomFormationName    Name of the bottom formation
/// @param  anAzimuth               Azimuth of the interface
/// @param  aDip                    Dip of the interface
/// @param  aPolarity               Polarity of the interface
/// @param  aLocation               Location of the interface
/// @return 0 on success
PUBLISH int gmapi_addOrientedInterfaceToSection(const char *aSectionName,
		const char *aTopFormationName, const char *aBottomFormationName,
		double anAzimuth, double aDip, int aPolarity, int aLocation);
// ####
/// Add a foliation to a section
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  aSectionName        Name of the section
/// @param  aFormationName      Name of the formation
/// @param  aobsID      Name of the formation
/// @param  aU, aV              U, V coordinates of the foliation point
/// @param  aDirection          Dip direction for the foliatoin
/// @param  Dip                 Dip of the foliation
/// @param  Polarity            Polarity for the foliation. (0=Normal, 1=Reversed)
/// @param  Provenance           Provenance for the foliation.
/// @return
PUBLISH int gmapi_addFoliationToSection(const char *aSectionName,
		const char *aFormationName, const char *aObsID, double aU, double aV,
		double aDirection, double aDip, int aPolarity, int aProvenance);
// ####
/// Add an apparent dip to a section. It is not possible to compute
/// the model when only apparent dip data is present. At least
/// one full foliation point must also be specified for each formation.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  aSectionName        Name of the section
/// @param  aFormationName      Name of the formation
/// @param  aobsID      Name of the formation
/// @param  aU, aV              U, V coordinates of the foliation point
/// @param  aDirection          Dip direction for the foliatoin
/// @param  Dip                 Dip of the foliation
/// @param  Provenance           Provenance for the foliation.
/// @return
PUBLISH int gmapi_addApparentDipToSection(const char *aSectionName,
		const char *aFormationName, const char *aObsID, double aU, double aV,
		double aDip, int aProvenance);
//####
/// Add a 3D interface point to a formation.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param aFormationName		Name of the formation to add the 3D contact point.
/// @param X, Y, Z				Coordinates of the 3D contact.
PUBLISH int gmapi_add3dInterface(const char *aFormationName, double X, double Y,
		double Z);
//####
/// Add a 3D interface point to a formation.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param aFormationName		Name of the formation to add the 3D contact point.
/// @param X, Y, Z				Coordinates of the 3D foliation.
/// @param direction			Direction of the foliation
/// @param dip					Dip of the foliation
/// @param Polarity				Polarity of the foliation
PUBLISH int gmapi_add3dFoliation(const char *aFormationName, double X, double Y,
		double Z, double aDirection, double aDip, int aPolarity);
// ####
/// Add a series to the model.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  aName       Name of the series to add, "all" for all the series in the model
/// @return 0 on success
PUBLISH int gmapi_addSeriesToModel(const char *aName);
// ####
/// Add a fault to the model
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  aName       Name of the fault to add, "all" for all the faults in the model
/// @return 0 on success
PUBLISH int gmapi_addFaultToModel(const char *aName);
// ####
/// Add a section to the model
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  aName       Name of the section to add, "all" for all the sections ins the model
/// @return 0 on success
PUBLISH int gmapi_addSectionToModel(const char *aName);
PUBLISH int gmapi_addBoreholeToModel(const char *aName);

// ####
/// Compute the model with logging of activity
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @return 0 on success
PUBLISH int gmapi_computeThisModelLogged();
// ####
/// Clear the model settings
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @return 0 on success
PUBLISH int gmapi_clearThisModel();
// ####
/// Compute the model
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @return 0 on success
PUBLISH int gmapi_computeThisModel();
// ####
/// Compute the model with a given radius
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  aRadius
/// @return 0 on success
PUBLISH int gmapi_computeThisModelWithRadius(double aRadius);
// ####
/// Compute the model using the given bounds and radius
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  xmin, ymin, zmin        Minimum of the bounds when computing the model
/// @param  xmax, ymax, zmax        maximum of the bounds when computing the model
/// @param  radius                  Radius of the compute
/// @return 0 on success
PUBLISH int gmapi_computeThisModelBoundedWithRadius(double aXmin, double aYmin, double aZmin,
		double aXmax, double aYmax, double aZmax, double aRadius);

/// Import a seismic survey given the input file, format, project file (created
/// or opened) and processing parameters.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  inpFile         Input filename
/// @param  prjFile         Project filename (either new or existing)
/// @param  isNewPrj        Flag indicating the project file should be loaded or created
/// @param  xCol            X data column index (1 relative)
/// @param  yCol            Y data column index (1 relative)
/// @param  zCol            Z data column index (1 relative)
/// @param  thinThresh      Thinning threshold used to reduce the number of seismic points
/// @param  intRadius       Radius around an intersection defining which points are included in calculating a
// best-fit plane for the dip and dip-direction
/// @param  splineDegree    Degree of spline to use for the sections (redundant almost.)
/// @param  colNames        Sequence of strings for the column names
/// @param  colStart        Sequence of integers for the column start index (1 relative)
/// @param  colEnd          Sequence of integers for the column end index (1 relative)
/// @return 0 on success -1 otherwise
PUBLISH int gmapi_importSeismicHorizons(const char *infile, const char *ddf,
		const char *prjFile, const int newPrj, const int xCol, const int yCol,
		const int zCol, double thinThresh, double intRadius,
		const int splineDegree);

/// load a standard 3 table implementation of a borehole database
/// collar Alias field must have 5 entries for the column names coresponding too "ID", "X", "Y", "Z", "LENGTH"
/// survey Alias field must have 4 entries for the column names coresponding too "ID", "DIP", "BEARING", "DOWN_HOLE_DISTANCE"
/// geology/lithology Alias field must have 4 entries for the column names coresponding too "ID", "FROM", "TO", "LITHOLOGY_CODE"
/// lithology code in this API must already correspond to what is being used inside your session ie you must already have created
/// the entry, if not, the interval is ignored
///
/// @note Requires a valid Geomodeller API license with write privileges
PUBLISH int gmapi_loadDrillholes(double precision, const char *collarFile,
		const char *surveyFile, const char *geologyFile,
		const char **collarAliases, const char **surveyAliases,
		const char **geologyAliases, const int invertDips = false,
		const int scanOnly = false);

/// Build a DTM from a File. Can be used to bring a new surface into your model eg bathymetry.
/// Forces the bounds and dimensions before building the surface.
/// @param  aFileName         Input filename
/// @param  aName         new section name
/// @param aXmin, aXmax		X min/max of the bounding box
/// @param aYmin, aYmax		Y min/max of the bounding box
/// @param aNx, aNy			Grid dimensions for sampling the DTM
/// @param   zConversionFactor scale factor for changing the values in the file
PUBLISH int gmapi_buildADTM(const char *aName, const char * aFileName,
		const double zConversionFactor, const double aXmin, const double aXmax,
		const double aYmin, const double aYmax, const int aNx, const int aNy,
		const int useMeanForNull = true, const double nullCellValue = 0.0);
// ####
/// Map UV coordinates to a XYZ point in cartesian space.
/// @note This function uses the currently active section as set by setActiveSection().
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  u, v        U, V coordinate pair.
/// @param  x, y, z     X, Y, Z reference parameters to hold the return values.
/// @return 0 on success, -1 if no projection section set.
PUBLISH int gmapi_uvToPoint(const char *secName, double U, double V, double x,
		double y, double z);
// ####
/// Map a XYZ cartesian point to UV space using the currently active section as set
/// in SetActiveSection(). This will return the U and V coordinates as well as the
/// nearest surface point on the section in surfX, surfY and surfZ.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  X           X coordinate
/// @param  Y           Y coordinate
/// @param  Z           Z coordinate
/// @param  surfX       Surface X coordinate
/// @param  surfY       Surface Y coordinate
/// @param  surfZ       Surface Z coordinate
/// @return 0 on success
PUBLISH int gmapi_pointToUV(const char *secName, double X, double Y, double Z,
		double &surfX, double &surfY, double &surfZ, double &U, double &V);

///  create a user friendly, easy way to get the Lithology voxet
/// you must have already done a compute model
/// creates a gocad style voxet with a Lithology field
PUBLISH int gmapi_SaveLithologyVoxet(const int nx, const int ny, const int nz,
		const char* output_suffix);
///  create a user friendly, easy way to get the iso potentials in a  voxet
/// you must have already done a compute model
/// creates a gocad style voxet with a Potential field
PUBLISH int gmapi_SavePotentialVoxet(const int nx, const int ny, const int nz,
		const char* output_suffix);
///  create a user friendly, easy way to get the iso potential gradient in a  voxet
/// you must have already done a compute model
/// creates a gocad style voxet with a Potential gradient field
PUBLISH int gmapi_SaveGradientVoxet(const int nx, const int ny, const int nz,
		const char* output_suffix, const int OneVoxet_Lithology, const int rank);
// ####
/// Build the 3D formations and fault shapes with default parameters
///
/// @note Requires a valid Geomodeller API license with write privileges
PUBLISH void gmapi_renderModelOnV3D();

// ####
/// Build the 3D formations and fault shapes using the given parameter
/// settings
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  nx, ny, nz      Resolution for the marching cubes grid in metres per cube
///                         or the number of cubes in XYZ (depends on the grid flag parameter)
/// @param  grid            Flag indicating if the nx, ny, nz parameters specify
///                         the size of each grid or the number of grids along each axis
/// @param  surface         Flag indicating if the renderer should produce surfaces or
///                         volumes
/// @param  topoLimited     Flag indicating if the render should be clipped at the topography.
/// @param  adaptTopo       Flag indicating if the render should adapt to the topography
/// @param  adaptX          Flag indicating if the render should adapt X
/// @param  adaptY          Flag indicating if the render should adapt X
/// @param  adaptZ          Flag indicating if the render should adapt X
/// @param  lookForOverturned   Flag indicating if the renderer should check for and
///                             handle overturned geology.
/// @param  NumberOfSmoothIter  Number of smoothing iterations to perform
/// @param  CreateShapes    Flag indicating if shapes should be produced for 3D display
///
/// @param  restart         Flag indicating if the render should restart from a set of TSurfs
PUBLISH void gmapi_renderModelOnV3DControlled(const int nx, const int ny,
		const int nz, const int grid, const int surface, const int volume,
		const int topoLimited, const int adaptTopo, const int adaptX,
		const int adaptY, const int adaptZ, const int lookForOverturned,
		const int NumberOfSmoothIter /*= *0*/, const int CreateShapes/*=*1*/,
		const int restart);

// LOOK INTO REPLACING THE HANDLES WITH SOMETHING MORE STANDARD...POSSIBLY HAVE FUNCTIONS TO SET
// THE CURRENT PROJECT/SECTION/WHATEVER BY NAME OR INDEX THEN A FUNCTION REQUIRING A HANDLE WILL OPERATE
// ON THE CURRENTLY SET OBJECT.
//
// For example: SetProject(const char* sName);              Sets the current Projet_Projet
// RenderModelOnSectionAsFilled(int uNb, int vNb);          Operates on the projcet set in SetProject(sName).

// ####
/// Render the model on the section as a filled polygon.
/// @note STUB
///
/// @note Requires a valid Geomodeller API license with write privileges
PUBLISH void gmapi_renderModelOnSectionAsFilled(int uNb, int vNb);
// ####
/// Returns the number of rendered formation boundaries for the section with the
/// specified index.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  secIndex        Index of the section to check the formation boundaries on.
/// @return Number of rendered formation boundaries on the given section.
PUBLISH int gmapi_getRenderedFormationBoundaryCount(int sectionIndex);
// ####
/// Returns the number of rendered formation polygon objects for the section with the
/// given index.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  secIndex        Index of the section to get the formation count from
/// @return Number of rendered formation polygon object for the given section.
PUBLISH int gmapi_getRenderedFormationPolygonCount(int sectionIndex);
// ####
/// Returns the number of rendered potential field contours objects for the section with the
/// given index.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  secIndex        Index of the section to get the formation count from
/// @return Number of rendered formation polygon object for the given section.
PUBLISH int gmapi_getRenderedPotentialContoursCount(int sectionIndex);
// ####
/// Retrieves the poly lines for a section at a specified boundary and fills a
/// GMAPI_ArrayOfPolylines2d structure. The caller is required to release the memory
/// allocated via a call to releaseArrayOfPolylines2d().
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  secIndex        Section index
/// @param  bndryIndex      Boundary index
/// @param  array           Reference to a GMAPI_ArrayOfPolylines2d structure to fill
///                         with polylines
PUBLISH void gmapi_getRenderedFormationBoundaryAt(int iSecIndex, int iBndryIndex,
		GMAPI_ArrayOfPolylines2d &polyLines);
// ####
/// Retrieves the rendered formation polygon for the specified section and polygon index.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  secIndex        Section index
/// @param  polyIndex       Polygon index
/// @param  array           Reference to a GMAPI_ArrayOfPolylines2d structure to fill
///                         with polylines
PUBLISH void gmapi_getRenderedFormationPolygonAt(int sectionIndex, int polygonIndex,
		GMAPI_ArrayOfPolylines2d &polyLines);
// ####
/// Retrieves the rendered potential contours for the given section at the specified
/// contours index.
///
/// @note Requires a valid Geomodeller API license with write privileges
///
/// @param  secIndex        Section index
/// @param  cntrsIndex      Contours index
/// @param  array           Reference to a GMAPI_ArrayOfPolylines2d structure to fill
///                         with polylines
PUBLISH void gmapi_getRenderedPotentialContoursAt(int sectionIndex, int contoursIndex,
		GMAPI_ArrayOfPolylines2d &polyLines);


// ####
/// Dump the potential field model information to stdout with an optional message header.
///
/// @note Requires a valid Geomodeller API license with write privileges
PUBLISH void gmapi_dumpModel(const char *message = NULL, const char *outfile = NULL);
// ####
/// Dump a summary of the project to stdout.
///
/// @note Requires a valid Geomodeller API license with write privileges
PUBLISH void gmapi_getSummary(const char *outfile = NULL);
// ####
/// Set the random seed
///
/// @note Requires a valid Geomodeller API license.
///
/// @param  mySeed      New seed for the random number generator.
PUBLISH void gmapi_setSeed(int mySeed);
// ####
/// Get the version string and copy into the given char* array. The array must
/// be large enough to hold the string, the length of which can be obtained with
/// GetVersionStringTextLength()
///
/// @note Requires a valid Geomodeller API license.
///
/// @param  ver     Array to hold the version string.
PUBLISH void gmapi_getVersionString(char *ver);
// ####
/// Get the length of the version string as required by a call to GetVersionString()
///
/// @note Requires a valid Geomodeller API license.
///
/// @return Length of the version string
PUBLISH int gmapi_getVersionStringTextLength();
// ####
/// Return the version number and store in the given char* array. The array must
/// be large enough to hold the string, the length of which can be obtained via a call
/// to GetVersionNumberTextLength()
///
/// @note Requires a valid Geomodeller API license.
///
/// @param  verNum      Array to store the version number
PUBLISH void gmapi_getVersionNumber(char *verNum);
// ####
/// Get the length of the version number string as required by a call to GetVersionNumber()
///
/// @note Requires a valid Geomodeller API license.
///
/// @return Length of the version number string.
PUBLISH int gmapi_getVersionNumberTextLength();
// ####
/// Get the build number for the geomodeller
///
/// @note Requires a valid Geomodeller API license.
///
/// @param  ver     Array to hold the build number
PUBLISH void gmapi_getBuildNumber(char *result);
// ####
/// Get the length of the build date string as required by a call to GetBuildDate()
///
/// @note Requires a valid Geomodeller API license.
///
/// @return Length of the build number string
PUBLISH int gmapi_getBuildNumberTextLength();
// ####
/// Get the build date and return in the given array. The array must be large enough
/// to hold the date string, the length of which can be obtained by calling GetBuildDateTextLength()
///
/// @note Requires a valid Geomodeller API license.
///
/// @param  date        String to hold the build date
PUBLISH void gmapi_getBuildDate(char *str);
// ####
/// Get the length of the build date string as required by a call to GetBuildDate()
///
/// @note Requires a valid Geomodeller API license.
///
/// @return Length of the build date string
PUBLISH int gmapi_getBuildDateTextLength();
// ####
/// Export a section to a file.
///
/// @note Requires a valid Geomodeller API license.
///
/// @param  secName     Name of the section to export
/// @param  fileName    Name of the output file.
PUBLISH void gmapi_exportSection(const char *inputSection, const char *outfile);
// ####
/// Import a section into the project  from a file.
///
/// @note Requires a valid Geomodeller API license.
///
/// @param  secName     Name of the section to import
/// @param  inFile      Name of the input file.
PUBLISH void gmapi_importSection(const char *inputSection, const char *infile);


// ####
/// export a 3D shape to a directory. No ZIP support, just separate files
/// @param outdir       Directory to store the files
/// @param unitName     Name of the unit to export.
/// @param type         FileType for the 3D product files.
/// @return 0 on success, -1 otherwise.
PUBLISH int gmapi_export3DShape(const char* outdir,const char* unitName, GMAPI_MeshType mt, GMAPI_FileType3D type);
// ####
/// export 3D shapes to a directory. No ZIP support, just separate files
/// @param outdir       Directory to store the files
/// @param type         FileType for the 3D product files.
/// @return 0 on success, -1 otherwise.
PUBLISH int gmapi_export3DShapes(const char* outdir, GMAPI_MeshType mt, GMAPI_FileType3D type);

//####
/// Build the mesh products as volume shells, surfaces or both. This will also
/// create a tetrahedral mesh of the project units and save it in the project directory.
/// @param topoLimited      Flag indicating whether to clip the shapes at the topography. 0 = NO clip, 1 = clip
/// @param borderLine       Flag indicating if the border triple lines are used when preserving sharp features. 
/// 0 = NO border line, 1 = border line 
/// @param insideLine       Flag indicating is interior (non-border) triple lines are used when preserving sharp features. 
/// 0 = NO inside line, 1 = inside line
/// @param angle            Minimum angle of the surface facets
/// @param size             Maximum facet radii size
/// @param tol              Precision defining the allowable error between facet surfaces and the implicit model.
/// @param ratio            Max. ratio between tetrahedron circumradius and shortest edge of the tet.
/// @param tetsize          Maximum tetrahedron size
/// @param ballradius       Size of the protecting sphere to preserve sharp features such as triple lines
/// @param minSizeTri       Minimum radii of the surface facets.
/// @param formations       Flag indicating if formation meshes are built. 0 = NO formations, 1 = formations
/// @param faults           Flag indicating if fault meshes are built. 0 = NO faults, 1 = faults
/// @param volumes          Flag indicating if volume shells meshes are built. 0 = NO volumes, 1 = volumes
/// @param surfaces         Flag indicating if surface meshes are built. 0 = NO surfaces, 1 = surfaces.
/// @param draw             Flag indicating if products should be rendered once created. Forced to 0 when no display.
///                         0 = NO draw, 1 = draw
/// @return 0 on success, -1 otherwise.
/*PUBLISH int gmapi_build3DShapes(int topoLimited, 
                                    int borderLine, 
                                    int insideLine, 
                                    double angle, 
                                    double size, 
                                    double tol, 
                                    double ratio, 
                                    double tetsize, 
                                    double ballradius, 
									double precisionfactor,
                                    double minSizeTri, 
                                    int formations,
                                    int faults,
                                    int volumes,
                                    int surfaces,
                                    int tetrahedrons,
                                    int draw);
*/
//####
/// Build the 3D shapes using CGAL and export to the directory exportDir.
/// A tetrahedral mesh is also saved using the .mesh format.
///
/// Shapes are saved in VTK poly data format, *.VTP files. The unit they belong
/// to is denoted by the filename
/// @param exportDir       Directory to save exported shapes.
/// @param topoLimited      Flag indicating whether to clip the shapes at the topography. 0 = NO clip, 1 = clip
/// @param borderLine       Flag indicating if the border triple lines are used when preserving sharp features. 
/// 0 = NO border line, 1 = border line 
/// @param insideLine       Flag indicating is interior (non-border) triple lines are used when preserving sharp features. 
/// 0 = NO inside line, 1 = inside line
/// @param borderPoint       Flag indicating if the border triple points are used when preserving sharp features. 
/// 0 = NO border point, 1 = border point 
/// @param insidePoint       Flag indicating is interior (non-border) triple points are used when preserving sharp features. 
/// 0 = NO inside point, 1 = inside point
/// @param smooth           Apply Taubin smoothing on the vertices.
/// @param angle            Minimum angle of the surface facets
/// @param size             Maximum facet radii size
/// @param tol              Precision defining the allowable error between facet surfaces and the implicit model.
/// @param ratio            Max. ratio between tetrahedron circumradius and shortest edge of the tet.
/// @param tetsize          Maximum tetrahedron size
/// @param ballradius       Size of the protecting sphere to preserve sharp features such as triple lines
/// @param minSizeTri       Minimum radii of the surface facets.
/// @param formations       Flag indicating if formation meshes are built. 0 = NO formations, 1 = formations
/// @param faults           Flag indicating if fault meshes are built. 0 = NO faults, 1 = faults
/// @param volumes          Flag indicating if volume shells meshes are built. 0 = NO volumes, 1 = volumes
/// @param surfaces         Flag indicating if surface meshes are built. 0 = NO surfaces, 1 = surfaces.
/// @param draw             Flag indicating if products should be rendered once created. Forced to 0 when no display.
///                         0 = NO draw, 1 = draw
/// @param tetrahedrons      Flag indicating if tetrahedrons are to be generated - vital for unstriuctured mesh
/// @param exportTripleLines Flag indicating if dump a copy of the triple line polylines ( can be VTK format)
/// @param useExistingTripleLines Flag indicating to skip the triple line calc, and resue an existing set

/// @return 0 on success, -1 otherwise.
// now use protbuf directly, not this method
/*
PUBLISH int gmapi_buildAndExport3DShapes(
				    const char* tagname,
				    const char* exportDir,
				    const char* tripleLineFileName,
                                    int topoLimited, 
                                    int borderLine, 
                                    int insideLine, 
                                    int borderPoint, 
                                    int insidePoint, 
                                    double smooth,
                                    double angle, 
                                    double size, 
                                    double tol, 
                                    double ratio, 
                                    double tetsize, 
                                    double ballradius, 
									double precisionfactor,
                                    double minSizeTri, 
                                    int formations,
                                    int faults,
                                    int volumes,
                                    int surfaces,
                                    int draw,
                                    int tetrahedrons,
                                    int exportTripleLines,
									int useExistingTripleLines);
*/
//####
/// Generate a report on the mesh quality given a VTK mesh file. 
/// Only VTP files are currently supported, others return an error.
/// @param inmeshfile       Input VTP mesh file to assess
/// @param outreportfile    Output report file
/// @param sharp_angle_threshold    Threshold to use for defining what is a sharp angle between two facets.
///                                 A value of -1.0 means ignore sharp angles. (default=-1.0)
/// @param facet_angle_minT         Minimum facet angle threshold
/// @param facet_angle_maxT         Maximum facet angle threshold
/// @param facet_size_minT          Minimum facet size threshold
/// @param facet_size_maxT          Maximum facet size threshold
/// @param write_vtp_files         Flag indicating VTP output files should be written for visualising the results.
/// @param vtp_dir                  Directory to write VTP files.
/// @param report_vertices          Flag indicating vertices should be validated
/// @param report_edges             Flag indicating edges should be validated and reported
/// @param report_facets            Flag indicating facets should be validated and reported.
/// @return 0 on success, -1 otherwise
PUBLISH int gmapi_generateMeshQualityReport(const char* inmeshfile, 
                                            const char* outreportfile, 
                                            const int report_vertices =1,
                                            const int report_edges = 1,
                                            const int report_facets = 1,
                                            const double sharp_angle_threshold = -1.0, 
                                            const double facet_angle_minT = 9999999999.9, 
                                            const double facet_angle_maxT = -9999999999.9,  
                                            const double facet_size_minT = 9999999999.9,
                                            const double facet_size_maxT = -9999999999.9,
                                            int write_vtp_files = 0,
                                            const char* vtp_dir = NULL);

//PUBLISH void gmapi_getProjectExtents(double &xmin, double &ymin, double &zmin,
//		double &xmax, double &ymax, double &zmax);
//
//PUBLISH void gmapi_setProjectExtents(double xmin, double ymin, double zmin,
//		double xmax, double ymax, double zmax);

// ####
/// Closes a Geomodeller project without a GUI.
///
/// @return 0 on success
/// @return -1 on error
PUBLISH int gmapi_closeProjectWithoutDisplay();
} // END extern "C"
#endif
/// @}
