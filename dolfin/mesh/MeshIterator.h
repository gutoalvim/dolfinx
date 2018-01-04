
#ifndef __MESH_ITERATOR_H
#define __MESH_ITERATOR_H

#include <memory>
#include <iterator>

#include "Mesh.h"
#include "MeshEntity.h"

namespace dolfin
{
  // Forward declarations
  class Vertex;
  class Edge;
  class Face;
  class Facet;
  class Cell;
  template<typename X> class entities;

  template<class T>
    class MeshIterator : public std::iterator<std::forward_iterator_tag, T>
  {
  public:

    /// Copy constructor
    MeshIterator(const MeshIterator& it) : _entity(it._entity),  _pos(it._pos), _index(it._index)
    {
      std::cout << "EMPTY COPY" << std::endl;
    }

    // Copy assignment
    const MeshIterator& operator= (const MeshIterator& m)
    {
      //std::cout << "ASSIGN" << std::endl;
      _entity = m._entity;
      _pos = m._pos;
      _index = m._index;
      return *this;
    }

    // Constructor with Mesh
    MeshIterator(const Mesh& mesh, std::size_t pos=0)
      : _entity(mesh, 0), _pos(pos), _index(nullptr)
    {
      std::cout << "Mesh constructor" << std::endl;
      // Check if mesh is empty
      //if (mesh.num_vertices() == 0)
      //  return;
    }

    // Constructor with MeshEntity
    MeshIterator(const MeshEntity& e, std::size_t pos=0)
      : _entity(e.mesh(), 0), _pos(pos)
    {
      std::cout << "AAAA" << std::endl;

      // Get connectivity
      const MeshConnectivity& c = e.mesh().topology()(e.dim(), _entity.dim());

      // Compute connectivity if empty
      if (c.empty())
        e.mesh().init(e.dim(), _entity.dim());

      _index = c(e.index());
    }

    MeshIterator& operator++()
    {
      ++_pos;
      return *this;
    }

    bool operator==(const MeshIterator& other) const
    {
      std::cout << "BBBB" << std::endl;
      return (_pos == other._pos and _index == other._index);
    }

    bool operator!=(const MeshIterator& other) const
    {
      //return (_pos != other._pos or _index != other._index);
      return (_pos != other._pos);
    }

    T* operator->()
    {
      std::cout << "CCC" << std::endl;
      _entity._local_index = (_index ? _index[_pos] : _pos);
      return &_entity;
    }

    T& operator*()
    {
      std::cout << "DDDD" << std::endl;
      _entity._local_index = (_index ? _index[_pos] : _pos);
      return _entity;
    }

  private:
    // MeshEntity
    T _entity;

    // Current position
    std::size_t _pos;

    // Mapping from pos to index (if any)
    const unsigned int* _index;

    template <typename X> friend class entities;
  };

  // Class defining begin() and end() methods for a given entity
  template<class T>
    class entities
  {
  public:

  entities(const Mesh& mesh) : _it_begin(mesh, 0), _it_end(mesh, 0)
    {
      const std::size_t dim = _it_begin._entity.dim();
      _it_end = MeshIterator<T>(mesh, mesh.topology().ghost_offset(dim));
    }

  entities(const MeshEntity& e) : _it_begin(e, 0), _it_end(_it_begin)
    {
      const std::size_t dim = _it_begin._entity.dim();
      _it_end._pos = e.num_entities(dim);
    }

    const MeshIterator<T>& begin() const
    { return _it_begin; }

    const MeshIterator<T>& end() const
    { return _it_end; }

  private:
    MeshIterator<T> _it_begin;
    MeshIterator<T> _it_end;
  };

  typedef entities<Cell> cells;
  typedef entities<Facet> facets;
  typedef entities<Face> faces;
  typedef entities<Edge> edges;
  typedef entities<Vertex> vertices;

}

#endif
