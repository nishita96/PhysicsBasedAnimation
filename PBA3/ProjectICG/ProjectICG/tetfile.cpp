#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <fstream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Polyhedron::HalfedgeDS HalfedgeDS;

class Obj_builder : public CGAL::Modifier_base<HalfedgeDS> {
public:
    Obj_builder(std::istream& node, std::istream& ele)
        : m_node(node), m_ele(ele), m_vertex_index(0) {}

    void operator()(HalfedgeDS& hds) {
        typedef typename HalfedgeDS::Vertex Vertex;
        typedef typename Vertex::Point Point;

        CGAL::Polyhedron_incremental_builder_3<HalfedgeDS> builder(hds, true);
        builder.begin_surface(0, 0, 0);

        // read vertices
        int num_vertices;
        m_node >> num_vertices;
        for (int i = 0; i < num_vertices; ++i) {
            double x, y, z;
            m_node >> x >> y >> z;
            builder.add_vertex(Point(x, y, z));
        }

        // read faces
        int num_faces;
        int ignored_attribute;
        m_ele >> num_faces >> ignored_attribute >> ignored_attribute;
        for (int i = 0; i < num_faces; ++i) {
            int face_type;
            int v1, v2, v3;
            m_ele >> face_type >> v1 >> v2 >> v3;
            builder.begin_facet();
            builder.add_vertex_to_facet(v1 - 1);
            builder.add_vertex_to_facet(v2 - 1);
            builder.add_vertex_to_facet(v3 - 1);
            builder.end_facet();
        }

        builder.end_surface();
    }

private:
    std::istream& m_node;
    std::istream& m_ele;
    int m_vertex_index;
};

int main()
{
    // Open the input files
    std::ifstream node_file("example.node");
    std::ifstream ele_file("example.ele");

    // Create an output stream for the OBJ file
    std::ofstream obj_file("example.obj");

    // Build the polyhedron
    Polyhedron polyhedron;
    Obj_builder obj_builder(node_file, ele_file);
    polyhedron.delegate(obj_builder);

    // Write the polyhedron to the output stream in OBJ format
    obj_file << polyhedron;

    // Close the input and output files
    node_file.close();
    ele_file.close();
    obj_file.close();

    return 0;
}
