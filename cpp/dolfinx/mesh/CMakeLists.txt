set(HEADERS_mesh
  ${CMAKE_CURRENT_SOURCE_DIR}/dolfin_mesh.h
  ${CMAKE_CURRENT_SOURCE_DIR}/GraphBuilder.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.h
  ${CMAKE_CURRENT_SOURCE_DIR}/MeshEntity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Geometry.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Partitioning.h
  ${CMAKE_CURRENT_SOURCE_DIR}/PermutationComputation.h
  ${CMAKE_CURRENT_SOURCE_DIR}/MeshQuality.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Topology.h
  ${CMAKE_CURRENT_SOURCE_DIR}/MeshTags.h
  ${CMAKE_CURRENT_SOURCE_DIR}/TopologyComputation.h
  ${CMAKE_CURRENT_SOURCE_DIR}/cell_types.h
  ${CMAKE_CURRENT_SOURCE_DIR}/utils.h
  PARENT_SCOPE)

target_sources(dolfinx PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/GraphBuilder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Geometry.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Partitioning.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PermutationComputation.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MeshQuality.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Topology.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/TopologyComputation.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/cell_types.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
)
