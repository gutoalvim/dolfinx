"""This demo solves the Stokes equations, using quadratic elements for
the velocity and first degree elements for the pressure (Taylor-Hood
elements). The sub domains for the different boundary conditions
used in this simulation are computed by the demo program in
src/demo/mesh/subdomains."""

__author__ = "Kristian B. Oelgaard (k.b.oelgaard@tudelft.nl)"
__date__ = "2007-11-16 -- 2008-12-05"
__copyright__ = "Copyright (C) 2007 Kristian B. Oelgaard"
__license__  = "GNU LGPL Version 2.1"

# Modified by Anders Logg, 2008.

from dolfin import *

# Load mesh and subdomains
mesh = Mesh("../../../../../data/meshes/dolfin-2.xml.gz")
sub_domains = MeshFunction("uint", mesh, "../subdomains.xml.gz")

# Define function spaces
V = VectorFunctionSpace(mesh, "CG", 2)
Q = FunctionSpace(mesh, "CG", 1)
W = V + Q

# No-slip boundary condition for velocity
noslip = Constant(mesh, (0, 0))
bc0 = DirichletBC(W.sub(0), noslip, sub_domains, 0)

# Inflow boundary condition for velocity
inflow = Function(V, ("-sin(x[1]*pi)", "0.0"))
bc1 = DirichletBC(W.sub(0), inflow, sub_domains, 1)

# Boundary condition for pressure at outflow
zero = Constant(mesh, 0.0)
bc2 = DirichletBC(W.sub(1), zero, sub_domains, 2)

# Collect boundary conditions
bcs = [bc0, bc1, bc2]

# Define variational problem
(v, q) = TestFunctions(W)
(u, p) = TrialFunctions(W)
f = Constant(mesh, (0, 0, 0))
a = (dot(grad(v), grad(u)) - div(v)*p + q*div(u))*dx
L = dot(v, f)*dx

# Compute solution
problem = VariationalProblem(a, L, bcs)
(u, p) = problem.solve().split()

# Save solution in VTK format
ufile_pvd = File("velocity.pvd")
ufile_pvd << u
pfile_pvd = File("pressure.pvd")
pfile_pvd << p

# Plot solution
plot(u)
plot(p)
interactive()
