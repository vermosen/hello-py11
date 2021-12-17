#pragma once
#ifndef HABU_PY_ADAPTERS_DATE_H
#define HABU_PY_ADAPTERS_DATE_H

#include <habu/date.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace pybind11 {
namespace detail {

  template <> 
  class type_caster<habu::date> {
  public:
      typedef habu::date type;

      // defined the value member
      PYBIND11_TYPE_CASTER(type, _("numpy.datetime64"));

      // python -> C++
      bool load(handle src, bool) {

        using namespace habu;

        if (!src) return false;

        // check that the object is indeed a numpy.datetime64
        if (strcmp(src.ptr()->ob_type->tp_name, "numpy.datetime64") == 0) {

          // check that we have the right numpy type
          if (src.attr("dtype").attr("str").cast<std::string>() == "<M8[D]") {
            static auto np = module::import("numpy");
            auto cast_f = np.attr("int64");
            auto raw = src.attr("astype")(cast_f).cast<std::int64_t>();            
            value = habu::date(raw);
            return true;
          }
        }
      
        return false;
      }

      // C++ -> python
      static handle cast(const habu::date &src, return_value_policy /* policy */, handle /* parent */) {
          
          // see https://github.com/pybind/pybind11/issues/1288
          using namespace habu;

          static auto np = module::import("numpy");
          auto raw_f = np.attr("int64");
          auto raw = raw_f(src.counter());
          auto retval = raw.attr("astype")("datetime64[D]");
          return retval;

          //return PyLong_FromLong(src.counter());
      }
  };

} // namespace detail
} // namespace pybind11

#endif // HABU_PY_ADAPTERS_DATE_H