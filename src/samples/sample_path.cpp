#include <rapidxml_ns/rapidxml_ns.hpp>
#include <svgpp/policy/xml/rapidxml_ns.hpp>
#include <svgpp/svgpp.hpp>

using namespace svgpp;

typedef rapidxml_ns::xml_node<> const * xml_element_t;

class Context
{
public:
  void path_move_to(double x, double y, tag::coordinate::absolute)
  {
  }

  void path_line_to(double x, double y, tag::coordinate::absolute)
  {
  }

  void path_cubic_bezier_to(
    double x1, double y1,
    double x2, double y2,
    double x, double y,
    tag::coordinate::absolute)
  {
  }

  void path_quadratic_bezier_to(
    double x1, double y1,
    double x, double y,
    tag::coordinate::absolute)
  {
  }

  void path_elliptical_arc_to(
    double rx, double ry, double x_axis_rotation,
    bool large_arc_flag, bool sweep_flag,
    double x, double y,
    tag::coordinate::absolute)
  {
  }

  void path_close_subpath()
  {
  }

  void path_exit()
  {
  }

  void on_enter_element(tag::element::any)
  {}

  void on_exit_element()
  {}
};

void loadSvg(xml_element_t xml_root_element)
{
  typedef
    boost::mpl::insert<
      boost::mpl::insert<
        traits::shape_elements,
        tag::element::svg
      >::type,
      tag::element::g
    >::type processed_elements_t;

  Context context;
  document_traversal<
    processed_elements<processed_elements_t>,
    processed_attributes<traits::shapes_attributes_by_element>
  >::load_document(xml_root_element, context);
}

int main()
{
  char text[] = "<svg/>";
  rapidxml_ns::xml_document<> doc;    // character type defaults to char
  try
  {
    doc.parse<0>(text);  
    if (rapidxml_ns::xml_node<> * svg_element = doc.first_node("svg"))
    {
      loadSvg(svg_element);
    }
  }
  catch (std::exception const & e)
  {
    std::cerr << "Error loading SVG: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
