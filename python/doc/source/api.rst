=============
API reference
=============

Python
======

Public user interface
^^^^^^^^^^^^^^^^^^^^^

.. autosummary::
   :toctree: _autogenerated

   dolfinx.common
   dolfinx.fem
   dolfinx.function
   dolfinx.generation
   dolfinx.io
   dolfinx.jit
   dolfinx.la
   dolfinx.mesh
   dolfinx.pkgconfig
   dolfinx.plotting
   dolfinx.legacy


Low-level API
^^^^^^^^^^^^^

dolfinx.common module
--------------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.common

dolfinx.fem modulex
------------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.fem


dolfinx.fem module
-----------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.fem.assemble
   dolfinx.fem.coordinatemapping
   dolfinx.fem.dirichletbc
   dolfinx.fem.dofmap
   dolfinx.fem.formmanipulations
   dolfinx.fem.form
   dolfinx.fem.interpolation
   dolfinx.fem.problem
   dolfinx.fem.solvers
   dolfinx.fem.solving


dolfinx.function module
----------------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.function
   dolfinx.functionspace

dolfinx.generation module
------------------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.generation


dolfinx.io module
----------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.io

dolfinx.jit module
-----------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.jit

dolfinx.la module
----------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.la.solver


dolfinx.mesh module
------------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.mesh


dolfinx.pkgconfig module
-----------------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.pkgconfig

dolfinx.plotting module
----------------------

.. autosummary::
   :toctree: _autogenerated

   dolfinx.plotting


pybind11 wrapped interface
^^^^^^^^^^^^^^^^^^^^^^^^^^

These are interfaces to the C++ component of DOLFIN, and are low-level
and subject to change. They are not intended for application-level
use.

.. autosummary::
   :toctree: _autogenerated

   dolfinx.cpp.common
   dolfinx.cpp.fem
   dolfinx.cpp.function
   dolfinx.cpp.generation
   dolfinx.cpp.geometry
   dolfinx.cpp.graph
   dolfinx.cpp.io
   dolfinx.cpp.log
   dolfinx.cpp.mesh
   dolfinx.cpp.refinement


C++
===

The C++ API is documented `here
<https://fenicsproject.org/docs/dolfinx/dev/cpp/>`_.
