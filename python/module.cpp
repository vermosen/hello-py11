#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include "adapters/dates.h"
#include "adapters/date.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: scikit_build_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("date_to_int", [](const habu::date& dt) {
        return dt.counter();
    });

    m.def("int_to_date", [](int ctr) {
        return habu::date(ctr);
    });

    m.def("dates_to_ints", [](const std::vector<habu::date>& dates) {
        std::vector<std::int64_t> rv;
        for (auto& d : dates) {
            rv.push_back(d.counter());
        }
        return rv;
    });

    m.def("ints_to_dates", [](const std::vector<std::int64_t>& ctrs) {
        std::vector<habu::date> rv;
        for (auto& i : ctrs) {
            rv.push_back(habu::date(i));
        }
        return rv;
    });

    m.def("int_to_date_uni", [](int ctr) -> habu::date {
        return habu::date(ctr);
    });

    m.def("int_to_date_uni", [](const std::vector<int>& ctrs) -> std::vector<habu::date> {
        std::vector<habu::date> rv;
        for (auto& i : ctrs) {
            rv.push_back(habu::date(i));
        }
        return rv;
    });

    //m.def("numpy")

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
