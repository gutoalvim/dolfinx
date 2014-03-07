"""Unit tests for MultiMesh Integration"""

# Copyright (C) 2014 Anders Logg and August Johansson
#
# This file is part of DOLFIN.
#
# DOLFIN is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# DOLFIN is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with DOLFIN. If not, see <http://www.gnu.org/licenses/>.
#
# First added:  2014-03-04
# Last changed: 2014-03-07

import unittest
import numpy

from dolfin import *


def triangulation_to_mesh_2d(triangulation):
    editor = MeshEditor()
    mesh = Mesh()
    editor.open(mesh, 2, 2)
    num_cells = len(triangulation) / 6
    num_vertices = len(triangulation) / 2
    editor.init_cells(num_cells)
    editor.init_vertices(num_vertices)
    for i in xrange(num_cells):
        editor.add_cell(i, 3*i, 3*i + 1, 3*i + 2)
    for i in xrange(num_vertices):
        editor.add_vertex(i, triangulation[2*i], triangulation[2*i + 1])
    editor.close()
    return mesh

class TriangleIntegrationTest(unittest.TestCase):

    def test_integrate(self):

        if MPI.size(mpi_comm_world()) > 1: return

        # Create two meshes of the unit square
        mesh_0 = UnitSquareMesh(10, 10)
        mesh_1 = UnitSquareMesh(11, 11)
        mesh_1.translate(Point(0.632350,0.278498))


        multimesh = MultiMesh()
        multimesh.add(mesh_0)
        multimesh.add(mesh_1)
        multimesh.build()

        print multimesh.num_parts()



        V_0 = FunctionSpace(mesh_0, "CG", 1)
        V_1 = FunctionSpace(mesh_1, "CG", 1)

        V_multi = MultiMeshFunctionSpace()
        V_multi.add(V_0)
        V_multi.add(V_1)

        u = MultiMeshFunction(V_multi)
        u.vector()[:] = 1.



        # # Translate second mesh randomly
        # #dx = Point(numpy.random.rand(),numpy.random.rand())
        # dx = Point(0.278498, 0.546881)
        # mesh_1.translate(dx)

        # exactvolume = (1 - abs(dx[0]))*(1 - abs(dx[1]))

        # # Compute triangulation volume using the quadrature rules
        # volume = 0
        # for c0 in cells(mesh_0):
        #     for c1 in cells(mesh_1):
        #         triangulation = c0.triangulate_intersection(c1)
        #         if (triangulation.size>0):
        #             # compute_quadrature_rule(triangulation,
        #             #                         2,2,1)
        #             compute_quadrature_rule(c0,1)

        #             tmesh = triangulation_to_mesh_2d(triangulation)
        #             for t in cells(tmesh):
        #                 volume += t.volume()



        # errorstring = "translation=" + str(dx[0]) + str(" ") + str(dx[1])
        # self.assertAlmostEqual(volume, exactvolume,7,errorstring)



if __name__ == "__main__":
        unittest.main()

