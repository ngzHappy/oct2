#if !defined(__OCV__OPENCV__EXCEPTION__)
#define __OCV__OPENCV__EXCEPTION__

#include "core_utility_global.hpp"
#include <memory>
#include <utility>
#include <string>
#include <cstddef>
#include <cstdint>
#include <opencv2/opencv.hpp>

#define opencv_line() __LINE__
#define opencv_file() __FILE__
#define opencv_func() __func__

namespace cv {
class Exception;
}

namespace opencv_exception {

typedef void (*ErrorCallBackFunction)(
        const cv::Exception &,
        const std::string &,
        std::size_t,
        const char *,
        const char *,
        std::shared_ptr<const void>);

CORE_UTILITYSHARED_EXPORT std::pair<ErrorCallBackFunction,std::shared_ptr<const void>> set_error_function(ErrorCallBackFunction,std::shared_ptr<const void>/**/=nullptr);
CORE_UTILITYSHARED_EXPORT std::pair<ErrorCallBackFunction,std::shared_ptr<const void>> get_error_function();
inline std::pair<ErrorCallBackFunction,std::shared_ptr<const void>> set_error_function(const std::pair<ErrorCallBackFunction,std::shared_ptr<const void>> & d){
    return set_error_function(d.first,d.second);
}
CORE_UTILITYSHARED_EXPORT void error(
        const cv::Exception &,
        const std::string & /*_what*/,
        std::size_t /*_Line*/,
        const char * /*_File*/,
        const char * /*_Func*/
        );

}


#endif
