#include "Symbol.h"

// 不要让Symbol.h中也引用这个头文件
#include "Frontend_util.h"

std::shared_ptr<Type> Sym_label::get_type() const
{
    Frontend_util::report_internal_error("试图对Sym_label获取值类型.");
    return std::shared_ptr<Type>();
}