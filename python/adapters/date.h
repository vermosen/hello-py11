#pragma once
#ifndef HABU_PY_ADAPTERS_DATE_H
#define HABU_PY_ADAPTERS_DATE_H

#include <habu/date.h>
#include <pybind11/pybind11.h>

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

          if (strcmp(src.ptr()->ob_type->tp_name, "numpy.datetime64") == 0) {
              static PyObject* astype_ptr  = module::import("numpy").attr("datetime64").attr("astype").cast<object>().release().ptr();
              static PyObject* dt_type_ptr = module::import("numpy").attr("int64").cast<object>().release().ptr();

              object astype  = reinterpret_borrow<object>(astype_ptr);
              object dt_type = reinterpret_borrow<object>(dt_type_ptr);
              src = astype(src, dt_type);
          }

          value = 0;
          return true;
      }

      // C++ -> python
      static handle cast(const habu::date &src, return_value_policy /* policy */, handle /* parent */) {
          
          using namespace habu;

          return nullptr;
      }
  };

} // namespace detail
} // namespace pybind11

#endif // HABU_PY_ADAPTERS_DATE_H