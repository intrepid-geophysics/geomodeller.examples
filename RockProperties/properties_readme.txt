Examples of using a 3D geology model - your best effort
and observed gravity and magnetic datasets in grid form, 
to derive the least squares best fit rock properties
that can explain, using your geology model, and the grids,
the observed signals.
The key to this working is that your model must have various linear combinations
of the observed formations, when the model is discretized
into columns. In other words, this algorithm fails for  exact layer-cake scenarios,
so get real, and make your geology model follow what is actually seen in nature.

You have to propose starting property distributions for each formation, 
that have the possibility of being reasonable, for the rocks involved.
The way the method works, is to test the mean and one standard deviation either 
side of the mean, for each formation, forming a linear set of equations to solve.

# (c) 2017 Intrepid Geophysics