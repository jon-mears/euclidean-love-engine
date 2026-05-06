/*

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
// flag to false. Can have a separate step in which matrices are updated.
// Because drawing order should not be constrained by this characteristic to
// allow for layers and transparency.

// It's clearly reasonable to exclude certain types of transformations from the
// hierarchy, not so resonable to exclude SPECIFIC transformations. Need not
// implement such functionality.

// Should probably allow for the use of Lua at some point.

// Could just use two clean flags instead of having a pointer to a parent and
// an array of children. The second clean flag indicates whether or not the
// parent should be queried for its transformation data that frame.

// Optimization hints: each component can implement custom (optimizing) logic
// if a static analysis reveals that particular methods are never used. Should
// have a fine-grained option to disallow optimization.

// Should investigate how Unity handles certain things.

// For the transformation should have a way to save parent transformations
// with frequently updating children.For example, a translation is the highest
// ancestor but translation changes the most often. Ideally, given a scheme
// like this:
// [Static x13 matrices] * [Dynamic x1 matrix] * [Static x21 matrices]
// We'd be able to perform just three multiplications:
// [Cached product of x13 static matrices] * [Dynamic x1 matrix] *
// [Cached product of x21 static matrices].

This would require the use of another flag which marks whether the descendant
matrix is clean or not. So there will be mPMatrix, mLMatrix, mCMatrix,
mPClean, mLClean, mCClean.

Could have some sort of model matrix manager with a view of the matrices that
must be updated. To generalize it can just be a matrix multiplication manager
that can view an arbitrary sequence of matrix multiplications and only update
the matrices that need to be updated and subsequently only perform the matrix
multiplications that need to be performed. For example, its view at the end of
a frame could be:
[-------xxx---------x-x--------],
where - is clean and x is dirty. In such a case, 5 local matrix updates and 9
matrix multiplications are all that must occur. But with flat traversal, 5
local matrix updates (again) occur and _23_ matrix multiplications occur
(on account of needing to perform all the multiplications in sequence starting
between the first x and the preceding -).

Each matrix multiplication manager would need to have a Result() method to
obtain the final result. But each matrix in the sequence has a LocalResult,
LeftResult, and RightResult method.

[-------xx------+-------x-----]

Let's say LeftResult is called on +. There is a LeftHeap and a RightHeap. The
LeftHeap is ordered such that the leftmost dirty operation is on top, and so
on. The LeftHeap is peeked. If it is to the left of +, then its local result is
computed and subsequently its left result is computed. And the process
continues. It's easy to see how this process occurs too on the right side.

This does not work too well because it only really makes sense to store the
complete left result and complete right result at a given point. This basically
requires that each point has a left result of length n and a right result of
length m.

The LeftHeap and RightHeap are members of the CachedOperationManager.

Ideally, there'd be options to use or omit this feature. Or a list of matrices
which actually update can be included in an optimization hint. Might be
hyper-optimization for the time being.

Something like this is still technically possible, it'd just require O(n^2)
memory.

Could probably be further generalized to be a CachedOperation. Yes,
CachedOperation is an appealing generalization.

There's still a way this can be done but multiple clean flags would need to be
used.

[----x---------]

1: CAN OBTAIN RESULT (0)
[---------------] Local
[0123456789abcde] Left [0 is local]
[edcba9876543210] Right [0 is right]

2: Dirty Matrix (0)
[-------x-------] Local
[0123456x0000000] Left [0 is local]
[0000000x6543210] Right [0 is local]

3: Compute matrix, left matrix, and right matrix (3)
[---------------] Local
[012345670000000] Left [0 is local]
[000000076543210] Right [0 is local]

4: Clean everything up (2)
[---------------] Local
[01234567000000e] Left [0 is local]
[e00000076543210] Right [0 is local]
*/