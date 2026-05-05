// It's clear that maintaining spaces within transform components is
// inefficient because instead of first constructing the spaces (by applying
// transformations to the standard basis) and then applying the resulting
// change-of-basis matrix to the input, you can just treat the input like it's
// a vertex and just transform it like normal (except [perhaps] the computation
// occurs on the CPU). This circumvents the application of the transformation
// to the standard basis, which can be expensive. But still, the computations
// used in the change-of-basis code are minimal for how generic the
// code is.

// Instead of the kinda weird Axis code I could just use 4x4 matrices and a
// homogeneous coordinate (1 for points, 0 for vectors, like usual).

// Current idea is to maybe use buffer feedback to save the status of the
// standard basis vectors under the action of the transformation? But I don't
// yet know fully how buffer feedback works.

// Could further generalize Space to allow for curvilinear spaces. Could maybe
// somehow recapture spherical/cylindrical coordinates using Spaces?

// Should create a separate menu for setting space. Can have one space (in
// which case all positions/rotations/scales are relative to that space).

// You can't really express a rotation or a scaling of a POINT wrt an arbitrary
// space, but you CAN for ANOTHER space. There's no scaling or rotation
// inherent to a singular point. So a rotation or a scaling of a space wrt to
// another space is the rotation or the scaling needed to get from the source
// space to the destination space.

// It does actually kinda make sense to include scalings in transformation
// gizmos, although it isn't conventional. Should include an option for it.
// (It IS significant that some vectors have greater magnitude in the resulting
// basis.)

// Main thing I'm interested in implementing are transformation components that
// only include certain transformation types. This way ALL transformations that
// occur are encoded as parents. This allows for things like shears and other
// such transformations in the future, for some objects NOT to be subject to
// some types of transformations, and for orders to be changed around.

// Would ideally design more robust logic for determining if a matrix is clean
// or not. Right now I'm just assuming each matrix needs to be recomputed each
// frame. Just need to ensure that each transformation is evaluated in order
// from top to bottom. Each Set* method will set the matrix_clean flag to false.
// Then, when going through each of the matrices from top-to-bottom, if the
// matrix is not clean, it will set the children transformations matrix_clean
// flag to false.

// It's clearly reasonable to exclude certain types of transformations from the
// hierarchy, not so resonable to exclude SPECIFIC transformations. Need not
// implement such functionality.