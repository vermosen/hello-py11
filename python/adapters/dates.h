#pragma once
#ifndef HABU_PY_ADAPTERS_DATES_H
#define HABU_PY_ADAPTERS_DATES_H

#include <habu/date.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace pybind11 {
namespace detail {

  template <> 
  class type_caster<std::vector<habu::date>> {
  public:
      typedef std::vector<habu::date> type;

      // defined the value member
      PYBIND11_TYPE_CASTER(type, _("numpy.ndarray"));

      // python -> C++
      bool load(handle src, bool) {

        using namespace habu;

        if (!src) return false;

        // check that the object is indeed a numpy.datetime64
        if (strcmp(src.ptr()->ob_type->tp_name, "numpy.ndarray") == 0) {

          // check that we have the right numpy type
          if (src.attr("dtype").attr("str").cast<std::string>() == "<M8[D]") {
            static auto np = module::import("numpy");
            auto cast_f = np.attr("int64");
            array_t<std::int64_t> raw = src.attr("astype")(cast_f);            
            
            std::vector<habu::date> res;
            auto r = raw.unchecked<1>();
            for (ssize_t i = 0; i < r.shape(0); i++) {
              res.push_back(habu::date(r(i)));
            }

            value = res;
            return true;
          }
        }
      
        return false;
      }

      static handle cast(const std::vector<habu::date> &src, return_value_policy policy, handle /* parent */) {
          
          using namespace habu;

          auto rv = array_t<std::int64_t>(src.size());
          buffer_info buf = rv.request();
          std::int64_t *ptr = static_cast<std::int64_t *>(buf.ptr);

          for (std::size_t i = 0; i < src.size(); i++) {
            ptr[i] = src[i].counter();
          }

          object h = rv.attr("astype")("datetime64[D]");
          h.inc_ref();
          return h;
      }
  };

} // namespace detail
} // namespace pybind11

#endif // HABU_PY_ADAPTERS_DATE_H