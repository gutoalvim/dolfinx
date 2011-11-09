// Copyright (C) 2011  André Massing
//
// This file is part of DOLFIN.
//
// DOLFIN is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DOLFIN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with DOLFIN. If not, see <http://www.gnu.org/licenses/>.
//
// Modified by André Massing, 2011
//
// First added:  2011-10-04
// Last changed: 2011-11-09
//
// Unit test for the IntersectionOperator

#include <dolfin.h>
#include <dolfin/common/unittest.h>

#include <vector>
#include <algorithm>

using namespace dolfin;
using dolfin::uint;


class Intersection3D : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(Intersection3D);
  CPPUNIT_TEST(testCellCellIntersection);
  CPPUNIT_TEST(testCellFacetIntersection);
  CPPUNIT_TEST(testCellEdgeIntersection);
//  CPPUNIT_TEST(testCellVertexIntersection);
  CPPUNIT_TEST_SUITE_END();

public:

  void testCellCellIntersection()
  {
    testEntityEntityIntersection<3,3>();
  }

  void testCellFacetIntersection()
  {
    testEntityEntityIntersection<3,2>();
  }

  void testCellEdgeIntersection()
  {
    testEntityEntityIntersection<3,1>();
  }

  void testCellVertexIntersection()
  {
    testEntityEntityIntersection<3,0>();
  }

  template <uint dim0, uint dim1> 
  void testEntityEntityIntersection()
  {
    cout <<"Run test with dim pair " << dim0 << " " << dim1 << endl;
    uint N = 3;
    UnitCube mesh(N,N,N);
    IntersectionOperator io(mesh,"ExactPredicates");
    
    //Compute incidences
    mesh.init(dim0,dim1);

    // Iterator over all entities and compute self-intersection
    // Should be same as looking up mesh incidences
    // as we use an exact kernel
   
    for (MeshEntityIterator entity(mesh,dim1); !entity.end(); ++entity)
    {
      // Compute intersection
      std::vector<uint> ids_result;
      io.all_intersected_entities(*entity,ids_result);
      cout << "--------------------------------------------------------------------------------" << endl;
      cout <<"Found " << ids_result.size() << " intersections" << endl;
      std::sort(ids_result.begin(),ids_result.end());
//      for (uint i = 0; i < ids_result.size(); ++i)
//        cout << ids_result[i] << " ";

      // Compute intersections via vertices and connectivity
      // information. Two entities of the same only intersect
      // if they share at least one vertex
      std::vector<uint> ids_result_2;
      for (VertexIterator vertex(*entity); !vertex.end(); ++vertex)
      {
	uint num_ent = vertex->num_entities(dim0);
	const uint * entities = vertex->entities(dim0);
	for (uint i = 0; i < num_ent; ++i)
	  ids_result_2.push_back(entities[i]);
      }

      //Sorting and removing duplicates
      std::sort(ids_result_2.begin(),ids_result_2.end());
      std::vector<uint>::iterator it = std::unique(ids_result_2.begin(),ids_result_2.end());
      ids_result_2.resize(it - ids_result_2.begin());
      cout <<"Found " << ids_result_2.size() << " intersections via connectivity" << endl;
      cout <<endl;
      cout << "--------------------------------------------------------------------------------" << endl;

      // Check against mesh incidences
      CPPUNIT_ASSERT(ids_result.size() == ids_result_2.size()); 
      uint last = ids_result.size() - 1;
      CPPUNIT_ASSERT(ids_result[0] == ids_result_2[0]); 
      CPPUNIT_ASSERT(ids_result[last] == ids_result_2[last]); 
    }
  }

};

int main()
{
  // FIXME: The following test breaks in parallel
  if (dolfin::MPI::num_processes() == 1)
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(Intersection3D);
  }

  DOLFIN_TEST;
  
}
